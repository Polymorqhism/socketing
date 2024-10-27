#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(12609);
  server_address.sin_addr.s_addr = INADDR_ANY;

  int binding = bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

  if(binding < 0) { std::cout << "couldnt bind" << std::endl; close(server_socket); };
  int listening = listen(server_socket, 1);
  
  if(listening < 0) { std::cout << "couldnt listen" << std::endl; close(server_socket); };

  
  while (true) {
    int client_socket = accept(server_socket, nullptr, nullptr);

    if(client_socket < 0) { std::cout << "couldnt accept" << std::endl; continue;} else { std::cout << "client omg" << std::endl;};
    while(true) {
        char buffer[1024] = {0};
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

        if (bytes_received <= 0) {
            break;
        }

        if (buffer[0] != '\0') {
            std::cout << buffer << std::endl;
            const char *reply = "received by server"; 
            send(client_socket, reply, strlen(reply), 0);
            memset(buffer, 0, sizeof(buffer));
            continue;
        }
    }
  }

}
