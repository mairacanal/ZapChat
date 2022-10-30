#pragma once

#include "../client/client.hpp"
#include <gtkmm.h>

/**
 * @brief Main window class, it is the graphical interface for the user to use.
 */
class Window : public Gtk::Window {

public:
    Window();

    void notify();
    void server_is_down();

private:
    // Signal Handlers
    void on_send_button_clicked();
    bool kill_window(GdkEventAny* event);

    // Dispatcher Handler
    void on_notification_from_client_thread();

    void update_widgets();
    void complete_login();

    void set_login_hierarchy();
    void draw_login_widgets();
    void clear_login_widgets();

    void set_chat_hierarchy();
    void draw_chat_widgets();

    // Error dialog
    void error_login_dialog();
    void error_server_dialog();
    void general_error();

    // Member Data
    Gtk::Fixed mainFixed;
    Gtk::Box mainTopBox, mainBottomBox, loginBox;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TextView textView;
    Gtk::Button sendButton, loginUserSendButton;
    Gtk::Entry entry, loginUserEntry;

    std::unique_ptr<Gtk::MessageDialog> pDialog;

    Glib::Dispatcher dispatcher;
    Glib::Dispatcher serverDispatcher;
    Glib::Threads::Thread* clientThread;

    Client client;
};
