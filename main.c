#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6969
#define MESSAGE_LENGTH 256

typedef int SOCKET;

void initConnectionToServer (SOCKET *sock, struct sockaddr_in server);
int sendUserInputToServer (SOCKET sock, struct sockaddr_in server, int maxDataLength);
void handleError(char *message);

int main () {
    SOCKET sock;
    struct sockaddr_in server;
    int connected = 1;

    initConnectionToServer(&sock, server);

    while (connected) {
        connected = sendUserInputToServer(sock, server, MESSAGE_LENGTH);
    }

    close(sock);

    return 0;
}


void initConnectionToServer (SOCKET *sock, struct sockaddr_in server) {
    *sock = socket(AF_INET, SOCK_STREAM, 0);
    if (socket < 0) handleError("Error creating socket");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    int connection = connect(*sock, (struct sockaddr *)&server, sizeof(server));
    if (connection < 0) handleError("Failed to connect to remote host");
}


int sendUserInputToServer (SOCKET sock, struct sockaddr_in server, int maxDataLength) {
    char data[maxDataLength];

    printf("> "); fgets(data, maxDataLength, stdin);

    data[strcspn(data, "\n")] = '\0';

    if (strcmp(data, "disconnect") == 0) {
        return 0;
    }

    int dataLength = strlen(data) + 1;

    sendto(sock, data, dataLength, 0, (struct sockaddr*)&server, sizeof(server));

    return 1;
}


void handleError(char *message) {
    printf("%s", message);
    exit(EXIT_FAILURE);
}