#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MESSAGE_SIZE 256

int main(int argc, char** argv) {

    int server_socket_fd;

    server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);    

    if (server_socket_fd == -1) {
        perror("Error at socket init");
        return 1;
    }

    struct sockaddr_in server_socket_addr;
    server_socket_addr.sin_family = AF_INET;
    server_socket_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_socket_addr.sin_port = htons(9292);
    
    int connection_status = connect(server_socket_fd, 
            (struct sockaddr*)&server_socket_addr, 
                sizeof(server_socket_addr));
    
    if (connection_status == -1) {
        perror("Error at connection");
        return 2;
    }

    int write_status = write(server_socket_fd, "Hi", 2);
    if (write_status == -1) {
        perror("Error at write");
        return 3;
    }

    char response[2];
    int read_status = read(server_socket_fd, response, 2);

    if (read_status == -1) {
        perror("Error at reading response.");
        return 4;
    }

    printf("Response from server: %s\n", response);

    close(server_socket_fd);


    return 0;
}
