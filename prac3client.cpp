#include <iostream>
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") 

using namespace std;

int main() {
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;
    char buffer[1024];

    cout << "Initializing Winsock..." << endl;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        cout << "Failed. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Initialized." << endl;

    if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cout << "Could not create socket. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Socket created." << endl;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8888);

    if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        cout << "Connection failed. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Connected to server." << endl;

    const char* message = "Hello, Server!";
    send(client_socket, message, strlen(message), 0);

    int recv_size;
    if((recv_size = recv(client_socket, buffer, 1024, 0)) == SOCKET_ERROR) {
        cout << "Recv failed. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }
    buffer[recv_size] = '\0';
    cout << "Received message: " << buffer << endl;

    closesocket(client_socket);
    WSACleanup();

    return 0;
}


