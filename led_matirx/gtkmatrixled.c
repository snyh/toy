#include <gtk/gtk.h>
#include <glib.h>
#include <math.h>
#include "gtkmatrixled.h"
GArray *file_data = NULL;

G_DEFINE_TYPE (GtkMatrixLed, gtk_matrix_led, GTK_TYPE_DRAWING_AREA);

enum {
    PROP_0,
    PROP_COLOR_RED,
    PROP_COLOR_GREEN,
    PROP_COLOR_BULE,
    PROP_COLOR_ALPHA,
    PROP_BUF,
    PROP_X,
    PROP_Y,
    PROP_ID
};
enum {
    PLAY_SIGNAL,
    PAUSE_SIGNAL,
    STOP_SIGNAL,
    LAST_SIGNAL
};
static guint gtk_matrix_led_signals[LAST_SIGNAL] = { 0 };

/* helper function declatore */
static void
gtk_matrix_led_set_property (GObject *object,
                             guint prop_id,
                             const GValue *value,
                             GParamSpec *pspec);
static void
gtk_matrix_led_get_property (GObject *object,
                             guint prop_id,
                             GValue *value,
                             GParamSpec *psepc);
static gboolean 
gtk_matrix_led_expose (GtkMatrixLed *led, GdkEventExpose *event);
/* *************end**************/

/* function declare ****/
void gtk_matrix_led_set_x (GtkMatrixLed *led, gint x);
void gtk_matrix_led_set_y (GtkMatrixLed *led, gint y);
void gtk_matrix_led_set_id (GtkMatrixLed *led, gint id);
void gtk_matrix_led_set_color_red (GtkMatrixLed *led, gdouble red);
void gtk_matrix_led_set_color_green (GtkMatrixLed *led, gdouble green);
void gtk_matrix_led_set_color_bule (GtkMatrixLed *led, gdouble bule);
void gtk_matrix_led_set_color_alpha (GtkMatrixLed *led, gdouble alpha);
void gtk_matrix_led_set_buf (GtkMatrixLed *led, gpointer data);
/* ************end**************/

static void
gtk_matrix_led_class_init (GtkMatrixLedClass *klass)
{

  /* Override the standard functions for setting and retrieving properties.
   * and the gtk_widget expose_event
   */
  GTK_WIDGET_CLASS (klass)->expose_event = gtk_matrix_led_expose;
  G_OBJECT_CLASS (klass)->set_property = gtk_matrix_led_set_property;
  G_OBJECT_CLASS (klass)->get_property = gtk_matrix_led_get_property;
  /*
   * Register the matrix led signal, which will be emitted when
   * the widget plya, pause and stop
   */
  gtk_matrix_led_signals [PLAY_SIGNAL] =
    g_signal_new ("play", G_TYPE_FROM_CLASS (klass),
                  G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
                  G_STRUCT_OFFSET (GtkMatrixLedClass, play),
                  NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
  gtk_matrix_led_signals [PAUSE_SIGNAL] =
    g_signal_new ("pause", G_TYPE_FROM_CLASS (klass),
                  G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
                  G_STRUCT_OFFSET (GtkMatrixLedClass, pause),
                  NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
  gtk_matrix_led_signals [STOP_SIGNAL] =
    g_signal_new ("stop", G_TYPE_FROM_CLASS (klass),
                  G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
                  G_STRUCT_OFFSET (GtkMatrixLedClass, stop),
                  NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);

    /* Register GObject properties */
    g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_COLOR_RED,
                                     g_param_spec_double ("color-red",
                                                          "",
                                                          "",
                                                          0.0, 1.0, 0.0,
                                                          G_PARAM_READWRITE));
    g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_COLOR_GREEN,
                                     g_param_spec_double ("color-green",
                                                          "",
                                                          "",
                                                          0.0, 1.0, 0.0,
                                                          G_PARAM_READWRITE));
    g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_COLOR_BULE,
                                     g_param_spec_double ("color-bule",
                                                          "",
                                                          "",
                                                          0.0, 1.0, 1.0,
                                                          G_PARAM_READWRITE));
    g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_COLOR_ALPHA,
                                     g_param_spec_double ("color-alpha",
                                                          "",
                                                          "",
                                                          0.0, 1.0, 1.0,
                                                          G_PARAM_READWRITE));

    g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_BUF,
                                     g_param_spec_pointer ("buf",
                                                          "MatrixLed data buf",
                                                          "The 32 byte data"
                                                          " buffer",
                                                          G_PARAM_READWRITE));

    g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_X,
                                     g_param_spec_int ("x", 
                                                       "MatrixLed x",
                                                       "The length of x",
                                                       0, 255, 16,
                                                       G_PARAM_READWRITE));
    g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_Y,
                                     g_param_spec_int ("y", 
                                                       "MatrixLed y",
                                                       "The length of y",
                                                       0, 255, 16,
                                                       G_PARAM_READWRITE));
    g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_ID,
                                     g_param_spec_int ("id", 
                                                       "id",
                                                       "id",
                                                       0, 255, 0,
                                                       G_PARAM_READWRITE));

}

static gboolean 
gtk_matrix_led_expose (GtkMatrixLed *led, GdkEventExpose *event)
{
  gchar zero[32] = {0};
  if (led->buf == NULL)
    led->buf = zero;
  cairo_t *cr;
  cr = gdk_cairo_create ( GTK_WIDGET (led)->window);
  gdouble *color = led->color;
  //g_print ("x:%d, y:%d\n", led->x, led->y);
  gint8 row, col;
  gint i = 0;


  for (row = 0; row < led->y; row++) {
      for (col = 0; col < led->x; col++) {
              cairo_arc (cr, 13 + 20 * col, 13  + 20 * row,
                         8, 0, 2 * M_PI); 
              if (
                  ( ((gchar *)led->buf)[i]
                    >>
                    7 - (col < 8 ? col : col -8)) 
                  &
                  0x1
                  )
                cairo_set_source_rgba (cr, color[0], color[1], 
                                       color[2], 1);
              else
                cairo_set_source_rgba (cr, color[0], color[1], 
                                       color[2], color[3] / 10);
              cairo_fill (cr);

              if (col == 7 || col == 15)
                i++;
      }
  }

  cairo_destroy (cr);
  return ;
}
void gtk_matrix_led_set_buf (GtkMatrixLed *led, gpointer data)
{
  led->buf = data;
}
void gtk_matrix_led_set_x (GtkMatrixLed *led, gint x)
{
  led->x = x;
}
void gtk_matrix_led_set_y (GtkMatrixLed *led, gint y)
{
  led->y = y;
}
void gtk_matrix_led_set_id (GtkMatrixLed *led, gint id)
{
  led->id = id;
}
void gtk_matrix_led_set_color_red (GtkMatrixLed *led, gdouble red)
{
  led->color[0] = red;
}
void gtk_matrix_led_set_color_green (GtkMatrixLed *led, gdouble green)
{
  led->color[1] = green;
}
void gtk_matrix_led_set_color_bule (GtkMatrixLed *led, gdouble bule)
{
  led->color[2] = bule;
}
void gtk_matrix_led_set_color_alpha (GtkMatrixLed *led, gdouble alpha)
{
  led->color[0] = alpha;
}

static void
gtk_matrix_led_set_property (GObject *object,
                             guint prop_id,
                             const GValue *value,
                             GParamSpec *pspec)
{
  GtkMatrixLed *led;
  led = GTK_MATRIX_LED (object);
  switch (prop_id)
    {
    case PROP_BUF:
      g_object_set_data(G_OBJECT (object), "buf",
                        g_value_get_pointer (value));
    case PROP_X:
      gtk_matrix_led_set_x (led, g_value_get_int (value));
      break;
    case PROP_Y:
      gtk_matrix_led_set_y (led, g_value_get_int (value));
      break;
    case PROP_ID:
      gtk_matrix_led_set_id (led, g_value_get_int (value));
      break;
    case PROP_COLOR_RED:
      gtk_matrix_led_set_color_red (led, g_value_get_double (value));
      break;
    case PROP_COLOR_GREEN:
      gtk_matrix_led_set_color_green (led, g_value_get_double (value));
      break;
    case PROP_COLOR_BULE:
      gtk_matrix_led_set_color_bule (led, g_value_get_double (value));
      break;
    case PROP_COLOR_ALPHA:
      gtk_matrix_led_set_color_alpha (led, g_value_get_double (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
static void
gtk_matrix_led_get_property (GObject *object,
                             guint prop_id,
                             GValue *value,
                             GParamSpec *pspec)
{
  GtkMatrixLed *led;
  led = GTK_MATRIX_LED (object);
  switch (prop_id)
    {
    case PROP_X:
      g_value_set_int (value, led->x);
      break;
    case PROP_Y:
      g_value_set_int (value, led->y);
      break;
    case PROP_ID:
      g_value_set_int (value, led->id);
      break;
    case PROP_COLOR_RED:
      g_value_set_double (value, led->color[0]);
      break;
    case PROP_COLOR_GREEN:
      g_value_set_double (value, led->color[1]);
      break;
    case PROP_COLOR_BULE:
      g_value_set_double (value, led->color[2]);
      break;
    case PROP_COLOR_ALPHA:
      g_value_set_double (value, led->color[3]);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
gtk_matrix_led_init (GtkMatrixLed *led)
{
  gtk_widget_set_size_request (GTK_WIDGET (led), 326 , 326);
  led->color[0] = 0;
  led->color[1] = 0;
  led->color[2] = 1;
  led->color[3] = 1;

  g_print ("one......\n");
  g_signal_connect (G_OBJECT (led), "play",
                    G_CALLBACK (gtk_matrix_led_play), NULL);
  g_signal_connect (G_OBJECT (led), "pause",
                    G_CALLBACK (gtk_matrix_led_pause), NULL);
  g_signal_connect (G_OBJECT (led), "stop",
                    G_CALLBACK (gtk_matrix_led_stop), NULL);
}


GtkWidget*
gtk_matrix_led_new (int x, int y, int id)
{ 
  return g_object_new (GTK_TYPE_MATRIX_LED, "x", x, "y", y, "id", id, NULL);
}


gboolean gtk_matrix_led_load_from_file (const gchar *file, int bufsize)
{

  if (file_data != NULL)
    g_array_free (file_data, TRUE);
  file_data = g_array_new (FALSE, FALSE, bufsize);
  gchar data[32];
  gconstpointer ptr;
  gchar *str;
  gchar *str_save;

  if (!g_file_get_contents (file, &str, NULL, NULL))
    g_error ("ERROR:open file error\n");
  str_save = str;

  while (*str != '\0') {

      sscanf ((const gchar*)str, 

              "0x%02x, 0x%02x, 0x%02x, 0x%02x, "
              "0x%02x, 0x%02x, 0x%02x, 0x%02x,\n"
              "0x%02x, 0x%02x, 0x%02x, 0x%02x, "
              "0x%02x, 0x%02x, 0x%02x, 0x%02x,\n"
              "0x%02x, 0x%02x, 0x%02x, 0x%02x, "
              "0x%02x, 0x%02x, 0x%02x, 0x%02x,\n"
              "0x%02x, 0x%02x, 0x%02x, 0x%02x, "
              "0x%02x, 0x%02x, 0x%02x, 0x%02x,\n",

              &data[0],  &data[1],  &data[2],  &data[3],
              &data[4],  &data[5],  &data[6],  &data[7],
              &data[8],  &data[9],  &data[10], &data[11], 
              &data[12], &data[13], &data[14], &data[15],
              &data[16], &data[17], &data[18], &data[19], 
              &data[20], &data[21], &data[22], &data[23],
              &data[24], &data[25], &data[26], &data[27],
              &data[28], &data[29], &data[30], &data[31]
              );

      ptr = data;
      g_array_append_vals (file_data, ptr, 1);
      str = str + 197;
  }

  g_free (str_save);
  return TRUE;

}

gboolean data_shift (gpointer data)
{
  typedef  struct {
      gchar data[32];
  }mybuf;
  static i = 0;
  if ( i < file_data->len)
    i += 2;
  else 
    i = 0;

  GtkMatrixLed *led = GTK_MATRIX_LED (data);
  led->buf = (gpointer)&g_array_index(file_data, mybuf, i + led->id);
  gtk_widget_queue_draw (led);
}

void gtk_matrix_led_play (GtkMatrixLed* led, gpointer data)
{

  if (file_data == NULL) {
      g_print ("no file \n");
      return;
  }
  g_timeout_add (1000, data_shift, led);
  
}
void gtk_matrix_led_pause (GtkMatrixLed* led)
{
  g_print ("LED%d is pause..........\n", led->id);
}
void gtk_matrix_led_stop (GtkMatrixLed* led)
{
  g_print ("LED%d is stop..........\n", led->id);
}

