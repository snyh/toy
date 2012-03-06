#ifndef __CALLBACK_H__
#define __CALLBACK_H__
#include <gtk/gtk.h>
extern 
gboolean select_data_file (void);
/*
 *
void matrix_play (GtkWidget *widget, gpointer data);

void matrix_stop (GtkWidget *widget, gpointer data);
void matrix_pause (GtkWidget *widget, gpointer data);
*
*/

void matrix_play ();

void matrix_stop ();
void matrix_pause ();
gboolean load_file (GtkFileChooserButton *widget, gpointer data);



#endif
