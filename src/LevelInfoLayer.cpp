#include <Geode/modify/LevelInfoLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
	#ifdef GEODE_IS_WINDOWS
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	#endif
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1)) return false;
		#ifdef GEODE_IS_WINDOWS
		if (getChildByIDRecursive("refresh-button")) {
			this->defineKeybind("refresh-page"_spr, [this]() {
				if (Utils::isSceneRunning("LevelInfoLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("refreshAnywhere")) {
						LevelInfoLayer::onUpdate(nullptr);
					} else { Utils::refreshKeybindDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("info-button")) {
			this->defineKeybind("comments"_spr, [this]() {
				if (Utils::isSceneRunning("LevelInfoLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("viewCommentsAnywhere")) {
						LevelInfoLayer::onInfo(nullptr);
					} else { Utils::viewCommentsDisabled(); }
				}
			});
		}
		#endif
		return true;
	}
	// apply the original values of the gamevars found during game launch (online levels)
	void onPlay(CCObject* sender) {
		Utils::restoreOrigGMGVs(GameManager::get(), true, false);
		LevelInfoLayer::onPlay(sender);
	}
};