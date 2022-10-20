#pragma once

#include <gtkmm.h>

class Window : public Gtk::Window {

public:
    Window();
    virtual ~Window() = default;

private:
    Gtk::Fixed fixed;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::Button sendButton;
    Gtk::Label label;

    int clicked = 0;
};
