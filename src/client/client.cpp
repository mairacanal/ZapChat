/**
 * @file client.cpp
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

#include "client.hpp"
#include "../gtk/window.hpp"

/**
 * @brief Construct a new Client:: Client object
 */
Client::Client()
    : username {}
    , message {}
    , mutex {}
{
}

/**
 * @brief Send a standard message when a user connects into the server
 */
void Client::connect_client()
{
    message = ">> " + username + " joined the chat! <<";
    send_message(message);
}

/**
 * @brief Send a standard message when a user disconnects the server
 */
void Client::disconnect_client()
{
    message = ">> " + username + " exited the chat! <<";
    send_message(message);
}

/**
 * @brief Destroy the Client:: Client object
 */
Client::~Client()
{
    delete socket;
}

/**
 * @brief Starts the client, connects it to the server and maintains the connection
 * by receiving messages
 * @param caller Window reference to be used by dispatchers
 */
void Client::run(Window* caller)
{
    char initialMessage[MAX_MESSAGE_SIZE];

    {
        Glib::Threads::Mutex::Lock lock(mutex);
        isRunning = true;
        this->message = "";
    }

    socket = new Socket(PORT);

    if (socket->connect() == -1) {
        caller->server_is_down();
        while (socket->connect() == -1) { }
    }

    // Read the inital message from server
    read(socket->get_fd(), initialMessage, sizeof(initialMessage));

    if (std::strcmp(initialMessage, "Connection succeed")) {
        isRunning = false;
        return;
    }

    connect_client();

    // Main comunication loop
    while (isRunning) {
        char message[MAX_MESSAGE_SIZE];
        Glib::Threads::Mutex::Lock lock(mutex);

        if (recv(socket->get_fd(), message, MAX_MESSAGE_SIZE, 0) <= 0) {
            break;
        }

        this->message = Glib::ustring { message };

        lock.release();
        caller->notify();
    }

    disconnect_client();
    isRunning = false;
}

/**
 * @brief Sends a message to the socket
 * @param message String with the message that the user has typed
 */
void Client::send_message(Glib::ustring message) const
{
    message.resize(MAX_MESSAGE_SIZE);
    send(socket->get_fd(), (const void*)message.c_str(), message.size(), 0);
    message.empty();
}

/**
 * @brief Get message from the server to the GUI
 * @param message String of the message to be displayed in the window
 */
void Client::get_message(Glib::ustring* message) const
{
    if (message)
        *message = this->message;
}

/**
 * @brief Set the user's name.
 * @param user String of the user's name.
 */
void Client::set_username(Glib::ustring user)
{
    username = user;
}

/**
 * @brief Retrives the username
 * @return Glib::ustring username.
 */
Glib::ustring Client::get_username() const
{
    return username;
}

/**
 * @brief Check if the server is still running
 * @return true if the server IS NOT running
 * @return false if the server IS running
 */
bool Client::has_stopped() const
{
    return !isRunning;
}
