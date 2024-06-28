#ifndef SOCKET_ADDR_HH
#define SOCKET_ADDR_HH

//Local libraries
#include "logging.hh"

//Third-party libraries
#include <winsock.h>

//Standard libraries
#include <cstdint>

//Difference between sockaddr and sockaddr_in
/*
    sockaddr is a generic socket address structure that can be used to store any type of socket address. 
    sockaddr_in is a specific socket address structure used for IPv4 addresses. 
    It includes fields for the address family (AF_INET), port number, and IP address.

*/

class socket_addr_in /*IPv4 ADDR*/ {
public: // Variables
    // sin_family is the address family that the socket is going to communicate with.
    // an address family is a set of protocols that can be used to communicate between two sockets.
    // For example, AF_INET is the address family for IPv4, and AF_INET6 is the address family for IPv6.
    int16_t     sin_family; 

    // sin_port is the port number that the socket is going to communicate with.
    // The port number is used to identify the application that the socket is going to communicate with.
    // For example, port 80 is used for HTTP, and port 443 is used for HTTPS.
    uint16_t    sin_port;

    // sin_addr is the IP address that the socket is going to communicate with.
    // The IP address is used to identify the host that the socket is going to communicate with.
    uint64_t    sin_addr;

    // sin_zero is a padding field that is used to make the structure the same size as a sockaddr structure.
    // This is done so that the sockaddr_in structure can be used in functions that expect a sockaddr structure.
    uint8_t     sin_zero[8];

public: // Methods
    // Constructor
    socket_addr_in(const uint16_t PORT) : sin_family(AF_INET), sin_port(htons(PORT)), sin_addr(INADDR_ANY) {
        memset(sin_zero, 0, sizeof(sin_zero));
    }

    // Destructor
    ~socket_addr_in() = default;

};


#endif // SOCKET_ADDR_HH