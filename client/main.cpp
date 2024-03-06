#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <vector>
//#include <fstream>
#include "user.h"
//#include "user.h"
//#include "treat_file.h"
int main(){
    WSADATA wsadata;
    int initialize;
    //std::fstream file("users.txt",std::ios::in, std::ios::out);
    std::vector<char> buffer(2);
    //Initialize Winsock winsock
    initialize = WSAStartup(MAKEWORD(2,2), &wsadata);
    if(initialize!=0){
        printf("Problem with start: %d\n", initialize);
        return 1;
    }
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listenSocket == INVALID_SOCKET){
        std::cerr << "Erro del socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    sockaddr_in service;
    //Secure for clear the memory in service
    memset(&service,0, sizeof(service));
    //Create the structure of the socket
    service.sin_family = AF_INET;
    service.sin_addr.s_addr= INADDR_ANY;
    service.sin_port = htons(8080);

    if(bind(listenSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        closesocket(listenSocket);
        std::cerr << "Error listening socket" << std::endl;
        WSACleanup();
        return 1;
    }

    if(listen(listenSocket, SOMAXCONN) == SOCKET_ERROR){
        closesocket(listenSocket);
        std::cerr << "Error listening socket" << std::endl;
        WSACleanup();
        return 1;
    }


    SOCKET clientSocket;
    sockaddr_in clientinfo;
    int clientinfosize = sizeof(clientinfo);
    /*clientSocket = accept(listenSocket, NULL,NULL);
    if (clientSocket == INVALID_SOCKET) {
    printf("accept failed: %d\n", WSAGetLastError());
    closesocket(listenSocket);
    WSACleanup();
    }*/
    clientSocket = accept(listenSocket, (sockaddr*)&clientinfo, &clientinfosize);
    if(clientSocket == INVALID_SOCKET){
        std::cerr << "Invalid socket" << std::endl;
    }
    char recvbuff[512];
    int recvbuflen = 512;
    int bytesreceived = recv(clientSocket, recvbuff,recvbuflen,0);
    for(int i = 0; i<recvbuflen;i++){
        printf("%s",recvbuff[i]);
    }
    if (bytesreceived > 0) {
    // Procesar los datos recibidos y enviar una respuesta
    std::string response = "Mensaje recibido: " + std::string(recvbuff, bytesreceived);
    send(clientSocket, response.c_str(), response.length(), 0);
}

       closesocket(clientSocket);
       WSACleanup();
       return 0;
}
