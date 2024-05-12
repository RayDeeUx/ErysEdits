#include <Geode/modify/FMODAudioEngine.hpp>
#include "Manager.hpp"
#include "Utils.hpp"
#include <regex>

using namespace geode::prelude;

static std::regex songEffectRegex(R"(.*(?:\\|\/)(\S+)\.(mp3|ogg|wav|flac))", std::regex::optimize | std::regex::icase);

class $modify(MyFMODAudioEngine, FMODAudioEngine) {
	#ifndef __APPLE__
	void preloadEffect(gd::string p0) {
		FMODAudioEngine::sharedEngine()->preloadEffect(p0);
		if (!PlayLayer::get()) return;
		auto manager = Manager::getSharedInstance();
		auto vanillaSFX = manager->vanillaSFX;
		std::string path = p0;
		std::smatch match;
		if (path.find("geode") != std::string::npos && (path.find("mods") != std::string::npos || path.find("config") != std::string::npos)) {
			if (path.find("flafy.autonong") != std::string::npos || path.find(".autonong") != std::string::npos) {
				manager->lastPlayedEffect = "[From Auto NONG]"; // better safe than sorry
			} else if (path.find("fleym.nongd") != std::string::npos || path.find(".nongd") != std::string::npos) {
				manager->lastPlayedEffect = "[From Jukebox]"; // better safe than sorry
			} else if (path.find("adam_729.randdeathsounds") != std::string::npos || path.find(".randdeathsounds") != std::string::npos) {
				manager->lastPlayedEffect = "[From RandDeathSounds]";
			} else if (path.find("crewly.comboburst") != std::string::npos || path.find(".comboburst") != std::string::npos) {
				manager->lastPlayedEffect = "[From Combo Burst]"; // fallback in case Combo Burst does its thing
			} else {
				manager->lastPlayedEffect = "[From another Geode mod]";
			}
		} else if (std::find(vanillaSFX.begin(), vanillaSFX.end(), path) == vanillaSFX.end()) {
			if (std::regex_match(path, match, songEffectRegex)) {
				if (path.find("cb_char") != std::string::npos) {
					manager->lastPlayedEffect = "[From Combo Burst]"; // fallback for current combo burst behavior as of may 11 2024
				} else {
					manager->lastPlayedEffect = fmt::format("{}.{}", match[1].str(), match[2].str());
				}
			} else {
				manager->lastPlayedEffect = fmt::format("{}", path);
			}
		}
	}
	#endif
	void playEffect(gd::string p0, float p1, float p2, float p3) {
		auto manager = Manager::getSharedInstance();
		auto badSFX = manager->badSFX;
		if (std::find(badSFX.begin(), badSFX.end(), std::string(p0)) == badSFX.end() || Utils::isSceneRunning("PauseLayer") || !(Utils::modEnabled() && Utils::get("disableRewardsSFX")) || !manager->isPlayerDead) {
			FMODAudioEngine::sharedEngine()->playEffect(p0, p1, p2, p3);
		}
	}
	void loadMusic(gd::string p0, float p1, float p2, float p3, bool p4, int p5, int p6) {
		FMODAudioEngine::loadMusic(p0, p1, p2, p3, p4, p5, p6);
		if (!PlayLayer::get()) return;
		auto manager = Manager::getSharedInstance();
		std::string path = p0;
		std::smatch match;
		if (path.find("geode") != std::string::npos && (path.find("mods") != std::string::npos || path.find("config") != std::string::npos)) {
			if (path.find("flafy.autonong") != std::string::npos || path.find(".autonong") != std::string::npos) {
				manager->lastPlayedSong = "[Replaced by Auto NONG]";
			} else if (path.find("fleym.nongd") != std::string::npos || path.find(".nongd") != std::string::npos) {
				manager->lastPlayedSong = "[Replaced by Jukebox]";
			} else {
				manager->lastPlayedSong = "[From another Geode mod]";
			}
		} else if (std::regex_match(path, match, songEffectRegex)) {
			manager->lastPlayedSong = fmt::format("{}.{}", match[1].str(), match[2].str());
		} else {
			manager->lastPlayedSong = fmt::format("{}", path);
		}
	}
};