#include"stdafx.h"
#include <iostream>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<tchar.h>
#include<string>

using namespace std;
int main()
{
    cout << "-------CLIENT-------" << endl;
    SOCKET clientSocket;
    int port = 55555;
    WSADATA wsadata;
    int wsaerr,a;
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
    char x[100];
    do {
        char x[100];

        cout << "\nEnter Message: ";
        cin.getline(x, 100);
        int count = send(clientSocket, x, 100, 0);
        if (count > 0)
            cout << "your message is sent" << endl;
        else
            WSACleanup();
        a= strcmp(x, "exit");
    } while (a != 0);
    system("pause");
    return 0;
}
