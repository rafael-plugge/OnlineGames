#ifndef _TEXTURE_GRAPHICS_H
#define _TEXTURE_GRAPHICS_H

// Graphics
namespace app::gra
{
	class Texture
	{
	public: // Constructors/Destructor/Assignments
		Texture(std::shared_ptr<SDL_Renderer> renderer, std::string const & file);

		Texture() = default;
		Texture(Texture const &) = delete;
		Texture(Texture &&) = default;

		~Texture() = default;

		Texture & operator=(Texture const &) = delete;
		Texture & operator=(Texture &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		bool loadTexture(std::shared_ptr<SDL_Renderer> renderer, std::string const & file);
		SDL_Texture const * get() const { return m_texture.get(); }
		SDL_Texture * get() { return m_texture.get(); }
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
		static app::util::UPtrTexture loadTextureFromFile(std::shared_ptr<SDL_Renderer> renderer, std::string const & file);
		static app::util::UPtrSurface loadSurfaceFromFile(std::string const & file);
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		app::util::UPtrTexture m_texture;
	};
}

#endif // !_TEXTURE_GRAPHICS_H
