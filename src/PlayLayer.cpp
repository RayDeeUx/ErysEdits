#include <Geode/modify/PlayLayer.hpp>
#include <regex>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

static std::regex tapsCountRegex(R"(Taps: (\d+)\n)", std::regex::optimize | std::regex::icase);

class $modify(MyPlayLayer, PlayLayer) {
	struct Fields {
		int jumps = 0;
		Manager* manager = Manager::getSharedInstance();
	};
	void levelComplete() {
		PlayLayer::levelComplete();
		Utils::restoreOrigGMGVs(GameManager::get());
		if (Utils::modEnabled() && Utils::get("hideLevelCompleteVisuals")) { m_fields->manager->isLevelComplete = true; }
	}
	void onQuit() {
		Utils::restoreOrigGMGVs(GameManager::get(), true, false);
		if (Utils::modEnabled() && Utils::get("hideLevelCompleteVisuals")) { m_fields->manager->isLevelComplete = false; }
		m_fields->manager->lastPlayedSong = "N/A";
		#ifndef __APPLE__
		m_fields->manager->lastPlayedEffect = "N/A";
		m_fields->manager->currentChannel = 0;
		#else
		m_fields->manager->lastPlayedEffect = "[MacOS issue]";
		#endif
		PlayLayer::onQuit();
		m_fields->jumps = 0;
	}
	void fullReset() {
		PlayLayer::fullReset();
		m_fields->jumps = 0;
	}
	void incrementJumps() {
		PlayLayer::incrementJumps();
		m_fields->jumps += 1;
	}
	#ifndef __APPLE__
	void onExit() {
		Utils::restoreOrigGMGVs(GameManager::get(), false);
		PlayLayer::onExit();
	}
	#endif
	void addObject(GameObject* theObject) {
		bool dontSkip = true;
		if (Utils::modEnabled()) {
			#ifdef __APPLE__
			auto mTS = m_fields->manager->miscIDToSetting;
			if (mTS.find(theObject->m_objectID) != mTS.end() && Utils::get(mTS.find(theObject->m_objectID)->second)) { dontSkip = false; }
			#endif
			if (m_level->m_levelType == GJLevelType::Saved && theObject->m_isHighDetail && GameManager::get()->getGameVariable("0108") && (Utils::getInt("alwaysLDM") == 3 || (Utils::getInt("alwaysLDM") == 2 && m_level->m_stars.value() != 0) || (Utils::getInt("alwaysLDM") == 1 && m_level->m_stars.value() == 0))) {
				dontSkip = false;
			}
			if (Utils::get("forceVisibleEffect") && theObject->m_hasNoEffects) {
				theObject->m_hasNoEffects = false;
			}
			if (Utils::get("forceAudioScale") && theObject->m_hasNoAudioScale && (!m_fields->manager->isBreakingPlatforming || !m_level->isPlatformer())) {
				theObject->m_hasNoAudioScale = false;
			}
		}
		if (dontSkip) { PlayLayer::addObject(theObject); }
	}
	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);
		if (!Utils::modEnabled()) {
			return;
		} else {
			if (Utils::get("debugTextToggle")) {
				if (auto debugText = getChildByID("debug-text")) {
					auto theLevel = this->m_level;
					
					std::string status = Utils::buildPlayerStatusString(m_player1, theLevel, this, false);
					std::string statusTwo = "";
					if (m_fields->manager->isDualsTime) { statusTwo = Utils::buildPlayerStatusString(m_player2, theLevel, this, true); }
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
					if (auto debugTextNode = typeinfo_cast<CCLabelBMFont*>(debugText)) {
						if (debugTextNode->isVisible()) {
							if (!Utils::get("chromaDebugText")) {
								debugTextNode->setColor({255, 255, 255}); // ensure that node color is white in case someone turns off chroma mode mid-session
							}
							if (Utils::get("maxAlphaDebugText")) {
								debugTextNode->setOpacity(255);
							} else {
								debugTextNode->setOpacity(Utils::getInt("debugTextAlpha"));
							}
							std::string debugText = debugTextNode->getString();
							if (Utils::get("logDebugText")) {
								log::info("--- LOGGED DEBUG TEXT [BEFORE ERYSEDITS] ---:\n{}", debugText);
							}
							#ifndef __APPLE__
							if (Utils::get("addCurrentChannel")) {
								debugText = std::regex_replace(debugText, std::regex("\n-- Audio --"), fmt::format("\nChannel: {}\n\r-- Audio --", m_fields->manager->currentChannel));
							}
							#endif
							if (Utils::get("lastPlayedSong")) {
								debugText = std::regex_replace(debugText, std::regex("\n(\r)?-- Audio --\nSongs: "), fmt::format("\n-- Audio --\nLast Song: {}\nLast SFX: {}\nSongs: ", m_fields->manager->lastPlayedSong, m_fields->manager->lastPlayedEffect));
							}
							if (Utils::get("includeJumps")) {
								std::smatch match;
								if (std::regex_search(debugText, match, tapsCountRegex)) {
									debugText = std::regex_replace(debugText, std::regex("Taps: \\d+\nTimeWarp: "), fmt::format("Taps: {} [{}]\nTimeWarp: ", match[1].str(), m_fields->jumps)); // jump
								}
							}
							if (Utils::get("accuratePosition")) {
								debugText = std::regex_replace(debugText, std::regex("\nX: (\\d)+\n"), fmt::format("\nX: {:.{}f}\n", m_player1->m_position.x, 4));
								debugText = std::regex_replace(debugText, std::regex("\nY: (\\d)+\n"), fmt::format("\nY: {:.{}f}\n", m_player1->m_position.y, 4));
							}
							if (Utils::get("conditionalValues")) {
								debugText = std::regex_replace(debugText, std::regex("\nTimeWarp: 1\n"), "\n");
								debugText = std::regex_replace(debugText, std::regex("\nGravity: 1\n"), "\n");
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
								if (m_fields->manager->isDualsTime) {
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
								if (debugText.find("TimeWarp: ") != std::string::npos) {
									debugText = std::regex_replace(debugText, std::regex("\nGravity: "), " | Gravity: "); // TimeWarp and Gravity
								}
								if (debugText.find("Gradients: ") != std::string::npos) {
									debugText = std::regex_replace(debugText, std::regex("\nParticles: "), " | Particles: "); // Gradients and Particles
								}
								debugText = std::regex_replace(debugText, std::regex("\nY: "), " | Y: "); // X and Y position
							}
							if (Utils::get("compactAudioSection") && debugText.find("Songs: ") != std::string::npos) {
								debugText = std::regex_replace(debugText, std::regex("\nSFX: "), " | SFX: ");
							}
							if (Utils::get("expandPerformance")) {
								debugText = std::regex_replace(debugText, std::regex("-- Perf --"), "-- Performance --");
							}
							if (Utils::get("tapsToClicks")) {
								if (theLevel->isPlatformer()) {
									debugText = std::regex_replace(debugText, std::regex("Taps: "), "Actions: ");
								} else {
									debugText = std::regex_replace(debugText, std::regex("Taps: "), "Clicks: ");
								}
							}
							if (Utils::get("fixLevelIDLabel")) {
								debugText = std::regex_replace(debugText, std::regex("LevelID: "), "Level ID: ");
							}
							if (Utils::get("pluralAttempts")) {
								debugText = std::regex_replace(debugText, std::regex("Attempt: "), "Attempts: ");
							}
							if (Utils::get("addGameplayHeader")) {
								debugText = std::string("-- Gameplay --\n") + debugText;
							}
							if (Utils::get("logDebugText")) {
								log::info("--- LOGGED DEBUG TEXT [AFTER ERYSEDITS] ---:\n{}", debugText);
							}
							if (Utils::get("blendingDebugText")) {
								debugTextNode->setBlendFunc({GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA}); // Manager::glBlendFuncs[5], Manager::glBlendFuncs[7]
							}
							if (Utils::get("modLoaderInfo")) {
								debugText = debugText +
								fmt::format(
									"-- Geode --\nVersion: {}\nGD: {} for {}\nMods: {} + {} = {} ({}){}\nForward Compat: {}",
									m_fields->manager->geodeVer,
									m_fields->manager->gameVer,
									m_fields->manager->platform,
									m_fields->manager->loadedMods,
									m_fields->manager->disabledMods,
									m_fields->manager->installedMods,
									m_fields->manager->problems,
									m_fields->manager->fourGBStatus,
									m_fields->manager->forwardCompat
								);
							}
							debugTextNode->setString(debugText.c_str()); // set the string
							debugTextNode->setScale(0.5 * (940.f / 1004.f)); // spaceUK style; capeling doesnt want watermarks for some reason D:<
							debugTextNode->setPositionY(312.5f); // spaceUK style; capeling doesnt want watermarks for some reason D:<
						}
					}
				}
			}
			if (Utils::get("hideLevelCompleteVisuals") && m_fields->manager->isLevelComplete) {
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
	}
};