#include"stdafx.h"
#include <iostream>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<tchar.h>
#include<string>

using namespace std;
class message
{
    SOCKET clientSocket;
    public:
        int recieve(SOCKET client_socket);
        int sendmessage(SOCKET client_socket);
};
int main()
{
    cout << "-------CLIENT-------" << endl;
    SOCKET clientSocket;
    int port = 55555;
    WSADATA wsadata;
    message m;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsadata);
    if (wsaerr != 0)
    {
        cout << "winsock dll not found" << endl;
        return 0;
    }
    else
    {
        cout << "winsock dll found" << endl;
        cout << "status" << wsadata.szSystemStatus << endl;
    }
    cout << "====setting up socket====" << endl;
    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        cout << "error in socket()" << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
        cout << "socket() is running" << endl;
    cout << "====connecting client to server====" << endl;
    sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_port = htons(port);
    InetPton(AF_INET, _T("127.0.0.1"), &client.sin_addr.s_addr);
    if (connect(clientSocket, (SOCKADDR*)&client, sizeof(client)) == SOCKET_ERROR)
    {
        cout << "client failed to connect" << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
    {
        cout << "client is connected to server" << endl;
        cout << "client and server can now start sending and recieving messages"<<endl;
    }

    cout << "start messaging" << endl;
    cout << "enter close to stop messaging" << endl;
    cout << "1. send message" << endl;
    cout << "2.recieve message" << endl;
    cout << "0. exit" << endl;
    while (1) {
        cout << "enter your option" << endl;
        char choice[100];

        cin >> choice;
        send(clientSocket, choice, 100, 0);
        if (int(choice) == 1) {
            m.sendmessage(clientSocket);
        }
        else if (int(choice) == 2) {
            m.recieve(clientSocket);
        }
        else if (int(choice) == 0) {
            system("pause");
        }
        else
            cout << "invalid" << endl;
    }
    WSACleanup();
   
                                
}
int message::sendmessage(SOCKET clientsocket)
{
        char x[100];
        cout << "\nEnter Message: ";
        cin.getline(x, 100);
        int count = send(clientsocket, x, 100, 0);
        if (count > 0)
            cout << "your message is sent" << endl;
        else
            WSACleanup();
    return 0;
}
int message::recieve(SOCKET clientSocket) {
    char x[100];
    int count = recv(clientSocket, x, 100, 0);
    if (count > 0)
        cout << "message recieved:" << x << endl;
    else
        WSACleanup();
    return 0;
}
