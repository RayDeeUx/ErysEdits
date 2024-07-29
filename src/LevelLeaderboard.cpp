#ifndef GEODE_IS_MACOS
#include <Geode/modify/LevelLeaderboard.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyLevelLeaderboard, LevelLeaderboard) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	bool init(GJGameLevel* p0, LevelLeaderboardType p1, LevelLeaderboardMode p2) {
		if (!LevelLeaderboard::init(p0, p1, p2)) { return false; }
		if (getChildByIDRecursive("update-button")) {
			this->defineKeybind("refresh-page"_spr, [this]() {
				if (Utils::isLevelLeaderboard()) { // infoLayerRecursive because sometimes it's a child of profilePage
					if (Utils::modEnabled() && Utils::getBool("refreshAnywhere")) {
						LevelLeaderboard::onUpdate(nullptr);
					} else { Utils::refreshKeybindDisabled(); }
				}
			});
		}
		return true;
	}
};
#endif