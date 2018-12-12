#include "stdafx.h"
#include "Server.h"

constexpr bool publicIp = false;

app::Server::Server()
	: m_running()
	, m_wsaInit(false)
	, m_serverSocket(INVALID_SOCKET)
	, m_clientSockets{ INVALID_SOCKET, INVALID_SOCKET }
	, m_addressInfo()
{
}

app::Server::~Server()
{
	if (m_wsaInit) { WSACleanup(); }
	if (m_serverSocket != INVALID_SOCKET) { closesocket(m_serverSocket); }
}

int app::Server::run()
{

	using clock = std::chrono::high_resolution_clock;
	constexpr app::time::nanoseconds updateStep =
		app::time::toNanos(std::chrono::duration<double, std::milli>(10 / 60.0 * 1000.0));
	clock::time_point deltaTimePoint = clock::now();
	app::time::nanoseconds elapsedTime = updateStep;
	app::time::nanoseconds deltaRenderStep = app::time::nanoseconds::zero();

	if (m_running.store(this->init()); !m_running.load()) { return EXIT_FAILURE; }

	while (m_running.load())
	{
		elapsedTime += app::time::toNanos(clock::now() - deltaTimePoint);
		deltaTimePoint = clock::now();
		while (elapsedTime > updateStep)
		{
			this->update(updateStep);
			elapsedTime -= updateStep;
		}
	}

	std::system("pause");
	return EXIT_SUCCESS;
}

bool app::Server::init()
{
	try
	{
		return this->initWindowsSocket() && this->initServerAddress() && this->initServerSocket();
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "Server::init failed with Error: [\n", e.what(), "\n]" });
		return false;
	}
}

bool app::Server::initWindowsSocket()
{
	try
	{
		WSADATA wsadata;
		if (auto result = WSAStartup(MAKEWORD(2, 2), &wsadata); result != NULL)
		{
			m_wsaInit = false;
			Console::writeLine({ "WSAStartup failed with error: [", std::to_string(result), "]" });
			throw;
		}
		else
		{
			m_wsaInit = true;
		}

		return true;
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "Server::initWindowsSocket failed with Error: [\n", e.what(), "\n]" });
		return false;
	}
}

bool app::Server::initServerAddress()
{
	constexpr auto DEFAULT_PORT = 27020;
	try
	{
		m_addressInfo.sin_addr.s_addr = publicIp
			? htonl(INADDR_ANY)
			: inet_addr("127.0.0.1");
		m_addressInfo.sin_port = htons(DEFAULT_PORT);
		m_addressInfo.sin_family = AF_INET;

		return true;
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "Server::initServerAddress failed with Error: [\n", e.what(), "\n]" });
		return false;
	}
}

bool app::Server::initServerSocket()
{
	try
	{
		if (m_serverSocket = socket(AF_INET, SOCK_STREAM, NULL); m_serverSocket == INVALID_SOCKET)
		{
			Console::writeLine({ "Socket failed with error: [", std::to_string(WSAGetLastError()), "]" });
			throw;
		}

		if (auto result = bind(m_serverSocket, reinterpret_cast<SOCKADDR*>(&m_addressInfo), m_addressInfoLength); result == SOCKET_ERROR)
		{
			Console::writeLine({ "bind failed with error [", std::to_string(WSAGetLastError()), "]" });
			throw;
		}

		if (auto result = listen(m_serverSocket, SOMAXCONN); result == SOCKET_ERROR)
		{
			Console::writeLine({ "listen failed with error: [", std::to_string(WSAGetLastError()), "]" });
			throw;
		}
		return true;
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "Server::initServerAddress failed with Error: [\n", e.what(), "\n]" });
		return false;
	}
}

void app::Server::update(app::time::nanoseconds const & dt)
{
	if (this->isAcceptingConnections())
	{
		Console::writeLine("Accepting Incoming Connections");
		for (std::size_t i = 0; i < m_clientSockets.size(); ++i)
		{
			if (m_clientSockets.at(i) == INVALID_SOCKET)
			{
				m_clientSockets.at(i) = accept(m_serverSocket, reinterpret_cast<SOCKADDR*>(&m_addressInfo), &m_addressInfoLength);;
				Console::writeLine({ "Connection Received: [", std::to_string(m_clientSockets.at(i)), "]" });
				if (m_clientSockets.at(i) == INVALID_SOCKET)
				{
					Console::writeLine({ "accept failed with error: [", std::to_string(WSAGetLastError()), "]" });
				}
				else
				{
					if (i == 1)
					{
						
					}
					Console::writeLine("Connection successfull!");
				}
			}
		}
	}
	else
	{
		if (!m_running.load()) { return; }
		Console::writeLine("Settings client threads");
		auto clientThreads = std::vector<std::thread>();
		auto lambda = [this](auto clientSocket, auto targetSocket, std::string clientName, std::size_t index) -> void
		{
			Console::writeLine({ clientName, ": starting thread" });
			Console::writeLine({ clientName, ": awaiting bytes... " });

			auto type = app::PacketType::Position;
			while (true)
			{
				if (!app::net::recv(clientSocket, type)) break;
				if (!app::net::processPacket(clientSocket, targetSocket, type)) break;
			}
			Console::writeLine({ clientName, ": Lost connection" });
			closesocket(clientSocket);
		};
		clientThreads.push_back(std::thread(lambda, m_clientSockets.at(0), m_clientSockets.at(1), std::string("client[0]"), 0));
		clientThreads.push_back(std::thread(lambda, m_clientSockets.at(1), m_clientSockets.at(0), std::string("client[1]"), 1));
		for (auto & thread : clientThreads) { thread.join(); }
		m_running.store(false);
	}
}

bool app::Server::isAcceptingConnections()
{
	return std::find_if(std::execution::par, m_clientSockets.begin(), m_clientSockets.end(), [](auto sock) { return sock == INVALID_SOCKET; }) != m_clientSockets.end();
}
