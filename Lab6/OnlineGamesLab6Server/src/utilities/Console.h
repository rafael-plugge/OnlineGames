#ifndef _DEBUG_CONSOLE_H
#define _DEBUG_CONSOLE_H

#include <string>
#include <iostream>

namespace app
{
	namespace debug
	{
		inline void log(std::string const & str);
		inline void logLine(std::string const & str);

		#ifndef _DEBUG

		inline void app::debug::log(std::string const & str) { }
		inline void app::debug::logLine(std::string const & str) { }

		#else

		inline void app::debug::log(std::string const & str)
		{
			std::cerr << str;
		}

		inline void app::debug::logLine(std::string const & str)
		{
			app::debug::log(str);
			std::cerr << std::endl;
		}

		#endif
	}
}

#endif // !_DEBUG_CONSOLE_H