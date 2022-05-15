#include "chat_irc.h"

int main () {
    SOCKET sock;
    struct sockaddr_in server;
    pthread_t dataRecv;
    pthread_t sendData;
    int connected = 1;

    initConnectionToServer(&sock, server);

    while (connected) {
        pthread_create(&dataRecv, NULL, getRemoteServerData, (void*)&sock);

        connected = sendUserInputToServer(sock, server, MESSAGE_LENGTH);

        pthread_join(dataRecv, NULL);
    }

    close(sock);

    return 0;
}