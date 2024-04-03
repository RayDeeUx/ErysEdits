#include <Geode/modify/PlayerObject.hpp>
#include <regex>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyPlayerObject, PlayerObject) {
	void animatePlatformerJump(float p0) {
		if (!(Utils::modEnabled() && Utils::get("disablePlatformerJumpAnim"))) { PlayerObject::animatePlatformerJump(p0); }
	}
	void playerDestroyed(bool p0) {
		auto gm = GameManager::get();
		auto manager = Manager::getSharedInstance();
		manager->isPlayerDead = true;
		if (Utils::modEnabled() && gm->getPlayLayer()) {
			auto fmod = FMODAudioEngine::sharedEngine();
			auto pl = PlayLayer::get();
			if (Utils::get("forceStopMusicOnDeath")) {
				if (pl && this == pl->m_player2 && !pl->m_level->m_twoPlayerMode) { return; } // avoid stopping sfx twice -- thank you clicksounds
				fmod->stopAllMusic();
				fmod->stopAllEffects();
			}
			if (Utils::get("forcePlayDeathSFXOnDeath") && manager->isLevelDisablingDeathSFX) {
				if (pl && this == pl->m_player2 && !pl->m_level->m_twoPlayerMode) { return; } // avoid playing death sfx twice -- thank you clicksounds
				std::string deathSFX = "explode_11.ogg";
				float volume = gm->m_sfxVolume;
				auto randDeathSounds = Loader::get()->getLoadedMod("adam_729.randdeathsounds");
				auto controlVanillaSFX = Loader::get()->getLoadedMod("raydeeux.controlvanillasfx");
				// mimic adam_729's randomdeathsounds' behavior
				if (randDeathSounds && randDeathSounds->getSettingValue<bool>("enabled")) {
					std::vector<std::string> deathSounds;
					for (const auto& file : std::filesystem::directory_iterator((randDeathSounds->getSaveDir() / "deathsounds").string())) {
						if (Utils::isSupportedExtension(file.path().extension().string())) {
							deathSounds.push_back(file.path().string());
						}
					}
					if (!deathSounds.empty()) { deathSFX = deathSounds[rand() % deathSounds.size()].c_str(); }
				}
				// mimic controlvanillasfx's behavior
				if (controlVanillaSFX && controlVanillaSFX->getSettingValue<bool>("enabled")) {
					if (!randDeathSounds || !randDeathSounds->getSettingValue<bool>("enabled")) { volume = controlVanillaSFX->getSettingValue<int64_t>("volume") / 100.f; }
					else { volume = 1.f; }
				}
				fmod->playEffect(deathSFX, 1.f, 1.f, volume);
			}
		}
		PlayerObject::playerDestroyed(p0);
	}
};