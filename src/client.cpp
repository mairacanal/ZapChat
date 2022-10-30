/**
 * @file client.cpp
 * @author Felipe de Alcântara Tomé (11800970)
 * @author Francisco Reis Nogueira (11954374)
 * @author Luiz Henrique Pereira (11918539)
 * @author Maíra de Souza Canal (11819403)
 * @author João Augusto Fernandes Barbosa (11953348)
 * @version 0.1
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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
