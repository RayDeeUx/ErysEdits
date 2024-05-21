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
	};
	std::string extractModID(const std::smatch& theMatch) {
		log::info("{}", theMatch.size());
		for (auto matchString : theMatch) {
			log::info("matchString: {}", matchString.str());
		}
		log::info("theMatch[m_fields->desiredIndex].str(): {}", theMatch[m_fields->desiredIndex].str());
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
		if (!PlayLayer::get()) return; // dont record files outside of playlayer
		if (!Utils::modEnabled()) return; // ignore if mod disabled. should've done this sooner
		m_fields->manager->lastPlayedEffect = parsePath(p0);
	}
	#endif
	void playEffect(gd::string p0, float p1, float p2, float p3) {
		auto badSFX = m_fields->manager->badSFX;
		if (std::find(badSFX.begin(), badSFX.end(), std::string(p0)) == badSFX.end() || Utils::isSceneRunning("PauseLayer") || !(Utils::modEnabled() && Utils::get("disableRewardsSFX")) || !m_fields->manager->isPlayerDead) {
			FMODAudioEngine::sharedEngine()->playEffect(p0, p1, p2, p3);
		}
	}
	void loadMusic(gd::string p0, float p1, float p2, float p3, bool p4, int p5, int p6) {
		FMODAudioEngine::loadMusic(p0, p1, p2, p3, p4, p5, p6);
		if (!PlayLayer::get()) return; // dont record files outside of playlayer
		if (!Utils::modEnabled()) return; // ignore if mod disabled. should've done this sooner
		if (std::find(m_fields->manager->vanillaSFX.begin(), m_fields->manager->vanillaSFX.end(), p0) != m_fields->manager->vanillaSFX.end()) return;
		m_fields->manager->lastPlayedSong = parsePath(p0);
	}
};
