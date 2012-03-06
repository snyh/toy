#include "drawwindow.h"
#include <gtk/gtk.h>
#include <cairo.h>
#include <gtk/gdk.h>



gboolean drawwindow_expose (GtkWidget *widget, ,GdkEventExpose event,
                            gpointer data)
{
  cairo_t *cr;

}

GtkWidget*
drawwindow_create (int width, int height)
{
  g_return_val_if_fail (width < 8, NULL);
  g_return_val_if_fail (height < 8, NULL);
  GtkWidget *draw_area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (GTK_WINDOW (draw_area), width, height);
  g_signal_connect (G_OBJECT (draw_area),"expose_event",
                    G_CALLBACK (drawwindow_expose), NULL);

  return draw_area;
}
