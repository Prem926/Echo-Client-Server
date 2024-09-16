#include <iostream>
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") 

using namespace std;

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int client_len;
    char buffer[1024];

    cout << "Initializing Winsock..." << endl;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        cout << "Failed. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Initialized." << endl;

    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cout << "Could not create socket. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Socket created." << endl;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if(bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        cout << "Bind failed. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Bind done." << endl;

    listen(server_socket, 3);

    cout << "Waiting for incoming connections..." << endl;
    client_len = sizeof(struct sockaddr_in);
    client_socket = accept(server_socket, (struct sockaddr *)&client, &client_len);
    if(client_socket == INVALID_SOCKET) {
        cout << "Accept failed. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Connection accepted." << endl;

    int recv_size;
    if((recv_size = recv(client_socket, buffer, 1024, 0)) == SOCKET_ERROR) {
        cout << "Recv failed. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }
    buffer[recv_size] = '\0';
    cout << "Received message: " << buffer << endl;

    const char* message1 = "Hi, my name is Prem Joshi , Sir Please give 10/10 :)";
    send(client_socket, message1, strlen(message1), 0);

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}