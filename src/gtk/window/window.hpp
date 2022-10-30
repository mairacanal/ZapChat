#pragma once

#include <gtkmm/application.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/fixed.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <gtkmm/window.h>
#include <gtkmm/messagedialog.h>

/**
 * @brief Main window class, it is the graphical interface for the user to use.
 * 
 */
class Window : public Gtk::Window {

public:
    Window();
    virtual ~Window() = default;

private:
    void set_login_hierarchy();
    void draw_login_widgets();
    void clear_login_widgets();
    void error_login_dialog();
    
    void set_chat_hierarchy();
    void draw_chat_widgets();

    void update_widgets();
    void complete_login();

    Gtk::Fixed mainFixed;
    Gtk::Box mainTopBox, mainBottomBox, loginBox;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TextView textView;
    Gtk::Button sendButton, loginUserSendButton;
    Gtk::Entry entry, loginUserEntry;

    std::unique_ptr<Gtk::MessageDialog> m_pDialog;
};
