//Design a client server program in tcp where server handles 
//the multiple clients . In this program you have to 
//design one server and 5 clients , then all the clients can communicate with the server . OK .

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
    clientAddr.sin_port = 7500;
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

    return 0;
}