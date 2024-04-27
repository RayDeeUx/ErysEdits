#include <Geode/modify/GJBaseGameLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyGJBaseGameLayer, GJBaseGameLayer) {
	void update(float dt) {
		GJBaseGameLayer::update(dt);
		#ifndef __APPLE__
		Manager::getSharedInstance()->currentChannel = m_gameState.m_currentChannel;
		#endif
	}
	void toggleDualMode(GameObject * p0, bool p1, PlayerObject * p2, bool p3) {
		GJBaseGameLayer::toggleDualMode(p0, p1, p2, p3);
		if (Utils::modEnabled()) {
			auto manager = Manager::getSharedInstance();
			if (Utils::get("addPlayerInfo")) { manager->isDualsTime = p1; }
			// i've had horror stories of hooking playlayer onentertransitiondidfinish so im hooking it here instead
			if (Utils::get("hideLevelCompleteVisuals")) { manager->isLevelComplete = false; }
			manager->isPlayerDead = false;
		}
	}
};