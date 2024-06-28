#include "src/tcp_server.hh"

#define PORT 8080

int main() {
    tcp_server server("127.0.0.1", PORT);
    return 0;
}