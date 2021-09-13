//created by samuel wong

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include <assert.h>
#include <unistd.h>

#define BUFFSIZE 256
typedef struct{
		GtkWidget *note;
		GtkLabel *mes1;
		GtkLabel *mes2;
		GtkLabel *mes3;
		GtkLabel *mes4;
		GtkLabel *mes5;
		GtkLabel *mes6;
		GtkLabel *mes7;
}Messages;
typedef struct{
		GtkWidget *note;
		int *porter;
}khoi;

const char *Program	/* program name for descriptive diagnostics */
	= NULL;
struct sockaddr_in
	ServerAddress;	/* server address we connect with */

int create_login(int *argc, char **argv[]);

static void close_flist(GtkWidget *window);

static void close_main();

static void make_friend_list();

static void delete_friend(GtkButton *button, Messages *Message);

static void set_online();

static void set_busy();

static void set_offline();

static void make_home(GtkNotebook *notebook);

static void close_home(GtkWidget *notebook);

static void user_login(GtkWidget *Button, GtkWindow *window);

static void delete_window(GtkWidget *window);

static void new_friend(GtkEntry *entry, GtkWidget *notebook);

GtkWidget *CreateWindow(int *argc, char **argv[]);

void UpdateWindow(void);

char* get(char* command);

static void send_chat_message(GtkEntry *entry, Messages *Message);

static void close_friend(GtkButton *button, Messages *Message);

static gboolean autoupdate(gpointer data);