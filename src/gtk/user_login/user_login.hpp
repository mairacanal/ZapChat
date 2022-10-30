#pragma once

#include <gtkmm/application.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/fixed.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <gtkmm/window.h>

class UserLoginScreen : public Gtk::Window {

public:
    UserLoginScreen();
    virtual ~UserLoginScreen() = default;

private:
    void set_hierarchy();
    void draw_widgets();
    Glib::ustring complete_login();

    Gtk::Fixed mainFixed;
    Gtk::Box mainBox;
    Gtk::Entry userEntry;
    Gtk::Button sendButton;
};