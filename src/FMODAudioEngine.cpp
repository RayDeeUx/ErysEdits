#include <Geode/modify/FMODAudioEngine.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

// const std::list<std::string> vanillaSFX = { "achievement_01.ogg", "buyItem01.ogg", "buyItem03.ogg", "chest07.ogg", "chest08.ogg", "chestClick.ogg", "chestLand.ogg", "chestOpen01.ogg", "counter003.ogg", "crystal01.ogg", "door001.ogg", "door01.ogg", "door02.ogg", "endStart_02.ogg", "explode_11.ogg", "gold01.ogg", "gold02.ogg", "grunt01.ogg", "grunt02.ogg", "grunt03.ogg", "highscoreGet02.ogg", "magicExplosion.ogg", "playSound_01.ogg", "quitSound_01.ogg", "reward01.ogg", "secretKey.ogg", "unlockPath.ogg" };
const std::list<std::string> badSFX = { "magicExplosion.ogg", "gold02.ogg", "secretKey.ogg" };

using namespace geode::prelude;

class $modify(MyFMODAudioEngine, FMODAudioEngine) {
	void playEffect(gd::string p0, float p1, float p2, float p3) {
		auto manager = Manager::getSharedInstance();
		if (std::find(badSFX.begin(), badSFX.end(), std::string(p0)) == badSFX.end() || !(Utils::modEnabled() && Utils::get("disableRewardsSFX")) || !manager->isPlayerDead) {
			FMODAudioEngine::playEffect(p0, p1, p2, p3);
        }
	}
};