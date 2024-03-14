#include "socket.h"
int main(){
    Server servidor(1000);
    servidor.start();

    return 0;

    /*WSADATA wsadata;
    int make, sendmake;

    struct addrinfo *result = NULL, *ptr = NULL, hints;

    SOCKET listenSocket;


    make = WSAStartup(MAKEWORD(2,2), &wsadata);
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
    std::cout << "Conectando" << std::endl;
    std::vector<SOCKET> clientSockets;
    while (true){
         std::cout << "Conectado" << std::endl;
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket != INVALID_SOCKET) {
             clientSockets.push_back(clientSocket);
        }
        for(auto& socket : clientSockets){
            char recvbuff[512];
            ZeroMemory(recvbuff, 512);
            make = recv(socket,recvbuff,512,0);
            if(make>0){
                printf("I receive : %s", recvbuff);
                sendmake = send(socket,recvbuff,make,0);
            }
            else{
                std::cout << "Desconecto" << std::endl;
                printf("Socket_error: %d\n", WSAGetLastError());
                closesocket(socket);
                socket = INVALID_SOCKET;
            }
        }
        for (int i = clientSockets.size() - 1; i >= 0; --i) {
            if (clientSockets[i] == INVALID_SOCKET) {
                closesocket(clientSockets[i]);
                clientSockets.erase(clientSockets.begin() + i);
            }
        }
    }//Fin del bucle while(true)
    std::cout << "Close the socket" << std::endl;
    closesocket(listenSocket);
    WSACleanup();
    return 0;*/
}
