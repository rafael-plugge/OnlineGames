#include "stdafx.h"
#include "Console.h"

#ifdef _DEBUG_THREAD_SAFE
std::mutex app::Console::s_mutex = std::mutex();
#endif // _DEBUG_THREAD_SAFE
