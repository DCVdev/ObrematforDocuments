#include <winsock2.h>
#include "Employee.h"

int main(){
    WSADATA wsaData;
    SOCKET serverSocket,clientSocket;
    struct sockaddr_in server,client;
    int c;

    std::cout<<"Initializing Winsock..."<<std::endl;
    if(WSAStartup(MAKEWORD(2,2), &wsaData)!= 0){
        std::cout<<"Code Failed" << WSAGetLastError()<<std::endl;
        return 1;
    }

    if((serverSocket=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET){
        std::cout<<"Could not create socket: "<<WSAGetLastError()<<std::endl;
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr= INADDR_ANY;
    server.sin_port = htons(8808);

    if(bind(serverSocket,(struct sockaddr *)&server,sizeof(server)) == SOCKET_ERROR){
        std::cout<<"Bind failed with error code: "<<WSAGetLastError()<<std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    listen(serverSocket,3);

    std::cout << "Waiting for incoming connections..." << std::endl;
    c = sizeof(struct sockaddr_in);
    clientSocket = accept(serverSocket, (struct sockaddr *)&client, &c);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Accept failed with error code : " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connection accepted." << std::endl;
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
