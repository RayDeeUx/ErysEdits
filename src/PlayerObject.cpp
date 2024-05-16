#include <Geode/modify/PlayerObject.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyPlayerObject, PlayerObject) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	static void onModify(auto & self)
	{
		(void) self.setHookPriority("PlayerObject::playerDestroyed", INT32_MAX - 1);
	}
	void playerDestroyed(bool p0) {
		m_fields->manager->isPlayerDead = true;
		if (Utils::modEnabled() && PlayLayer::get()) {
			if (Utils::get("forceStopMusicOnDeath")) {
				auto pl = PlayLayer::get();
				auto fmod = FMODAudioEngine::sharedEngine();
				fmod->pauseAllMusic();
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