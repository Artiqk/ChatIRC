#include "chat_irc.h"

int main () {
    SOCKET sock;
    pthread_t dataRecv;
    pthread_t sendData;
    connected = 1;

    initConnectionToServer(&sock);

    pthread_create(&dataRecv, NULL, getRemoteServerData, (void*)&sock);
    pthread_create(&sendData, NULL, sendUserInputToServer, (void*)&sock);

    pthread_join(dataRecv, NULL);
    pthread_join(sendData, (void *)&connected);
    

    close(sock);

    return 0;
}