// Write a C program using TCP to implement file transfer. The client sends the file name, the server 
// checks the if the file is present, if not found, replies "Not Found" else if found, sends the content 
// of the file.

// Server File

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

    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientAddr.sin_port = htons(6600);
    clientAddr.sin_family = AF_INET;
    sizeAddr = sizeof(clientAddr);

    if(bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind Error");
        exit(EXIT_FAILURE);
    }

    if(listen(sock, 5) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

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
    printf("readFlag %d\n", readFlag);

    char fileContent[1024], ch;
    int i = 0;
    FILE * fp;
    if((fp = fopen(buffer, "r")) == NULL) {
        char * notfound = "File doesnt exist";
        int k=send(newsock, notfound , strlen(notfound), 0);
        printf("Send to file not found %d\n", k);
    }else {
        while((ch = fgetc(fp)) != EOF) {
            fileContent[i++] = ch;
        }
        fileContent[i] = '\0';

        for(int t=0;t<strlen(fileContent);t++) {
            printf("%c", fileContent[t]);
        }

        int k=send(newsock, fileContent , strlen(fileContent), 0);
        printf("Send to : %d\n", k);
        fclose(fp);
    }

    return 0;
}