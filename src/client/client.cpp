#include "client.hpp"
#include "../gtk/window/window.hpp"

/**
 * @brief Construct a new Client:: Client object
 * 
 */
Client::Client()
    : username { }
    , message {}
    , mutex {}
{
    socket = new Socket(PORT);
}

/**
 * @brief Sends a message when a user connects into the server
 * 
 */
void Client::connect_client()
{
    message = ">> " + username + " joined the chat! <<";
    send_message(message);
}

/**
 * @brief Sends a message when a user disconnects the server
 * 
 */
void Client::disconnect_client()
{
    message = ">> " + username + " exited the chat! <<";
    send_message(message);
}

/**
 * @brief Destroy the Client:: Client object
 * 
 */
Client::~Client()
{
    delete socket;
}

/**
 * @brief Starts the client, connects it to the server
 * 
 * @param caller Window reference to use the dispatchers
 */
void Client::run(Window* caller)
{   

    if(socket->connect() == -1){
        caller->server_is_down();
        while(socket->connect() == -1){

        }
    }

    std::cout << socket->connect();
    char initialMessage[MAX_MESSAGE_SIZE];

    {
        Glib::Threads::Mutex::Lock lock(mutex);
        isRunning = true;
        this->message = "";
    }

    
    
    // lê a mensagem inicial do servidor
    read(socket->getFd(), initialMessage, sizeof(initialMessage));

    if (std::strcmp(initialMessage, "Connection succeed")) {
        isRunning = false;
        return;
    }

    connect_client();
    caller->notify();

    // loop principal de comunicação
    while (isRunning) {
        char message[MAX_MESSAGE_SIZE];
        Glib::Threads::Mutex::Lock lock(mutex);

        if (recv(socket->getFd(), message, MAX_MESSAGE_SIZE, 0) <= 0) {
            raise(SIGTERM);
            break;
        }

        this->message = Glib::ustring { message };

        lock.release();
        caller->notify();
    }

    isRunning = false;
}

/**
 * @brief Sends a message to the socket
 * 
 * @param message String of the message that the user has typed
 */
void Client::send_message(Glib::ustring message) const
{
    message.resize(MAX_MESSAGE_SIZE);
    send(socket->getFd(), (const void*)message.c_str(), message.size(), 0);
    message.empty();
}

/**
 * @brief Recive a message from the server
 * 
 * @param message String of the message
 */
void Client::get_message(Glib::ustring* message) const
{
    if (message)
        *message = this->message;
}

/**
 * @brief Sets the user's name.
 * 
 * @param user String of the user's name.
 */
void Client::set_username(Glib::ustring user)
{
    username = user;
}

/**
 * @brief Retrives the username
 * 
 * @return Glib::ustring username.
 */
Glib::ustring Client::get_username() const
{
    return username;
}

/**
 * @brief Check if the server is still running
 * 
 * @return true if the server IS NOT running 
 * @return false if the server IS running 
 */
bool Client::has_stopped() const
{
    return !isRunning;
}
