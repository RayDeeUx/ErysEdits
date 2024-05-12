#include <Geode/modify/FMODAudioEngine.hpp>
#include "Manager.hpp"
#include "Utils.hpp"
#include <regex>

using namespace geode::prelude;

static std::regex songEffectRegex(R"(.*(?:\\|\/)(\S+)\.(mp3|ogg|wav|flac))", std::regex::optimize | std::regex::icase);
static std::regex geodeAudioRegex(R"(([a-z0-9\-_]+\.[a-z0-9\-_]+)(?:\\|\/)([\S ]+)\.(mp3|ogg|wav|flac))", std::regex::optimize | std::regex::icase);

class $modify(MyFMODAudioEngine, FMODAudioEngine) {
	#ifndef __APPLE__
	void preloadEffect(gd::string p0) {
		FMODAudioEngine::sharedEngine()->preloadEffect(p0);
		if (!PlayLayer::get()) return; // dont record files outside of playlayer
		auto manager = Manager::getSharedInstance();
		auto vanillaSFX = manager->vanillaSFX;
		std::string path = p0;
		std::smatch match;
		std::smatch geodeMatch;
		// log::info("the path: {}", path);
		if (path.find("geode") != std::string::npos && (path.find("mods") != std::string::npos || path.find("config") != std::string::npos)) {
			if (std::regex_search(path, geodeMatch, geodeAudioRegex)) {
				if (auto mod = Loader::get()->getLoadedMod(geodeMatch[1].str())) {
					manager->lastPlayedEffect = fmt::format("[From {}]", mod->getName());
				} else {
					manager->lastPlayedEffect = "[From another Geode mod]";
				}
			}
		} else if (std::find(vanillaSFX.begin(), vanillaSFX.end(), path) == vanillaSFX.end()) {
			if (std::regex_match(path, match, songEffectRegex)) {
				if (std::regex_search(path, geodeMatch, geodeAudioRegex)) {
					if (auto mod = Loader::get()->getLoadedMod(geodeMatch[1].str())) {
						manager->lastPlayedEffect = fmt::format("[From {}]", mod->getName());
					} else {
						manager->lastPlayedEffect = "[From another Geode mod]";
					}
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
		if (!PlayLayer::get()) return; // dont record files outside of playlayer
		auto manager = Manager::getSharedInstance();
		std::string path = p0;
		std::smatch match;
		std::smatch geodeMatch;
		// log::info("the path: {}", path);
		if (path.find("geode") != std::string::npos && (path.find("mods") != std::string::npos || path.find("config") != std::string::npos)) {
			if (std::regex_search(path, match, geodeAudioRegex)) {
				if (auto mod = Loader::get()->getLoadedMod(match[1].str())) {
					manager->lastPlayedSong = fmt::format("[From {}]", mod->getName());
				} else {
					manager->lastPlayedSong = "[From another Geode mod]";
				}
			}
		} else if (std::regex_match(path, match, songEffectRegex)) {
			if (std::regex_search(path, geodeMatch, geodeAudioRegex)) {
				if (auto mod = Loader::get()->getLoadedMod(geodeMatch[1].str())) {
					manager->lastPlayedSong = fmt::format("[From {}]", mod->getName());
				} else {
					manager->lastPlayedSong = "[From another Geode mod]";
				}
			} else {
				manager->lastPlayedSong = fmt::format("{}.{}", match[1].str(), match[2].str());
			}
		} else {
			manager->lastPlayedSong = fmt::format("{}", path);
		}
	}
};