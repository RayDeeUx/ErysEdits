#include <Geode/modify/LevelPage.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

// restore the original values of the gamevars found during game launch (main levels)
class $modify(MyLevelPage, LevelPage) {
	void onPlay(CCObject* sender) {
		Utils::restoreOrigGMGVs(GameManager::get(), true, true);
		if (Utils::modEnabled() && Utils::get("forcePlayDeathSFXOnDeath") && Utils::get("advancedForceDeathSFX") && Utils::isRandDeathSounds()) { Utils::decompLevelDisablesSFX(m_level->m_levelString); }
		LevelPage::onPlay(sender);
	}
	#ifdef GEODE_IS_WINDOWS
	void onSecretDoor(CCObject* sender) {
		if (Utils::shiftDown()) { LevelPage::onSecretDoor(sender); }
	}
	#endif
};