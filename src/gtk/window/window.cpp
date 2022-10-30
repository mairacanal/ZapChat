#include "window.hpp"

Window::Window()
    : mainTopBox { Gtk::Orientation::ORIENTATION_VERTICAL }
    , mainBottomBox { Gtk::Orientation::ORIENTATION_HORIZONTAL }
{
    set_hierarchy();
    draw_widgets();
    show_all_children();
}

void Window::set_hierarchy()
{
    // Window
    add(mainFixed);

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

    // Create a text buffer mark for use in update_widgets().
    auto buffer = textView.get_buffer();
    buffer->create_mark("last_line", buffer->end(), /* left_gravity= */ true);
}

void Window::draw_widgets()
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

    sendButton.signal_button_release_event().connect(
        [&](GdkEventButton*) {
            this->update_widgets();
            return true;
        });

    // Text View
    textView.set_right_margin(0);
    textView.set_bottom_margin(0);
}

void Window::update_widgets()
{
    auto buffer = textView.get_buffer();
    buffer->set_text(buffer->get_text() + "MENSAGEM QUE VAI SER RECEBIDA\n");

    auto iter = buffer->end();
    iter.set_line_offset(0);
    auto mark = buffer->get_mark("last_line");
    buffer->move_mark(mark, iter);
    textView.scroll_to(mark);
}
