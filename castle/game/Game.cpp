#include "Game.h"

#include <vector>
#include <memory>

#include "../../watchtower/device/Device.vulkan.h"

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


Game::Game(SystemWindow& window) {
	impl = std::make_shared<Impl>();
}
void Game::OnUpdate(std::shared_ptr<Updater> updater) {
	impl->OnUpdate(updater);
}
