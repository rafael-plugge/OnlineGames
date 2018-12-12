#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib") //Required for WinSock
#include <WinSock2.h> //For win sockets
#include <string> //For std::string
#include <iostream> //For std::cout, std::endl, std::cin.getline
#include "Player.h"
//Deal with cyclical referencing
class Game;

enum Packet
{
	P_ChatMessage,
	P_Test,
	P_PlayerData,
	P_Authority,
	P_SetPlayer,
	P_EndGame
};
class Client
{
public: //Public functions
	Client(std::string IP, int PORT);
	bool Connect();

	bool SendString(std::string & _string);
	bool SendPlayer(Player&);
	bool sendEndGame(bool& _end);

	bool CloseConnection();
	void setGame(Game* _game) { game = _game; }
private: //Private functions
	bool ProcessPacket(Packet _packettype);
	static void ClientThread();
	//Sending Funcs
	bool sendall(char * data, int totalbytes);
	bool SendInt(int _int);
	bool sendBoolean(bool _boolean);
	bool SendPacketType(Packet _packettype);
	

	//Getting Funcs
	bool recvall(char * data, int totalbytes);
	bool GetInt(int & _int);
	bool GetPacketType(Packet & _packettype);
	bool GetString(std::string & _string);
	bool GetPlayer(Player& _player);
	bool getBoolean(bool _bool);
	bool getEndGame();

private:
	SOCKET Connection;//This client's connection to the server
	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
	//hold pointer to the game object in order to be able to alter the game
	Game* game;
};

static Client * clientptr; //This client ptr is necessary so that the ClientThread method can access the Client instance/methods. Since the ClientThread method is static, this is the simplest workaround I could think of since there will only be one instance of the client.
#include "Game.h"
