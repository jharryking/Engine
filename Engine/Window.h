#pragma once
//#include <memory>
#include "SDL.h"
#include <iostream>
#include <assert.h>

class Window {
public:
	~Window();
	Window() = delete;
	Window(int width, int height, bool fullscreen, bool border);

	bool set_window_size(int width, int height, bool fullscreen, bool border);
	void toggle_fullscreen();

	int get_width() { return _width; }
	int get_height() { return _height; }
	SDL_Window* get_SDL_window() { return _window; }
private:
	int _width;
	int _height;
	bool _is_fullscreen;
	bool _is_bordered;
	SDL_Window* _window = nullptr;

};
