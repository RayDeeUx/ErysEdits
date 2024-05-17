#include <Geode/modify/FMODAudioEngine.hpp>
#include "Manager.hpp"
#include "Utils.hpp"
#include <regex>

using namespace geode::prelude;

static std::regex songEffectRegex(R"(.*(?:\\|\/)(\S+)\.(mp3|ogg|wav|flac))", std::regex::optimize | std::regex::icase);
static std::regex geodeAudioRegex(R"(((?!\S+geode)(?:([a-z0-9\-_]+\.[a-z0-9\-_]+)(?:\\|\/))([\S ]+)\.(mp3|ogg|wav|flac)$)", std::regex::optimize | std::regex::icase);

class $modify(MyFMODAudioEngine, FMODAudioEngine) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	std::string parsePath(std::string path) {
		std::smatch match;
		std::smatch geodeMatch;
		std::string result = "";
		if (path.find("geode") != std::string::npos && (path.find("mods") != std::string::npos || path.find("config") != std::string::npos)) {
			if (std::regex_search(path, geodeMatch, geodeAudioRegex)) {
				if (auto mod = Utils::getMod(geodeMatch[1].str())) {
					result = fmt::format("[From {}]", mod->getName());
				} else {
					result = "[From another Geode mod]";
				}
			}
		} else if (std::regex_match(path, match, songEffectRegex)) {
			if (std::regex_search(path, geodeMatch, geodeAudioRegex)) {
				if (auto mod = Utils::getMod(geodeMatch[1].str())) {
					result = fmt::format("[From {}]", mod->getName());
				} else {
					result = "[From another Geode mod]";
				}
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
		if (std::find(m_fields->manager->vanillaSFX.begin(), m_fields->manager->vanillaSFX.end(), p0) != m_fields->manager->vanillaSFX.end()) return;
		m_fields->manager->lastPlayedSong = parsePath(p0);
	}
};
