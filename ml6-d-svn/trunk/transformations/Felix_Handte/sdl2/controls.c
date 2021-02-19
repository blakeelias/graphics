#include "globals.h"
#include "controls.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

static gint exit_cwindow(GtkWidget *widget, gpointer user_data);
static gint addpt_button_clicked(GtkWidget *widget, gpointer user_data);
static gint drawl_button_clicked(GtkWidget *widget, gpointer user_data);
static gint spher_button_clicked(GtkWidget *widget, gpointer user_data);
static gint trans_button_clicked(GtkWidget *widget, gpointer user_data);
static gint scale_button_clicked(GtkWidget *widget, gpointer user_data);
static gint rotax_button_clicked(GtkWidget *widget, gpointer user_data);
static gint rotay_button_clicked(GtkWidget *widget, gpointer user_data);
static gint rotaz_button_clicked(GtkWidget *widget, gpointer user_data);

void mode_change(int mode);

GtkWidget *cwindow;
GtkWidget *table;
GtkWidget *rotlabel;
GtkWidget *sellabel;
GtkWidget *curlabel;
GtkWidget *addptbutton;
GtkWidget *drawlbutton;
GtkWidget *spherbutton;
GtkWidget *transbutton;
GtkWidget *scalebutton;
GtkWidget *rotaxbutton;
GtkWidget *rotaybutton;
GtkWidget *rotazbutton;

void controls_init(int *argc, char ***argv){
	gtk_init(argc, argv);
	
	cwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(cwindow), "FelixDraw - Mode");
	g_signal_connect(cwindow, "destroy", G_CALLBACK(exit_cwindow), NULL);
	
	table = gtk_table_new(6, 3, 0);
	gtk_container_add(GTK_CONTAINER(cwindow), table);
	
	rotlabel = gtk_label_new("Rotations:");
	sellabel = gtk_label_new("Current Transformation:");
	curlabel = gtk_label_new("");
	gtk_table_attach_defaults(GTK_TABLE(table), rotlabel, 1, 4, 3, 4);
	gtk_table_attach_defaults(GTK_TABLE(table), sellabel, 1, 4, 5, 6);
	gtk_table_attach_defaults(GTK_TABLE(table), curlabel, 1, 4, 6, 7);
	
	addptbutton = gtk_button_new_with_label("Add Point");
	drawlbutton = gtk_button_new_with_label("Add Line");
	spherbutton = gtk_button_new_with_label("Add Sphere");
	transbutton = gtk_button_new_with_label("Translate");
	scalebutton = gtk_button_new_with_label("Scale");
	rotaxbutton = gtk_button_new_with_label("X");
	rotaybutton = gtk_button_new_with_label("Y");
	rotazbutton = gtk_button_new_with_label("Z");
	g_signal_connect(addptbutton, "clicked", G_CALLBACK(addpt_button_clicked), NULL);
	g_signal_connect(drawlbutton, "clicked", G_CALLBACK(drawl_button_clicked), NULL);
	g_signal_connect(spherbutton, "clicked", G_CALLBACK(spher_button_clicked), NULL);
	g_signal_connect(transbutton, "clicked", G_CALLBACK(trans_button_clicked), NULL);
	g_signal_connect(scalebutton, "clicked", G_CALLBACK(scale_button_clicked), NULL);
	g_signal_connect(rotaxbutton, "clicked", G_CALLBACK(rotax_button_clicked), NULL);
	g_signal_connect(rotaybutton, "clicked", G_CALLBACK(rotay_button_clicked), NULL);
	g_signal_connect(rotazbutton, "clicked", G_CALLBACK(rotaz_button_clicked), NULL);
	gtk_table_attach_defaults(GTK_TABLE(table), addptbutton, 1, 2, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(table), drawlbutton, 2, 3, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(table), spherbutton, 3, 4, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(table), transbutton, 1, 2, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(table), scalebutton, 2, 3, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(table), rotaxbutton, 1, 2, 4, 5);
	gtk_table_attach_defaults(GTK_TABLE(table), rotaybutton, 2, 3, 4, 5);
	gtk_table_attach_defaults(GTK_TABLE(table), rotazbutton, 3, 4, 4, 5);
	
	gtk_widget_show_all(cwindow);
	
	addpt_button_clicked(NULL, NULL);
}

void controls_main(void){
	if(gtk_events_pending()){
		busy = 1;
		gtk_main_iteration();
	}
}

static gint exit_cwindow(GtkWidget *widget, gpointer user_data){
	raise(SIGQUIT);
	return 0;
}

static gint addpt_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Add Point");
	mode_change(MODE_ADDPT);
	return 0;
}

static gint drawl_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Add Line");
	mode_change(MODE_DRAWL);
	return 0;
}

static gint spher_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Add Sphere");
	mode_change(MODE_SPHER);
	return 0;
}

static gint trans_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Translate");
	mode_change(MODE_TRANS);
	return 0;
}

static gint scale_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Scale");
	mode_change(MODE_SCALE);
	return 0;
}

static gint rotax_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Rotate in X");
	mode_change(MODE_ROTAX);
	return 0;
}

static gint rotay_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Rotate in Y");
	mode_change(MODE_ROTAY);
	return 0;
}

static gint rotaz_button_clicked(GtkWidget *widget, gpointer user_data){
	gtk_label_set_text(GTK_LABEL(curlabel), "Rotate in Z");
	mode_change(MODE_ROTAZ);
	return 0;
}

void mode_change(int mode){
	matrix_col_resize(is.p, 1);
	is.p->nc = 0;
	is.mode = mode;
	is.ms = 0;
}
