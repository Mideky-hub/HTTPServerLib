#ifndef TCP_SERVER_HH
#define TCP_SERVER_HH

// Local libraries
#include "logging.hh"
#include "socket_addr.hh"

// Third-party libraries
#include <winsock.h>
#if defined(_WIN32)
    void handle_error_winsock(errno_t err) {
        switch(err){
            case WSASYSNOTREADY:
                sys::exit(EXIT_FAILURE, "WSAStartup failed: Network subsystem is unavailable.");
                break;
            case WSAVERNOTSUPPORTED:
                sys::exit(EXIT_FAILURE, "WSAStartup failed: The version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation.");
                break;
            case WSAEINPROGRESS:
                sys::exit(EXIT_FAILURE, "WSAStartup failed: A blocking Windows Sockets 1.1 operation is in progress.");
                break;
            case WSAEPROCLIM:
                sys::exit(EXIT_FAILURE, "WSAStartup failed: A limit on the number of tasks supported by the Windows Sockets implementation has been reached.");
                break;
            case WSAEFAULT:
                sys::exit(EXIT_FAILURE, "WSAStartup failed: The lpWSAData parameter is not a valid pointer.");
                break;
            default:
                break;
        }
    }
#endif

// Standard libraries
#include <iostream>
#include <string>
#include <memory>
#include <cstdint>

class tcp_server {
private:
    SOCKET m_socket;
    SOCKET mn_socket; 
    uint16_t m_port;
    LPWSADATA WSAData;
    std::string m_addr; 
public:

    tcp_server(std::string m_addr, short m_port) : m_addr(m_addr), m_port(m_port){
        this->start_server();
    }

    ~tcp_server() {
        sys::log(logging::LOG_INFO, "Server shutting down...");
        delete this->WSAData;
        closesocket(this->m_socket);
        closesocket(this->mn_socket);
        #if defined(_WIN32)
            WSACleanup();
        #endif
        sys::log(logging::LOG_INFO, "Server shut down");
        exit(EXIT_SUCCESS);
    }

    int start_server();
    void bind_socket(socket_addr_in& m_addr_in);
    void start_listener();
    int accept_connection();
};

void tcp_server::bind_socket(socket_addr_in& m_addr_in){
    sys::log(logging::LOG_DEBUG, "Binding socket to address");
    errno_t err = bind(this->m_socket, (sockaddr*) &m_addr_in, sizeof(m_addr_in));
    if(err == SOCKET_ERROR){
        perror("Failed to bind socket");
    }
    sys::log(logging::LOG_DEBUG, "Socket bound to address");
}

void tcp_server::start_listener(){
    sys::log(logging::LOG_DEBUG, "Starting listener...");
    errno_t err = listen(this->m_socket, SOMAXCONN);
    if(err == SOCKET_ERROR) {
        perror("Failed to start listener");
    }
    sys::log(logging::LOG_DEBUG, "Listening on socket at " + this->m_addr + ":" + std::to_string(this->m_port));
}

int tcp_server::accept_connection() {
    sys::log(logging::LOG_DEBUG, "Accepting connection...");
    this->mn_socket = accept(this->m_socket, NULL, NULL);
    errno_t err = this->mn_socket;
    if(err == INVALID_SOCKET) {
        perror("Failed to accept connection");
    }
    sys::log(logging::LOG_DEBUG, "Connection accepted");
    return EXIT_SUCCESS;
}

int tcp_server::start_server() {
    WSACleanup(); // Clean up the WSAData in case it was already initialized
    sys::log(logging::LOG_INFO, "Starting server...");

    #if defined(_WIN32)
        sys::log(logging::LOG_DEBUG, "Windows detected");
        this->WSAData = new WSADATA;
        sys::log(logging::LOG_DEBUG, "WSAData created");
        errno_t err = WSAStartup(MAKEWORD(2, 0), this->WSAData);
        if (err != 0) {
            sys::log(logging::LOG_ERROR, "WSAStartup failed");
            handle_error_winsock(err);
        }      
        sys::log(logging::LOG_DEBUG, "WSAStartup initialized");
    #endif

    this->m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(this->m_socket == INVALID_SOCKET) {
        sys::exit(EXIT_FAILURE, "Failed to create socket.");
    }
    sys::log(logging::LOG_DEBUG, "Socket created");

    socket_addr_in m_addr_in(inet_addr(this->m_addr.c_str()), htons(this->m_port));
    sys::log(logging::LOG_DEBUG, "Socket address created");

    int opt = 1;
    if(setsockopt(this->m_socket, SOL_SOCKET, SO_REUSEADDR, (char*) &opt, sizeof(opt)) == SOCKET_ERROR) {
        sys::exit(EXIT_FAILURE, "Failed to set socket options.");
    }
    sys::log(logging::LOG_DEBUG, "Socket options set");

    this->bind_socket(m_addr_in);
    this->start_listener();
    this->accept_connection();

    sys::log(logging::LOG_INFO, "Server started on " + this->m_addr + ":" + std::to_string(this->m_port));


    return 0;
}

#endif // TCP_SERVER_HH