#include <gtk/gtk.h>
#include "gtkmatrixled.h"
#include "interface.h"
#include "callback.h"

GtkWidget *led1, *led2;
guchar buffer[64];
GString *matrix_data;


int main (int argc, char *argv[])
{
  GtkWidget *window;
  gtk_init (&argc, &argv);

  matrix_data = g_string_sized_new (1024);

  window = main_window_create();
  gtk_widget_show_all (window);

  gtk_main ();
  return 0;
}
