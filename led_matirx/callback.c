#include "callback.h"
#include "gtkmatrixled.h"
#include <stdio.h>
extern GtkWidget *led1, *led2;
gboolean load_file (GtkFileChooserButton *widget, gpointer data)
{

  gchar *file = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (widget));
  if (file == NULL)
    return FALSE;

  gtk_matrix_led_load_from_file (file, 32);
  /*
  GtkMatrixLedClass *klass;
  klass = GTK_MATRIX_LED_CLASS (G_OBJECT_GET_CLASS (led1));

  g_printf ("ledmatrix->file_data[0] = 0x%02x\n", klass->file_data[0]);
  */
}

void matrix_play ()
{
  g_signal_emit_by_name (led1, "play");
  g_signal_emit_by_name (led2, "play");
}
void matrix_stop ()
{
  g_signal_emit_by_name (led1, "stop");
  g_signal_emit_by_name (led2, "stop");
}
void matrix_pause ()
{
  g_signal_emit_by_name (led1, "pause");
  g_signal_emit_by_name (led2, "pause");
}

