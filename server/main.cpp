#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <vector>
//#include <fstream>
#include "user.h"
//#include "user.h"
//#include "treat_file.h"
#define DEFAULT_PORT "8080"
int main(){
    WSADATA wsadata;
    int make, sendmake;

    struct addrinfo *result = NULL, *ptr = NULL, hints;

    SOCKET listenSocket, clientSocket;

    char recvbuff[512];
    int recvbuflen = 512;

    make = WSAStartup(MAKEWORD(2,2), &wsadata);
    //sendmake = WSAStartup(MAKEWORD(2,2),&wsadata);
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    make = getaddrinfo(NULL,DEFAULT_PORT,&hints,&result);

    listenSocket = socket(result->ai_family,result->ai_socktype,result->ai_protocol);

    make = bind(listenSocket,result->ai_addr,result->ai_addrlen);
    freeaddrinfo(result);

    if(listen(listenSocket,SOMAXCONN) == SOCKET_ERROR){
        printf( "Listen failed with error: %d\n", WSAGetLastError() );
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    clientSocket = accept(listenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        printf("accept failed: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    do{
        make = recv(clientSocket,recvbuff,recvbuflen,0);
        if(make>0){
            printf("I receive : %s", recvbuff);
            sendmake = send(clientSocket,recvbuff,make,0);
        }
        else{
            printf("recv failed: %d\n", WSAGetLastError());
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }
    }while(make>0);
    return 0;
}
