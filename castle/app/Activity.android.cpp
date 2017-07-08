
#include "../../keep/window/OpenGLWindow.h"
#include "../game/Game.h"

#include "../../keep/utils/android.h"

void android_main(struct android_app* state) {
	int result = 0;

	AndroidWindowInfo windowInfo;
	windowInfo.appState = state;

	OpenGLWindow window(windowInfo);
    SPtr<Device> device = nullptr;
    UPtr<Game> game = nullptr;
    while(game == nullptr) {
        window.ProcessMessages();
        if(state->window != nullptr) {
            device = window.AcquireDevice();
            game = Game::Create(device);
        }
    }

	while(window.ProcessMessages() != WindowStatus::Quit) {
        device->Clear();
        game->Render();
        device->Present();
    }

	window.Exit(result);
}