#include "stdafx.h"
#include "Console.h"


#ifndef _DEBUG

constexpr void app::debug::log(std::string const & str) { }
constexpr void app::debug::logLine(std::string const & str) { }

#else

constexpr void app::debug::log(std::string const & str)
{
	std::cerr << str;
}

constexpr void app::debug::logLine(std::string const & str)
{
	app::debug::log(str);
	std::cerr << std::endl;
}

#endif
