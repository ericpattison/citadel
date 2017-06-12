#include "Game.h"

#include <vector>

class Game::Impl {
public:
	Impl() {
	}

	void OnUpdate(std::shared_ptr<Updater> updater) {
		updaters.push_back(updater);
	}

private:
	std::vector<std::shared_ptr<Updater>> updaters;
};

/*UPtr<Game>
Game::Create() {
	GameRegistrar::Creator Create = GameRegistrar::GetCreator();
	UPtr<Game> game = (*Create)();

	return game;
}*/

Game::Game() {
	impl = std::make_shared<Impl>();
}
void Game::OnUpdate(std::shared_ptr<Updater> updater) {
	impl->OnUpdate(updater);
}

__attribute__ ((visibility ("default"))) void RegisterGame() {

}