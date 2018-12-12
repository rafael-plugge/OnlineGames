#ifndef _SERVER_H
#define _SERVER_H

#include "../../Project1Client/src/utilities/Network.h"

namespace app
{
	class Server
	{
	public: // Constructors/Destructor/Assignments
		Server();
		~Server();

		Server(Server const &) = default;
		Server & operator=(Server const &) = default;

		Server(Server &&) = default;
		Server & operator=(Server &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		int run();
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
		bool init();
		bool initWindowsSocket();
		bool initServerAddress();
		bool initServerSocket();
		void update(app::time::nanoseconds const & dt);

		bool isAcceptingConnections();
	private: // Private Static Variables
	private: // Private Member Variables
		std::atomic_bool m_running;
		bool m_wsaInit;
		SOCKET m_serverSocket;
		SOCKADDR_IN m_addressInfo;
		int m_addressInfoLength = sizeof(SOCKADDR);
		std::array<SOCKET, 2> m_clientSockets;

	};
}

#endif // !_SERVER_H
