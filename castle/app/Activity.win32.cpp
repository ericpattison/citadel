#include "../../keep/types.h"
#include "../../keep/constants.h"
#include "../../keep/window/OpenGLWindow.h"

#include "../game/Game.h"

#include <iostream>

int main(int argc, char const* argv[]) {
	int result = 0;

	WindowInfo windowInfo;
	windowInfo.width = 1280;
	windowInfo.height = 720;
	windowInfo.title = L"Citadel";

	OpenGLWindow window(windowInfo);
	std::unique_ptr<Game> game = Game::Create();

	while (window.ProcessMessages() != WindowStatus::Quit) {

	}

	window.Exit(result);
	return result;
}
