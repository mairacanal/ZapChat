#pragma once

#include <gtkmm/window.h>
#include <gtkmm/application.h>
#include <gtkmm/fixed.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/frame.h>
#include <gtkmm/textview.h>

class Window : public Gtk::Window {

public:
    Window();
    virtual ~Window() = default;
    void set_hierarchy();
    void draw_widgets();
    void update_widgets();

private:
    Gtk::Fixed main_fixed;
    Gtk::Box main_top_box, main_bottom_box;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TextView text_view;
    Gtk::Button sendButton;
    Gtk::Entry entry;
};
