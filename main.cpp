#include "src/tcp_server.hh"

int main() {
    tcp_server server("127.0.0.1", 8080);
    return 0;
}