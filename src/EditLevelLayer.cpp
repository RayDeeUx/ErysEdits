#include <Geode/modify/EditLevelLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

// apply the appropriate values to the gamevars for local levels (from "play" button in local edit level layer page)
class $modify(MyEditLevelLayer, EditLevelLayer) {
	void onPlay(CCObject* sender) {
		Utils::applyGMGVs(m_level->m_isVerifiedRaw);
		if (Utils::modEnabled() && Utils::get("forcePlayDeathSFXOnDeath") && Utils::get("advancedForceDeathSFX") && Utils::isRandDeathSounds()) { Utils::decompLevelDisablesSFX(m_level->m_levelString); }
		EditLevelLayer::onPlay(sender);
	}
};