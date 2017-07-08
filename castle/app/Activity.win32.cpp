#include "../../keep/types.h"
#include "../../keep/constants.h"
#include "../../keep/window/OpenGLWindow.h"

#include "../game/Game.h"
#include <Windows.h>
#include <iostream>

int main(int argc, char const* argv[]) {
	FreeConsole();
	int result = 0;

	WindowInfo windowInfo;
	windowInfo.width = 1280;
	windowInfo.height = 720;
	windowInfo.title = L"Citadel";

	OpenGLWindow window(windowInfo);
	SPtr<Device> device = window.AcquireDevice();
	std::unique_ptr<Game> game = Game::Create(device);

	while (window.ProcessMessages() != WindowStatus::Quit) {
		device->Clear();
		game->Render();
		device->Present();
	}

	window.Exit(result);
	return result;
}
