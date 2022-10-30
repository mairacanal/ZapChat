#include <gtkmm.h>
#include "gtk/window/window.hpp"
#include "client/client.hpp"

int main(int argc, char* argv[])
{   
    auto application = Gtk::Application::create(argc, argv);

    Window window;
    Client* cl;

    /* cl = Client::GetInstance(4040, 256, "127.0.0.1", "Teste"); */
    /* cl->Run(); */

    return application->run(window);
}
