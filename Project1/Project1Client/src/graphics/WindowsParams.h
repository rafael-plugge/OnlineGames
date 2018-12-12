#ifndef _GRAPHICS_WINDOWS_PARAMS_H
#define _GRAPHICS_WINDOWS_PARAMS_H

namespace app::gra
{
	struct WindowsParams
	{
	public: // Constructors/Destructor/Assignments
		WindowsParams() = default;
		~WindowsParams() = default;

		WindowsParams(WindowsParams const &) = default;
		WindowsParams & operator=(WindowsParams const &) = default;

		WindowsParams(WindowsParams &&) = default;
		WindowsParams & operator=(WindowsParams &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::string title = "";
		std::size_t width = 0u;
		std::size_t height = 0u;
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

#endif // !_GRAPHICS_WINDOWS_PARAMS_H
