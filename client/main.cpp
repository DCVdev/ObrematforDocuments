#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#define DEFAULT_PORT "8080"

int main(int argc, char **argv)
{
    WSADATA wsaData;
    int make;

    struct addrinfo *result=NULL,*ptr=NULL,hints;

    SOCKET connectSocket;

    int recvbuflen = 512;
    const char* buffer = "I am sending something, receive it and send me";
    char recvbuff[512];

    char continues = 's';
    //Initialize
    make = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(make!=0){
        printf("Error: %d", make);
        return 1;
    }
    memset(&hints,0,sizeof(hints));//Clear the memory
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    //Address and port
    make = getaddrinfo(argv[1],DEFAULT_PORT,&hints,&result);

    //Create a Socket
    ptr = result;//Get parameters of hints through result
    connectSocket = socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
    // Connect to server
    make = connect(connectSocket,ptr->ai_addr,(int)ptr->ai_addrlen);
    // Manage a error
    //freeaddrinfo(result);

    do{
        //Send data
        make = send(connectSocket,buffer,(int)strlen(buffer),0);
        if (make == SOCKET_ERROR) {
            printf("send failed: %d\n", WSAGetLastError());
            closesocket(connectSocket);
            WSACleanup();
            return 1;
        }
        //Receive data
        make = recv(connectSocket,recvbuff,recvbuflen,0);
        if (make > 0)
            printf("Finally I receive something: %d\n", make);
        else if (make == 0)
            printf("Connection closed\n");
        else
            printf("receive failed: %d\n", WSAGetLastError());
        std::cout << "Do you want to continue -s/n-" << std::endl;
        std::cin >> continues;
    }while(continues == 's');
    make = shutdown(connectSocket,SD_SEND);
    closesocket(connectSocket);
    WSACleanup();

    return 0;
}
