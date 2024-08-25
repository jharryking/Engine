#include "EventHandler.h"

EventHandler::~EventHandler() {
	renderer_p = nullptr;
}

EventHandler::EventHandler(Renderer* renderer) {
	renderer_p = renderer;
}

void EventHandler::process_input() {
	//std::cout << &(Engine::instance().renderer) << "    " << &(_engine_p->renderer);
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				is_running = false;
			else if (event.key.keysym.sym == SDLK_f) // fullscreen
				renderer_p->render_toggle_fullscreen();
			break;
		}
	}
	SDL_QUIT;
}
