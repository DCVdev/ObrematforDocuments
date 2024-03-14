#ifndef SOCKET_H
#define SOCKET_H
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
class Server{
public:
    int port;
    SOCKET listeningSocket;
    std::vector<SOCKET> clientSockets;
    //Builder
    Server(int port);

    //Destroyer
    ~Server();

    //Start
    void start();
};

#endif // SOCKET_H
