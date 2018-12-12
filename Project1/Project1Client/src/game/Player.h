#ifndef _GAME_PLAYER_H
#define _GAME_PLAYER_H

namespace app::game
{
	class Player
	{
	public: // Constructors/Destructor/Assignments
		Player();
		~Player() = default;

		Player(Player const &) = default;
		Player & operator=(Player const &) = default;

		Player(Player &&) = default;
		Player & operator=(Player &&) = default;

	public: // Public Static Functions
		static Player create(bool isFirstPlayer, std::shared_ptr<SDL_Renderer> renderer, std::string const & textureFile);
	public: // Public Member Functions
		void update(app::time::nanoseconds const & dt);
	public: // Public Static Variables
	public: // Public Member Variables
		math::Vector2i m_position = { 0, 0 };
		float m_radius = 10.0f;
		std::shared_ptr<gra::Texture> m_texture = nullptr;
		bool m_finish = false;
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		app::inp::KeyHandler<app::KeyCode> & m_keyHandler;
	};
}

#endif // !_GAME_PLAYER_H
