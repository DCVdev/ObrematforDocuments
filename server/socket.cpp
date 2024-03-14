#include "socket.h"

Server::Server(int port) : port(port), listeningSocket(INVALID_SOCKET){
        WSADATA wsadata;
        int make = WSAStartup(MAKEWORD(2,2), &wsadata);
        if(make!=0){
            std::cerr << "No se pudo iniciar Winsock" << make << std::endl;
            exit(1);
        }
}
Server::~Server(){
    for(auto& socket : clientSockets){
            closesocket(socket);
        }
        closesocket(listeningSocket);
        WSACleanup();
}
void Server::start(){
    listeningSocket = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
        if(listeningSocket == INVALID_SOCKET){
            std::cerr << "Error en el socket " << WSAGetLastError() << std::endl;
            WSACleanup();
            exit(2);
        }
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(port);
        hint.sin_addr.S_un.S_addr = INADDR_ANY;

        if(bind(listeningSocket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR){
            std::cerr << "Link error" << WSAGetLastError() << std::endl;
            closesocket(listeningSocket);
            WSACleanup();
            exit(3);
        }

        if(listen(listeningSocket, SOMAXCONN) == SOCKET_ERROR){
            std::cerr << "Link error" << WSAGetLastError() << std::endl;
            closesocket(listeningSocket);
            WSACleanup();
            exit(4);
        }

        while(true){
            SOCKET clientSocket = accept(listeningSocket, nullptr, nullptr);
            if(clientSocket != INVALID_SOCKET){
                clientSockets.push_back(clientSocket);
            }

            for(auto& socket : clientSockets){
                char recvbuff[1024];
                ZeroMemory(recvbuff,1024);

                int receive = recv(socket, recvbuff, 1024, 0);
                if(receive > 0){
                    int sendbuff = send(socket, recvbuff, 1024, 0);
                    std::cout << "Envie cosas" <<  std::endl;
                }
                else{
                    std::cout << "Error al recibir" << std::endl;
                    closesocket(socket);
                    socket = INVALID_SOCKET;
                }
            }
            clientSockets.erase(clientSockets.begin(), clientSockets.end());
        }
}
