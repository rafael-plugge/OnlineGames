#ifndef _PLAYER_H
#define _PLAYER_H

#include <SDL/SDL.h>

enum class Color { RED, BLUE, GREEN };

class Player
{
public: // Constructors/Destructor/Assignments
	Player();
	Player(int rad, int x, int y, Color _col);
	~Player();

	Player(Player const &) = default;
	Player & operator=(Player const &) = default;

	Player(Player &&) = default;
	Player & operator=(Player &&) = default;

public: // Public Static Functions
public: // Public Member Functions
	void draw(SDL_Renderer* renderer);
	void update();
	void setTexture(SDL_Texture* _tex);
public: // Public Static Variables
public: // Public Member Variables
	int m_radius;
	int m_xPos;
	int m_yPos;
	Color m_color;
	SDL_Texture* texture;
	SDL_Rect playerRect;
protected: // Protected Static Functions
protected: // Protected Member Functions
protected: // Protected Static Variables
protected: // Protected Member Variables
private: // Private Static Functions
private: // Private Member Functions
private: // Private Static Variables
private: // Private Member Variables
};

#endif // !_PLAYER_H
