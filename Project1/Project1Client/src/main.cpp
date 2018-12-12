#include "stdafx.h"
#include "Client.h"
#include "Game.h"

int main(int argc, char** argv)
{
	SDL_SetMainReady();

	auto client = app::Client();
	auto game = app::Game(client);
	auto const exitCode = client.run(game.m_enemy);
	if (exitCode == EXIT_FAILURE) { return EXIT_FAILURE; }
	return game.run();
}