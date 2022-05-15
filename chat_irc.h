#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef int SOCKET;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6969
#define MESSAGE_LENGTH 256


struct sockaddr_in server;
int connected;


void initConnectionToServer (SOCKET *sock);

void* sendUserInputToServer (void *sock);

void* getRemoteServerData (void *sock);

void handleError(char *message);


void initConnectionToServer (SOCKET *sock) {
    *sock = socket(AF_INET, SOCK_STREAM, 0);
    if (socket < 0) handleError("Error creating socket");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    int connection = connect(*sock, (struct sockaddr *)&server, sizeof(server));
    if (connection < 0) handleError("Failed to connect to remote host");
}


void* sendUserInputToServer (void* sock) {
    while (connected) {
        SOCKET sockt = *((SOCKET *)sock);

        char data[MESSAGE_LENGTH];

        printf("> "); fgets(data, MESSAGE_LENGTH, stdin);

        data[strcspn(data, "\n")] = '\0';

        if (strcmp(data, "disconnect") == 0) {
            return (void *)0;
        }

        int dataLength = strlen(data) + 1;

        sendto(sockt, data, dataLength, 0, (struct sockaddr*)&server, sizeof(server));
    }

    return (void *)1;
}


void* getRemoteServerData (void* sock) {
    while (connected) {
        SOCKET sockt = *((SOCKET *) sock);

        char incomingData[MESSAGE_LENGTH];

        memset(incomingData, 0, sizeof(incomingData));

        recv(sockt, incomingData, sizeof(incomingData), 0);

        printf("%s", incomingData);
    }

    return NULL;
}


void handleError(char *message) {
    printf("%s", message);
    exit(EXIT_FAILURE);
}