#include "stdafx.h"
#include "Window.h"

app::gra::Window::Window(
	app::gra::WindowsParams params
)
	: m_keyhandler(app::inp::KeyHandler<app::KeyCode>::getRef())
	, m_mousehandler(app::inp::MouseHandler<app::ButtonCode>::getRef())
	, m_open(true)
	, m_title(std::move(params.title))
	, m_width(std::move(params.width))
	, m_height(std::move(params.height))
	, m_window(nullptr)
	, m_renderer(nullptr)
	, m_rect{ 0, 0, 0, 0 }
{
	m_open = this->init();
}

app::gra::Window::~Window()
{
}

void app::gra::Window::pollEvents()
{
	typedef SDL_EventType EventType;
	typedef app::ButtonCode ButtonCode;
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case EventType::SDL_QUIT:
			m_open = false;
			break;
		case EventType::SDL_MOUSEMOTION:
			m_mousehandler.updatePosition(sdlEvent.motion.x, sdlEvent.motion.y);
			break;
		case EventType::SDL_MOUSEBUTTONUP:
			m_mousehandler.updateButton(static_cast<ButtonCode>(sdlEvent.button.button), false);
			break;
		case EventType::SDL_MOUSEBUTTONDOWN:
			m_mousehandler.updateButton(static_cast<ButtonCode>(sdlEvent.button.button), true);
			break;
		case EventType::SDL_KEYUP:
			m_keyhandler.updateKey(sdlEvent.key.keysym.sym, false);
			break;
		case EventType::SDL_KEYDOWN:
			m_keyhandler.updateKey(sdlEvent.key.keysym.sym, true);
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) { m_open = false; }
			break;
		default:
			break;
		}
	}
}

void app::gra::Window::clear() const
{
	SDL_SetRenderDrawColor(m_renderer.get(), s_BG_COLOR.r, s_BG_COLOR.g, s_BG_COLOR.b, s_BG_COLOR.a);
	SDL_RenderClear(m_renderer.get());
}

void app::gra::Window::draw(app::game::Player const & player, app::time::nanoseconds const & dt)
{
	m_rect.x = player.m_position.x;
	m_rect.y = player.m_position.y;
	m_rect.w = player.m_radius;
	m_rect.h = player.m_radius;

	SDL_RenderCopy(m_renderer.get(), player.m_texture->get(), nullptr, &m_rect);
}

void app::gra::Window::display() const
{
	SDL_RenderPresent(m_renderer.get());
}

bool app::gra::Window::init()
{
	try
	{
		if (SDL_Init(SDL_INIT_VIDEO) != NULL)
		{
			std::string const errorMsg("Failed to initialize SDL Video subsystem");
			SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, errorMsg.c_str());
			return false;
		}
		if (!this->initWindow())
		{
			std::string errorMsg("Failed to initialize SDL Window::\"");
			errorMsg.append(m_title.c_str()).append("\"\n  ").append(SDL_GetError());
			SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, errorMsg.c_str());
			return false;
		}
		if (!this->initRenderer(m_window))
		{
			std::string errorMsg("Faild to initialize SDL Renderer from the SDL Window::\"");
			errorMsg.append(m_title.c_str()).append("\"\n  ").append(SDL_GetError());
			SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, errorMsg.c_str());
			return false;
		}

		return true;
	}
	catch (const std::exception& e)
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, e.what());
		return false;
	}
}

bool app::gra::Window::initWindow()
{
	typedef SDL_WindowFlags WindowFlags;
	constexpr auto centerPos = SDL_WINDOWPOS_CENTERED;
	constexpr auto windowFlags = WindowFlags::SDL_WINDOW_ALLOW_HIGHDPI | WindowFlags::SDL_WINDOW_SHOWN;
	SDL_Window * pWindow = nullptr;

	pWindow = SDL_CreateWindow(m_title.c_str(), centerPos, centerPos, m_width, m_height, windowFlags);

	const bool success = nullptr != pWindow;
	if (success) { m_window.reset(pWindow); }
	return success;
}

bool app::gra::Window::initRenderer(app::gra::Window::UPtrWindow const & uptrSdlWindow)
{
	SDL_Renderer * pRenderer = nullptr;

	pRenderer = SDL_CreateRenderer(uptrSdlWindow.get(), -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);

	const bool success = nullptr != pRenderer;
	if (success) { m_renderer.reset(pRenderer, app::util::SdlDeleter()); }
	return success;
}
