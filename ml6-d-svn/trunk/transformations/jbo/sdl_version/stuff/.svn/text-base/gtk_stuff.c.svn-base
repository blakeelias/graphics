#include "gtk_stuff.h"

#include <gtk/gtk.h>
#include <gdk/gdkx.h>

GtkWidget *window;
GtkWidget *frame;
GtkWidget *button;

static gint exit_window(GtkWidget *widget, gpointer user_data);
static gint button_press(GtkWidget *widget, gpointer user_data);

void initWindow(int *argc, char ***argv){
	gtk_init(argc, argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), WINDOW_TITLE);

	//gtk_widget_set_size_request(window, WIDTH, HEIGHT);
	//gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
	
	//gtk_widget_realize(window); //           Required to get a valid X window ID
	//gtk_main_iteration(); // Apparently also required to get a valid X window ID
	
	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), frame);
	
	button = gtk_button_new_with_label("Blah");
	gtk_fixed_put(GTK_FIXED(frame), button, 0, 0);
	
	gtk_widget_show_all(window);
	//gtk_main_iteration();
	
	g_signal_connect(window, "destroy", G_CALLBACK(exit_window), NULL);

  g_signal_connect(button, "clicked", G_CALLBACK(button_press), NULL);
}

void doGtk(void){
	while(gtk_events_pending()){
		gtk_main_iteration();
	}
}

static gint exit_window(GtkWidget *widget, gpointer user_data){
	raise(SIGQUIT);
	return 0;
}

static gint button_press(GtkWidget *widget, gpointer user_data) {
  printf("BLAH\n");
  return 0;
}
