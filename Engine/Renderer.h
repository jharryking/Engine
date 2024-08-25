#pragma once
#include <vector>
#include "Window.h"


/*

MAKE TEXTURE CLASS

*/


class Renderer {
public:
	Renderer() = delete;
	Renderer(Window* window);

	void render();
	void update();
	void render_window_size(int width, int height, bool fullscreen, bool border);
	void render_toggle_fullscreen();

private:
	Window* _window_p = nullptr;


	bool initialize();
	void init_color_buff();

	void draw_pixel(int x, int y,  uint32_t color);
	void draw_grid();
	void draw_rect(int x, int y, int width, int height, uint32_t color);

	SDL_Renderer* _renderer = nullptr;

	uint32_t* _color_buffer = nullptr;
	int _color_buffer_width;
	int _color_buffer_height;

	void render_color_buffer();
	void clear_color_buffer(uint32_t color);

	SDL_Texture* _color_buffer_texture = nullptr;

};

