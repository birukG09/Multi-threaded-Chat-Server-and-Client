#include <iostream>
#include <thread>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>

void receive_messages(int sock) {
    char buffer[1024];
    while (true) {
        ssize_t bytes_received = recv(sock, buffer, sizeof(buffer)-1, 0);
        if (bytes_received <= 0) break;
        buffer[bytes_received] = '\0';
        std::cout << "Message: " << buffer << std::endl;
    }
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed\n";
        return 1;
    }

    std::thread(receive_messages, sock).detach();

    std::string input;
    while (true) {
        std::getline(std::cin, input);
        send(sock, input.c_str(), input.size(), 0);
        if (input == "exit") break;
    }

    close(sock);
    return 0;
}
