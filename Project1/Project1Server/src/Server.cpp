#include "Server.h"

Server::Server(int PORT, bool BroadcastPublically) //Port = port to broadcast on. BroadcastPublically = false if server is not open to the public (people outside of your router), true = server is open to everyone (assumes that the port is properly forwarded on router settings)
{
	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	if (BroadcastPublically) //If server is open to public
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	else //If server is only for our router
		addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Broadcast locally
	addr.sin_port = htons(PORT); //Port
	addr.sin_family = AF_INET; //IPv4 Socket

	sListen = socket(AF_INET, SOCK_STREAM, NULL); //Create socket to listen for new connections
	if (bind(sListen, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) //Bind the address to the socket, if we fail to bind the address..
	{
		std::string ErrorMsg = "Failed to bind the address to our listening socket. Winsock Error:" + std::to_string(WSAGetLastError());
		MessageBoxA(NULL, ErrorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);\
		exit(1);
	}
	if (listen(sListen, SOMAXCONN) == SOCKET_ERROR) //Places sListen socket in a state in which it is listening for an incoming connection. Note:SOMAXCONN = Socket Oustanding Max Connections, if we fail to listen on listening socket...
	{
		std::string ErrorMsg = "Failed to listen on listening socket. Winsock Error:" + std::to_string(WSAGetLastError());
		MessageBoxA(NULL, ErrorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	server = this;
}

bool Server::ListenForNewConnection()
{
	SOCKET newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); //Accept a new connection
	if (newConnection == 0) //If accepting the client connection failed
	{
		std::cout << "Failed to accept the client's connection." << std::endl;
		return false;
	}
	else //If client connection properly accepted
	{

		std::cout << "Client Connected! ID:" << TotalConnections << std::endl;
		Connections[TotalConnections] = newConnection; 
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(TotalConnections), NULL, NULL); 
		std::string MOTD = "Welcome!";
		SendString(TotalConnections, MOTD);
		if (TotalConnections == 0) //player 1
		{	
			//if this is the first connection make them the authoritative host.
			SendPacketType(TotalConnections, P_Authority);

			//create player 1 and send data to that client
			Player playerPlayer(50, 100, 100, Color::RED);
			sendSetPlayer(TotalConnections, playerPlayer);
		}
		else if (TotalConnections == 1) //player 2
		{
			//create player 2 and send data to that client
			Player playerPlayer(50, 500, 200, Color::BLUE);
			sendSetPlayer(TotalConnections, playerPlayer);
		}
		TotalConnections += 1; //Incremenent total # of clients that have connected
		return true;
	}
}

bool Server::ProcessPacket(int ID, Packet _packettype)
{
	switch (_packettype)
	{
		case P_ChatMessage: //Packet Type: chat message
		{
			std::string Message; //string to store our message we received
			if (!GetString(ID, Message)) //Get the chat message and store it in variable: Message
				return false; //If we do not properly get the chat message, return false
							  //Next we need to send the message out to each user
			for (int i = 0; i < TotalConnections; i++)
			{
				if (i == ID) //If connection is the user who sent the message...
					continue;//Skip to the next user since there is no purpose in sending the message back to the user who sent it.
				if (!SendString(i, Message)) //Send message to connection at index i, if message fails to be sent...
				{
					std::cout << "Failed to send message from client ID: " << ID << " to client ID: " << i << std::endl;
				}
			}
			std::cout << "Processed chat message packet from user ID: " << ID << std::endl;
			break;
		}
		case P_PlayerData: //Packet type: player data
		{
			Player* player = new Player();
			if (!GetPlayer(ID, *player))
			{
				delete player;
				return false;
			}
			for (int i = 0; i < TotalConnections; i++)
			{
				if (i == ID) //If connection is the user who sent the message...
					continue;//Skip to the next user since there is no purpose in sending the message back to the user who sent it.
				if (!SendPlayer(i, *player)) //Send message to connection at index i, if message fails to be sent...
				{
					std::cout << "Failed to send player data from client ID: " << ID << " to client ID: " << i << std::endl;
				}
			}
			std::cout << "player id[" << ID << "] radius [" << player->m_radius << "]" << std::endl;
			std::cout << "	(x,y) -> (" << player->m_xPos << "," << player->m_yPos << ")" << std::endl;
			delete player;
			break;
		}
		case P_EndGame:
		{
			std::cout << "Game State = end" << std::endl;
			bool* gameState = new bool();
			if (!getEndGame(ID, *gameState))
			{
				delete gameState;
				return false;
			}
			for (int i = 0; i < TotalConnections; i++)
			{
				if (i == ID) //If connection is the user who sent the message...
					continue;//Skip to the next user since there is no purpose in sending the message back to the user who sent it.
				if (!sendEndGame(i, *gameState)) //Send message to connection at index i, if message fails to be sent...
				{
					std::cout << "Failed to send endgame data from client ID: " << ID << " to client ID: " << i << std::endl;
				}
			}
			delete gameState;
			break;
		}
		default: //If packet type is not accounted for
		{
			std::cout << "Unrecognized packet: " << _packettype << std::endl; //Display that packet was not found
			break;
		}
	}
	return true;
}

void Server::ClientHandlerThread(int ID) //ID = the index in the SOCKET Connections array
{
	Packet PacketType;
	while (true)
	{
		if (!server->GetPacketType(ID, PacketType)) //Get packet type
			break; //If there is an issue getting the packet type, exit this loop
		if (!server->ProcessPacket(ID, PacketType)) //Process packet (packet type)
			break; //If there is an issue processing the packet, exit this loop
	}
	std::cout << "Lost connection to client ID: " << ID << std::endl;
	closesocket(server->Connections[ID]);
	return;
}