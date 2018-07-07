#include <iostream>
#include <winsock2.h>
#include <string>
#include <Windows.h>

#pragma comment(lib,"ws2_32.lib")
using namespace std;

class Server
{
public:
	Server(int);
	~Server();
	int WSA_Startup();
	int SocketCreation();
	int bindSocket();
	void listenToPort();
	int ProvideServic();
private:
	WSADATA WsaDat;
	SOCKET Socket;
	SOCKADDR_IN serverInf;
	SOCKET TempSock;
	u_long iMode;
	char buffer[1024];
	int port;
};

Server::Server(int port)
{
	this->port = port;

	WSA_Startup();
	SocketCreation();
	bindSocket();
	listenToPort();
	ProvideServic();
}

Server::~Server()
{
}

int Server::WSA_Startup()
{
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
	{
		cout << "WSA Initialization failed!" << endl;
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	cout << "WSA Initialization ..." << endl;
}

int Server::SocketCreation()
{
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		cout << "Socket creation failed." << endl;
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	cout << "Socket creation ..." << endl;
}

int Server::bindSocket()
{
	serverInf.sin_family = AF_INET;
	serverInf.sin_addr.s_addr = INADDR_ANY;
	serverInf.sin_port = htons(port);

	if (bind(Socket, (SOCKADDR*)(&serverInf), sizeof(serverInf)) == SOCKET_ERROR)
	{
		cout << "Unable to bind socket!" << endl;
		WSACleanup();
		system("PAUSE");
		return 0;
	}
	cout << "bind socket ..." << endl;
}

void Server::listenToPort()
{
	listen(Socket, 5);

	TempSock = SOCKET_ERROR;

	while (TempSock == SOCKET_ERROR)
	{
		listen(Socket, 5);
		cout << "Waiting for incoming connections..." << endl;
		TempSock = accept(Socket, NULL, NULL);
	}
}

int Server::ProvideServic()
{
	// If iMode!=0, non-blocking mode is enabled.
	iMode = 1;
	ioctlsocket(Socket, FIONBIO, &iMode);

	Socket = TempSock;
	cout << "Client connected!" << endl << endl;

	TXT_File file;
	file.Load_Account();

	StrProcessing inpoutprocess(Socket, file);

	// Main loop
	for (;;)
	{
		int nError = WSAGetLastError();

		if (nError != WSAEWOULDBLOCK && nError != 0 && nError != 183)
		{
			cout << "Winsock error code: " << nError << endl;
			cout << "Client disconnected!" << endl;

			// Shutdown our socket
			shutdown(Socket, SD_SEND);

			// Close our socket entirely
			closesocket(Socket);

			break;
		}

		memset(buffer, 0, 1023);
		int iReciveResult = recv(Socket, buffer, 1024, 0);

		while (iReciveResult < 1 && nError != WSAEWOULDBLOCK && nError != 0)
		{
			iReciveResult = recv(Socket, buffer, 1024, 0);
			int nError = WSAGetLastError();
		}

		inpoutprocess.inputprocessing(buffer);
		cout << buffer << endl;
	}

	WSACleanup();
	//system("PAUSE");
	return 0;
}