#include "engine.h"

Engine::~Engine() {
	//dont need to delete because it's already deleted in there destuctors
	window = nullptr; 
	renderer = nullptr;
}

bool Engine::start() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error initializing SDL" << SDL_GetError();
		return false;
	}

	while (event_handler.is_running) {
		event_handler.process_input();
		renderer->update();
		renderer->render();
	}
	SDL_Quit();

	return false;
}
