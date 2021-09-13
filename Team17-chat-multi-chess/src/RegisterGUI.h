/*Created by Hayley Sperber 2/28/19*/

GtkWidget *gtk_entry_new(void);

void gtk_entry_set_text(GtkEntry *entry, const gchar *text);

const gchar *gtk_entry_get_text(GtkEntry *entry);

void gtk_editable_set_editable(GtkEditable *entry, gboolean editable);

void gtk_entry_set_visibility(GtkEntry *entry, gboolean visible);

void gtk_editable_select_region(GtkEditable *entry, gint start, gint end);











