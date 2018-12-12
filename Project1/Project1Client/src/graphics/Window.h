#ifndef _WINDOW_H
#define _WINDOW_H

#include "utilities/SdlDeleter.h"
#include "WindowsParams.h"
#include "game/Player.h"

namespace app::gra
{
	class Window
	{
	private: // Private type definitions
		typedef std::unique_ptr<SDL_Window, util::SdlDeleter> UPtrWindow;
		typedef std::unique_ptr<SDL_Renderer, util::SdlDeleter> UPtrRenderer;

	public: // Constructors/Destructor/Assignments
		Window(app::gra::WindowsParams params);
		~Window();

	public: // Public Member Functions

		void pollEvents();
		void clear() const;

		void draw(app::game::Player const & player, app::time::nanoseconds const & dt);

		void display() const;

		inline constexpr bool const & isOpen() { return m_open; }
		inline std::shared_ptr<SDL_Renderer> getRenderer() { return m_renderer; }
	public: // Public Member Variables
	protected: // Protected Member Functions
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
		bool init();
		bool initWindow();
		bool initRenderer(UPtrWindow const & uptrSdlWindow);

	private: // Private Static Variables
		static constexpr SDL_Color s_BG_COLOR = { 0u, 0u, 0u, 255u };
	private: // Private Member Variables
		app::inp::KeyHandler<app::KeyCode> & m_keyhandler;
		app::inp::MouseHandler<app::ButtonCode> & m_mousehandler;
		bool m_open;
		std::string m_title;
		std::size_t m_width;
		std::size_t m_height;
		UPtrWindow m_window;
		std::shared_ptr<SDL_Renderer> m_renderer;
		SDL_Rect m_rect;
	};

}


#endif // !_WINDOW_H