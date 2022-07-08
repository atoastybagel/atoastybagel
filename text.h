#ifndef TEXT_H
#define TEXT_H
#include "init.h"
#include "texture_loader.h"

class text 
{
public:
	text()
	{
		txt_texture = nullptr;
		m_font = nullptr;
		rerender_text = false;
		m_color = { 0, 0, 0 };
		m_width = 0;
		m_height = 0;
	}
	~text()
	{
		clean();
	}

	bool load_font(std::string font_path, int font_ptsize)
	{
		bool success = false;
		m_font = TTF_OpenFont(font_path.c_str(), font_ptsize);
		if (m_font == nullptr)
		{
			printf("FAILED TO OPEN FONT (test::load_font()) TTF_IMAGE_ERROR: %s\n", TTF_GetError());
			success = false;
		}
		else
		{
			success = true;
		}
		return success;
	}
	bool load_text(std::string text, SDL_Color text_color)
	{
		clean();
		m_color = text_color;
		SDL_Surface* temp_surface = TTF_RenderText_Blended_Wrapped(m_font, text.c_str(), text_color, 640);
		if (temp_surface == NULL)
		{
			printf("FAILED TO LOAD TEXT ONTO SURFACE! TTF_IMAGE_ERROR: %s\n", TTF_GetError());
		}
		else
		{
			txt_texture = SDL_CreateTextureFromSurface(framework::renderer, temp_surface);
			if (txt_texture == NULL)
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

		return txt_texture != nullptr;
	}
	void handle_events(SDL_Event &txt_event)
	{
		if (txt_event.type == SDL_KEYDOWN)
		{
			if (txt_event.key.keysym.sym == SDLK_BACKSPACE && m_input_text.length() > 0)
			{
				//lop off character
				m_input_text.pop_back();
				rerender_text = true;
			}
			//Handle copy
			else if (txt_event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
			{
				SDL_SetClipboardText(m_input_text.c_str());
			}
			//Handle paste
			else if (txt_event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
			{
				m_input_text = SDL_GetClipboardText();
				rerender_text = true;
			}
		}
		else if (txt_event.type == SDL_TEXTINPUT)
		{
			if (!(SDL_GetModState() & KMOD_CTRL && (txt_event.text.text[0] == 'c' || txt_event.text.text[0] == 'C' || txt_event.text.text[0] == 'v' || txt_event.text.text[0] == 'V')))
			{
				//Append character
				m_input_text += txt_event.text.text;
				rerender_text = true;
			}
		}
	}
	void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
	{
		if (rerender_text == true)
		{
			//Text is not empty
			if (m_input_text != "")
			{
				//Render new text
				clean();
				m_color = m_color;
				SDL_Surface* temp_surface = TTF_RenderText_Blended_Wrapped(m_font, m_input_text.c_str(), m_color, 640);
				if (temp_surface == NULL)
				{
					printf("FAILED TO RERENDER TEXT ONTO SURFACE! TTF_IMAGE_ERROR: %s\n", TTF_GetError());
				}
				else
				{
					txt_texture = SDL_CreateTextureFromSurface(framework::renderer, temp_surface);
					if (txt_texture == nullptr)
					{
						printf("FAILED TO RECREATE TEXTURE FROM SURFACE! SDL_IMAGE_ERROR: %s\n", SDL_GetError());
					}
					else
					{
						m_width = temp_surface->w;
						m_height = temp_surface->h;
					}
					SDL_FreeSurface(temp_surface);
				}
			}
			//Text is empty
			else
			{
				//Render space texture
				clean();
				m_color = m_color;
				SDL_Surface* temp_surface = TTF_RenderText_Blended_Wrapped(m_font, m_input_text.c_str(), m_color, 640);
				if (temp_surface == NULL)
				{
					printf("FAILED TO RERENDER TEXT ONTO SURFACE! TTF_IMAGE_ERROR: %s\n", TTF_GetError());
				}
				else
				{
					txt_texture = SDL_CreateTextureFromSurface(framework::renderer, temp_surface);
					if (txt_texture == NULL)
					{
						printf("FAILED TO RECREATE TEXTURE FROM SURFACE! SDL_IMAGE_ERROR: %s\n", SDL_GetError());
					}
					else
					{
						m_width = temp_surface->w;
						m_height = temp_surface->h;
					}
					SDL_FreeSurface(temp_surface);
				}
				
			}
		}
		rerender_text = false;
		SDL_Rect dst_rect = { x, y, m_width, m_height };
		if (clip != NULL)
		{
			dst_rect.w = clip->w;
			dst_rect.h = clip->h;
		}
	
		SDL_RenderCopyEx(framework::renderer, txt_texture, clip, &dst_rect, angle, center, flip);
		
	}
	void clean()
	{
		if (txt_texture != nullptr)
		{
			SDL_DestroyTexture(txt_texture);
			//m_texture = nullptr;
			//TTF_CloseFont(m_font);
			//m_font = nullptr;

			m_width = 0;
			m_height = 0;
		}
	}

private:
	SDL_Texture* txt_texture;
	TTF_Font* m_font;

	std::string m_input_text;
	SDL_Color m_color;

	bool rerender_text;
	int m_width;
	int m_height;

};

class t_level
{
public:
	t_level()
	{
		SDL_StartTextInput();
	}
	~t_level()
	{

	}

	void load()
	{
		background.load_img_file("assets/template2.png");
		input_t.load_font("assets/fourBit.ttf", 24);
		output_t.load_font("assets/fourBit.ttf", 12);
		input_t.load_text("QUESTION", { 255, 33, 66 });
		output_t.load_text("LOL", { 66, 33, 66 });
	}
	void handle_events(SDL_Event& input)
	{
		input_t.handle_events(input);
		output_t.handle_events(input);
	}
	void render()
	{
		background.draw_texture(0, 0, NULL, 0.0, NULL, SDL_FLIP_NONE);

		SDL_Rect top = { 0, 0, 64, 24 };
		SDL_Rect bottom = { 0, 450, 64, 24 };
		input_t.render(0, 0, &top, 0.0, NULL, SDL_FLIP_NONE);
		output_t.render(0, 0, &bottom, 0.0, NULL, SDL_FLIP_NONE);
	}
	void clean()
	{
		background.clean();
		input_t.clean();
		output_t.clean();
	}
private:
	texture background;
	text input_t;
	text output_t;

};

#endif