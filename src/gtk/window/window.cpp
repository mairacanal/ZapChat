#include "window.hpp"

/**
 * @brief Constructor for window class
 *
 */
Window::Window()
    : mainTopBox{Gtk::Orientation::ORIENTATION_VERTICAL}
    , loginBox{Gtk::Orientation::ORIENTATION_VERTICAL}
    , mainBottomBox{Gtk::Orientation::ORIENTATION_HORIZONTAL}
    , dispatcher{}
    , client{}
    , clientThread{nullptr}
{
    set_login_hierarchy();
    draw_login_widgets();
    show_all_children();

    serverDispatcher.connect(
        sigc::mem_fun(*this, &Window::error_server_dialog));
}

/**
 * @brief Creates the widgets hierarchy for the login screen
 *
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
 * @brief Draws each widget, sets size and specific details
 *
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
    loginUserSendButton.set_label("Send");
    loginUserSendButton.set_visible(true);
    loginUserSendButton.set_can_focus(true);
    loginUserSendButton.set_focus_on_click(true);

    // Function that runs when the user clicks the `send` button
    loginUserSendButton.signal_button_release_event().connect(
        [&](GdkEventButton *)
        {
            // Get buffer content
            auto buffer = loginUserEntry.get_buffer();
            Glib::ustring username = buffer->get_text();

            // Username verification
            if (username != "")
            {
                // Ok
                client.set_username(username);
                this->complete_login();
            }
            else
            {
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
    m_pDialog.reset(new Gtk::MessageDialog(*this, "Enter a valid username"));
    general_error();
}

/**
 * @brief Creates and shows an error message dialog when the
 * user enters an invalid username.
 */
void Window::error_server_dialog()
{
    m_pDialog.reset(new Gtk::MessageDialog(*this, "Server is down!"));
    general_error();
}

void Window::general_error()
{
    m_pDialog->set_modal(true);
    m_pDialog->signal_response().connect(
        sigc::hide(sigc::mem_fun(*m_pDialog, &Gtk::Widget::hide)));

    m_pDialog->show();
}

/**
 * @brief When user enters a valid username the screen is redrawn
 *
 */
void Window::complete_login()
{
    // Setup window again
    clear_login_widgets();

    set_chat_hierarchy();
    draw_chat_widgets();

    sendButton.signal_clicked().connect(
        sigc::mem_fun(*this, &Window::on_send_button_clicked));

    dispatcher.connect(
        sigc::mem_fun(*this, &Window::on_notification_from_client_thread));

    clientThread = Glib::Threads::Thread::create(
        sigc::bind(sigc::mem_fun(client, &Client::run), this));

    show_all_children();
}

/**
 * @brief Clears all the login widgets that were being used.
 *
 */
void Window::clear_login_widgets()
{
    loginBox.remove(loginUserSendButton);
    loginBox.remove(loginUserEntry);

    mainFixed.remove(loginBox);
}

/**
 * @brief Setup the chat screen's widgets hierarchy
 *
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
 *
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
    entry.set_placeholder_text("Digite uma mensagem de 70 chars");
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
    //
    // Create a text buffer mark for use in update_widgets().
    auto buffer = textView.get_buffer();
    buffer->create_mark("last_line", buffer->end(), /* left_gravity= */ true);

    show_all_children();
}

/**
 * @brief Update the textview widget to recive messages
 *
 */
void Window::update_widgets()
{
    Glib::ustring message_from_client_thread{};

    client.get_message(&message_from_client_thread);

    if (message_from_client_thread != lastMessage)
    {
        auto buffer = textView.get_buffer();
        buffer->set_text(buffer->get_text() + message_from_client_thread + "\n");

        lastMessage = message_from_client_thread;

        // Scroll the last inserted line into view
        auto iter = buffer->end();
        iter.set_line_offset(0);
        auto mark = buffer->get_mark("last_line");
        buffer->move_mark(mark, iter);
        textView.scroll_to(mark);
    }
}

void Window::notify()
{
    dispatcher.emit();
}

void Window::on_notification_from_client_thread()
{
    if (clientThread && client.has_stopped())
    {
        clientThread->join();
        clientThread = nullptr;
    }
    update_widgets();
}

void Window::on_send_button_clicked()
{
    const Glib::ustring message = client.get_username() + ": " + entry.get_text();

    client.send_message(message);
    entry.set_text("");
}

void Window::server_is_down()
{
    serverDispatcher.emit();
}