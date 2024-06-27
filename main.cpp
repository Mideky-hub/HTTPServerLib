#include "src/tcp_server.hh"

#define PORT 8080

int main() {
    tcp_server server("localhost", PORT);
    return 0;
}