#pragma once

#include "gtkmm.h"

#include "../socket/socket.hpp"

class Window;

/**
 * @brief Class of the Client (user)
 */
class Client {
private:
    // Port to instanciate a socket
    static constexpr int PORT = 4040;

    // Maximum message size allowed
    static constexpr int MAX_MESSAGE_SIZE = 256;

    // Synchronizes access to member data
    mutable Glib::Threads::Mutex mutex;

    // Data used by both GUI thread and client thread
    Glib::ustring message;
    Glib::ustring username;

    bool isRunning;
    Socket* socket;

    void connect_client();

public:
    Client();

    // Thread function
    void run(Window* caller);

    // Manage messages
    void send_message(Glib::ustring message) const;
    void get_message(Glib::ustring* message) const;

    // Manage username
    void set_username(Glib::ustring user);
    Glib::ustring get_username() const;

    void disconnect_client();
    bool has_stopped() const;

    ~Client();
};
