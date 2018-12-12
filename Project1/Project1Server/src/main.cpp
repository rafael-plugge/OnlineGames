#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2test.lib")
#pragma comment(lib, "SDL2_image.lib")
#include "Server.h"
#include "Player.h"

int main(int argc, char** argv)
{
	Server * server = new Server(2178, false);
	for (int i = 0; i < 3; ++i) { server->ListenForNewConnection(); }
	std::system("pause");
	if (server != nullptr) { delete server; }
	return EXIT_SUCCESS;
}