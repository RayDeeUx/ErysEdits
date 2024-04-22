#include <Geode/modify/EditLevelLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

// apply the appropriate values to the gamevars for local levels (from "play" button in local edit level layer page)
class $modify(MyEditLevelLayer, EditLevelLayer) {
	void onPlay(CCObject* sender) {
		Utils::applyGMGVs(m_level->m_isVerifiedRaw);
		EditLevelLayer::onPlay(sender);
	}
};