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
    socket_addr_in(uint64_t addr, uint16_t port) : sin_family(AF_INET), sin_port(port), sin_addr(addr) {
        memset(sin_zero, 0, sizeof(sin_zero));
    }

    // Destructor
    ~socket_addr_in() = default;

};

void handle_error_binding_socket(errno_t err){
    switch(err){
        case EACCES:
            sys::exit(EXIT_FAILURE, "The address is protected, and the user is not the superuser.");
            break;
        case EADDRINUSE:
            sys::exit(EXIT_FAILURE, "The given address is already in use.");
            break;
        case EBADF:
            sys::exit(EXIT_FAILURE, "sockfd is not a valid file descriptor.");
            break;
        case EINVAL:
            sys::exit(EXIT_FAILURE, "The socket is already bound to an address.");
            break;
        case ENOTSOCK:
            sys::exit(EXIT_FAILURE, "The file descriptor sockfd does not refer to a socket.");
            break;
        case EADDRNOTAVAIL:
            sys::exit(EXIT_FAILURE, "A nonexistent interface was requested or the requested address was not local.");
            break;
        case EFAULT:
            sys::exit(EXIT_FAILURE, "addr points outside the user's accessible address space.");
            break;
        case ELOOP:
            sys::exit(EXIT_FAILURE, "Too many symbolic links were encountered in resolving addr.");
            break;
        case ENAMETOOLONG:
            sys::exit(EXIT_FAILURE, "addr is too long.");
            break;
        case ENOENT:
            sys::exit(EXIT_FAILURE, "A component in the directory prefix of the socket pathname does not exist.");
            break;
        case ENOMEM:
            sys::exit(EXIT_FAILURE, "Insufficient kernel memory was available.");
            break;
        case ENOTDIR:
            sys::exit(EXIT_FAILURE, "A component of the path prefix is not a directory.");
            break;
        case EROFS:
            sys::exit(EXIT_FAILURE, "The socket inode would reside on a read-only filesystem.");
            break;
        default:
            break;
    }
}
#endif // SOCKET_ADDR_HH