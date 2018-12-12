#pragma once
#include <SDL/SDL.h> //SDL/
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <functional>
#include <vector>
#include <memory>
#include "Player.h"
#undef main //some weird vodoo magic with sdl sdl_main is included automatically so have to do this define

// Deal with cyclical referencing
class Client;
class Game
{
public:
	Game(Client* session);
	~Game();
	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();
	//method to load a texture
	SDL_Texture* loadTexture(std::string path);

	void loop();

	//Frees media and shuts down SDL
	void close();
	//draw method
	void draw();
	void update();

	void setPlayer(Player newPlayer);
	void setEnemy(Player enemy);
	void setEnemyPos(int x, int y);

	void setAuthorative(bool newState);
	bool isEnemySet() { return m_enemyInit; }
	void setEnemyState(bool state) { m_enemyInit = state; }
	Player & getPlayer() { return m_player; }
	void setGameState(bool state) { m_gameState = state; }
	bool getGameState() { return m_gameState; }

private:
	//Screen dimension constants
	const int SCREEN_WIDTH = 600;
	const int SCREEN_HEIGHT = 300;
	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;

	//The image we will load and show on the screen
	SDL_Surface* gXOut = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	SDL_Texture* textureGreenPlayer = NULL;
	SDL_Texture* textureRedPlayer = NULL;
	SDL_Texture* textureBluePlayer = NULL;

	Player m_player;
	Player m_enemy;

	bool isAuthorative = false;

	//hold pointer to session to be able to call server functions in the game
	Client* session;
	int m_playerSpeed = 8;
	bool m_enemyInit = false;

	//used when the server sends info on textures prior to loading
	bool m_loadedMedia = false;

	bool m_gameState = false;
};

#include "Client.h"
