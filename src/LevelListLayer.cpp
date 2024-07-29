#ifndef GEODE_IS_MACOS
#include <Geode/modify/LevelListLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyLevelListLayer, LevelListLayer) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	bool init(GJLevelList* p0) {
		if (!LevelListLayer::init(p0)) { return false; }
		if (Utils::getModVersion(Utils::getMod("geode.node-ids")) == "v1.11.0") this->setID("LevelListLayer");
		if (Utils::getChildBySpriteFrameNameRecursive(this, "GJ_updateBtn_001.png")) {
			this->defineKeybind("refresh-page"_spr, [this]() {
				if (Utils::isSceneRunning("LevelListLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::getBool("refreshAnywhere")) {
						LevelListLayer::onRefresh(nullptr);
					} else { Utils::refreshKeybindDisabled(); }
				}
			});
		}
		return true;
	}
};
#endif