#include <gtkmm.h>
#include "gtk/window/window.hpp"
#include "./client/client.hpp"

int main(int argc, char *argv[])
{

   auto application = Gtk::Application::create(argc, argv);
   Window window;

   return application->run(window);
}
