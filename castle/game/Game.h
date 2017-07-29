#ifndef _GAME_H_
#define _GAME_H_

#include "../../keep/types.h"
#include "../../keep/constants.h"
#include "Updater.h"
#include "../renderers/Renderer.h"
#include "../../keep/window/SystemWindow.h"

#include <memory>


class Game {
public:
	static UPtr<Game> Create(SPtr<Device> device);

	Game();

	virtual void Update() = 0;
	virtual void Render() = 0;

	void DoUpdate();
	void DoRender();

	void OnUpdate(std::shared_ptr<Updater> updater);
	void OnRender(SPtr<Renderer> renderer);

private:
	class Impl;
	std::shared_ptr<Impl> impl;
};

typedef UPtr<Game> (*Creator)(SPtr<Device>);
extern "C" {
    struct GameRegistrar {
        GameRegistrar(Creator func);
        static Creator& GetCreator();
    };
}

#endif
