#include "stdafx.h"
#include "Network.h"


bool app::net::sendall(SOCKET clientSocket, char * data, int totalBytes)
{
	int bytesSent = 0;
	while (bytesSent < totalBytes)
	{
		int amountSent = ::send(clientSocket, data + bytesSent, totalBytes - bytesSent, NULL);
		if (amountSent == SOCKET_ERROR) return false;
		bytesSent += amountSent;
	}
	return true;
}

bool app::net::send(SOCKET clientSocket, bool start)
{
	int bufferLength = sizeof(bool);
	return send(clientSocket, PacketType::Start)
		&& send(clientSocket, bufferLength)
		&& sendall(clientSocket, reinterpret_cast<char*>(&start), bufferLength);
}

bool app::net::send(SOCKET clientSocket, int num)
{
	return sendall(clientSocket, reinterpret_cast<char*>(&num), sizeof(int));
}

bool app::net::send(SOCKET clientSocket, math::Vector2i position)
{
	const int bufferLength = sizeof(math::Vector2i);
	return send(clientSocket, PacketType::Position)
		&& send(clientSocket, bufferLength)
		&& sendall(clientSocket, reinterpret_cast<char*>(&position), bufferLength);
}

bool app::net::send(SOCKET clientSocket, PacketType packetType)
{
	return sendall(clientSocket, reinterpret_cast<char*>(packetType), sizeof(PacketType));
}

bool app::net::recvall(SOCKET clientSocket, char * data, int totalBytes)
{
	int bytesRec = 0;
	while (bytesRec < totalBytes)
	{
		int amountRec = ::recv(clientSocket, data, totalBytes - bytesRec, NULL);
		if (amountRec == SOCKET_ERROR) return false;
		bytesRec += amountRec;
	}
	return true;
}

bool app::net::recv(SOCKET clientSocket, bool & start)
{
	int bufferLength = 0;
	bool temp;
	bool result = recv(clientSocket, bufferLength)
		&& recvall(clientSocket, reinterpret_cast<char*>(&temp), bufferLength);
	if (result) { start = temp; }
	return result;
}

bool app::net::recv(SOCKET clientSocket, int & num)
{
	return recvall(clientSocket, reinterpret_cast<char*>(num), sizeof(int));
}

bool app::net::recv(SOCKET clientSocket, math::Vector2i & position)
{
	int bufferLength = 0;
	math::Vector2i temp;
	bool result = recv(clientSocket, bufferLength)
		&& recvall(clientSocket, reinterpret_cast<char*>(&temp), bufferLength);
	if (result)
	{
		position = temp;
	}
	return result;
}

bool app::net::recv(SOCKET clientSocket, PacketType & packetType)
{
	return recvall(clientSocket, reinterpret_cast<char*>(packetType), sizeof(PacketType));
}

bool app::net::processPacket(SOCKET clientSocket, SOCKET targetSocket, PacketType const & type)
{
	switch (type)
	{
	case PacketType::Position:
	{
		auto position = math::Vector2i();
		if (!recv(clientSocket, position))
		{
			return false;
		}
		if (!send(targetSocket, position))
		{
			Console::writeLine({ "Failed to send position", position });
		}
		break;
	}
	default:
		Console::writeLine({ "Unrecognized packet: [", std::to_string(static_cast<int>(type)), "]" });
		break;
	}

	return true;
}

bool app::net::processPacket(SOCKET clientSocket, game::Player & enemy, PacketType const & type)
{
	switch (type)
	{
	case PacketType::Start:
	{
		bool start;
		if (!recv(clientSocket, start)) return false;
		enemy.m_finish = start;
		break;
	}
	case PacketType::Position:
	{
		math::Vector2i newPosition;
		if (!recv(clientSocket, newPosition)) return false;
		enemy.m_position = newPosition;
		break;
	}
	default:
		Console::writeLine({ "Unrecognized packet: [", std::to_string(static_cast<int>(type)), "]" });
		break;
	}

	return true;
}
