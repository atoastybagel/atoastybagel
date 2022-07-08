#ifndef INIT_H
#define INIT_H

#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class framework
{
public:
	framework()
	{
		frame = 0;
	}
	void initialize(std::string title);
	void load_media();
	void handle_events();
	void update();
	void render();
	void close();

	static SDL_Renderer* renderer;
	static SDL_Event input;
	static bool is_running;
private:
	int frame;
	
};

class window
{
public:
	window()
	{
		m_window = NULL;
		window_width = 0;
		window_height = 0;
		window_has_mf = false;
		window_has_kb = false;
		window_is_full = false;
		window_is_mini = false;

	}
	//window initializer member functions
	void create_window(std::string &title);
	SDL_Renderer* create_renderer();
	void handle_window_event(SDL_Event &inputw);
	void clean();
private:
	//main window (private to protect from user tampering)
	SDL_Window* m_window;
	//contains windows current dimensions
	int window_width;
	int window_height;
	//user window event booleans
	bool window_has_mf;
	bool window_has_kb;
	bool window_is_full;
	bool window_is_mini;
public:
	//Window focii member functions
	int get_window_width() { return window_width; }
	int get_window_height() { return window_height; }
	bool window_mouse_focus() { return window_has_mf; }
	bool window_keyboard_focus() { return window_has_kb; }
	bool window_is_fullscreen() { return window_is_full; }
	bool window_is_minimized() { return window_is_mini; }
private: //temporary screen dimension ints holder
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
};
#endif