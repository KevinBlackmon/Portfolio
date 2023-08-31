
#include "Client.h"
#include "Server.h"

int main()
{
	int choice;
	std::string ipAdress = "";
	int port = 0;
	bool active = true;

	do
	{
		printf("Would you like to Create a Server or Client?\n");
		printf("1> Server\n");
		printf("2> Client\n");
		std::cin >> choice;
	} while (choice != 1 && choice != 2);

	if (choice == 1)
	{
		//Server
		printf("Enter a port number: ");
		std::cin >> port;
		ServerInit(port);
		Server_Update(active);
		Server_Stop();
	}
	else 
	{
		//Client
		printf("Enter a port number: ");
		std::cin >> port;
		printf("\nEnter a ip address: ");
		std::cin >> ipAdress;
		ClientInit(port, (char*)ipAdress.c_str());
		
		SetUserName();

		ClientUpdate();
		
		Client_Stop();
	}

	return WSACleanup();
}

