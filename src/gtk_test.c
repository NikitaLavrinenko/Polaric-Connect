// Include gtk
#include <gtk/gtk.h>
#include <app.h>

struct elements
{
    GtkWidget *window;
    GtkWidget *label_c_name;
    GtkWidget *label_u_name;
    GtkWidget *label_h_name;
    GtkWidget *label_psk;
    GtkWidget *label_key;
    GtkWidget *key;
    GtkWidget *psk;
    GtkWidget *u_name;
    GtkWidget *h_name;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *checkbutton;
    GtkWidget *ret_string;
    bool hide;
} typedef elements_t;

static void pass_key(GtkButton *button, gpointer *Elements)
{
    if (!((elements_t *)Elements)->hide)
    {
        gtk_widget_set_name(((elements_t *)Elements)->ret_string, "myRetLabel1");
        if (!gtk_entry_get_text_length(GTK_ENTRY(((elements_t *)Elements)->key)))
        {
            gtk_label_set_text(GTK_LABEL(((elements_t *)Elements)->ret_string), "The Key cannot be empty");
        }
        else if (!gtk_entry_get_text_length(GTK_ENTRY(((elements_t *)Elements)->u_name)))
        {
            gtk_label_set_text(GTK_LABEL(((elements_t *)Elements)->ret_string), "The Username cannot be empty");
        }
        else if (!gtk_entry_get_text_length(GTK_ENTRY(((elements_t *)Elements)->h_name)))
        {
            gtk_label_set_text(GTK_LABEL(((elements_t *)Elements)->ret_string), "The Hostname cannot be empty");
        }
        else if (!gtk_entry_get_text_length(GTK_ENTRY(((elements_t *)Elements)->psk)))
        {
            gtk_label_set_text(GTK_LABEL(((elements_t *)Elements)->ret_string), "The Password cannot be empty");
        }
        else
        {
            gtk_widget_set_name(((elements_t *)Elements)->ret_string, "myRetLabel2");
            gtk_label_set_text(GTK_LABEL(((elements_t *)Elements)->ret_string), "Check the website");
            ((elements_t *)Elements)->hide = true;
        }
    }
}

static void run_key(GtkButton *button, gpointer *Elements)
{
    char ret_string_buf[32];
    if (((elements_t *)Elements)->hide)
    {
        ((elements_t *)Elements)->hide = false;
        run_nfc_test_platform((char *)gtk_entry_get_text(GTK_ENTRY(((elements_t *)Elements)->u_name)), (char *)gtk_entry_get_text(GTK_ENTRY(((elements_t *)Elements)->h_name)), (char *)gtk_entry_get_text(GTK_ENTRY(((elements_t *)Elements)->psk)), (char *)gtk_entry_get_text(GTK_ENTRY(((elements_t *)Elements)->key)), ret_string_buf);
        gtk_widget_set_name(((elements_t *)Elements)->ret_string, "myRetLabel3");
        if (!strcmp(ret_string_buf, "success"))
        {
            gtk_label_set_text(GTK_LABEL(((elements_t *)Elements)->ret_string), "Browser session has finished");
        }
        else if (!strcmp(ret_string_buf, "ssh_error"))
        {
            gtk_label_set_text(GTK_LABEL(((elements_t *)Elements)->ret_string), "No Raspberry in local network with such parameters");
        }
        else if (!strcmp(ret_string_buf, "wrong"))
        {
            gtk_label_set_text(GTK_LABEL(((elements_t *)Elements)->ret_string), "Please load a new generated key");
        }
        else if (!strcmp(ret_string_buf, "error"))
        {
            gtk_label_set_text(GTK_LABEL(((elements_t *)Elements)->ret_string), "The platform is unavailable at the moment");
        }
        else if (!strcmp(ret_string_buf, "busy"))
        {
            gtk_label_set_text(GTK_LABEL(((elements_t *)Elements)->ret_string), "This key is already being used");
        }
        else
            gtk_label_set_text(GTK_LABEL(((elements_t *)Elements)->ret_string), "Unexpected error occurred");
    }
}

static void change_grid(GtkToggleButton *toggle_button, gpointer *Elements)
{
    gtk_entry_set_text(GTK_ENTRY(((elements_t *)Elements)->u_name), "pi");
    gtk_entry_set_text(GTK_ENTRY(((elements_t *)Elements)->h_name), "polaric");
    gtk_entry_set_text(GTK_ENTRY(((elements_t *)Elements)->psk), "polaric20");

    if ((bool)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_button)))
    {
        gtk_widget_hide(((elements_t *)Elements)->h_name);
        gtk_widget_hide(((elements_t *)Elements)->u_name);
        gtk_widget_hide(((elements_t *)Elements)->psk);
        gtk_widget_hide(((elements_t *)Elements)->label_h_name);
        gtk_widget_hide(((elements_t *)Elements)->label_u_name);
        gtk_widget_hide(((elements_t *)Elements)->label_psk);
    }
    else
    {
        gtk_widget_show(((elements_t *)Elements)->h_name);
        gtk_widget_show(((elements_t *)Elements)->u_name);
        gtk_widget_show(((elements_t *)Elements)->psk);
        gtk_widget_show(((elements_t *)Elements)->label_h_name);
        gtk_widget_show(((elements_t *)Elements)->label_u_name);
        gtk_widget_show(((elements_t *)Elements)->label_psk);
    }
}

static void on_activate(GtkApplication *app, gpointer *Elements)
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkPixbuf *icon;
    GdkScreen *screen;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "\
    #myGrid { \
        background-color:whitesmoke; \
        border-color: whitesmoke; \
    } \
    #myWindow { \
        background-color: whitesmoke; \
        border-color: whitesmoke; \
    } \
    #myLabel { \
        background-color: whitesmoke; \
        color:  black; \
        border-color: whitesmoke; \
        font-weight: 600; \
    } \
    #myEntry { \
        background-color: whitesmoke; \
        color: black; \
        border-color: #ff6b71; \
        margin-bottom: 5px; \
    } \
    #myEntry:focus{ \
        background-color: whitesmoke; \
        color: black; \
        border-color: green; \
        margin-bottom: 5px; \
    } \
    #myRetLabel1 { \
        color: red; \
        background-color: whitesmoke; \
        border-color: whitesmoke; \
        font-weight: 600; \
    } \
    #myRetLabel2 { \
        color:   green; \
        background-color: whitesmoke; \
        border-color: whitesmoke; \
        font-weight: 600; \
    } \
    #myRetLabel3 { \
        color:   orange; \
        background-color: whitesmoke; \
        border-color: whitesmoke; \
        font-weight: 600; \
    } \
    #myButton{ \
        color: whitesmoke;\
        border-color: #ff6b71; \
        background-color: #ff6b71; \
        background-image:none; \
        font-weight: 700; \
        font-size:large; \
    } \
    *:checked{ \
        color:#ff6b71; \
        border-color: #ff6b71; \
        background-image:none; \
        background-color: whitesmoke; \
    } \
    *{ border-color: #ff6b71; \
        background-image:none; \
        caret-color: #ff6b71; \
    }";
    GError *error = 0;

    gtk_css_provider_load_from_data(provider, myCssFile, strlen(myCssFile), &error);
    g_object_unref(provider);

    icon = gdk_pixbuf_new_from_file("/usr/share/pixmaps/polaric-connect.png", &error);

    // // Create a new window TOP
    ((elements_t *)Elements)->window = gtk_application_window_new(app);
    gtk_window_set_icon(GTK_WINDOW(((elements_t *)Elements)->window), icon);

    gtk_window_set_title(GTK_WINDOW(((elements_t *)Elements)->window), "Polaric Connect");
    gtk_window_set_resizable(GTK_WINDOW(((elements_t *)Elements)->window), true);
    // // Create a connect button
    ((elements_t *)Elements)->button = gtk_button_new_with_label(" Connect ");
    gtk_widget_set_name(((elements_t *)Elements)->button, "myButton");
    // // Create a check button
    ((elements_t *)Elements)->checkbutton = gtk_check_button_new();
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(((elements_t *)Elements)->checkbutton), true);
    // // lines
    ((elements_t *)Elements)->u_name = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(((elements_t *)Elements)->u_name), "pi");
    gtk_widget_set_name(((elements_t *)Elements)->u_name, "myEntry");
    ((elements_t *)Elements)->h_name = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(((elements_t *)Elements)->h_name), "polaric");
    gtk_widget_set_name(((elements_t *)Elements)->h_name, "myEntry");
    ((elements_t *)Elements)->psk = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(((elements_t *)Elements)->psk), "polaric20");
    gtk_widget_set_name(((elements_t *)Elements)->psk, "myEntry");
    ((elements_t *)Elements)->key = gtk_entry_new();
    gtk_widget_set_name(((elements_t *)Elements)->key, "myEntry");
    ((elements_t *)Elements)->ret_string = gtk_label_new("");
    gtk_label_set_width_chars(((elements_t *)Elements)->ret_string,52);
    ((elements_t *)Elements)->label_c_name = gtk_label_new(" Default Raspberry setup ");
    gtk_widget_set_name(((elements_t *)Elements)->label_c_name, "myLabel");
    ((elements_t *)Elements)->label_u_name = gtk_label_new(" Raspberry Username: ");
    gtk_widget_set_name(((elements_t *)Elements)->label_u_name, "myLabel");
    ((elements_t *)Elements)->label_h_name = gtk_label_new(" Raspberry Hostname: ");
    gtk_widget_set_name(((elements_t *)Elements)->label_h_name, "myLabel");
    ((elements_t *)Elements)->label_psk = gtk_label_new(" Raspberry Password: ");
    gtk_widget_set_name(((elements_t *)Elements)->label_psk, "myLabel");
    ((elements_t *)Elements)->label_key = gtk_label_new(" Generated Key: ");
    gtk_widget_set_name(((elements_t *)Elements)->label_key, "myLabel");
    // init start grid
    ((elements_t *)Elements)->grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(((elements_t *)Elements)->window), ((elements_t *)Elements)->grid);
    gtk_grid_attach(GTK_GRID(((elements_t *)Elements)->grid), ((elements_t *)Elements)->label_c_name, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(((elements_t *)Elements)->grid), ((elements_t *)Elements)->checkbutton, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(((elements_t *)Elements)->grid), ((elements_t *)Elements)->label_u_name, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(((elements_t *)Elements)->grid), ((elements_t *)Elements)->u_name, 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(((elements_t *)Elements)->grid), ((elements_t *)Elements)->label_h_name, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(((elements_t *)Elements)->grid), ((elements_t *)Elements)->h_name, 2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(((elements_t *)Elements)->grid), ((elements_t *)Elements)->label_psk, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(((elements_t *)Elements)->grid), ((elements_t *)Elements)->psk, 2, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(((elements_t *)Elements)->grid), ((elements_t *)Elements)->label_key, 1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(((elements_t *)Elements)->grid), ((elements_t *)Elements)->key, 2, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(((elements_t *)Elements)->grid), ((elements_t *)Elements)->ret_string, 1, 6, 2, 1);
    gtk_grid_attach(GTK_GRID(((elements_t *)Elements)->grid), ((elements_t *)Elements)->button, 1, 7, 2, 1);
    gtk_widget_show(((elements_t *)Elements)->label_c_name);
    gtk_widget_show(((elements_t *)Elements)->checkbutton);
    gtk_widget_show(((elements_t *)Elements)->label_key);
    gtk_widget_show(((elements_t *)Elements)->key);
    gtk_widget_show(((elements_t *)Elements)->ret_string);
    gtk_widget_show(((elements_t *)Elements)->button);

    gtk_widget_set_margin_top(GTK_WIDGET(((elements_t *)Elements)->grid), 10);
    gtk_widget_set_margin_end(GTK_WIDGET(((elements_t *)Elements)->grid), 10);
    gtk_widget_set_margin_start(GTK_WIDGET(((elements_t *)Elements)->grid), 10);
    gtk_widget_set_margin_bottom(GTK_WIDGET(((elements_t *)Elements)->grid), 10);
    gtk_widget_set_name(((elements_t *)Elements)->grid, "myGrid");
    gtk_widget_show(((elements_t *)Elements)->grid);
    gtk_widget_set_name(((elements_t *)Elements)->window, "myWindow");
    gtk_widget_show(((elements_t *)Elements)->window);

    // events on click buttons
    g_signal_connect(((elements_t *)Elements)->button, "pressed", G_CALLBACK(pass_key), Elements);
    g_signal_connect(((elements_t *)Elements)->button, "released", G_CALLBACK(run_key), Elements);
    g_signal_connect(((elements_t *)Elements)->checkbutton, "toggled", G_CALLBACK(change_grid), Elements);
    ((elements_t *)Elements)->hide = false;

    g_object_unref(icon);
}

int main(int argc, char *argv[])
{
    elements_t Elements;
    elements_t *pElements = &Elements;
    // Create a new application
    GtkApplication *app = gtk_application_new("com.aplication.rer", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), pElements);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
