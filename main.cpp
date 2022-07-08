#include "init.h"

framework* engine = nullptr;
int main(int argc, char* args[])
{
	engine = new framework;
	engine->initialize("Practice Box yuh");
	engine->load_media();
	while (engine->is_running)
	{
		
		engine->handle_events();
		engine->update();
		engine->render();
	}
	engine->close();
	return 0;
}