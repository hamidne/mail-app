#include <iostream>
#include <winsock2.h>

#pragma warning(disable : 4996)
#pragma comment(lib,"ws2_32.lib")

using namespace std;

class Client
{
	friend int LoginMenu();
	friend int SendMenu();
	friend void LoadAllMail(int);
	friend void LoadMail(int, int);
public:
	Client(int);
	~Client();
	int WSA_Startup();
	int createSocket();
	int resolveHostname();
	void setupSocket();
	int connectToServer();
	void sendMessage(const char *);
	char *getBuffer() const;

private:
	WSADATA WsaDat;
	SOCKET Socket;
	struct hostent *host;
	SOCKADDR_IN SockAddr;
	u_long iMode;
	char sendStr[512];
	char buffer[1024];
	char* tempBuffer;
	int port;

};

Client::Client(int port)
{
	this->port = port;

	WSA_Startup();
	createSocket();
	resolveHostname();
	setupSocket();
	connectToServer();
}

Client::~Client()
{
	WSACleanup();
}

int Client::WSA_Startup()
{
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
	{
		cout << "Winsock error - Winsock initialization failed" << endl;
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	cout << "--> Initializing Winsock\n*** Version: " << WsaDat.szDescription << endl;
}

int Client::createSocket()
{
	// Create our socket

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		cout << "Winsock error - Socket creation Failed!" << endl;
		WSACleanup();
		system("PAUSE");
		return 0;
	}
}

int Client::resolveHostname()
{
	// Resolve IP address for hostname

	if ((host = gethostbyname("localhost")) == NULL)
	{
		cout << "Failed to resolve hostname." << endl;
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	cout << "--> Setting server address" << endl;
	cout << "--> local ip: 127.0.0.1 at port: " << port << endl;
}

void Client::setupSocket()
{
	// Setup our socket address structure

	SockAddr.sin_port = htons(port);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	cout << "--> Creating client socket object" << endl;
}

int Client::connectToServer()
{
	// Attempt to connect to server
	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
	{
		cout << "Failed to establish connection with server" << endl;
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	// If iMode!=0, non-blocking mode is enabled.
	iMode = 1;
	ioctlsocket(Socket, FIONBIO, &iMode);

	cout << "*** Client ready ***" << endl << endl;
}

void Client::sendMessage(const char *sendMessage)
{
	send(Socket, sendMessage, strlen(sendMessage), 0);

	int nError = WSAGetLastError();
	if (nError != WSAEWOULDBLOCK&&nError != 0)
	{
		cout << "Winsock error code: " << nError << endl;
		cout << "Server disconnected!" << endl;
		// Shutdown our socket
		shutdown(Socket, SD_SEND);

		// Close our socket entirely
		closesocket(Socket);
		Sleep(500);
		exit(0);
	}

	// Display message from server

	memset(buffer, 0, 1023);
	int inDataLength = recv(Socket, buffer, 1024, 0);

	while (inDataLength < 1)
	{
		inDataLength = recv(Socket, buffer, 1024, 0);
	}

	cout << buffer << endl;
}