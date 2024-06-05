#pragma once

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <memory>

constexpr int DEFAULT_BUFLEN {512};

namespace hde 
{
    class ClientSocket
    {
        protected:
            //std::string m_port;
            //std::string m_address;
            WSADATA m_wsaData;
            addrinfo* m_result;
            addrinfo m_hints;
            SOCKET m_connectSocket;

        public:
            ClientSocket(int ipDomain,int socketType,int protocol);
            void initWSADATA();
            void getAddrInfo(std::string ipAddr, std::string port);
            void getAddrInfo(std::string port);
            void initSocketObj(addrinfo* ptr);
            void shutConnection(SOCKET socketType, int how);
            int tryConnection(addrinfo *ptr);
            int sendMsg(SOCKET socketType, const char* msg, int flags);
            int rcvMsg(SOCKET socketType, int flags);

            addrinfo* getResult() const { return this->m_result; }
            SOCKET getSocket() const { return this->m_connectSocket; }
    };

    class ServerSocket : public ClientSocket
    {
        protected:
            SOCKET m_listenSocket;
            SOCKET m_clientSocket;
        public:
            ServerSocket(int ipDomain,int socketType,int protocol);
            void initListenSocket();
            void bindSocket();
            void beginListen(int backlog);
            void acceptConnection();
            void closeSocket(SOCKET socketType);

            SOCKET getListenSocket() const { return this->m_listenSocket; }
            SOCKET getClientSocket() const { return this->m_clientSocket; }
    };
}