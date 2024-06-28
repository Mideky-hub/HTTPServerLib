#include "src/tcp_server.hh"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <address> " << "<port>" << std::endl;
        return 1;
    }

    std::unique_ptr<tcp_server> server = 
        std::make_unique<tcp_server>((std::string) argv[1], (uint16_t) std::stoi(argv[2]));
        
    return 0;
}