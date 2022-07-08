#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H
#include "init.h"

class texture
{
public:
	texture();
	~texture();

	bool load_img_file(std::string path);
	bool load_text(std::string text, TTF_Font* font, SDL_Color text_color);
	void draw_texture(int x, int y, SDL_Rect* clip , double angle, SDL_Point* center, SDL_RendererFlip flip);
	void clean();

	//modifiers


	//Clip handlers
	SDL_Rect set_clip(SDL_Rect r) { return m_clip = r; }
	SDL_Rect get_clip() const { return m_clip; }

	Sint16 set_clip_x(Sint16 x) { return m_clip.x = x; }
	Sint16 set_clip_y(Sint16 y) { return m_clip.y = y; }
	Uint16 set_clip_w(Uint16 w) { return m_clip.w = w; }
	Uint16 set_clip_h(Uint16 h) { return m_clip.h = h; }

	Sint16 get_clip_x() const { return m_clip.x; }
	Sint16 get_clip_y() const { return m_clip.y; }
	Uint16 get_clip_w() const { return m_clip.w; }
	Uint16 get_clip_h() const { return m_clip.h; }
protected:
	SDL_Rect m_clip = { 0, 0, 0, 0 };

private:
	SDL_Texture* m_texture;
	float m_width;
	float m_height;
	
};




#endif