#include "Player.h"



Player::Player()
	: m_radius()
	, m_xPos()
	, m_yPos()
	, m_color()
{
}

Player::Player(int rad, int x, int y, Color _col)
	: m_radius(rad)
	, m_xPos(x)
	, m_yPos(y)
	, m_color(_col)
{
	playerRect.w = rad;
	playerRect.h = rad;
	playerRect.x = x;
	playerRect.y = y;
}


Player::~Player()
{
}



void Player::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &playerRect);
}

void Player::update()
{
	playerRect.x = m_xPos;
	playerRect.y = m_yPos;
}

void Player::setTexture(SDL_Texture * _tex)
{
	texture = _tex;
}
