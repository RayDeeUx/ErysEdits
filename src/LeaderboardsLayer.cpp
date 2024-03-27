#include <Geode/modify/LeaderboardsLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyLeaderboardsLayer, LeaderboardsLayer) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	bool init(LeaderboardState p0) {
		if (!LeaderboardsLayer::init(p0)) { return false; }
		this->defineKeybind("refresh-page"_spr, [this]() {
			if (Loader::get()->isModLoaded("cvolton.betterinfo") && getChildByIDRecursive("cvolton.betterinfo/refresh-button") && Utils::isSceneRunning("LeaderboardsLayer") && Utils::noProfilePage() && Utils::noInfoLayer() && !Utils::isInfoLayerRecursive()) {
				if (Utils::modEnabled() && Utils::get("refreshAnywhere")) {
					// code from cvolton's betterinfo reused with permission
					// consent: https://discord.com/channels/911701438269386882/911702535373475870/1220852637608448050
					auto GLM = GameLevelManager::sharedState();
					GLM->updateUserScore();
					GLM->m_storedLevels->removeObjectForKey("leaderboard_creator");
					GLM->m_storedLevels->removeObjectForKey("leaderboard_friends");
					GLM->m_storedLevels->removeObjectForKey("leaderboard_global");
					GLM->m_storedLevels->removeObjectForKey("leaderboard_top");

					auto layer = LeaderboardsLayer::create(GLM->m_leaderboardState);
					auto scene = CCScene::create();
					scene->addChild(layer);
					CCDirector::sharedDirector()->replaceScene(scene);
				} else {
					if (Loader::get()->isModLoaded("cvolton.betterinfo")) { Utils::refreshKeybindDisabled(); } // only show if betterinfo is present, otherwise it'd be confusing
				}
			}
		});
		return true;
	}
};