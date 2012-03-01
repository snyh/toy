#include <ft2build.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include FT_FREETYPE_H
#include <stdio.h>
#include <iconv.h>
#include <glib.h>

guint *load_ucode (gchar *data);
gchar *u8_2_u2 (const gchar *in);
gint write_bitmap (FILE *f_out, guint ucode, gint psize, gchar *font_face);
void useage ();



int main (int argc, char **argv){
    guint *ucode = NULL;
    gchar *buf = NULL;
    gchar *font = "./font/wqy.tty";
    gchar f_size = 16;
    gchar *input = NULL, *output = "./output";
    FILE *f_out;

    // parse argument -------------------------------------
    gchar *l_opt_arg = NULL;
    gchar opt;
    static const gchar *shortopts = "s:f:i:o:h";
    struct option longopts[] = {
          {"size", required_argument, NULL, 's'},
          {"font", required_argument, NULL, 'f'},
          {"input", no_argument, NULL, 'i'},
          {"output", no_argument, NULL, 'o'},
          {"help", no_argument, NULL, 'h'},
          {0, 0, 0, 0},
    };
    while ((opt = getopt_long (argc, argv, shortopts, longopts, NULL)) != -1) {
        switch (opt) {
          case 's':
            f_size = strtol (optarg, NULL, 10);
            if (!f_size)
              g_printf ("error size\n"), exit(1);
            break;
          case 'f':
            font = strdup (optarg);
            break;
          case 'i':
            input = strdup (optarg);
            break;
          case 'o':
            output = strdup (optarg);
            break;
          case 'h':
            useage ();
          default:
            exit (0);
        }
    }
    if (optind == argc && input == NULL)
      useage ();
    // parse argement end----------------------------



    f_out = fopen (output, "w+");

    if (input) {
        gchar *str;
        gsize length;
        gchar *delimiter = "\n\t\r";

        g_file_get_contents (input, &str, &length, NULL);
        g_strdelimit (str, delimiter, ' ');
        printf ("%s\n", str);
        buf = u8_2_u2 (str);

        g_free (str);
        g_free (input);
    } else {
        buf = u8_2_u2 (argv[optind]);
    }

    ucode = load_ucode (buf);

    gsize i = 0;
    for (i = 0; i < *ucode; i = i + 2) {
        write_bitmap (f_out, ucode[i+1], f_size, font);
        g_printf ("\n");
    }


    fclose (f_out);
    g_free (ucode);
    g_free (buf);
    //g_free (font);
    //g_free (output);
    return 0;
}

gint write_bitmap (FILE *f_out, guint ucode, gint psize, gchar *font_face){
    FT_Library library;
    FT_Face face;
    FT_UInt glyph_index;
    gint row, pixel;


    if(FT_Init_FreeType(&library)
       || FT_New_Face(library,
                      font_face,
                      0,
                      &face)
       || FT_Set_Pixel_Sizes(face,
                             psize,
                             0)) {
        g_printf ("load font file error\n");
        exit (1);
    }

    glyph_index = FT_Get_Char_Index(face, ucode);
    if(glyph_index == 0) {
        g_printf ("load font file error\n");
        exit (1);
    }
    if(FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT)) {
        g_printf ("load font file error\n");
        exit(1);
    }
    if(FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO)) {
        g_printf ("load font file error\n");
        exit(1);
    }



    for(row = 0; row < face->glyph->bitmap.rows; ++row){
        for(pixel = 0; pixel < face->glyph->bitmap.width; ++pixel){
            g_printf("%c", (
                            face->glyph->bitmap.buffer [row * face->glyph->bitmap.pitch 
                            +
                            pixel/8 ] 

                            & (0xC0 >> (pixel % 8))
                           )
                     ? 'O' : ' ');
        }
        g_printf("\n");
    }

    for(row = 0; row < 32; ++row){
        fprintf(f_out, "0x%02x, ", face->glyph->bitmap.buffer[row]);
        if ((row + 1) % 8 == 0) 
          fprintf( f_out, "\n");
    }
    fprintf (f_out ,"\n");

    FT_Done_Face (face);
    face = NULL;
    FT_Done_FreeType (library);
    library = NULL;


    return 0;
}


gchar *u8_2_u2 (const gchar *in)
{
  gchar *src, *src_ptr;
  gchar *des, *des_ptr;
  gsize src_left, des_left, src_len;
  gsize i = 0;
  iconv_t id;
  gchar end = 1;

  id = iconv_open ("UCS-2", "UTF-8");
  if ( (iconv_t) -1 == id)
    g_printf ("iconv_open error\n");

  src_len = strlen (in);

  src = g_malloc (src_len + 1);
  des = g_malloc (src_len * 2 + 2);

  src_left = src_len;
  des_left = src_len * 2;

  strcpy (src, in);
  src_ptr = src;
  des_ptr = des;

  iconv (id, &src_ptr, &src_left, &des_ptr, &des_left);

  g_free (src);

  iconv_close (id);



  return des;
}

guint *load_ucode (gchar *data)
{
  guint *ucode = NULL;
  gchar end = 1; 
  gsize i = 0;
  gsize j;

  if (data == NULL)
    exit (1);

  while (end) {
      if ((data[i] == '\0') && (data[i+1] == '\0')) {
          end = 0;
          break;
      }
      i++;
      i++;
  }
  ucode = g_malloc (i * sizeof (guint)  );
  //g_printf ("malloc %d for ucode\n", i * sizeof (guint));

  *ucode = i;

  for (j = 0; j < i;  j = j + 2) {
      ucode[j+1] = (guchar) data[j] 
        + 
        (0x0000ffff & ( (guchar) data[j+1] << 8));
  }

  return ucode;

}

void useage ()
{
  printf (
          "This program convert letter to matrix data\n\n"
          "Usage: gend [OPTION]... [STRING]...\n\n"
          "\t-i, --input-file <arg>    file will used convert\n"        
          "\t                          default used the STRING\n"
          "\t-o, --output-file <arg>   file will be write the matrix data\n"
          "\t                          default file is 'output'\n" 
          "\t-f, --font <path>         use which font\n"
          "\t-s, --size <arg>          only use for display\n"
          "\t-q, --quiet               don't display used for shell\n"
          "\t-h, --help                print this help text\n\n"
          "write by snyh\n"
          "email: snyh1010@gmail.com\n"
          );

  exit (1);
}
