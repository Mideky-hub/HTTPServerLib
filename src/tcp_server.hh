#ifndef TCP_SERVER_HH
#define TCP_SERVER_HH

// Third-party libraries
#include <WinSock2.h>
#include <winsock.h>

// Standard libraries
#include <iostream>
#include <string>

class tcp_server {
private:
    SOCKET m_socket;
    SOCKET mn_socket; 
    short m_port;
    LPWSADATA WSAData;
    std::string m_addr; 
public:

    tcp_server(std::string m_addr, short m_port) : m_addr(m_addr), m_port(m_port){
        this->start_server();
    }

    ~tcp_server() {
        std::cout << "Server shutting down" << std::endl;
        delete this->WSAData;
        std::cout << "WSAData deleted" << std::endl;
        closesocket(this->m_socket);
        closesocket(this->mn_socket);
        std::cout << "Socket closed" << std::endl;
        #if defined(_WIN32)
            WSACleanup();
        #endif
        std::cout << "WSACleanup" << std::endl;
        exit(0);
    }

    int start_server();
};

int tcp_server::start_server() {
    std::cout << "Starting server" << std::endl;

    this->m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    this->WSAData = new WSADATA;
    
    if(this->m_socket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    std::cout << "Server started on " << this->m_addr << ":" << this->m_port << std::endl;

    return 0;
}

#endif // TCP_SERVER_HH