#include <Geode/modify/PlayerObject.hpp>
#include <regex>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyPlayerObject, PlayerObject) {
	static void onModify(auto & self)
	{
		self.setHookPriority("PlayerObject::playerDestroyed", INT64_MAX - 1);
	}
	void animatePlatformerJump(float p0) {
		if (!(Utils::modEnabled() && Utils::get("disablePlatformerJumpAnim"))) { PlayerObject::animatePlatformerJump(p0); }
	}
	void playerDestroyed(bool p0) {
		Manager::getSharedInstance()->isPlayerDead = true;
		if (Utils::modEnabled() && GameManager::get()->getPlayLayer()) {
			auto fmod = FMODAudioEngine::sharedEngine();
			auto pl = PlayLayer::get();
			if (Utils::get("forceStopMusicOnDeath")) {
				if (pl && this == pl->m_player2 && !pl->m_level->m_twoPlayerMode) { return; } // avoid stopping sfx twice -- thank you clicksounds
				fmod->stopAllMusic();
				fmod->stopAllEffects();
			}
		}
		PlayerObject::playerDestroyed(p0);
	}
};