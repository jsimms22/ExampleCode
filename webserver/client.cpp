#include "Networking/CustomSocket.hpp"

const std::string IP {"127.0.0.1"};
const std::string PORT {"27015"};

int main()
{
    addrinfo *ptr;
    int iResult = SOCKET_ERROR;
    // Initialize Winsock
    hde::ClientSocket client{AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP};
    // Resolve the server address and port
    client.getAddrInfo(IP, PORT);

    // Attempt to connect to an address until one succeeds
    for(ptr = client.getResult(); ptr != NULL ;ptr=ptr->ai_next) {
        // Create a SOCKET for connecting to server
        // Connect to server
        iResult = client.tryConnection(ptr);
        if (iResult != 0) {
            std::cout << "something bad happened" << std::endl;
            continue;
        }
        break;
    }

    freeaddrinfo(ptr);

    if (client.getSocket() == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    iResult = client.sendMsg(client.getSocket(), "hello server", 0);
    std::cout << "Bytes sent: " << iResult << std::endl;

    // shutdown the connection since no more data will be sent
    client.shutConnection(client.getSocket(), SD_SEND);

    // Receive until the peer closes the connection
    do {
        iResult = client.rcvMsg(client.getSocket(), 0);
        if ( iResult > 0 )
            std::cout << "Bytes received: " << iResult << std::endl;
        else if ( iResult == 0 )
            std::cout << "Connection closed\n";
        else
            std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;

    } while( iResult > 0 );
    
    // cleanup
    closesocket(client.getSocket());
    WSACleanup();

    return 0;
}