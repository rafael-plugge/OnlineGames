#ifndef _GAME_H
#define _GAME_H

#include "graphics/Window.h"
#include "game/Player.h"
#include "Client.h"

namespace app
{
	class Game
	{
	public: // Constructors/Destructor/Assignments
		Game(Client & client);
		~Game();

		Game(Game const &) = default;
		Game & operator=(Game const &) = default;

		Game(Game &&) = default;
		Game & operator=(Game &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		int run();
	public: // Public Static Variables
	public: // Public Member Variables
		std::atomic_bool m_start;
		game::Player m_player1;
		game::Player m_enemy;
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
		void update(app::time::nanoseconds const & dt);
		void render(app::time::nanoseconds const & dt);
	private: // Private Static Variables
	private: // Private Member Variables
		Client & m_client;
		inp::KeyHandler<KeyCode> & m_keyHandler;
		inp::MouseHandler<ButtonCode> & m_mouseHandler;
		gra::Window m_window;
	};
}



#endif // !_GAME_H
