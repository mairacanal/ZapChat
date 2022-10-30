#pragma once

#include <gtkmm.h>
#include "../../client/client.hpp"

/**
 * @brief Main window class, it is the graphical interface for the user to use.
 * 
 */
class Window : public Gtk::Window {

public:
    Window();
    void notify();
    void server_is_down();
    void error_login_dialog();
private:
    // Signal Handler
    void on_send_button_clicked();
    void update_widgets();
    void complete_login();

    // Dispatcher Handler
    void on_notification_from_client_thread();

    void set_login_hierarchy();
    void draw_login_widgets();
    void clear_login_widgets();

    
    void set_chat_hierarchy();
    void draw_chat_widgets();

    // Member Data
    Gtk::Fixed mainFixed;
    Gtk::Box mainTopBox, mainBottomBox, loginBox;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TextView textView;
    Gtk::Button sendButton, loginUserSendButton;
    Gtk::Entry entry, loginUserEntry;

    std::unique_ptr<Gtk::MessageDialog> m_pDialog;

    Glib::Dispatcher dispatcher;
    Glib::Dispatcher serverDispatcher;
    Client client;
    Glib::Threads::Thread* clientThread;

    Glib::ustring lastMessage;
};
