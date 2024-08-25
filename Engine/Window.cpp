#include "Window.h"

Window::~Window() {
	delete _window;
	_window = nullptr;
}

Window::Window(int width, int height, bool fullscreen, bool border) {
	assert(set_window_size(width, height, fullscreen, border));
	//exit();
}

bool Window::set_window_size(int width, int height, bool fullscreen, bool border) {
	uint32_t flag = 0;

	if (fullscreen) { //FULL SCREEN
		if (border) {
			flag = SDL_WINDOW_FULLSCREEN;
		}
		else {
			/* FULL SCREEN BORDERLESS*/
			flag = SDL_WINDOW_BORDERLESS;
			SDL_DisplayMode display_mode;
			SDL_GetCurrentDisplayMode(0, &display_mode);
			_width = display_mode.w;
			_height = display_mode.h;
		}
	}
	else { //NOT FULL SCREEN
		if (border) {
			flag = 0; //bordered flag

			SDL_DisplayMode display_mode;
			SDL_GetCurrentDisplayMode(0, &display_mode);

			if (display_mode.h == height && display_mode.w == width) {
				/* "FULL SCREEN" BORDERED*/
				SDL_Rect r;
				SDL_GetDisplayUsableBounds(0, &r);
				_width = r.w;
				_height = r.h;
			}
			else {
				_width = width;
				_height = height;
			}
		}
	}

	/* INIT WINDOW IF IT DOESN'T EXIST*/
	if (_window == nullptr) {
		_window = SDL_CreateWindow("Graphics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);
		if (!_window) {
			std::cout << "Error creating SDL window" << SDL_GetError();
			return false;
		}
	}
	SDL_SetWindowSize(_window, _width, _height);
	SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_SetWindowFullscreen(_window, flag);
	_is_fullscreen = fullscreen;
	_is_bordered = border;
	std::cout << "Created Window: " << _width << " " << _height << "\n";
	return true;
}

void Window::toggle_fullscreen() {
	if (_is_fullscreen) { // Windowded
		/*Get dimensions of windowded screen*/
		SDL_Rect r;
		SDL_GetDisplayUsableBounds(0, &r);
		_width = r.w;
		_height = r.h;

		/* Set new window size */
		SDL_SetWindowSize(_window, _width, _height);
		SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		SDL_SetWindowFullscreen(_window, 0);

		_is_fullscreen = false;
		_is_bordered = true;

	}
	else { // Fullscreen Borderless
		/*Get dimensions of the entire screen*/
		SDL_DisplayMode display_mode;
		SDL_GetCurrentDisplayMode(0, &display_mode);
		_width = display_mode.w;
		_height = display_mode.h;

		/* Set new window size */
		SDL_SetWindowSize(_window, _width, _height);
		SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		SDL_SetWindowFullscreen(_window, SDL_WINDOW_BORDERLESS);

		_is_fullscreen = true;
		_is_bordered = false;
	}

	std::cout << "Resized Window: " << _width << " " << _height << "\n";
}

