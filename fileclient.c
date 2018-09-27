// Write a C program using TCP to implement file transfer. The client sends the file name, the server 
// checks the if the file is present, if not found, replies "Not Found" else if found, sends the content 
// of the file.

// Client File

#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>


int main()
{
    int sock, newsock, opt=1, sizeAddr, readFlag;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[1024];
    char sendBuffer[1024];

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0 ) {
        perror("Socket Creation");
        exit(EXIT_FAILURE);
    }

    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("SetSockOpt Error");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = 5600;
    serverAddr.sin_family = AF_INET;
    sizeAddr = sizeof(serverAddr);


    clientAddr.sin_addr.s_addr = INADDR_ANY;
    clientAddr.sin_port = 6600;
    clientAddr.sin_family = AF_INET;

    if(bind(sock, (struct sockaddr *)&clientAddr, sizeof(clientAddr)) < 0) {
        perror("Bind Error");
        exit(EXIT_FAILURE);
    }

    if(connect(sock, (struct sockaddr *)&serverAddr, (socklen_t)sizeAddr) < 0) {
        perror("Connect");
        exit(EXIT_FAILURE);
    }

    printf("Enter your message : ");
    fgets(sendBuffer, 1024, stdin);
    
    int k=send(sock, sendBuffer , strlen(sendBuffer), 0);
    printf("Message sent\n");
    
    if((readFlag = recv(sock, buffer, 1024, 0)) < 0 ){
        perror("Recv");
        exit(-1);
    }

    buffer[readFlag] = '\0';

    printf("File Content : %s\n", buffer);

    return 0;
}