#ifndef __APPLE__
#include <Geode/modify/EndLevelLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyEndLevelLayer, EndLevelLayer) {
	void onMenu(cocos2d::CCObject* sender) {
		if (Utils::modEnabled() && Utils::get("hideLevelCompleteVisuals")) { Manager::getSharedInstance()->isLevelComplete = false; }
		EndLevelLayer::onMenu(sender);
	}
};
#endif