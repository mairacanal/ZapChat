#include "gtk/window.hpp"
#include <gtkmm/application.h>

/**
 * @brief Main function for the client
 *
 */
int main(int argc, char* argv[])
{
    auto application = Gtk::Application::create(argc, argv);
    Window window;

    return application->run(window);
}
