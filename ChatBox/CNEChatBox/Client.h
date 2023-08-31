#pragma once
#include "defines.h"

SOCKET Clientsocket;
std::string UserName;

void ClientInit(uint16_t port, char* address)
{
	WSADATA wsadata;
	WSAStartup(WINSOCK_VERSION, &wsadata);

	Clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Clientsocket == INVALID_SOCKET)
	{
		printf("DEBUG// Socket function incorrect\n");
		return;
	}
	else
		printf(" Socket function correct\n");
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	if (inet_addr(address) == INADDR_NONE)
	{
		printf("INVALID address");
		return;
	}
	serverAddr.sin_addr.S_un.S_addr = inet_addr(address);
	serverAddr.sin_port = htons(port);

	int result = connect(Clientsocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (result == SOCKET_ERROR)
	{
		printf("DEBUG// Connect function incorrect\n");
		return;
	}
	else
		printf(" Connected correct\n");
}



int Client_tcp_recv_whole(SOCKET s, char* buf, int len)
{
	int total = 0;
	do
	{
		int ret = recv(s, buf + total, len - total, 0);
		if (ret < 1)
			return ret;
		else
			total += ret;

	} while (total < len);

	return total;
}

int Client_tcp_send_whole(SOCKET skSocket, const char* data, uint16_t length)
{
	int bytesSent = 0;

	while (bytesSent < length)
	{
		int result = send(skSocket, (const char*)data + bytesSent, length - bytesSent, 0);

		if (result <= 0)
			return result;

		bytesSent += result;
	}

	return bytesSent;
}

void ClientSendMessage(SOCKET socket, const char* message)
{
	int size = (int)strlen(message);
	int iResult = Client_tcp_send_whole(socket, (char*)&size, 1);
	if (iResult == SOCKET_ERROR)
		printf("Connection closed\n");
	else if (iResult != 1)
		printf("recv failed: %d\n", WSAGetLastError());

	std::string input;
	input = message;
	iResult = Client_tcp_send_whole(socket, (char*)input.c_str(), input.length() + 1);
	if (iResult == SOCKET_ERROR)
		printf("Connection closed\n");
}


void ClientReadMessage(SOCKET socket)
{
	int iResult = 0;
	int size = 0;
	iResult = Client_tcp_recv_whole(socket, (char*)&size, 1);
	if (iResult > 0)
		printf("");
	else if (iResult == SOCKET_ERROR)
		printf("Connection closed\n");
	else
		printf("recv failed: %d\n", WSAGetLastError());

	std::string input;
	Client_tcp_recv_whole(socket, (char*)&input, (int)strlen(input.c_str()));
}

void SetUserName()
{
	printf("Enter a username: ");
	std::cin >> UserName;
}

void Commands()
{
	printf("in commands");
}

void LogMessages(const char* message)
{
	std::ofstream file;
	file.open("Log.txt", std::ios_base::in);
	if (file.is_open())
	{
		file.write(message, strlen(message));
	}
}

void ClientUpdate()
{
	while (true)
	{
		std::string input;
		std::getline(std::cin, input);
		if (input[0] == '$')
			Commands();
		if (input != "" && input[0] == '$')
		{
			input = UserName + ": " + input;
			ClientSendMessage(Clientsocket, input.c_str());
		}
	}
}


void Client_Stop()
{
	shutdown(Clientsocket, SD_BOTH);
	closesocket(Clientsocket);

}
