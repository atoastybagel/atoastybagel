#include "texture_loader.h"

texture::texture()
{
	m_texture = nullptr;
	m_width = 0.0f;
	m_height = 0.0f;
} 
texture::~texture()
{
	clean();
}
bool texture::load_img_file(std::string path)
{
	clean();
	SDL_Texture* temp_texture = NULL;
	SDL_Surface* temp_surface = IMG_Load(path.c_str());
	if (temp_surface == NULL)
	{
		printf("FAILED TO LOAD IMAGE ONTO SURFACE! SDL_IMAGE_ERROR: %s\n", IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 255, 255, 255));
		temp_texture = SDL_CreateTextureFromSurface(framework::renderer, temp_surface);
		if (temp_texture == NULL)
		{
			printf("FAILED TO CREATE TEXTURE FROM SURFACE! SDL_IMAGE_ERROR: %s\n", IMG_GetError());
		}
		else
		{
			m_width = temp_surface->w;
			m_height = temp_surface->h;
		}
		SDL_FreeSurface(temp_surface);
	}
	m_texture = temp_texture;
	return m_texture != nullptr;

}
bool texture::load_text(std::string text, TTF_Font* font, SDL_Color text_color)
{
	clean();
	SDL_Surface* temp_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
	if (temp_surface == NULL)
	{
		printf("FAILED TO LOAD TEXT ONTO SURFACE! TTF_IMAGE_ERROR: %s\n", TTF_GetError());
	}
	else
	{
		m_texture = SDL_CreateTextureFromSurface(framework::renderer, temp_surface);
		if (m_texture == NULL)
		{
			printf("FAILED TO CREATE TEXTURE FROM SURFACE! SDL_IMAGE_ERROR: %s\n", IMG_GetError());
		}
		else
		{
			m_width = temp_surface->w;
			m_height = temp_surface->h;
		}
		SDL_FreeSurface(temp_surface);
	}

	return m_texture != nullptr;
}
void texture::draw_texture(int x, int y, SDL_Rect* clip , double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect dst_rect = { x, y, m_width, m_height };
	if (clip != NULL)
	{
		dst_rect.w = clip->w;
		dst_rect.h = clip->h;
	}
	SDL_RenderCopyEx(framework::renderer, m_texture, clip, &dst_rect, angle, center, flip);

}
void texture::clean()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_clip = { 0, 0, 0, 0 };
		m_width = 0.0f;
		m_height = 0.0f;
	}
}

