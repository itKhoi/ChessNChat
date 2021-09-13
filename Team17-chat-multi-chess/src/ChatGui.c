#include "ChatGui.h"


char id[256] = {0};
char current_friend[256]={0};
GtkNotebook *notebook;
GtkWidget *login_box1, *login_box2;	
GtkWidget *Window;
Messages *message;
int get_flag = 0;

/* testing how to turn the message queue into actual messages
int main()
{
    char buffer[256]={0};
    strcat(buffer,"00000001,00000002");
    char *pt;
    pt = strtok(buffer,",");
    
    while(pt != NULL){
        char buffer2[256]={0};
        strcpy(buffer2,pt);
        printf("%s\n",buffer2);
        pt = strtok (NULL, ",");
    }
    
    

    return 0;
}
*/

/*setting all of the statuses that are going to be used*/
static void close_main(){
		set_offline();
		gtk_main_quit();
}
static void close_flist(GtkWidget *window){
		gtk_widget_destroy(window);
}

static void set_online(){
		char buffer[256]={0};
		strcat(buffer,"SETSTAT,");
		strcat(buffer,id);
		strcat(buffer,",1");
		get(buffer);
}
static void set_busy(){
		char buffer[256]={0};
		strcat(buffer,"SETSTAT,");
		strcat(buffer,id);
		strcat(buffer,",2");
		get(buffer);
}

static void set_offline(){
		char buffer[256]={0};
		strcat(buffer,"SETSTAT,");
		strcat(buffer,id);
		strcat(buffer,",0");
		get(buffer);
}
/*prints the friends list*/
static void make_friend_list(){
		GtkWidget *window;
		GtkWidget *text_view;
		GtkWidget *vbox;
		char *pt;
		char sending_command[256] = {0};
		char receiving_command[256] = {0};
		
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(window), "MaximumFriends");
		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
		gtk_container_set_border_width(GTK_CONTAINER(window), 10);
		gtk_window_set_default_size(GTK_WINDOW(window), 200, 400);
		g_signal_connect(window,"close_flist", G_CALLBACK(gtk_main_quit),NULL);		
		
		vbox = gtk_vbox_new(TRUE,5);
		gtk_container_add(GTK_CONTAINER(window), vbox);
		strcat(sending_command,"GETFRI,");
		strcat(sending_command,id);
		strcpy(receiving_command,get(sending_command));
		/*separates the string of friends into easy to read format*/
		if(strcmp(receiving_command,"")==0){
			GtkWidget *label;
			label = gtk_label_new("you have no friends");
			gtk_container_add(GTK_CONTAINER(vbox),label);
		}
		else{
			pt = strtok(receiving_command,",");
			while(pt != NULL){
				int x;
				
				char buffer[256] = {0};
				char buffer2[256] = {0};
				char buffer3[256] = {0};
				char buffer4[256] = {0};
				char buffer5[256] = {0};
				char buffer6[256] = {0};
				strcpy(buffer,pt);	
				strcat(buffer2,"GETNAME,");
				strcat(buffer2,pt);
				strcpy(buffer3,get(buffer2));
			
				strcat(buffer5,"GETSTAT,");
				strcat(buffer5,pt);
				strcat(buffer6,get(buffer5));
				x=atoi(buffer6);
			
				GtkWidget *label;
				strcat(buffer4,buffer3);
				strcat(buffer4,"ID#");
				strcat(buffer4,pt);
				strcat(buffer4," |status");
				if(x==0){
					strcat(buffer4,"  offline");
				}
				else if(x==1){
					strcat(buffer4,"  online");
				}
				else if(x==2){
					strcat(buffer4,"  busy");
				}
				else{
					strcat(buffer4,"unknown");
				}
			label = gtk_label_new(buffer4);
			gtk_container_add(GTK_CONTAINER(vbox),label);
			pt = strtok(NULL,",");
			usleep(500000);
			}
		}
		gtk_widget_show_all(window);
}
static void user_login(GtkWidget *Button, GtkWindow *window){
		/*Logic for loggin in*/
		const gchar *name1;
		const gchar *name2;
		char username[25] = {0};
		char password[25] = {0};
		char sending_command[256] = {0};
		
		name1 = gtk_entry_get_text(login_box1);
		sprintf(username,"%s",name1);
		name2 = gtk_entry_get_text(login_box2);
		sprintf(password,"%s",name2);
		
		strcat(sending_command,"LOGIN");
		strcat(sending_command,",");
		strcat(sending_command,username);
		strcat(sending_command,",");
		strcat(sending_command,password);

		if(strcmp(username,"")==0 || strcmp(password,"")==0){
			gtk_entry_set_text(GTK_ENTRY(login_box1), "No blank entries!");
		}
		else{
			strcpy(id, get(sending_command));
			if(strcmp(id,"0")==0){
				gtk_entry_set_text(GTK_ENTRY(login_box1), "Username does not exist!");
				gtk_entry_set_text(GTK_ENTRY(login_box2), "Please try again");
			}
			else if(strcmp(id,"-1")==0){
				gtk_entry_set_text(GTK_ENTRY(login_box1),"Incorrect Password!");
				gtk_entry_set_text(GTK_ENTRY(login_box2), "Please try again");
			}
			else{
				set_online();
				gtk_widget_hide(window);
				close_home(notebook);
				make_home(notebook);
				gtk_widget_show(Window);
			}
		}
}

static void user_register(GtkWidget *Button, GtkWindow *window){
		/*logic for registering an account*/
		const gchar *name1;
		const gchar *name2;
		char username[25] = {0};
		char password[25] = {0};
		char sending_command[256] = {0};
		
		name1 = gtk_entry_get_text(login_box1);
		sprintf(username, "%s", name1);
		name2 = gtk_entry_get_text(login_box2);
		sprintf(password,"%s", name2);
		strcat(sending_command,"REGISTER");
		strcat(sending_command,",");
		strcat(sending_command,username);
		strcat(sending_command,",");
		strcat(sending_command,password);
	
		if(strcmp(username,"")==0 || strcmp(password,"")==0){
			gtk_entry_set_text(GTK_ENTRY(login_box1), "No blank entries!");
		}
		else{	
			strcpy(id, get(sending_command));
			set_online();
			gtk_widget_hide(window);
			gtk_widget_show(Window);
		}
}

int create_login(int *argc, char **argv[]){
		/*creates the login GUI*/
		GtkWidget *window;
		GtkWidget *table;
		GtkWidget *label1, *label2;
		GtkWidget *button1, *button2;
		/*GtkWidget *entry_box1, *entry_box2;*/
		
		gtk_init(argc, argv);
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(window), "HURRY UP AND LOGIN!!!");
		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
		gtk_container_set_border_width(GTK_CONTAINER(window), 10);
		gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
		g_signal_connect(window,"destroy", G_CALLBACK(gtk_main_quit),NULL);
		gtk_widget_show(window);
		
		table = gtk_table_new(6,6,TRUE);
		gtk_container_add(GTK_CONTAINER(window),table);
		gtk_widget_show(table);
		
		label1 = gtk_label_new("Username");
		gtk_table_attach_defaults(GTK_TABLE(table), label1, 2,4,0,1);
		label2 = gtk_label_new("Password");
		gtk_table_attach_defaults(GTK_TABLE(table), label2, 2,4,2,3);
		gtk_widget_show(label1);
		gtk_widget_show(label2);
		
		button1 = gtk_button_new_with_label("LOGIN");
		g_signal_connect(button1, "clicked", G_CALLBACK(user_login), window);
		gtk_table_attach_defaults(GTK_TABLE(table), button1, 0 , 2, 5, 6);
		
		button2 = gtk_button_new_with_label("REGISTER");
		g_signal_connect(button2,"clicked", G_CALLBACK(user_register),window);
		gtk_table_attach_defaults(GTK_TABLE(table), button2, 4 , 6, 5, 6);
		
		gtk_widget_show(button1);
		gtk_widget_show(button2);
		
		login_box1 = gtk_entry_new();
		gtk_table_attach_defaults(GTK_TABLE(table), login_box1, 2,4,1,2);
		gtk_widget_show(login_box1);
		
		login_box2 = gtk_entry_new();
		gtk_table_attach_defaults(GTK_TABLE(table), login_box2, 2,4,3,4);
		gtk_widget_show(login_box2);
		
		return 1;
}
/*closes the home tab when a friend chat is opened*/
static void close_home(GtkWidget *notebook){
		gint page;
		page = gtk_notebook_get_current_page(notebook);
		gtk_notebook_remove_page(notebook, page);
		gtk_widget_queue_draw(GTK_WIDGET(notebook));
}
/*creates the home tab*/
static void make_home(GtkNotebook *notebook){
		GtkWidget *table2;
		GtkWidget *label;
		GtkWidget *entry_box;
		GtkWidget *frame;
		GtkWidget *button;
		const gchar fid;
		char friend_id[256]={0};
		char home_id[256]={0};
		
		/*First page for adding friends*/
		strcat(home_id,"You are ID#");
		strcat(home_id,id);
		frame = gtk_frame_new(home_id);
		gtk_container_set_border_width(GTK_CONTAINER(frame), 10);
		gtk_widget_set_size_request(frame, 100, 75);
		gtk_widget_show(frame);
		table2 = gtk_table_new(6,6, TRUE);
		gtk_container_add(GTK_CONTAINER(frame), table2);
		gtk_widget_show(table2);
		
		/*adding the entry to type in friend name*/
		entry_box = gtk_entry_new();
		gtk_table_attach_defaults(GTK_TABLE(table2), entry_box, 1,5,2,4);
		gtk_widget_show(entry_box);
		label = gtk_label_new("Enter the ID number of your friend \n    (non friend IDs will be added)");
		gtk_table_attach_defaults(GTK_TABLE(table2), label, 0,6,1,2);
		g_signal_connect(GTK_ENTRY(entry_box), "activate", G_CALLBACK(new_friend), notebook);
		gtk_widget_show(label);
		
		label = gtk_label_new("Home");
		gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame, label);
		
		g_timeout_add_seconds(5,autoupdate,notebook);
		
		button = gtk_button_new_with_label("Friend List");
		g_signal_connect(button, "clicked", G_CALLBACK(make_friend_list), NULL);
		gtk_table_attach_defaults(GTK_TABLE(table2), button, 2 , 4, 4, 5);
		gtk_widget_show(button);
		
		gtk_widget_show(frame);
}

static gboolean autoupdate(gpointer data){

	if(get_flag!=0){//If chatting send get message
		char sending_command[256] = {0};
		char receiving_command[256] = {0};
		char *pt;
		strcat(sending_command,"QUEUE,");
		strcat(sending_command,id);
		strcat(sending_command,",");
		strcat(sending_command,current_friend);
		strcpy(receiving_command,get(sending_command));
		
		pt = strtok(receiving_command,",");
		while(pt != NULL){
			char buffer [256] = {0};
			char buffer2[256] = {0};
			char buffer3[256] = {0};
			char buffer4[256] = {0};
			char buffer5[256] = {0};
			char buffer6[256] = {0};
			
			if(strcmp(receiving_command,"-1")==0){
				break;
			}
			
			strcpy(buffer,pt);	
			strcat(buffer2,"MESSAGE,");
			strcat(buffer2,buffer);
			strcpy(buffer3,get(buffer2));
			
			
			
			const gchar *omes1 = gtk_label_get_text(message -> mes1);
			const gchar *omes2 = gtk_label_get_text(message -> mes2);
			const gchar *omes3 = gtk_label_get_text(message -> mes3);
			const gchar *omes4 = gtk_label_get_text(message -> mes4);
			const gchar *omes5 = gtk_label_get_text(message -> mes5);
			const gchar *omes6 = gtk_label_get_text(message -> mes6);
			const gchar *omes7 = gtk_label_get_text(message -> mes7);
			
			gtk_label_set_text(message->mes7,omes6);
			gtk_label_set_text(message->mes6,omes5);
			gtk_label_set_text(message->mes5,omes4);
			gtk_label_set_text(message->mes4,omes3);
			gtk_label_set_text(message->mes3,omes2);
			gtk_label_set_text(message->mes2,omes1);
			gtk_label_set_text(message->mes1,buffer3);
			
			pt = strtok(NULL, ",");
			
		}
	}
	
	return TRUE;
}


/*creates the main chat GUI window*/
GtkWidget *CreateWindow(int *argc, char **argv[])
{		GtkWidget *window;
		GtkWidget *button;
		GtkWidget *table, *table2;
		GtkWidget *entry_box;
		GtkWidget *frame;
		GtkWidget *label;
		GtkWidget *checkbutton;
		
		gtk_init(argc, argv);
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(window), "MaximumChatting");
		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
		gtk_container_set_border_width(GTK_CONTAINER(window), 10);
		gtk_window_set_default_size(GTK_WINDOW(window), 400, 450);
		
		/*Create a table to format the chat box*/
		table = gtk_table_new(3,6,FALSE);
		gtk_container_add(GTK_CONTAINER(window), table);
		
		/* Creating the NoteBook*/
		notebook = gtk_notebook_new();
		gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
		gtk_table_attach_defaults(GTK_TABLE(table), notebook, 0, 6, 0, 1);
		gtk_widget_show(notebook);
		
		/*enter port stuff here for using the get function*/
		
		make_home(notebook);
		
		/* set pressing the x button to closing the window*/
		/*g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);*/
		g_signal_connect(window,"destroy", G_CALLBACK(close_main),NULL);	
		
		/*Show the window*/
		gtk_widget_show(table);
		gtk_widget_show(window);
		return(window);
}
void UpdateWindow(void)		/* render the window on screen */
{
   /* this server has it's own main loop for handling client connections;
    * as such, it can't have the usual GUI main loop (gtk_main);
    * instead, we call this UpdateWindow function on regular basis
    */
    while(gtk_events_pending())
    {
	gtk_main_iteration();
    }
} /* end of UpdateWindow */

/* updating the chat log with messages from other people*/
/*static void get_chat_message(){
	
}*/
/*function used to communicate with the server*/
char* get(char* command)
{
    int sockid = socket(AF_INET, SOCK_STREAM, 0);
    connect(sockid, (struct sockaddr *)&ServerAddress, sizeof(struct sockaddr_in));
    send(sockid, command, strlen(command), 0);
    char* buffer = malloc(sizeof(char) * BUFFSIZE);
    recv(sockid, buffer, BUFFSIZE, 0);

    return buffer;
}
/* sending messages to people need to send to their id*/
static void send_chat_message(GtkEntry *entry, Messages *Message){
		const gchar *name2;
		const gchar *omes1 = gtk_label_get_text(Message -> mes1);
		const gchar *omes2 = gtk_label_get_text(Message -> mes2);
		const gchar *omes3 = gtk_label_get_text(Message -> mes3);
		const gchar *omes4 = gtk_label_get_text(Message -> mes4);
		const gchar *omes5 = gtk_label_get_text(Message -> mes5);
		const gchar *omes6 = gtk_label_get_text(Message -> mes6);
		const gchar *omes7 = gtk_label_get_text(Message -> mes7);
		char bufferchat[100];
		char sending_command[256];
		char rec[256]={0};
		GtkWidget *masternote;
		masternote = Message->note;
		name2 = gtk_entry_get_text(entry);
		sprintf(bufferchat,"ME: %s",name2);
		
		strcpy(sending_command,"SEND,");
		strcat(sending_command, id);
		strcat(sending_command,",");
		strcat(sending_command, current_friend);
		strcat(sending_command, ",");
		strcat(sending_command, name2);
		
		strcpy(rec, get(sending_command));
		
		gtk_label_set_text(Message->mes7,omes6);
		gtk_label_set_text(Message->mes6,omes5);
		gtk_label_set_text(Message->mes5,omes4);
		gtk_label_set_text(Message->mes4,omes3);
		gtk_label_set_text(Message->mes3,omes2);
		gtk_label_set_text(Message->mes2,omes1);
		gtk_label_set_text(Message->mes1,bufferchat);
		
		/*g_print("does %s work\n\n", bufferchat);
		g_print("%s\n\n", name2);*/
		gtk_entry_set_text(GTK_ENTRY(entry), "");
}
/*close a friend tab*/
static void close_friend(GtkButton *button, Messages *Message){
		make_home(Message->note);
		get_flag = 0;
		set_online();
		gint page;
		page = gtk_notebook_get_current_page(Message->note);
		gtk_notebook_remove_page(Message->note, page);
		gtk_widget_queue_draw(GTK_WIDGET(Message->note));
		free(Message);
}

static void delete_friend(GtkButton *button, Messages *Message){
		char buffer[256]={0};
		get_flag = 0;
		strcat(buffer,"DELETEFRI,");
		strcat(buffer,id);
		strcat(buffer,",");
		strcat(buffer,current_friend);
		get(buffer);
		make_home(Message->note);
		set_online();
		gint page;
		page=gtk_notebook_get_current_page(Message->note);
		gtk_notebook_remove_page(Message->note, page);
		gtk_widget_queue_draw(GTK_WIDGET(Message->note));
		free(Message);
}
/*creates the new tab when a friend/new friend is added and it checks to see if u are friends*/
static void new_friend(GtkEntry *entry, GtkWidget *notebook){
		char bufferk[32]={0};
		char bufferj[32]={0};
		char *name;
		static int x = 0;
		char receiving_command[256]={0};
		char sending_command[256]={0};
		get_flag = 1;
		GtkWidget *frame, *table2, *button1, *button2, *label, *entry_box2;
		GtkWidget *text1, *text2, *text3, *text4, *text5, *text6, *text7;
		GtkTextBuffer *buffer;
		name = gtk_entry_get_text(entry);
		strcpy(bufferj, name);
		x++;
		/*gets the name of the friend you are talking to*/
		set_busy();
		strcat(sending_command,"GETNAME");
		strcat(sending_command,",");
		strcat(sending_command,bufferj);
		strcpy(receiving_command,get(sending_command));
		
		if(strcmp(receiving_command,"-1")==0){
			gtk_entry_set_text(GTK_ENTRY(entry), "Incorrect ID number!");
		}
		
		else if(strcmp(receiving_command,"-1")!=0){
			sprintf(current_friend,"%s",bufferj);
			close_home(notebook);
			
			/*adding a friend if they arent already*/
			char buffer[256] = {0};
			char buffer2[256] = {0};
			int my_id,friend_id;
			char *pt;
			int flag = 0;
			
			my_id = atoi(bufferj);
			strcat(buffer,"GETFRI,");
			strcat(buffer,id);
			strcat(buffer2,get(buffer));
			pt = strtok(buffer2,",");
				while(pt != NULL){
					char buffer3[256] = {0};
					strcpy(buffer3, pt);
					friend_id = atoi(buffer3);
					if(my_id == friend_id){
							flag = 1;
					}
					pt = strtok(NULL,",");
					usleep(200000);
				}
			if(flag == 0){
					char new_sending_command[256] = {0};
					strcat(new_sending_command, "ADDFRI,");
					strcat(new_sending_command, id);
					strcat(new_sending_command,",");
					strcat(new_sending_command, bufferj);
					get(new_sending_command);
			}
			/*Creates the frame of each page*/
			strcat(bufferk,"ID#  ");
			strcat(bufferk,bufferj);
			frame = gtk_frame_new (bufferk);
			gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
			gtk_widget_set_size_request (frame, 100, 75);
			gtk_widget_show (frame);
			
			/*Makes the table for chat box, textbox, and send button*/
			table2 = gtk_table_new(8, 6, TRUE);
			gtk_container_add(GTK_CONTAINER(frame),table2);
			gtk_widget_show(table2);
		
			/*using labels as the way to store messages and to display*/
			Messages *Message = malloc(sizeof(*Message));
			text1 = gtk_label_new("blank");
			text2 = gtk_label_new("blank");
			text3 = gtk_label_new("blank");
			text4 = gtk_label_new("blank");
			text5 = gtk_label_new("blank");
			text6 = gtk_label_new("blank");
			text7 = gtk_label_new("blank");
			
			message = Message;
			
			message -> note = notebook;
			Message -> mes1 = text1;
			Message -> mes2 = text2;
			Message -> mes3 = text3;
			Message -> mes4 = text4;
			Message -> mes5 = text5;
			Message -> mes6 = text6;
			Message -> mes7 = text7;
			

			message = Message;
			
			/*DONT FORGET TO FREE THIS STRUCT AFTER*/
			button2 = gtk_button_new_with_label("close tab");
			g_signal_connect(button2, "clicked", G_CALLBACK(close_friend), Message);
			gtk_table_attach_defaults(GTK_TABLE(table2), button2, 0 , 2, 7, 8);
			
			button1 = gtk_button_new_with_label("delete friend");
			g_signal_connect(button1,"clicked",G_CALLBACK(delete_friend), Message);
			gtk_table_attach_defaults(GTK_TABLE(table2),button1,4,6,7,8);
		
			gtk_table_attach_defaults(GTK_TABLE(table2), text7, 0, 6, 0, 1);
			gtk_table_attach_defaults(GTK_TABLE(table2), text6, 0, 6, 1, 2);
			gtk_table_attach_defaults(GTK_TABLE(table2), text5, 0, 6, 2, 3);
			gtk_table_attach_defaults(GTK_TABLE(table2), text4, 0, 6, 3, 4);
			gtk_table_attach_defaults(GTK_TABLE(table2), text3, 0, 6, 4, 5);
			gtk_table_attach_defaults(GTK_TABLE(table2), text2, 0, 6, 5, 6);
			gtk_table_attach_defaults(GTK_TABLE(table2), text1, 0, 6, 6, 7);
			gtk_widget_show_all(table2);
		
			entry_box2 = gtk_entry_new();
			gtk_table_attach_defaults(GTK_TABLE(table2), entry_box2, 2, 4, 7, 8);
			g_signal_connect(GTK_ENTRY(entry_box2), "activate", G_CALLBACK(send_chat_message), Message);
			gtk_widget_show(entry_box2);
		
			gtk_widget_show(frame);
			label = gtk_label_new (receiving_command);
			gtk_notebook_append_page (GTK_NOTEBOOK(notebook), frame, label);
		}
}

int main(int argc, char *argv[]){
		GtkWidget *LogWindow;
		Messages *message;
		GtkWidget *window;
		int login;
		char command[256] = {0};
		int port = -1;
		
		sscanf(argv[2], "%d", &port);
		if(port <= 0){
				printf("Wrong Command Line argument");
				return -1;
		}

		ServerAddress.sin_family = AF_INET;
		ServerAddress.sin_port = htons(port);
		ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
		
		Window = CreateWindow(&argc, &argv);
		gtk_widget_hide(Window);
		login = create_login(&argc, &argv);
		if(login == 1){
			
		}
		//UpdateWindow();
		gtk_main();
		
		return 0;
	
}