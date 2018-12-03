#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>

#include "utilities/Console.h"

namespace console = app::debug;
constexpr auto DEFAULT_BUFLEN = 512;
constexpr auto DEFAULT_PORT = "27015";
std::atomic_bool stop = false;

BOOL WINAPI ctrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
		// Handle the CTRL-C signal. 
	case CTRL_C_EVENT:
		printf("Ctrl-C event\n\n");
		Beep(750, 300);
		stop.store(true);
		return TRUE;

		// CTRL-CLOSE: confirm that the user wants to exit. 
	case CTRL_CLOSE_EVENT:
		Beep(600, 200);
		printf("Ctrl-Close event\n\n");
		return TRUE;

		// Pass other signals to the next handler. 
	case CTRL_BREAK_EVENT:
		Beep(900, 200);
		printf("Ctrl-Break event\n\n");
		return TRUE;

	case CTRL_LOGOFF_EVENT:
		Beep(1000, 200);
		printf("Ctrl-Logoff event\n\n");
		return FALSE;

	case CTRL_SHUTDOWN_EVENT:
		Beep(750, 500);
		printf("Ctrl-Shutdown event\n\n");
		return FALSE;

	default:
		return FALSE;
	}
}

int __cdecl main(void)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	auto clientSockets = std::vector<SOCKET>();
	clientSockets.reserve(5);

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	std::string terminateInput = "";

	SetConsoleCtrlHandler(ctrlHandler, true);

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	console::logLine("Accepting new connections");
	bool acceptIncomingConnections = true;
	do
	{
		// Accept a client socket
		SOCKET clientSocket = accept(ListenSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return EXIT_FAILURE;
		}
		console::logLine("Connection accepted! socket[" + std::to_string(clientSocket) + "]");
		clientSockets.push_back(std::move(clientSocket));

		console::logLine("Accept another connection: ");
		{
			auto inputStr = std::string();
			std::getline(std::cin, inputStr);
			acceptIncomingConnections = (inputStr == "y");
		}

	} while (acceptIncomingConnections);

	// No longer need server socket
	closesocket(ListenSocket);

	do
	{
		console::logLine("Processing packets");
		for (auto itt = clientSockets.begin(); itt != clientSockets.end(); ++itt)
		{
			console::log("Awaiting bytes...  ");
			SOCKET & socket = *itt;
			if (auto result = recv(socket, recvbuf, recvbuflen, 0); result > 0)
			{
				console::logLine("received!");
				console::logLine("Bytes received: " + std::to_string(result));

				// Echo buffer back to the sender
				if (auto sendResult = send(socket, recvbuf, result, 0); sendResult == SOCKET_ERROR)
				{
					console::logLine("send failed with error: " + std::to_string(WSAGetLastError()));
					closesocket(socket);
					itt = clientSockets.erase(itt);
					continue;
				}
				else
				{
					console::logLine("Bytes sent: " + std::to_string(sendResult));
				}
			}
			else if (result == 0)
			{
				console::logLine("Connection close requested...");
				if (auto closeResult = shutdown(socket, SD_SEND); closeResult != 0)
				{
					console::logLine("Error on closing connection");
					closesocket(socket);
					itt = clientSockets.erase(itt);
				}
				else
				{
					console::logLine("closed connection (" + std::to_string(socket) + ")");
				}
			}
			else
			{
				console::logLine("recv failed with error: " + std::to_string(WSAGetLastError()));
				closesocket(socket);
				itt = clientSockets.erase(itt);
			}
		}

		console::log("End server (y/n): ");
		{
			auto inputStr = std::string();
			std::getline(std::cin, inputStr);
			stop = (inputStr == "y");
		}
	} while (!stop.load());

	// cleanup
	for (auto & s : clientSockets) { if (s != INVALID_SOCKET) { shutdown(s, SD_BOTH); closesocket(s); } }
	WSACleanup();
	return EXIT_SUCCESS;
}
