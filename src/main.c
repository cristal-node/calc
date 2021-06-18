#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    GtkWidget *w_dlg_about;             // Pointer to about dialog box
    GtkTextBuffer *textbuffer_main;
    GtkTextBuffer *textbuffer_secondary;
} app_widgets;

typedef struct {
    char p1[256];
    char p2[256];
}string;

// typedef char marray[];

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
    widgets->textbuffer_main = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textbuffer1"));
    widgets->textbuffer_secondary = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textbuffer2"));

    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();
    g_slice_free(app_widgets, widgets);

    return 0;
}

// called when window is closed
void on_window_main_destroy(){gtk_main_quit();}

// Help --> About
void on_about_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts){
    gtk_widget_show(app_wdgts->w_dlg_about);}

// About dialog box Close button
void on_window_about_response(GtkDialog *dialog, gint response_id, app_widgets *app_wdgts){
    gtk_widget_hide(app_wdgts->w_dlg_about);}

void clear(GtkButton *button, app_widgets *app_wdgts){
    GtkTextIter start;
    GtkTextIter end;
    gtk_text_buffer_get_start_iter (app_wdgts->textbuffer_main, &start);
    gtk_text_buffer_get_end_iter (app_wdgts->textbuffer_main, &end);
    gchar *text = gtk_text_buffer_get_text (app_wdgts->textbuffer_main, &start, &end, FALSE);
    // Clear the text from window "Close the file"
    gtk_text_buffer_set_text(app_wdgts->textbuffer_main, "", -1);
    gtk_text_buffer_set_text(app_wdgts->textbuffer_secondary, text, -1);
}
void on_0_clicked(GtkButton *button, app_widgets *app_wdgts){
    GtkTextIter start;
    GtkTextIter end;
    gtk_text_buffer_get_start_iter(app_wdgts->textbuffer_main, &start);
    gtk_text_buffer_get_end_iter(app_wdgts->textbuffer_main, &end);
    gchar *text = gtk_text_buffer_get_text(app_wdgts->textbuffer_main, &start, &end, FALSE);

    strcat(text,"0");

    gtk_text_buffer_set_text(app_wdgts->textbuffer_main, text, -1);
}
long double ten_power(int n){
    long double a[6] = {1,10,100,1000,10000,100000};
    return a[n];
}
long double suuji(char *text){
    int a=0; // bool
    int e=0; // text position
    long double array[9];    // changable
    // long double num=atoi(text);

    // check negetive
    int n=0; // negetive boolean
    if(text[0]==0x2d){n=1;e++;}



    long double num=0;
    for (;text[e]!=0x00;e++){
        if(text[e]==0x2e){a=1;break;}
        array[e]=text[e]-'0';
    }
    for(int d=0;d<e;++d) // d is array position
    num+=array[d]*ten_power(e-(d+1));



    if(a){
        size_t i =0;
        for(;text[++e]!=0x00;i++)
        array[i]=text[e]-'0';
        for(int d=0;d<i;d++)
        num+=(array[d]/ten_power(d+1));
    }
    if(n)num*=-1;
    printf("num: %Lf\n",num);
    return num;
}
void *split(char *text, unsigned char symbol, string s){
    static char array[2][80];
    int p=0;
    for(size_t i=0;TRUE;i++){
        if(text[i]==0x00){array[p][i]=0x00;break;}
        if(text[i]==symbol){array[p][i]=0x00;p++;continue;}
        array[p][i]=text[i];
    }
    strcpy(s.p1,"test1");
    printf("p1 is:%s\n",s.p1);
    // s.p1=array[0];
    // s.p2=array[1];
    // return array;
}

// void parenthesis(char *text){}
void plus(char *text){
    // marray *d = split(text,0x2b);
    string txt;
    split(text,0x2b,txt);
    printf("p1 is:%s\n",txt.p1);
    // suuji(d[0]);
    }

void on_eq_clicked(GtkButton *button, app_widgets *app_wdgts){
    GtkTextIter start;
    GtkTextIter end;
    gtk_text_buffer_get_start_iter(app_wdgts->textbuffer_main, &start);
    gtk_text_buffer_get_end_iter(app_wdgts->textbuffer_main, &end);
    gchar *text = gtk_text_buffer_get_text(app_wdgts->textbuffer_main, &start, &end, FALSE);

    plus(text);
    // suuji(text);
/* 
    size_t i = 0;
    while (TRUE)
    {
        if(text[i++]==0x00)break;
    }
 */    
}