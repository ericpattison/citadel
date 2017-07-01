#include "../../keep/types.h"
#include "../../keep/constants.h"
#include "../../keep/window/OpenGLWindow.h"

#include "../../keep/utils/linux.h"

#include "../game/Game.h"

#include <iostream>
#include <stdio.h>

int main(int argc, char const* argv[]) {
	int result = 0;

	WindowInfo windowInfo;
	windowInfo.width = 1280;
	windowInfo.height = 720;
	windowInfo.title = L"Citadel";

	OpenGLWindow window(windowInfo);
	SPtr<Device> device = window.AcquireDevice();
	UPtr<Game> game = Game::Create(device);

	while (window.ProcessMessages() != WindowStatus::Quit) {
		printf("Frame\n"); 
		device->Clear();
		device->Present();
	}

	window.Exit(result);
	return result;
}
