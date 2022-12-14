/**
 * @file window.cpp
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

#include "window.hpp"

/**
 * @brief Constructor for Window class
 */
Window::Window()
    : mainTopBox { Gtk::Orientation::ORIENTATION_VERTICAL }
    , loginBox { Gtk::Orientation::ORIENTATION_VERTICAL }
    , mainBottomBox { Gtk::Orientation::ORIENTATION_HORIZONTAL }
    , dispatcher {}
    , client {}
    , clientThread { nullptr }
{
    set_login_hierarchy();
    draw_login_widgets();
    show_all_children();

    // Signal for Error dialogs
    serverDispatcher.connect(sigc::mem_fun(*this, &Window::error_server_dialog));
}

/**
 * @brief Creates the widgets hierarchy for the login screen
 */
void Window::set_login_hierarchy()
{
    // Window
    add(mainFixed);

    // Fixed
    mainFixed.add(loginBox);
    mainFixed.move(loginBox, 0, 0);

    // Box
    loginBox.pack_start(loginUserEntry, true, true, 0);
    loginBox.pack_start(loginUserSendButton, true, true, 0);
}

/**
 * @brief Draws each widget, sets its size and specific details
 */
void Window::draw_login_widgets()
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
    loginBox.set_size_request(300, 100);
    loginBox.set_visible(true);
    loginBox.set_can_focus(false);
    loginBox.set_spacing(5);

    // Entry
    loginUserEntry.set_size_request(300, 50);
    loginUserEntry.set_visibility(true);
    loginUserEntry.set_can_focus(true);
    loginUserEntry.set_placeholder_text("Enter username");
    loginUserEntry.set_max_length(32);

    // Button
    loginUserSendButton.set_size_request(300, 50);
    loginUserSendButton.set_label("Login");
    loginUserSendButton.set_visible(true);
    loginUserSendButton.set_can_focus(true);
    loginUserSendButton.set_focus_on_click(true);

    // Function that runs when the user clicks the `Login` button
    loginUserSendButton.signal_button_release_event().connect(
        [&](GdkEventButton*) {
            // Get buffer content
            auto buffer = loginUserEntry.get_buffer();
            Glib::ustring username = buffer->get_text();

            // Username verification
            if (username != "") {
                // Ok
                client.set_username(username);
                this->complete_login();
            } else {
                // Error
                error_login_dialog();
                loginUserEntry.error_bell();
            }
            return true;
        });
}

/**
 * @brief Creates and shows an error message dialog when the
 * user enters an invalid username.
 */
void Window::error_login_dialog()
{
    pDialog.reset(new Gtk::MessageDialog(*this, "Enter a valid username"));
    general_error();
}

/**
 * @brief Creates and shows an error message dialog when the
 * user enters an invalid username.
 */
void Window::error_server_dialog()
{
    pDialog.reset(new Gtk::MessageDialog(*this, "Waiting for server..."));
    general_error();
}

/**
 * @brief Runs the necessary commands to display any message dialog.
 */
void Window::general_error()
{
    pDialog->set_modal(true);
    pDialog->signal_response().connect(
        sigc::hide(sigc::mem_fun(*pDialog, &Gtk::Widget::hide)));

    pDialog->show();
}

/**
 * @brief When user enters a valid username, the screen is redrawn to the chat
 */
void Window::complete_login()
{
    // Setup window again
    clear_login_widgets();

    set_chat_hierarchy();
    draw_chat_widgets();

    // Signal Handler for the Send button
    sendButton.signal_clicked().connect(
        sigc::mem_fun(*this, &Window::on_send_button_clicked));

    // Dispatcher Handler to connect the Client backend to the GUI
    dispatcher.connect(
        sigc::mem_fun(*this, &Window::on_notification_from_client_thread));

    // Signal Handler to kill the window
    signal_delete_event().connect(sigc::mem_fun(this, &Window::kill_window));

    // Create thread for the Client backend
    clientThread = Glib::Threads::Thread::create(
        sigc::bind(sigc::mem_fun(client, &Client::run), this));

    show_all_children();
}

/**
 * @brief Clears all the login widgets that were being used.
 */
void Window::clear_login_widgets()
{
    loginBox.remove(loginUserSendButton);
    loginBox.remove(loginUserEntry);

    mainFixed.remove(loginBox);
}

/**
 * @brief Setup the chat screen's widgets hierarchy
 */
void Window::set_chat_hierarchy()
{
    // Fixed
    mainFixed.add(mainTopBox);
    mainFixed.add(mainBottomBox);
    mainFixed.move(mainTopBox, 0, 0);
    mainFixed.move(mainBottomBox, 0, 530);

    // Bottom box
    mainBottomBox.add(entry);
    mainBottomBox.add(sendButton);

    // Top box
    mainTopBox.pack_start(scrolledWindow, true, true, 0);

    // Scrolled
    textView.set_editable(false);
    scrolledWindow.add(textView);

    // Only show the scrollbars when they are necessary.
    scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolledWindow.set_hexpand(true);
    scrolledWindow.set_vexpand(true);
}

/**
 * @brief Draws the chat screen's widgets
 */
void Window::draw_chat_widgets()
{
    // Window
    set_title("ZapChat");
    set_default_size(410, 600);
    set_visible(true);
    set_can_focus(false);
    set_resizable(false);
    set_border_width(5);

    // Fixed
    mainFixed.set_size_request(430, 600);
    mainFixed.set_visible(true);
    mainFixed.set_can_focus(false);

    // Scrolled Window
    scrolledWindow.set_size_request(430, 525);
    scrolledWindow.set_visible(true);

    // Top Box
    mainTopBox.set_visible(true);
    mainTopBox.set_can_focus(false);

    // Bottom Box
    mainBottomBox.set_size_request(400, 70);
    mainBottomBox.set_visible(true);
    mainBottomBox.set_can_focus(false);
    mainBottomBox.set_spacing(5);

    // Entry
    entry.set_size_request(360, 70);
    entry.set_visibility(true);
    entry.set_can_focus(true);
    entry.set_placeholder_text("Maximum length of 70 characters");
    entry.set_max_length(70);

    // Send Button
    sendButton.set_size_request(40, 70);
    sendButton.set_label("Send");
    sendButton.set_visible(true);
    sendButton.set_can_focus(true);
    sendButton.set_focus_on_click(true);

    // Text View
    textView.set_right_margin(0);
    textView.set_bottom_margin(0);

    textView.set_pixels_above_lines(2);
    textView.set_pixels_below_lines(2);
    textView.set_pixels_inside_wrap(2);
    textView.set_wrap_mode(Gtk::WrapMode::WRAP_WORD_CHAR);

    // Create a text buffer mark for use in update_widgets().
    auto buffer = textView.get_buffer();
    buffer->create_mark("last_line", buffer->end(), /* left_gravity= */ true);

    show_all_children();
}

/**
 * @brief Update the textView widget to display the new messages
 */
void Window::update_widgets()
{
    Glib::ustring message_from_client_thread {};

    client.get_message(&message_from_client_thread);

    auto buffer = textView.get_buffer();
    buffer->set_text(buffer->get_text() + message_from_client_thread + "\n");

    // Scroll the last inserted line into view
    auto iter = buffer->end();
    iter.set_line_offset(0);
    auto mark = buffer->get_mark("last_line");
    buffer->move_mark(mark, iter);
    textView.scroll_to(mark);
}

/**
 * @brief Public function to emit a signal when a new message is received
 */
void Window::notify()
{
    dispatcher.emit();
}

/**
 * @brief Notifies that a message came from the server and update the widgets
 */
void Window::on_notification_from_client_thread()
{
    if (clientThread && client.has_stopped()) {
        clientThread->join();
        clientThread = nullptr;
    }
    update_widgets();
}

/**
 * @brief Sends a message (if exists) to the server.
 */
void Window::on_send_button_clicked()
{
    if (entry.get_text() != "") {
        client.send_message(client.get_username() + ": " + entry.get_text());
        entry.set_text("");
    }
}

/**
 * @brief Public function to emit if server is down
 */
void Window::server_is_down()
{
    serverDispatcher.emit();
}

/**
 * @brief Disconnects client from the server and kills the client process
 */
bool Window::kill_window(GdkEventAny* event)
{
    client.disconnect_client();
    exit(0);
}
