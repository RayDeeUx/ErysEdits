#include <Geode/modify/LevelPage.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

// restore the original values of the gamevars found during game launch (main levels)
class $modify(MyLevelPage, LevelPage) {
	void onPlay(CCObject* sender) {
		Utils::restoreOrigGMGVs(GameManager::get(), true, true);
		LevelPage::onPlay(sender);
	}
	#ifndef GEODE_IS_MACOS
	void onSecretDoor(CCObject* sender) {
		if (Utils::shiftDown()) { LevelPage::onSecretDoor(sender); }
	}
	#endif
};