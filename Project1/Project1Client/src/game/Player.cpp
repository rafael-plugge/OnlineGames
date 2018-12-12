#include "stdafx.h"
#include "Player.h"

app::game::Player::Player()
	: m_keyHandler(app::inp::KeyHandler<app::KeyCode>::getRef())
{
}

app::game::Player app::game::Player::create(bool isFirstPlayer, std::shared_ptr<SDL_Renderer> renderer, std::string const & textureFile)
{
	auto player = Player();
	if (isFirstPlayer)
	{
		player.m_position = { 341, 384 };
		player.m_radius = 150;
	}
	else
	{
		player.m_position = { 1024, 384 };
		player.m_radius = 100;
	}
	player.m_position = {
		player.m_position.x - static_cast<int>(player.m_radius / 2.0f),
		player.m_position.y - static_cast<int>(player.m_radius / 2.0f)
	};
	player.m_texture = std::make_shared<decltype(player.m_texture)::element_type>(renderer, textureFile);
	return player;
}

void app::game::Player::update(app::time::nanoseconds const & dt)
{
	const float & dtSecs = app::time::toSeconds(dt).count();
	constexpr auto speed = 250.0f;
	if (m_keyHandler.isKeyDown({ SDLK_w, SDLK_UP })) { m_position.y -= speed * dtSecs; }
	if (m_keyHandler.isKeyDown({ SDLK_s, SDLK_DOWN })) { m_position.y += speed * dtSecs; }
	if (m_keyHandler.isKeyDown({ SDLK_a, SDLK_LEFT })) { m_position.x -= speed * dtSecs; }
	if (m_keyHandler.isKeyDown({ SDLK_d, SDLK_RIGHT })) { m_position.x += speed * dtSecs; }
}
