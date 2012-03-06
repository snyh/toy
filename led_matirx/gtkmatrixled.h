#ifndef __GTK_MATRIX_LED_H__
#define __GTK_MATRIX_LED_H__

#include <gdk/gdk.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GTK_TYPE_MATRIX_LED     (gtk_matrix_led_get_type())
#define GTK_MATRIX_LED(obj)     (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
                                 GTK_TYPE_MATRIX_LED, GtkMatrixLed))
#define GTK_MATRIX_LED_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass),\
                                 GTK_TYPE_MATRIX_LED, GtkMatrixLedClass))
#define GTK_IS_MATRIX_LED(obj)  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
                                 GTK_TYPE_MATRIX_LED))
#define GTK_IS_MATRIX_LED_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass),\
                                         GTK_TYPE_MATRIX_LED))
#define GTK_MATRIX_LED_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS ((obj), \
                                  GTK_TYPE_MATRIX_LED, GtkMatrixLedClass))

typedef struct _GtkMatrixLed            GtkMatrixLed;
typedef struct _GtkMatrixLedClass       GtkMatrixLedClass;

struct CairoColor 
{
  gdouble red;
  gdouble green;
  gdouble bule;
  gdouble alpha;
};

struct _GtkMatrixLed
{
  GtkDrawingArea        parent;
  gpointer              buf;
  GTime                 delay;
  gdouble               color[4];
  gint                 x;
  gint                 y;
  gint                  id;
};


struct _GtkMatrixLedClass
{
  GtkDrawingAreaClass   parent_class;
  void  (* play) (GtkMatrixLed *led);
  void  (* pause) (GtkMatrixLed *led);
  void  (* stop) (GtkMatrixLed *led);

};


GType           gtk_matrix_led_get_type  (void) G_GNUC_CONST;

GtkWidget*      gtk_matrix_led_new (int x, int y, int id);
gboolean        gtk_matrix_led_load_from_data (GtkMatrixLed*, guchar*);
gboolean        gtk_matrix_led_load_from_file (const gchar*, int bufsize);
void            gtk_matrix_led_play (GtkMatrixLed*, gpointer data);
void            gtk_matrix_led_pause (GtkMatrixLed*);
void            gtk_matrix_led_stop (GtkMatrixLed*);

G_END_DECLS

#endif
