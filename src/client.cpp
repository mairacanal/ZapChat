#include <gtkmm.h>

#include "gtk/window/window.hpp"

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.chatroom");
    return app->make_window_and_run<Window>(argc, argv);
}
