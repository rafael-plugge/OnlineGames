#ifndef _UTILITIES_WINDOWS_SOCKET_DELETER_H
#define _UTILITIES_WINDOWS_SOCKET_DELETER_H

namespace app::util
{
	class WinSockDeleter
	{
	public: // Constructors/Destructor/Assignments
		WinSockDeleter() = default;
		~WinSockDeleter() = default;

		WinSockDeleter(WinSockDeleter const &) = default;
		WinSockDeleter & operator=(WinSockDeleter const &) = default;

		WinSockDeleter(WinSockDeleter &&) = default;
		WinSockDeleter & operator=(WinSockDeleter &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void operator()(struct addrinfo * ptr) const;
		void operator()(SOCKET * ptr) const;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_UTILITIES_WINDOWS_SOCKET_DELETER_H
