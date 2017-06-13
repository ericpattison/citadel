
#include "../../keep/window/OpenGLWindow.h"
#include "../game/Game.h"

#include "../../keep/utils/android.h"

void android_main(struct android_app* state) {
	int result = 0;

	AndroidWindowInfo windowInfo;
	windowInfo.appState = state;

	OpenGLWindow window(windowInfo);
    UPtr<Game> game = Game::Create();

	while(window.ProcessMessages() != WindowStatus::Quit) { }

	window.Exit(result);
}