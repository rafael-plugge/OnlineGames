#include "Client.h"

bool Client::recvall(char * data, int totalbytes)
{
	int bytesreceived = 0; //Holds the total bytes received
	while (bytesreceived < totalbytes) //While we still have more bytes to recv
	{
		int RetnCheck = recv(Connection, data + bytesreceived, totalbytes - bytesreceived, NULL); //Try to recv remaining bytes
		if (RetnCheck == SOCKET_ERROR) //If there is a socket error while trying to recv bytes
			return false; //Return false - failed to recvall
		bytesreceived += RetnCheck; //Add to total bytes received
	}
	return true; //Success!
}

bool Client::sendall(char * data, int totalbytes)
{
	int bytessent = 0; //Holds the total bytes sent
	while (bytessent < totalbytes) //While we still have more bytes to send
	{
		int RetnCheck = send(Connection, data + bytessent, totalbytes - bytessent, NULL); //Try to send remaining bytes
		if (RetnCheck == SOCKET_ERROR) //If there is a socket error while trying to send bytes
			return false; //Return false - failed to sendall
		bytessent += RetnCheck; //Add to total bytes sent
	}
	return true; //Success!
}
bool Client::SendInt(int _int)
{
	if (!sendall((char*)&_int, sizeof(int))) //Try to send int... If int fails to send
		return false; //Return false: int not successfully sent
	return true; //Return true: int successfully sent
}

bool Client::sendBoolean(bool _boolean)
{
	if (!sendall((char*)&_boolean, sizeof(bool)))
		return false;
	return true;
}

bool Client::GetInt(int & _int)
{
	if (!recvall((char*)&_int, sizeof(int))) //Try to receive int... If int fails to be recv'd
		return false; //Return false: Int not successfully received
	return true;//Return true if we were successful in retrieving the int
}

bool Client::SendPacketType(Packet _packettype)
{
	if (!sendall((char*)&_packettype, sizeof(Packet))) //Try to send packet type... If packet type fails to send
		return false; //Return false: packet type not successfully sent
	return true; //Return true: packet type successfully sent
}

bool Client::GetPacketType(Packet & _packettype)
{
	if (!recvall((char*)&_packettype, sizeof(Packet))) //Try to receive packet type... If packet type fails to be recv'd
		return false; //Return false: packet type not successfully received
	return true;//Return true if we were successful in retrieving the packet type
}

bool Client::SendString(std::string & _string)
{
	if (!SendPacketType(P_ChatMessage)) //Send packet type: Chat Message, If sending packet type fails...
		return false; //Return false: Failed to send string
	int bufferlength = _string.size(); //Find string buffer length
	if (!SendInt(bufferlength)) //Send length of string buffer, If sending buffer length fails...
		return false; //Return false: Failed to send string buffer length
	if (!sendall((char*)_string.c_str(), bufferlength)) //Try to send string buffer... If buffer fails to send,
		return false; //Return false: Failed to send string buffer
	return true; //Return true: string successfully sent
}

bool Client::SendPlayer(Player& _player)
{
	//SEND PACKET TYPE
	if (!SendPacketType(P_PlayerData))
		return false;
	int bufferLength = sizeof(Player);
	//SEND BUFFER LENGTH
	if (!SendInt(bufferLength))
		return false;
	//SEND OBJECT DATA
	if (!sendall((char*)&_player, bufferLength))
		return false;
	return true;
}

bool Client::sendEndGame(bool & _end)
{
	//SEND PACKET TYPE
	if (!SendPacketType(P_EndGame))
		return false;
	int bufferLength = sizeof(bool);
	//SEND BUFFER LENGTH
	if (!SendInt(bufferLength))
		return false;
	//SEND DATA
	if(!sendall((char*)&_end, bufferLength))
		return false;
	return true;
}

bool Client::GetString(std::string & _string)
{
	int bufferlength; //Holds length of the message
	if (!GetInt(bufferlength)) //Get length of buffer and store it in variable: bufferlength
		return false; //If get int fails, return false
	char * buffer = new char[bufferlength + 1]; //Allocate buffer
	buffer[bufferlength] = '\0'; //Set last character of buffer to be a null terminator so we aren't printing memory that we shouldn't be looking at
	if (!recvall(buffer, bufferlength)) //receive message and store the message in buffer array. If buffer fails to be received...
	{
		delete[] buffer; //delete buffer to prevent memory leak
		return false; //return false: Fails to receive string buffer
	}
	_string = buffer; //set string to received buffer message
	delete[] buffer; //Deallocate buffer memory (cleanup to prevent memory leak)
	return true;//Return true if we were successful in retrieving the string
}

bool Client::GetPlayer(Player & _player)
{
	int bufferLength = sizeof(Player); //set size of the buffer to be size of player object
	//RECEIVE BUFFER LENGTH
	if (!GetInt(bufferLength))
		return false;
	Player* tempPlayer = new Player(); //create a player object that will hold received data
	//RECEIVE OBJECT
	if (!recvall((char*)tempPlayer, bufferLength)) //receive player data giving in the temporary object and the length of buffer
	{
		delete tempPlayer; //if fail delete newly created object and return false
		return false;
	}
	_player = *tempPlayer; //if success assign temp player data to the actual player
	delete tempPlayer; //delete new object and return true
	return true;
}

bool Client::getBoolean(bool _bool)
{
	if (!recvall((char*)&_bool, sizeof(bool))) //Try to receive bool... If bool fails to be recv'd
		return false; //Return false: Int not successfully received
	return true;//Return true if we were successful in retrieving the bool
}

bool Client::getEndGame()
{
	int bufferLength = sizeof(bool); //set size of the buffer to be size of player object
	//RECEIVE BUFFER LENGTH
	if (!GetInt(bufferLength))
		return false;
	bool* gameEnd = new bool();
	//RECEIVE OBJECT
	if (!recvall((char*)gameEnd, bufferLength)) //receive player data giving in the temporary object and the length of buffer
	{
		return false;
	}
	game->setGameState(gameEnd);
	std::cout << "I received the end game state!" << std::endl;
	return true;
}


