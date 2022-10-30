#include "user_login.hpp"
#include <iostream>

UserLoginScreen::UserLoginScreen()
    : mainBox{Gtk::Orientation::ORIENTATION_VERTICAL}
{
    set_hierarchy();
    draw_widgets();
    show_all_children();
}

void UserLoginScreen::set_hierarchy()
{
    // Window
    add(mainFixed);

    // Fixed
    mainFixed.add(mainBox);
    mainFixed.move(mainBox, 0, 0);

    // Box
    mainBox.pack_start(userEntry, true, true, 0);
    mainBox.pack_start(sendButton, true, true, 0);
}

void UserLoginScreen::draw_widgets()
{
    // Window
    set_title("ZapChat - Login");
    set_default_size(300, 100);
    set_visible(true);
    set_can_focus(false);
    set_resizable(false);
    set_border_width(5);

    // Fixed
    mainFixed.set_size_request(300, 100);
    mainFixed.set_visible(true);
    mainFixed.set_can_focus(false);

    // Box
    mainBox.set_size_request(300, 100);
    mainBox.set_visible(true);
    mainBox.set_can_focus(false);
    mainBox.set_spacing(5);

    // Entry
    userEntry.set_size_request(300, 50);
    userEntry.set_visibility(true);
    userEntry.set_can_focus(true);
    userEntry.set_placeholder_text("Enter username");
    userEntry.set_max_length(32);

    // Button
    sendButton.set_size_request(300, 50);
    sendButton.set_label("Send");
    sendButton.set_visible(true);
    sendButton.set_can_focus(true);
    sendButton.set_focus_on_click(true);

    sendButton.signal_button_release_event().connect(
        [&](GdkEventButton *)
        {
            Glib::ustring username = this->complete_login();
            if(username != "") {
                std::cout << username << '\n';
            }
            return true;
        });
}

Glib::ustring UserLoginScreen::complete_login()
{
    // Enviar o nome do usuario para o cliente/servidor aqui!
    auto buffer = userEntry.get_buffer();
    // std::cout << buffer->get_text() << '\n';
    Glib::ustring bufferText = buffer->get_text();
    return bufferText;
}