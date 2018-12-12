#ifndef _NETWORK_H
#define _NETWORK_H

namespace app::net
{
	bool sendall(SOCKET clientSocket, char * data, int totalBytes);

	bool send(SOCKET clientSocket, bool start);
	bool send(SOCKET clientSocket, int num);
	bool send(SOCKET clientSocket, math::Vector2i position);
	bool send(SOCKET clientSocket, PacketType packetType);

	bool recvall(SOCKET clientSocket, char * data, int totalBytes);

	bool recv(SOCKET clientSocket, bool & start);
	bool recv(SOCKET clientSocket, int & num);
	bool recv(SOCKET clientSocket, math::Vector2i & position);
	bool recv(SOCKET clientSocket, PacketType & packetType);

	bool processPacket(SOCKET clientSocket, SOCKET targetSocket, PacketType const & type);
	bool processPacket(SOCKET clientSocket, game::Player & enemy, PacketType const & type);
}

#endif // !_NETWORK_H
