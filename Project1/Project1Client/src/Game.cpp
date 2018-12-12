#include "stdafx.h"
#include "Game.h"

app::Game::Game(app::Client & client)
	: m_client(client)
	, m_keyHandler(app::inp::KeyHandler<app::KeyCode>::getRef())
	, m_mouseHandler(app::inp::MouseHandler<app::ButtonCode>::getRef())
	, m_window(gra::WindowsParams{ "Online Games", 1366u, 768u })
	, m_start(false)
	, m_player1(game::Player::create(true, m_window.getRenderer(), "./res/green-circle.png"))
	, m_enemy(game::Player::create(false, m_window.getRenderer(), "./res/red-circle.png"))
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != NULL)
	{
		Console::writeLine({ "Failed to initialize SDL, Error: [", SDL_GetError(), "]" });
	}
}

app::Game::~Game()
{
	SDL_Quit();
}

int app::Game::run()
{
	using clock = std::chrono::high_resolution_clock;
	constexpr app::time::nanoseconds updateStep =
		app::time::toNanos(std::chrono::duration<double, std::milli>(1 / 60.0 * 1000.0));
	clock::time_point deltaTimePoint = clock::now();
	app::time::nanoseconds elapsedTime = updateStep;
	app::time::nanoseconds deltaRenderStep = app::time::nanoseconds::zero();

	while (m_window.isOpen())
	{
		m_window.pollEvents();
		deltaRenderStep =
			(elapsedTime += app::time::toNanos(clock::now() - deltaTimePoint));
		deltaTimePoint = clock::now();
		while (elapsedTime > updateStep)
		{
			this->update(updateStep);
			elapsedTime -= updateStep;
		}
		this->render(deltaRenderStep);
	}

	return EXIT_SUCCESS;
}

void app::Game::update(app::time::nanoseconds const & dt)
{
	if (m_player1.m_finish || m_enemy.m_finish) return;

	m_player1.update(dt);
	m_client.send(m_player1.m_position);

	m_keyHandler.update();
	m_mouseHandler.update();
}

void app::Game::render(app::time::nanoseconds const & dt)
{
	if (m_player1.m_finish || m_enemy.m_finish) return;
	m_window.clear();

	m_window.draw(m_player1, dt);
	m_window.draw(m_enemy, dt);

	m_window.display();
}
