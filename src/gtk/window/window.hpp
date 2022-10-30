#pragma once

#include <gtkmm/application.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/fixed.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <gtkmm/window.h>

class Window : public Gtk::Window {

public:
    Window();
    virtual ~Window() = default;

private:
    void set_hierarchy();
    void draw_widgets();
    void update_widgets();

    Gtk::Fixed mainFixed;
    Gtk::Box mainTopBox, mainBottomBox;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TextView textView;
    Gtk::Button sendButton;
    Gtk::Entry entry;
};
