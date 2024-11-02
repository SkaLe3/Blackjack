#include "Renderer/Texture.h"

namespace Core
{

	Texture::Texture(SDL_Surface* surface, SDL_Renderer* renderer)
		: m_Texture(nullptr), m_Width(0), m_Height(0)
	{
		m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
		BJ_ASSERT(m_Texture, "Failed to create texture: %s", SDL_GetError());

		m_Width = surface->w;
		m_Height = surface->h;
	}

	Texture::~Texture()
	{
		if (m_Texture)
		{
			SDL_DestroyTexture(m_Texture);
		}
	}

	SDL_Texture* Texture::GetInternal() const
	{
		return m_Texture;
	}

	int32 Texture::GetWidth() const
	{
		return m_Width;
	}

	int32 Texture::GetHeight() const
	{
		return m_Height;
	}

	glm::vec2 Texture::GetSize() const
	{
		return { m_Width, m_Height };
	}

}