#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2test.lib")
#pragma comment(lib, "SDL2_image.lib")

#include "Client.h"
#include "Player.h"
#include "Game.h"

int main(int argc, char** argv)
{
	Client * client = new Client("127.0.0.1", 2178);

	if (!client->Connect())
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return 1;
	}

	auto game = Game(client);
	client->setGame(&game);
	game.loop();

	if (client != nullptr) delete client;
	return EXIT_SUCCESS;
}