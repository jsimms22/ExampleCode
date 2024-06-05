#include "CustomSocket.hpp"

hde::ClientSocket::ClientSocket(int ipDomain, int socketType, int protocol)
{
    this->initWSADATA();

    ZeroMemory(&m_hints,sizeof(m_hints));
    this->m_hints.ai_family = ipDomain; // AF_INET for IPv4, AF_NET6 for IPv6, AF_UNSPEC for both (fails more easily)
    this->m_hints.ai_socktype = socketType; // SOCK_STREAM, stream socket needed for TCP
    this->m_hints.ai_protocol = protocol; // IPPROTO_TCP

    this->m_connectSocket = INVALID_SOCKET;
    this->m_result = NULL;
}

void hde::ClientSocket::initWSADATA()
{
    int iResult = WSAStartup(MAKEWORD(2,2), &this->m_wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed with error: " << iResult << std::endl;
        throw 1;
    }
}

void hde::ClientSocket::getAddrInfo(std::string ipAddr, std::string port)
{
    int iResult = getaddrinfo(ipAddr.c_str(),port.c_str(),&this->m_hints,&this->m_result);
    if (iResult != 0) {
        std::cout << "getaddrinfo failed: " << iResult << std::endl;
        WSACleanup(); // terminates the use of WS2_32 DLL
        throw 1;
    }
}

void hde::ClientSocket::getAddrInfo(std::string port)
{
    int iResult = getaddrinfo(NULL,port.c_str(),&this->m_hints,&this->m_result);
    if (iResult != 0) {
        std::cout << "getaddrinfo failed: " << iResult << std::endl;
        WSACleanup(); // terminates the use of WS2_32 DLL
        throw 1;
    }
}

void hde::ClientSocket::initSocketObj(addrinfo* ptr)
{
    this->m_connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (this->m_connectSocket == INVALID_SOCKET) {
        std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(this->m_result);
        WSACleanup(); // terminates the use of WS2_32 DLL
        throw 1;
    }
}

void hde::ClientSocket::shutConnection(SOCKET socketType, int how)
{
    int iResult = shutdown(socketType, how);
    if (iResult == SOCKET_ERROR) {
        std::cout << "shutdown failed with error: " << WSAGetLastError() << std::endl;
        closesocket(socketType);
        WSACleanup();
        throw 1;
    }
}

int hde::ClientSocket::tryConnection(addrinfo* ptr)
{
    hde::ClientSocket::initSocketObj(ptr);

    int iResult = connect(this->m_connectSocket, 
                          ptr->ai_addr, 
                          static_cast<int>(ptr->ai_addrlen));
    if (iResult == SOCKET_ERROR) {
        closesocket(this->m_connectSocket);
        this->m_connectSocket = INVALID_SOCKET;
    }
    return iResult;
}

int hde::ClientSocket::sendMsg(SOCKET socketType, const char* msg, int flags)
{
    int iResult = send(socketType, 
                       msg, 
                       static_cast<int>(strlen(msg)), 
                       flags);
    if (iResult == SOCKET_ERROR) {
        std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
        closesocket(socketType);
        WSACleanup();
    }
    return iResult; // returns number of bytes sent or error code
}

int hde::ClientSocket::rcvMsg(SOCKET socketType, int flags)
{
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult;

    iResult = recv(socketType, recvbuf, recvbuflen, flags);

    return iResult;
}

hde::ServerSocket::ServerSocket(int ipDomain, int socketType, int protocol)
    :ClientSocket{ipDomain, socketType, protocol} // set base class constructor to ours since no default set
{
    this->m_hints.ai_flags = AI_PASSIVE;

    this->m_listenSocket = INVALID_SOCKET;
    this->m_clientSocket = INVALID_SOCKET;
}

void hde::ServerSocket::initListenSocket()
{
    this->m_listenSocket = socket(this->m_result->ai_family, 
                                  this->m_result->ai_socktype, 
                                  this->m_result->ai_protocol);
    if (this->m_listenSocket == INVALID_SOCKET) {
        std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(this->m_result);
        WSACleanup(); // terminates the use of WS2_32 DLL
        throw 1;
    }
}

void hde::ServerSocket::bindSocket()
{
    int iResult = bind(this->m_listenSocket, 
                       this->m_result->ai_addr, 
                       static_cast<int>(this->m_result->ai_addrlen));
    if (iResult == SOCKET_ERROR) {
        std::cout << "bind failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(this->m_result);
        closesocket(m_listenSocket);
        WSACleanup();
        throw 1;
    }
}

void hde::ServerSocket::beginListen(int backlog)
{
    int iResult = listen(this->m_listenSocket, backlog);
    if (iResult == SOCKET_ERROR) {
        std::cout << "listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(m_listenSocket);
        WSACleanup();
        throw 1;
    }
}

void hde::ServerSocket::acceptConnection()
{
    this->m_clientSocket = accept(this->m_listenSocket, NULL, NULL);
    if (this->m_clientSocket == INVALID_SOCKET) {
        std::cout << "accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(this->m_listenSocket);
        WSACleanup();
        throw 1;
    }
}

void hde::ServerSocket::closeSocket(SOCKET socketType)
{
    closesocket(socketType);
}