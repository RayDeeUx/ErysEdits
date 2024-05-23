#include <Geode/modify/FMODAudioEngine.hpp>
#include "Manager.hpp"
#include "Utils.hpp"
#include <regex>

using namespace geode::prelude;

static std::regex songEffectRegex(R"(.*(?:\\|\/)(\S+)\.(mp3|ogg|wav|flac))", std::regex::optimize | std::regex::icase);
static std::regex geodeAudioRegex(R"(((?!\S+geode)(?:\\|\/)(?:([a-z0-9\-_]+\.[a-z0-9\-_]+)(?:\\|\/))([\S ]+)\.(mp3|ogg|wav|flac))$)", std::regex::optimize | std::regex::icase);

class $modify(MyFMODAudioEngine, FMODAudioEngine) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
		int desiredIndex = 2; // easier place to change index
		const std::list<std::string> vanillaSFX = { "achievement_01.ogg", "buyItem01.ogg", "buyItem03.ogg", "chest07.ogg", "chest08.ogg", "chestClick.ogg", "chestLand.ogg", "chestOpen01.ogg", "counter003.ogg", "crystal01.ogg", "door001.ogg", "door01.ogg", "door02.ogg", "endStart_02.ogg", "explode_11.ogg", "gold01.ogg", "gold02.ogg", "grunt01.ogg", "grunt02.ogg", "grunt03.ogg", "highscoreGet02.ogg", "magicExplosion.ogg", "playSound_01.ogg", "quitSound_01.ogg", "reward01.ogg", "secretKey.ogg", "unlockPath.ogg" };
		const std::list<std::string> badSFX = { "achievement_01.ogg", "magicExplosion.ogg", "gold02.ogg", "secretKey.ogg" };
	};
	std::string extractModID(const std::smatch& theMatch) {
		/*
		log::info("{}", theMatch.size());
		for (auto matchString : theMatch) {
			log::info("matchString: {}", matchString.str());
		}
		log::info("theMatch[m_fields->desiredIndex].str(): {}", theMatch[m_fields->desiredIndex].str());
		*/
		if (const Mod* mod = Utils::getMod(theMatch[m_fields->desiredIndex].str())) {
			return fmt::format("[From {}]", mod->getName());
		} else {
			return "[From another Geode mod]";
		}
	}
	std::string parsePath(std::string path) {
		// log::info("path before: {}", path);
		std::smatch match;
		std::smatch geodeMatch;
		std::string result = "";
		path = std::regex_replace(path, std::regex("com\.geode\.launcher\/"), ""); // android is cring
		// log::info("path after: {}", path);
		if (path.find("geode") != std::string::npos && (path.find("mods") != std::string::npos || path.find("config") != std::string::npos)) {
			if (std::regex_search(path, geodeMatch, geodeAudioRegex)) {
				result = extractModID(geodeMatch);
			} else {
				result = "[Something went wrong...]";
			}
		} else if (std::regex_match(path, match, songEffectRegex)) {
			if (std::regex_search(path, geodeMatch, geodeAudioRegex)) {
				result = extractModID(geodeMatch);
			} else {
				result = fmt::format("{}.{}", match[1].str(), match[2].str());
			}
		} else {
			result = fmt::format("{}", path);
		}
		return result;
	}
	#ifndef __APPLE__
	void preloadEffect(gd::string p0) {
		FMODAudioEngine::sharedEngine()->preloadEffect(p0);
		if (!Utils::modEnabled()) return; // ignore if mod disabled. should've done this sooner
		if (!PlayLayer::get()) return; // dont record files outside of playlayer
		m_fields->manager->lastPlayedEffect = parsePath(p0);
	}
	#endif
	void playEffect(gd::string p0, float p1, float p2, float p3) {
		if (std::find(m_fields->badSFX.begin(), m_fields->badSFX.end(), std::string(p0)) == m_fields->badSFX.end() || Utils::isSceneRunning("PauseLayer") || !(Utils::modEnabled() && Utils::getBool("disableRewardsSFX")) || !m_fields->manager->isPlayerDead) {
			FMODAudioEngine::sharedEngine()->playEffect(p0, p1, p2, p3);
		}
	}
	void loadMusic(gd::string p0, float p1, float p2, float p3, bool p4, int p5, int p6) {
		FMODAudioEngine::loadMusic(p0, p1, p2, p3, p4, p5, p6);
		if (!Utils::modEnabled()) return; // ignore if mod disabled. should've done this sooner
		if (!PlayLayer::get()) return; // dont record files outside of playlayer
		if (std::find(m_fields->vanillaSFX.begin(), m_fields->vanillaSFX.end(), p0) != m_fields->vanillaSFX.end()) return;
		m_fields->manager->lastPlayedSong = parsePath(p0);
	}
};
