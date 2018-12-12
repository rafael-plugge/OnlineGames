#include "stdafx.h"
#include "Texture.h"

app::gra::Texture::Texture(std::shared_ptr<SDL_Renderer> renderer, std::string const & file)
	: m_texture(nullptr)
{
	this->loadTexture(renderer, file);
}

bool app::gra::Texture::loadTexture(std::shared_ptr<SDL_Renderer> renderer, std::string const & file)
{
	auto uptrTexture = Texture::loadTextureFromFile(renderer, file);

	if (nullptr == uptrTexture)
	{
		std::string const errorMsg("Error loading image file ('" + file + "')");
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, errorMsg.c_str());
		return false;
	}

	m_texture.swap(uptrTexture);
	return true;
}

app::util::UPtrTexture app::gra::Texture::loadTextureFromFile(std::shared_ptr<SDL_Renderer> renderer, std::string const & file)
{
	util::UPtrSurface pTempSurface = Texture::loadSurfaceFromFile(file);

	SDL_Texture * pTempTexture = nullptr;
	pTempTexture = SDL_CreateTextureFromSurface(renderer.get(), pTempSurface.get());
	if (pTempTexture == nullptr) { return nullptr; }

	return app::util::UPtrTexture(pTempTexture);
}

app::util::UPtrSurface app::gra::Texture::loadSurfaceFromFile(std::string const & file)
{
	SDL_Surface * pTempSurface = nullptr;
	pTempSurface = IMG_Load(file.c_str());
	if (pTempSurface == nullptr) { return nullptr; }

	return app::util::UPtrSurface(pTempSurface);
}
