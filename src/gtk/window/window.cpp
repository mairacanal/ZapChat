#include "window.hpp"

Window::Window()
{
    add(scrolledWindow);
    scrolledWindow.add(fixed);

    sendButton.set_label("Send");
    sendButton.signal_button_release_event().connect([&](GdkEventButton*) {
        label.set_text(Glib::ustring::compose("button clicked %1 times", ++clicked));
        return true;
    });
    fixed.add(sendButton);
    fixed.move(sendButton, 50, 50);

    label.set_text(Glib::ustring::compose("button clicked %1 times", clicked));
    fixed.add(label);
    fixed.move(label, 50, 200);

    set_title("Chatroom");
    set_default_size(200, 200);
    show_all();
}
