#pragma once

#include <csignal>
#include <iostream>
#include <sstream>

#include "gtkmm.h"

#include "../socket/socket.hpp"

class Window;

/**
 * @brief Class of the client (user)
 * 
 */
class Client {
private:
    static constexpr int PORT = 4040;
    static constexpr int MAX_MESSAGE_SIZE = 256;

    // Synchronizes access to member data
    mutable Glib::Threads::Mutex mutex;

    // Data used by both GUI thread and client thread
    Glib::ustring message;
    Glib::ustring username;

    bool isRunning;
    Socket* socket;

    void connect_client();

    void disconnect_client();

public:
    Client();

    // Thread function
    void run(Window* caller);

    void send_message(Glib::ustring message) const;
    void get_message(Glib::ustring* message) const;

    void set_username(Glib::ustring user);
    Glib::ustring get_username() const;

    bool has_stopped() const;

    ~Client();
};
