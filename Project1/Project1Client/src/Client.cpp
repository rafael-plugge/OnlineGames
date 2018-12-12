#include "stdafx.h"
#include "Client.h"

static app::Client * client = nullptr;

void clientThread(app::game::Player * enemy)
{
	app::PacketType type;
	while (true)
	{
		if (!app::net::recv(client->m_socket, type)) break;
		if (!app::net::processPacket(client->m_socket, *enemy, type)) break;
	}
}

app::Client::Client()
	: m_running()
	, m_wsaInit(false)
	, m_socket(INVALID_SOCKET)
	, m_addressInfo()
	, m_address()
	, m_sendBuffer()
	, m_receiveBuffer()
{
	m_receiveBuffer.resize(128);
	client = this;
}

app::Client::~Client()
{
	if (m_wsaInit) { WSACleanup(); }
}

int app::Client::run(app::game::Player & enemy)
{
	if (m_running.store(this->init()); !m_running.load()) { return EXIT_FAILURE; }

	Console::writeLine("Setting up message thread");
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)clientThread, (LPVOID)&enemy, NULL, NULL);

	return EXIT_SUCCESS;
}

void app::Client::send(math::Vector2i position)
{
	if (app::net::send(this->m_socket, position))
	{
		Console::writeLine({ "Bytes sent: [", std::to_string(sizeof(math::Vector2i)), "]" });
	}
	else
	{
		Console::writeLine({ "Failed to send packet [", position, "]" });
	}
}

bool app::Client::init()
{
	try
	{
		return this->initWindowsSocket() && this->initAddressInfo() && this->initServerConnection();
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "Error: [", e.what(), "]" });
		return false;
	}
}

bool app::Client::initWindowsSocket()
{
	WSADATA wsadata;
	if (auto result = WSAStartup(MAKEWORD(2, 2), &wsadata); result != NULL)
	{
		m_wsaInit = false;
		Console::writeLine({ "WSAStartup failed with error: [", std::to_string(result), "]" });
		return false;
	}
	else
	{
		m_wsaInit = true;
	}

	return true;
}

bool app::Client::initAddressInfo()
{
	constexpr auto DEFAULT_PORT = 27020;
	try
	{
		auto input = std::string();
		do
		{
			Console::write("Enter Server IP Address: ");
			std::cin >> input;
		} while (input.empty());
		m_address = std::move(input);

		m_addressInfo.sin_addr.s_addr = inet_addr(m_address.c_str());
		m_addressInfo.sin_port = htons(DEFAULT_PORT);
		m_addressInfo.sin_family = AF_INET;

		return true;
	}
	catch (std::exception const & e)
	{
		return false;
	}
}

bool app::Client::initServerConnection()
{
	m_socket = socket(AF_INET, SOCK_STREAM, NULL);
	if (auto result = connect(m_socket, reinterpret_cast<SOCKADDR*>(&m_addressInfo), sizeof(SOCKADDR)); result != NULL)
	{
		Console::writeLine("Unable to connect to server!");
		return false;

	}
	return true;
}

void app::Client::update(app::time::nanoseconds const & dt)
{
}
