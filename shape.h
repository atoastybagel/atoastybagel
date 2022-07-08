#ifndef SHAPE_H
#define SHAPE_H
#include "init.h"

class line
{
private:
	SDL_Point start_point{};
	SDL_Point end_point{};
	SDL_Color m_color{};
public:
	line(SDL_Point x_pair, SDL_Point y_pair, SDL_Color color)
		: start_point{ x_pair }, end_point{ y_pair }, m_color{ color }
	{}
	~line()
	{
		start_point.x = 0;
		start_point.y = 0;
		end_point.x = 0;
		end_point.y = 0;
		m_color = { 0, 0, 0, 0 };
	}

	void draw()
	{
		SDL_SetRenderDrawColor(framework::renderer, m_color.r, m_color.g, m_color.b, m_color.a);
		SDL_RenderDrawLine(framework::renderer, start_point.x, start_point.y, end_point.x, end_point.y);
	}
};


class rectangle
{
public:
	rectangle()
	{};
	~rectangle()
	{};

	void draw(int x, int y, int w, int h)
	{
		SDL_Rect sclip = { x, y, w, h };
		SDL_SetRenderDrawColor(framework::renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(framework::renderer, &sclip);
	}

};




#endif