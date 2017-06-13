#include "Game.h"

#include <vector>

__attribute__ ((visibility ("default")))
GameRegistrar::GameRegistrar(Creator func) {

}

__attribute__((visibility("default")))
Creator& GameRegistrar::GetCreator() {
    static Creator creatorFunc;
    return creatorFunc;
}

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

UPtr<Game>
Game::Create() {
    Creator Create = GameRegistrar::GetCreator();
    return (*Create)();
}

Game::Game() {
	impl = std::make_shared<Impl>();
}
void Game::OnUpdate(std::shared_ptr<Updater> updater) {
	impl->OnUpdate(updater);
}


__attribute__ ((visibility ("default")))
void RegisterGame() {

}