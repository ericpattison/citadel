#include "../../keep/types.h"
#include "../../keep/constants.h"
#include "../../keep/window/Window.h"

#include "../game/Game.h"

#include <iostream>

void main(int argc, char const* argv[]) {
	int result = 0;

	WindowInfo windowInfo;
	windowInfo.width = 1280;
	windowInfo.height = 720;
	windowInfo.title = "Citadel";

	Window window(windowInfo);
	std::unique_ptr<Game> game = Game::Create(window);

	while (window.ProcessMessages() != WindowStatus::Quit) {

	}

	window.Exit(result);
}