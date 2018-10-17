#ifndef _DEBUG_CONSOLE_H
#define _DEBUG_CONSOLE_H

#include <string>
#include <iostream>

namespace app
{
	namespace debug
	{
		inline constexpr void log(std::string const & str);
		inline constexpr void logLine(std::string const & str);
	}
}

#endif // !_DEBUG_CONSOLE_H