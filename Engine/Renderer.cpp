#include "Renderer.h"
#include <iostream>
#include <assert.h>


Renderer::Renderer(Window* window) {
	_window_p = window;
	assert(initialize());
	//exit();
}


void Renderer::render() {
	render_color_buffer();
	clear_color_buffer(0x000000);
	SDL_RenderPresent(_renderer);
}

void Renderer::update() {
	draw_grid();
	draw_pixel(0, 0, 0xFF00FF);
	draw_rect(500, 0, 100, 50, 0xFF0000);
	return;
}

void Renderer::render_window_size(int width, int height, bool fullscreen, bool border) {
	_window_p->set_window_size(width, height, fullscreen, border);
	init_color_buff(); //Replaces old color buffer with new size
}

void Renderer::render_toggle_fullscreen() {
	_window_p->toggle_fullscreen();
	init_color_buff();
}

bool Renderer::initialize() {
	// MAKE SURE IT ISN'T ALREADY INIT
	if (_renderer != nullptr) {
		return false;
	}

	//INIT RENDERER
	_renderer = SDL_CreateRenderer(_window_p->get_SDL_window(), -1, 0); // -1 gets primary display
	if (!_renderer) {
		std::cout << "Error creating SDL renderer" << SDL_GetError();
		return false;
	}

	//INIT COLOR BUFFER AND COLOR BUFFER TEXTURE
	init_color_buff();

	return true;

}

void Renderer::init_color_buff() {

	if (_color_buffer != nullptr) {
		delete[] _color_buffer;
		SDL_DestroyTexture(_color_buffer_texture);
	}

	// Gets dimensions of color buffer
	_color_buffer_width = _window_p->get_width();
	_color_buffer_height = _window_p->get_height();


	// Allocate memory for the color buffer
	_color_buffer = new uint32_t[_color_buffer_height * _color_buffer_width];
	// Create SDL texture to display color buffer
	_color_buffer_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		_color_buffer_width, _color_buffer_height); // argb 8888 8*4 = 32, uint32 uses 32 bits


}

void Renderer::draw_pixel(int x, int y, uint32_t color) {
	if ((y >= _color_buffer_height) || (x >= _color_buffer_width)) {
		return;
	}
	_color_buffer[(_color_buffer_width * y) + x] = color;
}

void Renderer::draw_grid() {
	for (int y = 0; y < _color_buffer_height; y += 10) {
		for (int x = 0; x < _color_buffer_width; x += 10) {
			draw_pixel(x, y, 0xFF333333);
		}
	}
}

void Renderer::render_color_buffer() {
	SDL_UpdateTexture(_color_buffer_texture, NULL, _color_buffer,
		(int)(sizeof(uint32_t) * _color_buffer_width)); // Copy color buffer into texture
	SDL_RenderCopy(_renderer, _color_buffer_texture, NULL, NULL); // Copy entire texture into renderer
}

void Renderer::clear_color_buffer(uint32_t color) {
	// sets all pixels in color buffer
	for (int y = 0; y < _color_buffer_height; y++) {
		for (int x = 0; x < _color_buffer_width; x++) {
			draw_pixel(x, y, color);
		}
	}
}

void Renderer::draw_rect(int x, int y, int width, int height, uint32_t color) {
	for (int y_p = 0; y_p < height; y_p++) {
		for (int x_p = 0; x_p < width; x_p++) {
			draw_pixel(x_p + x, y_p + y, color);
		}
	}
	//std::cout << "Rect created at " << x << " " << y  << "\n";
}
