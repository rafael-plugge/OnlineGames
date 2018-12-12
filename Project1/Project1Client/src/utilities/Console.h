﻿#ifndef _DEBUG_CONSOLE_H
#define _DEBUG_CONSOLE_H

namespace app
{
	class Console
	{
	public: // Constructors/Destructor/Assignments
	public: // Public Static Functions
		#ifdef _DEBUG

		#ifdef _DEBUG_THREAD_SAFE

		/// <summary>
		/// Output to the console the passed text.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="text">read-only reference to the text that will be output'd to console.</param>
		static inline void write(std::string const & text)
		{
			auto lock = std::lock_guard<decltype(Console::s_mutex)>(s_mutex);
			std::cout << text;
		}

		/// <summary>
		/// Output to the console the collection of text passed.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="texts">read-only reference to the collection of text that will be output'd to console.</param>
		static inline void write(std::initializer_list<std::string> const & texts)
		{
			auto lock = std::lock_guard<decltype(Console::s_mutex)>(s_mutex);
			for (auto const & text : texts) { std::cout << text; }
		}

		/// <summary>
		/// Output to the console a empty new line.
		///
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		static inline void writeLine()
		{
			auto lock = std::lock_guard<decltype(Console::s_mutex)>(s_mutex);
			std::cout << std::endl;
		}

		/// <summary>
		/// Output to the console the passed text, ending with a new line.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="text">read-only refernece to the text that will be output'd to console.</param>
		static inline void writeLine(std::string const & text)
		{
			auto lock = std::lock_guard<decltype(Console::s_mutex)>(s_mutex);
			std::cout << text << std::endl;
		}

		/// <summary>
		/// Output to the console the collection of text, after which adds a new line.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="texts">read-only reference to the collection of text that will be output'd to console.</param>
		static inline void writeLine(std::initializer_list<std::string> const & texts)
		{
			auto lock = std::lock_guard<decltype(Console::s_mutex)>(s_mutex);
			for (auto const & text : texts) { std::cout << text; } std::cout << std::endl;
		}

		#else

		/// <summary>
		/// Output to the console the passed text.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="text">read-only reference to the text that will be output'd to console.</param>
		static inline void write(std::string const & text) { std::cout << text; }

		/// <summary>
		/// Output to the console the collection of text passed.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="texts">read-only reference to the collection of text that will be output'd to console.</param>
		static inline void write(std::initializer_list<std::string> const & texts) { for (auto const & text : texts) { std::cout << text; } }

		/// <summary>
		/// Output to the console a empty new line.
		///
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		static inline void writeLine() { std::cout << std::endl; }

		/// <summary>
		/// Output to the console the passed text, ending with a new line.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="text">read-only refernece to the text that will be output'd to console.</param>
		static inline void writeLine(std::string const & text) { std::cout << text << std::endl; }

		/// <summary>
		/// Output to the console the collection of text, after which adds a new line.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="texts">read-only reference to the collection of text that will be output'd to console.</param>
		static inline void writeLine(std::initializer_list<std::string> const & texts) { for (auto const & text : texts) { std::cout << text; } std::cout << std::endl; }

		#endif

		#else

		static inline void write(std::string const & text) {}
		static inline void write(std::initializer_list<std::string> const & texts) {}
		static inline void writeLine() {}
		static inline void writeLine(std::string const & text) {}
		static inline void writeLine(std::initializer_list<std::string> const & texts) {}

		#endif
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
		#ifdef _DEBUG_THREAD_SAFE
		static std::mutex s_mutex;
		#endif // _DEBUG_THREAD_SAFE
	private: // Private Member Variables

	};
}

#endif // !_DEBUG_CONSOLE_H
