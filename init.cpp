#include "init.h"
#include "texture_loader.h"
#include "text.h"
#include "shape.h"

static window main_window;
SDL_Event framework::input;
SDL_Renderer* framework::renderer = nullptr;
bool framework::is_running = false;

TTF_Font* gfont = NULL;
texture testicle;

t_level level;


void framework::initialize(std::string title)
{
	int flags = 0;
	int image_flags = IMG_INIT_PNG;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL2 FAILED to initialize! SDL_Error: %s \n", SDL_GetError());
		is_running = false;
	}
	else
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		main_window.create_window(title);
		renderer = main_window.create_renderer();
		if (renderer == NULL)
		{
			printf("SDL2 window and or renderer interface(s) failed to initialize!\n");
			is_running = false;
		}
		else if (!(IMG_Init(image_flags) & image_flags))
		{
			printf("SDL_IMAGE FAILED TO INITIALIZE -IMG_INIT_PNG- IMAGEFLAGS! SDL_IMAGE_ERROR: %s\n", IMG_GetError());
			is_running = false;
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			is_running = true;
		}
		if (TTF_Init() != 0)
		{
			printf("TTF FAILED TO INITIALIZE!");
		}
	}
}
void framework::load_media()
{
	level.load();
}
void framework::handle_events()
{
	/*essential*/
	SDL_PollEvent(&input);
	switch (input.type)
	{
	case SDL_QUIT:
		is_running = false;
		break;
	default:
		break;
	}
	//interface input controller
	main_window.handle_window_event(input);

	//other events:
	level.handle_events(input);

}
void framework::update()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}
void framework::render()
{
	level.render();
	SDL_RenderPresent(renderer);
}
void framework::close()
{
	

	//constant
	main_window.clean();
	if (renderer != NULL)
	{
		
		SDL_DestroyRenderer(framework::renderer);
		framework::renderer = NULL;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		testicle.clean();
		
	}
	
}



void window::create_window(std::string &title)
{
	//Set texture filtering to linear TEMP POSITION
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("WARNING: Linear texture filtering not enabled!");
	}

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (m_window != NULL)
	{
		window_has_mf = true;
		window_has_kb = true;
		window_width = SCREEN_WIDTH;
		window_height = SCREEN_HEIGHT;
		framework::is_running = true;
	}
	else
	{
		framework::is_running = false;
	}
}
SDL_Renderer* window::create_renderer()
{
	return SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}
void window::handle_window_event(SDL_Event &inputw)
{
	if (inputw.type == SDL_WINDOWEVENT)
	{
		switch (inputw.window.event)
		{
			//Get new dimensions and repaint on window size change
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			window_width = inputw.window.data1;
			window_height = inputw.window.data2;
			SDL_RenderPresent(framework::renderer);
			break;

			//Repaint on exposure
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(framework::renderer);
			break;

			//Mouse entered window
		case SDL_WINDOWEVENT_ENTER:
			window_has_mf = true;
			break;

			//Mouse left window
		case SDL_WINDOWEVENT_LEAVE:
			window_has_mf = false;
			break;

			//Window has keyboard focus
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			window_has_kb = true;
			break;

			//Window lost keyboard focus
		case SDL_WINDOWEVENT_FOCUS_LOST:
			window_has_kb = false;
			break;
			//Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			window_is_mini = true;
			break;

			//Window maxized
		case SDL_WINDOWEVENT_MAXIMIZED:
			window_is_mini = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			window_is_mini = false;
			break;
		}

	}
	//Enter exit full screen on return key
	else if (inputw.type == SDL_KEYDOWN && inputw.key.keysym.sym == SDLK_ESCAPE)
	{
		if (window_is_full)
		{
			SDL_SetWindowFullscreen(m_window, SDL_FALSE);
			window_is_full = false;
		}
		else
		{
			SDL_SetWindowFullscreen(m_window, SDL_TRUE);
			window_is_full = true;
			window_is_mini = false;
		}
	}
}
void window::clean()
{
	
	if (m_window != NULL)
	{
		window_has_mf = false;
		window_has_kb = false;
		window_width = 0;
		window_height = 0;
		SDL_DestroyWindow(m_window);
		
	}
	
}