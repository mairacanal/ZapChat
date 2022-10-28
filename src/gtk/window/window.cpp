#include "window.hpp"
#include <iostream>
#include <vector>
#include <string>

Window::Window() : main_top_box{Gtk::Orientation::ORIENTATION_VERTICAL}, main_bottom_box{Gtk::Orientation::ORIENTATION_HORIZONTAL}
{
    set_hierarchy();
    draw_widgets();
    show_all_children();
}

void Window::set_hierarchy()
{
    // Window
    add(main_fixed);

    // Fixed
    main_fixed.add(main_top_box);
    main_fixed.add(main_bottom_box);
    main_fixed.move(main_top_box, 0, 0);
    main_fixed.move(main_bottom_box, 0, 530);

    // Bottom box
    main_bottom_box.pack_start(entry, true, true, 0);
    main_bottom_box.pack_start(sendButton, true, true, 0);

    // Top box
    main_top_box.pack_start(scrolledWindow, true, true, 0);

    // Scrolled 
    scrolledWindow.add(label);
}

void Window::draw_widgets()
{
    // Window
    set_title("ZapChat");
    set_default_size(400, 600);
    set_visible(true);
    set_can_focus(false);
    set_resizable(false);
    set_border_width(0.05);

    // override_background_color(background_color, background_color,background_color,1);

    // Fixed
    main_fixed.set_size_request(400, 600);
    main_fixed.set_visible(true);
    main_fixed.set_can_focus(false);

    // Scrolled Window
    scrolledWindow.set_size_request(400, 500);
    scrolledWindow.set_visible(true);

    main_top_box.set_visible(true);
    main_top_box.set_can_focus(false);

    main_bottom_box.set_visible(true);
    main_bottom_box.set_can_focus(false);

    entry.set_size_request(360, 70);
    entry.set_visibility(true);
    entry.set_can_focus(true);
    entry.set_placeholder_text("Digite uma mensagem de 70 chars");
    entry.set_max_length(70);

    sendButton.set_size_request(40, 70);
    sendButton.set_label("Send");
    sendButton.set_visible(true);
    sendButton.set_can_focus(true);
    sendButton.set_focus_on_click(true);

    label.set_text("Testing");
}
