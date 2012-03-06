#include <gtk/gtk.h>
#include "gtkmatrixled.h"
#include "callback.h"
#include "interface.h"
extern GtkWidget *led1, *led2;

GtkWidget* create_list ()
{
  enum {
      DATA_LED1_1_COLUMN,
      DATA_LED1_2_COLUMN,
      DATA_LED2_1_COLUMN,
      DATA_LED2_2_COLUMN,
      N_COLUMNS
  };
  GtkListStore *store = gtk_list_store_new (N_COLUMNS, 
                                            G_TYPE_UCHAR,
                                            G_TYPE_UCHAR,
                                            G_TYPE_UCHAR,
                                            G_TYPE_UCHAR);
  GtkTreeIter iter;
  gtk_list_store_append (store, &iter);
  gtk_list_store_set (store, &iter,
                      DATA_LED1_1_COLUMN, 0x13,
                      DATA_LED1_2_COLUMN, 0x01,
                      DATA_LED2_1_COLUMN, 0x22,
                      DATA_LED2_2_COLUMN, 0x11,
                      -1);
  gtk_list_store_append (store, &iter);
  gtk_list_store_set (store, &iter,
                      DATA_LED1_1_COLUMN, 0x14,
                      DATA_LED1_2_COLUMN, 0x09,
                      DATA_LED2_1_COLUMN, 0x20,
                      DATA_LED2_2_COLUMN, 0x18,
                      -1);

  GtkWidget *tree;
  tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  renderer = gtk_cell_renderer_text_new ();

  column = gtk_tree_view_column_new_with_attributes ("LED1左",
                                                     renderer,
                                                     "text", DATA_LED1_1_COLUMN,
                                                     NULL);
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);
  column = gtk_tree_view_column_new_with_attributes ("LED1右",
                                                     renderer,
                                                     "text", DATA_LED1_1_COLUMN,
                                                     NULL);
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);
  column = gtk_tree_view_column_new_with_attributes ("LED2左",
                                                     renderer,
                                                     "text", DATA_LED2_1_COLUMN,
                                                     NULL);
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);
  column = gtk_tree_view_column_new_with_attributes ("LED2右",
                                                     renderer,
                                                     "text", DATA_LED2_1_COLUMN,
                                                     NULL);
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);

  return tree;
}
GtkWidget *produce_window_create ()
{
  return gtk_label_new ("hehe");
}
GtkWidget *com_window_create ()
{
  return gtk_label_new ("hehe");
}

GtkWidget *simulate_window_create ()
{
  GtkWidget *vbox;
  GtkWidget *button;
  GtkWidget *sep;
  GtkWidget *expander;
  GtkWidget *file_chooser;
  GtkWidget *hbox, *entry_run, *label;


  vbox = gtk_vbox_new (FALSE, 0);

  hbox = gtk_hbox_new (TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 5);
  led1 = gtk_matrix_led_new (16, 16, 0);
  gtk_box_pack_start (GTK_BOX (hbox), led1, TRUE, TRUE, 5);
  led2 = gtk_matrix_led_new (16, 16, 1);
  gtk_box_pack_start (GTK_BOX (hbox), led2, TRUE, TRUE, 5);


  sep = gtk_hseparator_new ();
  gtk_box_pack_start (GTK_BOX (vbox), sep, TRUE, TRUE, 5);
  expander = gtk_expander_new_with_mnemonic ("(_Display)显示点阵数据");
  GtkWidget *tree = create_list ();
  gtk_container_add (GTK_CONTAINER (expander), tree);
  gtk_box_pack_start (GTK_BOX (vbox), expander, TRUE, TRUE, 5);


  hbox = gtk_hbox_new (TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 5);
  label = gtk_label_new ("数据文件:");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, TRUE, 5);
  file_chooser = gtk_file_chooser_button_new ("选择点阵数据文件", 
                                        GTK_FILE_CHOOSER_ACTION_OPEN);
  g_signal_connect (G_OBJECT (file_chooser), "file-set",
                    G_CALLBACK (load_file), NULL);
  gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (file_chooser), "./");
  gtk_box_pack_start (GTK_BOX (hbox), file_chooser, FALSE, TRUE, 5);



  hbox = gtk_hbox_new (TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 5);
  button = gtk_button_new_from_stock (GTK_STOCK_MEDIA_PLAY);
  g_signal_connect (G_OBJECT (button), "clicked",
                    G_CALLBACK (matrix_play), file_chooser);
  gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 5);
  button = gtk_button_new_from_stock (GTK_STOCK_MEDIA_PAUSE);
  g_signal_connect (G_OBJECT (button), "clicked",
                    G_CALLBACK (matrix_pause), file_chooser);
  gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 5);
  button = gtk_button_new_from_stock (GTK_STOCK_MEDIA_STOP);
  g_signal_connect (G_OBJECT (button), "clicked",
                    G_CALLBACK (matrix_stop), NULL);
  gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 5);



  return vbox;
}

GtkWidget *main_window_create ()
{
  GtkWidget *window;
  GtkWidget *notebook;
  GtkWidget *child_window;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "点阵数据生成、模拟、通讯系统");
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (gtk_main_quit), NULL);

  notebook = gtk_notebook_new ();
  gtk_notebook_append_page (
                            GTK_NOTEBOOK (notebook),
                            produce_window_create (),
                            gtk_label_new ("数据生成")
                           );
  gtk_notebook_append_page (
                            GTK_NOTEBOOK (notebook),
                            simulate_window_create (),
                            gtk_label_new ("模拟显示")
                           );
  gtk_notebook_append_page (
                            GTK_NOTEBOOK (notebook),
                            com_window_create (),
                            gtk_label_new ("通讯模块")
                           );
  gtk_container_add (GTK_CONTAINER (window), notebook);

  return window;
}
