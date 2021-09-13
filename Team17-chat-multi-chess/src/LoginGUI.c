/*Created by Hayley Sperber 2/28/19*/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "LoginGUI.h"

static void enter_callback(GtkWidget *widget, GtkWidget *entry){
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}

static void entry_toggle_editable(GtkWidget *checkbutton, GtkWidget *entry){
        gtk_editable_set_editable (GTK_EDITABLE (entry), GTK_TOGGLE_BUTTON (checkbutton)->active);

}

static void entry_toggle_visibility(GtkWidget *checkbutton, GtkWidget *entry){
        gtk_entry_set_visibility (GTK_ENTRY (entry), GTK_TOGGLE_BUTTON (checkbutton)->active);

}

int main(int argc, char *argv[]){

    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *entry, *entry2;
    GtkWidget *button1, *button2;
    GtkWidget *check;
    GtkWidget *label;
    GtkWidget *table;
    gint tmp_pos;

    gtk_init (&argc, &argv);

    /* create a new window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(GTK_WIDGET (window), 750, 750);
    gtk_window_set_title(GTK_WINDOW (window), "Login");
    g_signal_connect(window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped(window, "delete-event", G_CALLBACK (gtk_widget_destroy), window);

    /*vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);*/

    table = gtk_table_new(5, 3, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    /* text entry for username */   
    /*label = gtk_label_new("Username\n");*/ 
    entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY (entry), 50);
    g_signal_connect(entry, "activate", G_CALLBACK (enter_callback), entry);
    gtk_entry_set_text(GTK_ENTRY (entry), "Username");
    tmp_pos = GTK_ENTRY(entry)->text_length;
    /*gtk_editable_insert_text(GTK_EDITABLE (entry), " world", -1, &tmp_pos);*/
    gtk_editable_select_region(GTK_EDITABLE (entry), 0, GTK_ENTRY (entry)->text_length);
    /*gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);*/

    gtk_table_attach_defaults(GTK_TABLE(table), entry, 1, 2, 1, 2);

    gtk_widget_show (entry);
    gtk_widget_show(label);

    /*hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_widget_show (hbox);*/


    /* text entry for password */ 
    entry2 = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY (entry2), 50);
    g_signal_connect(entry2, "activate", G_CALLBACK (enter_callback), entry2);
    gtk_entry_set_text(GTK_ENTRY (entry2), "Password");
    tmp_pos = GTK_ENTRY(entry2)->text_length;
    /*gtk_editable_insert_text(GTK_EDITABLE (entry2), " world", -1, &tmp_pos);*/
    gtk_editable_select_region (GTK_EDITABLE (entry2), 0, GTK_ENTRY (entry2)->text_length);
    /*gtk_box_pack_start(GTK_BOX (vbox), entry2, TRUE, TRUE, 0);*/

    gtk_table_attach_defaults(GTK_TABLE(table), entry2, 1, 2, 2, 3);

    gtk_widget_show (entry2);

    /* login button */
    button1 = gtk_button_new_with_label("Login");
    g_signal_connect_swapped (button1, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    /*gtk_box_pack_start (GTK_BOX (vbox), button1, TRUE, TRUE, 0);*/
    gtk_widget_set_can_default(button1, TRUE);
    gtk_widget_grab_default(button1);

    gtk_table_attach_defaults(GTK_TABLE(table), button1, 1, 2, 3, 4);

    gtk_widget_show(button1);

    /* register button */
    button2 = gtk_button_new_with_label("Register");
    g_signal_connect_swapped (button2, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    /*gtk_box_pack_start (GTK_BOX (vbox), button2, TRUE, TRUE, 0);*/
    gtk_widget_set_can_default(button2, TRUE);
    gtk_widget_grab_default(button2);

    gtk_table_attach_defaults(GTK_TABLE(table), button2, 1, 2, 4, 5);

    gtk_widget_show(button2);


    gtk_widget_show(table);
    gtk_widget_show(window);

    gtk_main();

    return 0;
}







