#ifndef _GAME_H_
#define _GAME_H_

#include "../../keep/types.h"
#include "../../keep/constants.h"
#include "Updater.h"
#include "../../keep/window/Window.h"

#include <memory>


class Game {
public:
	static std::unique_ptr<Game> Create(Window& window);
	static String Name();

	Game(Window& window);

	virtual void Update() = 0;
	virtual void Render() = 0;

	void OnUpdate(std::shared_ptr<Updater> updater);

private:
	class Impl;
	std::shared_ptr<Impl> impl;
};

#endif