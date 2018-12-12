#ifndef _CLIENT_H
#define _CLIENT_H

#include "utilities/WinSockDeleter.h"
#include "utilities/Network.h"
#include "game/Player.h"

namespace app
{
	class Client
	{
	public: // Constructors/Destructor/Assignments
		Client();
		~Client();

		Client(Client const &) = default;
		Client & operator=(Client const &) = default;

		Client(Client &&) = default;
		Client & operator=(Client &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		int run(app::game::Player & enemy);

		void send(math::Vector2i position);
	public: // Public Static Variables
	public: // Public Member Variables
		SOCKET m_socket;
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
		bool init();
		bool initWindowsSocket();
		bool initAddressInfo();
		bool initServerConnection();

		void update(app::time::nanoseconds const & dt);
	private: // Private Static Variables
	private: // Private Member Variables
		std::atomic_bool m_running;
		bool m_wsaInit;
		SOCKADDR_IN m_addressInfo;
		std::string m_address;
		std::vector<char> m_sendBuffer;
		std::mutex m_receiveBufferMutex;
		std::vector<char> m_receiveBuffer;
	};
}

#endif // !_CLIENT_H
