#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <vector>
#include "Player.h"

enum Packet
{
	P_ChatMessage,
	P_Test,
	P_PlayerData,
	P_Authority,
	P_SetPlayer,
	P_EndGame
};

class Server
{
public: // Constructors/Destructor/Assignments
	Server(int PORT, bool BroadcastPublically = false);
	~Server() = default;

	Server(Server const &) = default;
	Server & operator=(Server const &) = default;

	Server(Server &&) = default;
	Server & operator=(Server &&) = default;

public: // Public Static Functions
public: // Public Member Functions
	bool ListenForNewConnection();
public: // Public Static Variables
public: // Public Member Variables
protected: // Protected Static Functions
protected: // Protected Member Functions
protected: // Protected Static Variables
protected: // Protected Member Variables
private: // Private Static Functions
	static void ClientHandlerThread(int ID);
private: // Private Member Functions
	bool sendall(int ID, char * data, int totalbytes);
	bool recvall(int ID, char * data, int totalbytes);

	bool SendInt(int ID, int _int);
	bool GetInt(int ID, int & _int);

	bool SendPlayer(int ID, Player & _player);
	bool GetPlayer(int ID, Player & _player);

	bool getEndGame(int ID, bool& _end);
	bool sendEndGame(int ID, bool& _end);

	bool SendPacketType(int ID, Packet _packettype);
	bool GetPacketType(int ID, Packet & _packettype);

	bool SendString(int ID, std::string & _string);
	bool GetString(int ID, std::string & _string);

	bool ProcessPacket(int ID, Packet _packettype);

	bool sendSetPlayer(int ID, Player & _player);
private: // Private Static Variables
private: // Private Member Variables
	SOCKET Connections[3];
	int TotalConnections = 0;
	int maxRoomConnections = 3;
	int currentRoomConnections = 0;


	SOCKADDR_IN addr; //Address that we will bind our listening socket to
	int addrlen = sizeof(addr);
	SOCKET sListen;
	bool enemy1Initialized = false;
	bool enemy2Initialized = false;
};

static Server * server; //Serverptr is necessary so the static ClientHandler method can access the server instance/functions.
