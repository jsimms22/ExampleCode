#include "Networking/CustomSocket.hpp"

// const std::string IP {"127.0.0.1"};
const std::string PORT {"27015"};

int main()
{
    int iResult = SOCKET_ERROR;
    // Initialize Winsock
    hde::ServerSocket server{AF_INET, SOCK_STREAM, IPPROTO_TCP};
    
    // Resolve the server address and port
    server.getAddrInfo(PORT);
    
    // set up listening socket
    server.initListenSocket();

    // bind listening socket
    server.bindSocket();

    freeaddrinfo(server.getResult());

    // begin listening
    server.beginListen(SOMAXCONN);

    // accept client
    server.acceptConnection();

    // No longer need server socket - unless wanting to accept additional clients
    server.closeSocket(server.getListenSocket());
    
    // Receive until the peer shuts down the connection
    do {

        iResult = server.rcvMsg(server.getClientSocket(), 0);
        if (iResult > 0) {
            std::cout << "Bytes received: " << iResult << std::endl;

            // Echo the buffer back to the sender
            int iSendResult = server.sendMsg(server.getClientSocket(), "hello client", 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(server.getClientSocket());
                WSACleanup();
                return 1;
            }
            std::cout << "Bytes sent: " << iSendResult << std::endl;
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else  {
            std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
            closesocket(server.getClientSocket());
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done
    server.shutConnection(server.getClientSocket(), SD_SEND);

    // cleanup
    server.closeSocket(server.getClientSocket());
    WSACleanup();

    return 0;
}