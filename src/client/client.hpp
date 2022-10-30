#pragma once

#include <csignal>
#include <iostream>
#include <sstream>

#include "gtkmm.h"

#include "../socket/socket.hpp"

class Window;

class Client {
private:
    // Synchronizes access to member data
    mutable Glib::Threads::Mutex mutex;

    // Data used by both GUI thread and client thread
    Glib::ustring message;

    int port;
    bool isRunning;
    std::string user;
    Socket* socket;

public:
    int maxMessageSize;

    Client(int port, int maxMessageSize, std::string user);

    void Connect(char* message);
    void Disconnect();

    // Thread function
    void run(Window* caller);
    void send_message(Glib::ustring message) const;
    void get_message(Glib::ustring* message) const;
    bool has_stopped() const;

    ~Client();
};
