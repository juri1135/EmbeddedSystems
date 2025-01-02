#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SIZE 1024

void receiveFile(int sockfd)
{
    char buffer[SIZE] = {0};

    while(1) {
        // recv func's return val is the number of btyes received
        int size=recv(sockfd,buffer,sizeof(buffer),0);
        if(size<=0) {
            close(sockfd);
            return;
        }

        printf("[RECEIVED] %s", buffer);
        bzero(buffer, SIZE);
    }
}

int main()
{
    int port = 8080;
    int ret,addr;

    int serverSocket,lis;
    struct sockaddr_in clientAddress;
    
    // 현대차_B_06_03 p.7
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0) {
        perror("[Error] in socket");
        exit(1);
    }
    printf("[STARTING] TCP File Server started.\n");
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_port = port;
    clientAddress.sin_addr.s_addr = INADDR_ANY;

    addr=bind(serverSocket, (struct sockaddr*)&clientAddress, sizeof(clientAddress));
    if(addr < 0){
        perror("[Error] in binding");
        exit(1);
    }

    lis=listen(serverSocket,SIZE);
    if(listen<0){
        perror("[Error] in listening");
        exit(1);
    }
    socklen_t addrSize = sizeof(clientAddress);
    // ret is a file descriptor for a new socket
    ret= accept(serverSocket, (struct sockaddr*)&clientAddress, &addrSize);
    if(ret < 0) {
        perror("[Error] in Connecting");
        exit(1);
    }
     
    

    
    receiveFile(ret);
    printf("\n[CLOSING] Closing the server.\n");
    close(ret);
    close(serverSocket);
    return 0;
}