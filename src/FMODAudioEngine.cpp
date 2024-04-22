#include <Geode/modify/FMODAudioEngine.hpp>
#include "Manager.hpp"
#include "Utils.hpp"
#include <regex>

using namespace geode::prelude;

static std::regex songEffectRegex(R"(.*(?:\\|\/)(\S+)\.(mp3|ogg))", std::regex::optimize | std::regex::icase);

class $modify(MyFMODAudioEngine, FMODAudioEngine) {
	#ifndef GEODE_IS_MACOS
	void playEffectAdvanced(gd::string p0, float p1, float p2, float p3, float p4, bool p5, bool p6, int p7, int p8, int p9, int p10, bool p11, int p12, bool p13, bool p14, int p15, int p16, float p17, int p18) {
		auto manager = Manager::getSharedInstance();
		auto vanillaSFX = manager->vanillaSFX;
		std::string path = p0;
		std::smatch match;
		if (path.find("geode") != std::string::npos && (path.find("mods") != std::string::npos || path.find("config") != std::string::npos)) {
			manager->lastPlayedEffect = "[From another Geode mod]";
		} else if (std::find(vanillaSFX.begin(), vanillaSFX.end(), path) == vanillaSFX.end()) {
			if (std::regex_match(path, match, songEffectRegex)) {
				manager->lastPlayedEffect = fmt::format("{}.{}", match[1].str(), match[2].str());
			} else {
				manager->lastPlayedEffect = fmt::format("{}", path);
			}
		}
		FMODAudioEngine::playEffectAdvanced(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18);
	}
	#endif
	void playEffect(gd::string p0, float p1, float p2, float p3) {
		auto manager = Manager::getSharedInstance();
		auto badSFX = manager->badSFX;
		if (std::find(badSFX.begin(), badSFX.end(), std::string(p0)) == badSFX.end() || Utils::isSceneRunning("PauseLayer") || !(Utils::modEnabled() && Utils::get("disableRewardsSFX")) || !manager->isPlayerDead) {
			FMODAudioEngine::playEffect(p0, p1, p2, p3);
		}
	}
	void loadMusic(gd::string p0, float p1, float p2, float p3, bool p4, int p5, int p6) {
		auto manager = Manager::getSharedInstance();
		std::string path = p0;
		std::smatch match;
		if (path.find("fleym.") != std::string::npos) {
			manager->lastPlayedSong = "[Replaced by Jukebox]";
		} else if (path.find("geode") != std::string::npos && (path.find("mods") != std::string::npos || path.find("config") != std::string::npos)) {
			manager->lastPlayedSong = "[From another Geode mod]";
		} else if (std::regex_match(path, match, songEffectRegex)) {
			manager->lastPlayedSong = fmt::format("{}.{}", match[1].str(), match[2].str());
		} else {
			manager->lastPlayedSong = fmt::format("{}", path);
		}
		FMODAudioEngine::loadMusic(p0, p1, p2, p3, p4, p5, p6);
	}
};