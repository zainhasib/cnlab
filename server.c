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

    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = 5600;
    serverAddr.sin_family = AF_INET;

    /*
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientAddr.sin_port = htons(6600);
    clientAddr.sin_family = AF_INET;
    */
    sizeAddr = sizeof(clientAddr); 

    if(bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind Error");
        exit(EXIT_FAILURE);
    }

    if(listen(sock, 5) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    while(1) {
        if((newsock = accept(sock, (struct sockaddr *)&clientAddr, (socklen_t *)&sizeAddr))   < 0) {
            perror("Accept");
            exit(EXIT_FAILURE);
        }
        
        if((readFlag = recv(newsock, buffer, 1024, 0)) < 0 ){
            perror("Recv");
            exit(-1);
        }

        buffer[readFlag-1] = '\0';

        printf("Recieved Message : %s\n", buffer);
    }

    return 0;
}