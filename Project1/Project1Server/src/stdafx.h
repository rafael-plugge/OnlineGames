// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef _DEBUG

/*********************************/
/**    BEGIN Debug Libraries    **/
/*********************************/
/*********************************/
/**     END Debug Libraries     **/
/*********************************/

#else

/*********************************/
/**   BEGIN Release Libraries   **/
/*********************************/
/*********************************/
/**    END Release Libraries    **/
/*********************************/

#endif

/*********************************/
/** BEGIN Independant Libraries **/
/*********************************/
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2test.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment (lib, "Ws2_32.lib")
/*********************************/
/**  END Independant Libraries  **/
/*********************************/

// STL Common C libraries
#include <cstddef>
#include <cstdint>

// STL Containers
#include <iterator>
#include <array>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <queue>

// STL Utility libraries
#include <exception>
#include <type_traits>
#include <memory>
#include <random>
#include <chrono>
#include <functional>
#include <tuple>
#include <initializer_list>
#include <limits>

// STL Input/Output libraries
#include <string>
#include <sstream>
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <filesystem>

// STL Multithreading libraries
#include <thread>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <future>
#include <condition_variable>
#include <execution>

// Windows libraries
#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>

// SDL Library
#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

// SDL Image Library
#include <SDL/SDL_image.h>

/*********************************/
/**         Includes here       **/
/*********************************/

// Global constants
namespace app
{
	typedef SDL_Keycode KeyCode;
	enum class ButtonCode
	{
		Left = SDL_BUTTON_LEFT
		, Middle = SDL_BUTTON_MIDDLE
		, Right = SDL_BUTTON_RIGHT
	};
}

#define _DEBUG_THREAD_SAFE
#include "../../Project1Client/src/utilities/Console.h"
#include "../../Project1Client/src/utilities/Time.h"
#include "../../Project1Client/src/utilities/WinSockDeleter.h"
#include "../../Project1Client/src/utilities/SdlDeleter.h"
#include "../../Project1Client/src/utilities/PacketType.h"
#include "../../Project1Client/src/math/Vector2.h"
#include "../../Project1Client/src/input/Keyhandler.h"
#include "../../Project1Client/src/graphics/Texture.h"
#include "../../Project1Client/src/game/Player.h"
