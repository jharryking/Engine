#pragma once

#include "EventHandler.h"

class Engine {
public:
	Engine() {}
	~Engine();


	bool start();

private:
	Window* window = new Window(800, 600, false, true);
	Renderer* renderer = new Renderer(window);
	EventHandler event_handler{ renderer };
};



