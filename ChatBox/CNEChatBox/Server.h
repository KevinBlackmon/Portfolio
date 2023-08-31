#pragma once
#include "defines.h"

SOCKET listenSocket;
SOCKET AcceptSocket;

fd_set Masterset;
fd_set Readyset;

void ServerInit(uint16_t port)
{
	WSADATA wsadata;
	WSAStartup(WINSOCK_VERSION, &wsadata);

	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
	{
		printf("Socket is not created");
		return;
	}

	sockaddr_in listen_in;
	listen_in.sin_family = AF_INET;
	listen_in.sin_addr.S_un.S_addr = INADDR_ANY;
	listen_in.sin_port = htons(port);

	int result = bind(listenSocket, (SOCKADDR*)&listen_in, sizeof(listen_in));
	if (result == SOCKET_ERROR)
	{
		printf("Binding is incorrect");
		return;
	}

	result = listen(listenSocket, 5);
	if (result == SOCKET_ERROR)
	{
		printf("There is a listen error");
		return;
	}



	FD_ZERO(&Masterset);
	FD_ZERO(&Readyset);
	FD_SET(listenSocket, &Masterset);


}






int Server_tcp_recv_whole(SOCKET s, char* buf, int len)
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

int Server_tcp_send_whole(SOCKET skSocket, const char* data, uint16_t length)
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


void ServerSend(std::string sendBuffer)
{
	int iResult = send(AcceptSocket, sendBuffer.c_str(), (int)strlen(sendBuffer.c_str()), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		WSACleanup();
		return;
	}
}

void ServerRead(SOCKET socket)
{
	int iResult = 0;
	int size = 0;
	iResult = Server_tcp_recv_whole(socket, (char*)&size, 1);
	if (iResult == SOCKET_ERROR || iResult == 0)
	{
		printf("Connection closed\n");
		return;
	}
	else if (iResult != 1)
	{
		printf("recv failed: %d\n", WSAGetLastError());
		return;
	}

	std::string input;
	input.resize(size);
	iResult = Server_tcp_recv_whole(socket, (char*)input.c_str(), input.length()+1);
	if (iResult == SOCKET_ERROR)
	{
		printf("Connection closed\n");
		return;
	}
	printf(input.c_str());
	printf("\n");
}

void Server_Update(bool active)
{
	while (active)
	{
		Readyset = Masterset;

		int readyFD = select(0, &Readyset, NULL, NULL, NULL);
		for (size_t i = 0; i < readyFD; i++)
		{
			if (Readyset.fd_array[i] == listenSocket)
			{
				if (FD_ISSET(Readyset.fd_array[i], &Readyset))
				{
					SOCKET tempSocket = accept(listenSocket, NULL, NULL);
					if (tempSocket == INVALID_SOCKET)
					{
						printf("There was a connection error\n");
						return;
					}
					else
					{
						printf("Client conneted correctly\n");
						FD_SET(tempSocket, &Masterset);
					}
				}
			}
			else
			{
				//Message stuff
				ServerRead(Readyset.fd_array[i]);
			}
		}
	}
}


void Server_Stop()
{
	shutdown(listenSocket, SD_BOTH);
	closesocket(listenSocket);

	shutdown(AcceptSocket, SD_BOTH);
	closesocket(AcceptSocket);
}

