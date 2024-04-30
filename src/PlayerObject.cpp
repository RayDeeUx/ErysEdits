#include <Geode/modify/PlayerObject.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyPlayerObject, PlayerObject) {
	static void onModify(auto & self)
	{
		(void) self.setHookPriority("PlayerObject::playerDestroyed", INT64_MAX - 1);
	}
	void playerDestroyed(bool p0) {
		Manager::getSharedInstance()->isPlayerDead = true;
		if (Utils::modEnabled() && PlayLayer::get()) {
			if (Utils::get("forceStopMusicOnDeath")) {
				auto pl = PlayLayer::get();
				auto fmod = FMODAudioEngine::sharedEngine();
				fmod->stopAllMusic();
				if (this == pl->m_player2 && pl->m_level->m_twoPlayerMode) {
					PlayerObject::playerDestroyed(p0);
					return; // avoid stopping sfx twice -- thank you clicksounds
				} else {
					fmod->stopAllEffects();
				}
			}
		}
		PlayerObject::playerDestroyed(p0);
	}
};