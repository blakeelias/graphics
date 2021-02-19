#include "controls.h"

#include <stdlib.h>
#include <unistd.h>
#include "SDL.h"
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

static gint exit_c_window(GtkWidget *widget, gpointer user_data);
static gint drawl_button_clicked(GtkWidget *widget, gpointer user_data);
static gint trans_button_clicked(GtkWidget *widget, gpointer user_data);
static gint scale_button_clicked(GtkWidget *widget, gpointer user_data);
static gint rotax_button_clicked(GtkWidget *widget, gpointer user_data);
static gint rotay_button_clicked(GtkWidget *widget, gpointer user_data);
static gint rotaz_button_clicked(GtkWidget *widget, gpointer user_data);

GtkWidget *cwindow;
GtkWidget *table;
GtkWidget *rotlabel;
GtkWidget *sellabel;
GtkWidget *curlabel;
GtkWidget *drawlbutton;
GtkWidget *transbutton;
GtkWidget *scalebutton;
GtkWidget *rotaxbutton;
GtkWidget *rotaybutton;
GtkWidget *rotazbutton;

void initControls(void){
	cwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(cwindow), "FelixDraw - Mode");
	g_signal_connect(cwindow, "destroy", G_CALLBACK(exit_c_window), NULL);
	
	table = gtk_table_new(5, 3, 0);
	gtk_container_add(GTK_CONTAINER(cwindow), table);
	
	rotlabel = gtk_label_new("Rotations:");
	sellabel = gtk_label_new("Current Transformation:");
	curlabel = gtk_label_new("");
	gtk_table_attach_defaults(GTK_TABLE(table), rotlabel, 1, 4, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(table), sellabel, 1, 4, 4, 5);
	gtk_table_attach_defaults(GTK_TABLE(table), curlabel, 1, 4, 5, 6);
	
	drawlbutton = gtk_button_new_with_label("Add Line");
	transbutton = gtk_button_new_with_label("Translate");
	scalebutton = gtk_button_new_with_label("Scale");
	rotaxbutton = gtk_button_new_with_label("X");
	rotaybutton = gtk_button_new_with_label("Y");
	rotazbutton = gtk_button_new_with_label("Z");
	g_signal_connect(drawlbutton, "clicked", G_CALLBACK(drawl_button_clicked), NULL);
	g_signal_connect(transbutton, "clicked", G_CALLBACK(trans_button_clicked), NULL);
	g_signal_connect(scalebutton, "clicked", G_CALLBACK(scale_button_clicked), NULL);
	g_signal_connect(rotaxbutton, "clicked", G_CALLBACK(rotax_button_clicked), NULL);
	g_signal_connect(rotaybutton, "clicked", G_CALLBACK(rotay_button_clicked), NULL);
	g_signal_connect(rotazbutton, "clicked", G_CALLBACK(rotaz_button_clicked), NULL);
	gtk_table_attach_defaults(GTK_TABLE(table), drawlbutton, 1, 2, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(table), transbutton, 2, 3, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(table), scalebutton, 3, 4, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(table), rotaxbutton, 1, 2, 3, 4);
	gtk_table_attach_defaults(GTK_TABLE(table), rotaybutton, 2, 3, 3, 4);
	gtk_table_attach_defaults(GTK_TABLE(table), rotazbutton, 3, 4, 3, 4);
	
	//g_signal_connect(
	
	gtk_widget_show_all(cwindow);
}

static gint exit_c_window(GtkWidget *widget, gpointer user_data){
	raise(SIGQUIT);
	return 0;
}

static gint drawl_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Add Line");
	return 0;
}

static gint trans_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Translate");
	return 0;
}

static gint scale_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Scale");
	return 0;
}

static gint rotax_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Rotate in X");
	return 0;
}

static gint rotay_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Rotate in Y");
	return 0;
}

static gint rotaz_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Rotate in Z");
	return 0;
}
