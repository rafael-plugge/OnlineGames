// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// Define what libraries to use
#define _USE_SDL
#define _USE_ENTT
#define _USE_JSON


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
#ifdef _USE_SDL

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2test.lib")
#pragma comment(lib, "SDL2_image.lib")

#endif // _USE_SDL
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
#include <variant>
#include <optional>

// STL Input/Output libraries
#include <string>
#include <sstream>
#include <istream>
#include <ostream>
#include <fstream>
#include <iostream>
#include <filesystem>

// STL Multithreading libraries
#include <thread>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <future>
#include <condition_variable>

/*********************************/
/**         Includes here       **/
/*********************************/

// SDL Library
#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

// SDL Image Library
#include <SDL/SDL_image.h>

// Entt Library
#include <entt/entt.hpp>

// Modern C++ Json Library
#include <Js/json.hpp>

// Global constants
namespace app
{
}