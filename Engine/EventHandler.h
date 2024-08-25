#pragma once

#include "Window.h"
#include "Renderer.h"

class EventHandler {
public:
	~EventHandler();
	EventHandler() = delete;
	EventHandler(Renderer* renderer);

	void process_input();

	bool is_running = true;
private:
	Renderer* renderer_p;
};
