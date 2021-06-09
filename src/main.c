#include <gtk/gtk.h>

typedef struct {
    GtkWidget *w_dlg_about;             // Pointer to about dialog box
} app_widgets;


int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
    // instantiate structure, allocating memory for it
    app_widgets     *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    widgets->w_dlg_about = GTK_WIDGET(gtk_builder_get_object(builder, "window_about"));

    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();
    g_slice_free(app_widgets, widgets);

    return 0;
}

// called when window is closed
void on_window_main_destroy(){
    gtk_main_quit();
}

// Help --> About
void on_about_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts){
    gtk_widget_show(app_wdgts->w_dlg_about);
}

// About dialog box Close button
void on_window_about_response(GtkDialog *dialog, gint response_id, app_widgets *app_wdgts){
    gtk_widget_hide(app_wdgts->w_dlg_about);
}