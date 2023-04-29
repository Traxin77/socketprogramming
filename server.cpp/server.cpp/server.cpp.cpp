
#include "stdafx.h"
#include<winsock2.h>
#include"iostream"
#include<ws2tcpip.h>
#include<tchar.h>
using namespace std;

int main(int argc,char* argv[])
{
    SOCKET serverSocket, acceptSocket;
    cout << "------SERVER------";
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
    cout << "Setting up socket" << endl;
    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        cout << "error in socket()" << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
        cout << "socket() is running" << endl;
    cout << "Binding the ip address" << endl;
    sockaddr_in s1;
    s1.sin_family = AF_INET;
    s1.sin_port = htons(port);//convert 16 bit to tcp network byte order
    s1.sin_addr.s_addr = INADDR_ANY;
    InetPton(AF_INET,_T("127.0.0.1"),&s1.sin_addr.s_addr);

    if (bind(serverSocket, (SOCKADDR*)&s1, sizeof(s1)) == SOCKET_ERROR)
    {   cout<<"binding error"<<WSAGetLastError << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else
    {
        cout << "binding done" << endl;
    }
    cout <<"Initiate listen" << endl;
    if (listen(serverSocket, 1) == SOCKET_ERROR)
        cout << "error in listening of socket" << WSAGetLastError() << endl;
    else
        cout << "listening succesfull waiting for connection" << endl;
    
    cout << "Accepting connection from client" << endl;
    acceptSocket = accept(serverSocket,NULL,NULL);
    if (acceptSocket == INVALID_SOCKET)
    {
        cout << "accept failed" << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    }
    cout << "connection accepted" << endl;
    cout << "server and client are connected"<<endl;
    char x[100];
    do {
        int count = recv(acceptSocket, x, 100, 0);
        if (count > 0)
            cout << "message recieved:" << x << endl;
        else
            WSACleanup();
        a = strcmp(x, "exit");
    } while (a!= 0);
    return 0;
}

