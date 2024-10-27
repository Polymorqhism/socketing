#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


int main() {
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in server_address;
  server_address.sin_port = htons(12609);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;

  int connection = connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address));
  if(connection < 0) { std::cout << "error connectioning" << std::endl; close(client_socket); return 1;};

  while(true) {
    char message[1024];

    scanf("%s", message);

    int sending = send(client_socket, message, strlen(message), 0);

    if(sending < 0) { std::cout << "error sendinging" << std::endl; };


    char buffer[1024] = {0};

    recv(client_socket, buffer, sizeof(buffer), 0);

    std::cout << buffer << std::endl;

  }
}
