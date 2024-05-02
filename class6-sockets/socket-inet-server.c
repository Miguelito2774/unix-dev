#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CONNECTIONS 5
#define MESSAGE_SIZE 256

int main(int argc, char** argv) {

    int server_socket_fd, client_socket_fd;

    server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket_fd == -1) {
        perror("Error at socket init");
        return 1;
    }


    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(9292);

    int bind_status = bind(server_socket_fd, 
            (struct sockaddr*)&server_addr, 
                sizeof(server_addr));

    if (bind_status == -1) {
        perror("Error at bind");
        return 2;
    }

    int listen_status = listen(server_socket_fd, MAX_CONNECTIONS); 
    if (listen_status == -1) {
        perror("Error at listening");
        return 3;
    }

    struct sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);
    client_socket_fd = accept(server_socket_fd, 
            (struct sockaddr*)&client_addr, 
                (socklen_t * )&client_addr_size);

    if (client_socket_fd == -1) {
        perror("Error accepting request");
        return 4;
    }

    char buffer[MESSAGE_SIZE];
    int read_status = read(client_socket_fd, &buffer, MESSAGE_SIZE);
    if (read_status == -1) {
        perror("Error reading request");
        return 5;
    }

    printf("MEssage from client: %s\n", buffer);

    //Revisar como responde un servidor HTTP y en ves del Ok deberías responder algo similar
    int write_status = write(client_socket_fd, "Ok", 2);
    if (write_status == -1) {
        perror("Error at response");
        return 6;
    }

    close(client_socket_fd);
    close(server_socket_fd);
 
    return 0;
}