#include <Geode/modify/PlayLayer.hpp>
#include <regex>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
	void levelComplete() {
		PlayLayer::levelComplete();
		Utils::restoreOrigGMGVs(GameManager::get());
		if (Utils::modEnabled() && Utils::get("hideLevelCompleteVisuals")) { Manager::getSharedInstance()->isLevelComplete = true; }
	}
	void onQuit() {
		Utils::restoreOrigGMGVs(GameManager::get(), true, false);
		auto manager = Manager::getSharedInstance();
		if (Utils::modEnabled() && Utils::get("hideLevelCompleteVisuals")) { manager->isLevelComplete = false; }
		manager->lastPlayedSong = "N/A";
		#ifndef __APPLE__
		manager->lastPlayedEffect = "N/A";
		manager->currentChannel = 0;
		#else
		manager->lastPlayedEffect = "[MacOS issue]";
		#endif
		PlayLayer::onQuit();
	}
	#ifndef __APPLE__
	void onExit() {
		Utils::restoreOrigGMGVs(GameManager::get(), false);
		PlayLayer::onExit();
	}
	#endif
	#ifdef __APPLE__
	void addObject(GameObject* p0) {
		auto mTS = Manager::getSharedInstance()->miscIDToSetting;
		bool dontSkip = true;
		if (mTS.find(p0->m_objectID) != mTS.end() && Utils::get(mTS.find(p0->m_objectID)->second)) { dontSkip = false; }
		if (dontSkip) { PlayLayer::addObject(p0); }
	}
	#endif
	void postUpdate(float dt) {
		if (!Utils::modEnabled()) {
			PlayLayer::postUpdate(dt);
			return;
		}
		auto manager = Manager::getSharedInstance();

		PlayLayer::postUpdate(dt);
		/*
			calling the original function in this specific position per cvolton's advice in https://discord.com/channels/911701438269386882/979402752121765898/1213615245260627999
			> whether its before or after original depends on where you put your code
			> if its before the call to original or after the call to original
		*/
		if (Utils::get("debugTextToggle")) {
			auto theLevel = this->m_level;
			std::string status = Utils::buildPlayerStatusString(m_player1, theLevel, this, false);
			std::string statusTwo = "";
			if (manager->isDualsTime) { statusTwo = Utils::buildPlayerStatusString(m_player2, theLevel, this, true); }
			std::string level = Utils::buildLevelTraitsString(theLevel);
			
			std::string ending = "\n-- Area --\n";
			std::string endingTwo = "\n-- Perf --\n--";
			for (int i = this->getChildrenCount(); i-- > 0; ) {
				auto theObject = this->getChildren()->objectAtIndex(i);
				if (auto ccCircleWave = typeinfo_cast<CCCircleWave*>(theObject)) {
					ccCircleWave->setVisible(false);
					continue;
				}
			}
			auto debugTextNode = typeinfo_cast<CCLabelBMFont*>(getChildByIDRecursive("debug-text"));
			if (debugTextNode->isVisible()) {
				std::string debugText = debugTextNode->getString();
				if (Utils::get("logDebugText")) { log::info("--- LOGGED DEBUG TEXT [BEFORE ERYSEDITS] ---:\n{}", debugText); }
				#ifndef __APPLE__
				if (Utils::get("addCurrentChannel")) {
					debugText = std::regex_replace(debugText, std::regex("\n-- Audio --"), fmt::format("\nChannel: {}\n\r-- Audio --", manager->currentChannel));
				}
				#endif
				if (Utils::get("lastPlayedSong")) {
					debugText = std::regex_replace(debugText, std::regex("\n(\r)?-- Audio --\nSongs: "), fmt::format("\n-- Audio --\nLast Song: {}\nLast SFX: {}\nSongs: ", manager->lastPlayedSong, manager->lastPlayedEffect));
				}
				if (Utils::get("accuratePosition")) {
					debugText = std::regex_replace(debugText, std::regex("\nX: (\\d)+\n"), fmt::format("\nX: {:.{}f}\n", m_player1->m_position.x, 4));
					debugText = std::regex_replace(debugText, std::regex("\nY: (\\d)+\n"), fmt::format("\nY: {:.{}f}\n", m_player1->m_position.y, 4));
				}
				if (Utils::get("conditionalValues")) {
					debugText = std::regex_replace(debugText, std::regex("\nTimeWarp: 1"), "");
					debugText = std::regex_replace(debugText, std::regex("\nGravity: 1"), "");
					debugText = std::regex_replace(debugText, std::regex("\nGradients: 0"), "");
					debugText = std::regex_replace(debugText, std::regex("\nParticles: 0"), "");
					debugText = std::regex_replace(debugText, std::regex("\nChannel: 0"), "");
					debugText = std::regex_replace(debugText, std::regex("\nMove: 0\n"), "\n");
					debugText = std::regex_replace(debugText, std::regex("\nSongs: 0\n"), "\n");
					debugText = std::regex_replace(debugText, std::regex("\nSFX: 0\n"), "\n");
					debugText = std::regex_replace(debugText, std::regex("\nRotate: 0\n"), "\n");
					debugText = std::regex_replace(debugText, std::regex("\nScale: 0\n"), "\n");
					debugText = std::regex_replace(debugText, std::regex("\nFollow: 0\n"), "\n");
					debugText = std::regex_replace(debugText, std::regex(endingTwo), "\n--");
					debugText = std::regex_replace(debugText, std::regex("\nMove: 0 / 0"), "");
					debugText = std::regex_replace(debugText, std::regex("\nRotate: 0 / 0"), "");
					debugText = std::regex_replace(debugText, std::regex("\nScale: 0 / 0"), "");
					debugText = std::regex_replace(debugText, std::regex("\nFollow: 0 / 0"), "");
					debugText = std::regex_replace(debugText, std::regex("\nColOp: 0 / 0"), "");
					if (debugText.compare(debugText.size() - ending.size(), ending.size(), ending) == 0) {
						debugText = std::regex_replace(debugText, std::regex(ending), "\n");
					}
				}
				if (Utils::get("addPlayerInfo")) {
					if (manager->isDualsTime) {
						debugText = std::regex_replace(
							debugText,
							std::regex("\n-- Audio --"),
							fmt::format("\nP1 Status: {}\nP2 Status: {}\n-- Audio --", status, statusTwo)
						);
					} else {
						debugText = std::regex_replace(
							debugText,
							std::regex("\n-- Audio --"),
							fmt::format("\nStatus: {}\n-- Audio --", status)
						);
					} 
				}
				if (Utils::get("addLevelTraits")) {
					debugText = std::regex_replace(
						debugText,
						std::regex("\n-- Audio --"),
						fmt::format("\nLevel: {}\n-- Audio --", level)
					);
				}
				if (Utils::get("compactGameplaySection")) {
					debugText = std::regex_replace(debugText, std::regex("\nTaps: "), " | Taps: "); // Attempt and Taps
					if (debugText.find("TimeWarp: ") != std::string::npos) { debugText = std::regex_replace(debugText, std::regex("\nGravity: "), " | Gravity: "); } // TimeWarp and Gravity
					if (debugText.find("Gradients: ") != std::string::npos) { debugText = std::regex_replace(debugText, std::regex("\nParticles: "), " | Particles: "); } // Gradients and Particles
					debugText = std::regex_replace(debugText, std::regex("\nY: "), " | Y: "); // X and Y position
				}
				if (Utils::get("compactAudioSection") && debugText.find("Songs: ") != std::string::npos) { debugText = std::regex_replace(debugText, std::regex("\nSFX: "), " | SFX: "); }
				if (Utils::get("expandPerformance")) { debugText = std::regex_replace(debugText, std::regex("-- Perf --"), "-- Performance --"); }
				if (Utils::get("tapsToClicks")) {
					if (theLevel->isPlatformer()) { debugText = std::regex_replace(debugText, std::regex("Taps: "), "Actions: "); }
					else { debugText = std::regex_replace(debugText, std::regex("Taps: "), "Clicks: "); }
				}
				if (Utils::get("fixLevelIDLabel")) { debugText = std::regex_replace(debugText, std::regex("LevelID: "), "Level ID: "); }
				if (Utils::get("pluralAttempts")) { debugText = std::regex_replace(debugText, std::regex("Attempt: "), "Attempts: "); }
				if (Utils::get("addGameplayHeader")) { debugText = std::string("-- Gameplay --\n") + debugText; }
				if (Utils::get("logDebugText")) { log::info("--- LOGGED DEBUG TEXT [AFTER ERYSEDITS] ---:\n{}", debugText); }
				if (Utils::get("blendingDebugText")) { debugTextNode->setBlendFunc({GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA}); } // Manager::glBlendFuncs[5], Manager::glBlendFuncs[7]
				if (Utils::get("modLoaderInfo")) {
					debugText = debugText +
					fmt::format(
						"-- Geode --\nVersion: {}\nGD: {} for {}\nMods: {} + {} = {} ({}){}\nForward Compat: {}",
						manager->geodeVer,
						manager->gameVer,
						manager->platform,
						manager->loadedMods,
						manager->disabledMods,
						manager->installedMods,
						manager->problems,
						manager->fourGBStatus,
						manager->forwardCompat
					);
				}
				debugTextNode->setString(debugText.c_str()); // set the string
				debugTextNode->setScale(0.5 * (940.f / 1004.f)); // spaceUK style; capeling doesnt want watermarks for some reason D:<
				debugTextNode->setPositionY(312.5f); // spaceUK style; capeling doesnt want watermarks for some reason D:<
			}
		}
		if (Utils::get("hideLevelCompleteVisuals") && manager->isLevelComplete) {
			auto mainNode = getChildByIDRecursive("main-node");
			for (int k = 0; k < mainNode->getChildrenCount(); k++) {
				if (auto whereEverythingIs = typeinfo_cast<CCLayer*>(mainNode->getChildren()->objectAtIndex(k))) {
					for (int j = 0; j < whereEverythingIs->getChildrenCount(); j++) {
						if (auto ccCircleWave = typeinfo_cast<CCCircleWave*>(whereEverythingIs->getChildren()->objectAtIndex(j))) {
							ccCircleWave->setVisible(false);
						} else if (auto ccLightFlash = typeinfo_cast<CCLightFlash*>(whereEverythingIs->getChildren()->objectAtIndex(j))) {
							ccLightFlash->setVisible(false);
						}
					}
				}
			}
		}
	}
};