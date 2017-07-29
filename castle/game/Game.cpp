#include "Game.h"
#include "../../keep/containers/vector.h"

#include <functional>

template<class F, class I>
UpdateMethod BindUpdateMethod(F func, I inst) {
	return std::bind(func, inst);
}

template<class F, class I>
UpdateMethod BindRenderMethod(F func, I inst) {
	return std::bind(func, inst);
}

EXPORT
GameRegistrar::GameRegistrar(Creator func) {
	GetCreator() = func;
}

EXPORT
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

	void OnRender(SPtr<Renderer> renderer) {
		renderers.push(renderer);
	}

	void DoUpdate(UpdateMethod update) {}

	void DoRender(RenderMethod render) {
		auto pitr = MakeSPtr<Vector<SPtr<Renderer>>::Iterator>(renderers.begin());
		auto next = MakeSPtr<next_t>();
		auto weakNext = std::weak_ptr<next_t>(next);

		*next = [this, render, pitr, weakNext] {
			auto&it = *pitr;
			if (it != renderers.end()) {
				auto& func = (*it)->RenderMethod();
				it++;
				auto nxt = weakNext.lock();
				func(nxt);
			}
			else {
				render();
			}
		};
		(*next)();
	}

private:
	std::vector<std::shared_ptr<Updater>> updaters;
	Vector<SPtr<Renderer>> renderers;
};

UPtr<Game>
Game::Create(SPtr<Device> device) {
    Creator Create = GameRegistrar::GetCreator();
    return (*Create)(device);
}

Game::Game() {
	impl = std::make_shared<Impl>();
}

void Game::DoUpdate() {
	impl->DoUpdate(BindUpdateMethod(&Game::Update, this));
}

void Game::DoRender() {
	impl->DoRender(BindRenderMethod(&Game::Render, this));
}

void Game::OnUpdate(std::shared_ptr<Updater> updater) {
	impl->OnUpdate(updater);
}

void Game::OnRender(SPtr<Renderer> renderer) {
	impl->OnRender(renderer);
}