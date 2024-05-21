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
		#ifdef __APPLE__
		const std::map<int, std::string> miscIDToSetting = {
			{ 1006, "disablePulse" },
			{ 3010, "disableAreaTint" },
			{ 1520, "disableShake" },
			{ 3602, "disableSFX" },
			{ 3603, "disableEditSFX" }
		};
		#endif
	};
	std::string buildPlayerStatusString(PlayerObject* thePlayer, GJGameLevel* theLevel, bool isPlayerTwo) {
		std::string status = "Unknown";
		if (thePlayer->m_isShip) {
			if (theLevel->isPlatformer()) { status = "Jetpack"; }
			else { status = "Ship"; }
		}
		else if (thePlayer->m_isBall) { status = "Ball"; }
		else if (thePlayer->m_isBird) { status = "UFO"; }
		else if (thePlayer->m_isDart) { status = "Wave"; }
		else if (thePlayer->m_isRobot) { status = "Robot"; }
		else if (thePlayer->m_isSpider) { status = "Spider"; }
		else if (thePlayer->m_isSwing) { status = "Swing"; }
		else { status = "Cube"; }

		if (thePlayer->m_vehicleSize == .6f) { status = "Mini " + status; }
		else if (thePlayer->m_vehicleSize != 1.f) { status = status + " of unknown size"; }

		if (thePlayer->m_isPlatformer) {
			if (thePlayer->m_isUpsideDown) {
				if (thePlayer->m_isSideways) {
					if (Utils::get("compactDirections")) {status = "->] " + status;}
					else { status = "Rightwards " + status; }
				}
				else { status = "Flipped " + status; }
			} else if (thePlayer->m_isSideways) {
				if (Utils::get("compactDirections")) {status = "[<- " + status;}
				else { status = "Leftwards " + status; }
			}
		} else {
			if (thePlayer->m_isUpsideDown) { status = "Flipped " + status; }
			if (thePlayer->m_isSideways) {
				if (thePlayer->m_isGoingLeft) {
					if (Utils::get("compactDirections")) {status = "\\/ " + status;}
					else { status = "Downwards " + status; }
				}
				else {
					if (Utils::get("compactDirections")) {status = "/\\ " + status;}
					else { status = "Upwards " + status; }
				}
			} else if (thePlayer->m_isGoingLeft) {
				if (Utils::get("compactDirections")) {status = "<- " + status;}
				else { status = "Reversed " + status; }
			}
		}

		if (thePlayer->m_isDashing) { status = "<" + status + ">"; }

		if (!isPlayerTwo) {
			if (m_fields->manager->isDualsTime) { status = status + " [Dual]"; }

			if (m_isPracticeMode) { status = status + " {Practice}"; }
			else if (m_isTestMode) { status = status + " {Testmode}"; }
		}

		if (thePlayer->m_isDead) { status = status + " (Dead)"; }

		return fmt::format("{:.1f}x ", thePlayer->m_playerSpeed) + status;
	}
	std::string buildLevelTraitsString(GJGameLevel* theLevel) {
		std::string level = "Unknown";
		if (theLevel->isPlatformer()) {
			level = "Platformer";
		} else {
			level = "Classic";
			if (theLevel->m_levelLength == 0.f) { level = level + " [Tiny]"; }
			else if (theLevel->m_levelLength == 1.f) { level = level + " [Short]"; }
			else if (theLevel->m_levelLength == 2.f) { level = level + " [Medium]"; }
			else if (theLevel->m_levelLength == 3.f) { level = level + " [Long]"; }
			else { level = level + " [XL]"; }
		}

		if (theLevel->m_levelType == GJLevelType::Editor) {
			if (theLevel->m_isVerifiedRaw) { level = level + " (Verified)";}
			else { level = level + " (Unverified)"; }
		} else {
			if (theLevel->m_levelType == GJLevelType::Saved) { level = level + " (Online)"; }
			else if (theLevel->m_levelType == GJLevelType::Local) { level = level + " (Official)"; }
			else { level = level + " (Unknown)"; }
		}

		if (theLevel->m_twoPlayerMode) { level = level + " {2P}"; }

		if (
			(theLevel->m_accountID.value() == 13950148 && theLevel->m_levelType == GJLevelType::Saved)
		    || GameManager::get()->m_playerUserID.value() == 128138354 && theLevel->m_levelType != GJLevelType::Saved
		) { level = level + " <HOMOPHOBIC>"; }

		if (m_fields->manager->isLevelComplete) { level = level + " <Completed>"; }

		return level;
	}
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
			const auto mTS = m_fields->miscIDToSetting;
			if (mTS.contains(theObject->m_objectID) && Utils::get(mTS.find(theObject->m_objectID)->second)) { dontSkip = false; }
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
				if (const auto debugText = getChildByID("debug-text")) {
					auto theLevel = m_level;
					
					std::string status = MyPlayLayer::buildPlayerStatusString(m_player1, theLevel, false);
					std::string statusTwo = "";
					if (m_fields->manager->isDualsTime) { statusTwo = MyPlayLayer::buildPlayerStatusString(m_player2, theLevel, true); }
					std::string level = MyPlayLayer::buildLevelTraitsString(theLevel);
					
					std::string ending = "\n-- Area --\n";
					std::string endingTwo = "\n-- Perf --\n--";
					for (unsigned int i = getChildrenCount(); i-- > 0; ) {
						auto theObject = getChildren()->objectAtIndex(i);
						if (const auto ccCircleWave = typeinfo_cast<CCCircleWave*>(theObject)) {
							ccCircleWave->setVisible(false);
						}
					}
					if (const auto debugTextNode = typeinfo_cast<CCLabelBMFont*>(debugText)) {
						if (debugTextNode->isVisible()) {
							if (!Utils::get("chromaDebugText")) {
								debugTextNode->setColor({255, 255, 255}); // ensure that node color is white in case someone turns off chroma mode mid-session
							}
							if (Utils::get("maxAlphaDebugText")) {
								debugTextNode->setOpacity(255);
							} else {
								debugTextNode->setOpacity(Utils::getInt("debugTextAlpha"));
							}
							std::string debugTextContents = debugTextNode->getString();
							if (Utils::get("logDebugText")) {
								log::info("--- LOGGED DEBUG TEXT [BEFORE ERYSEDITS] ---:\n{}", debugTextContents);
							}
							#ifndef __APPLE__
							if (Utils::get("addCurrentChannel")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\n-- Audio --"), fmt::format("\nChannel: {}\n\r-- Audio --", m_gameState.m_currentChannel));
							}
							#endif
							if (Utils::get("lastPlayedSong")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\n(\r)?-- Audio --\nSongs: "), fmt::format("\n-- Audio --\nLast Song: {}\nLast SFX: {}\nSongs: ", m_fields->manager->lastPlayedSong, m_fields->manager->lastPlayedEffect));
							}
							if (Utils::get("includeJumps")) {
								std::smatch match;
								if (std::regex_search(debugTextContents, match, tapsCountRegex)) {
									debugTextContents = std::regex_replace(debugTextContents, std::regex("Taps: \\d+\nTimeWarp: "), fmt::format("Taps: {} [{}]\nTimeWarp: ", match[1].str(), m_fields->jumps)); // jump
								}
							}
							if (Utils::get("accuratePosition")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nX: (\\d)+\n"), fmt::format("\nX: {:.{}f}\n", m_player1->m_position.x, 4));
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nY: (\\d)+\n"), fmt::format("\nY: {:.{}f}\n", m_player1->m_position.y, 4));
							}
							if (Utils::get("conditionalValues")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nTimeWarp: 1\n"), "\n");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nGravity: 1\n"), "\n");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nGradients: 0"), "");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nParticles: 0"), "");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nChannel: 0"), "");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nMove: 0\n"), "\n");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nSongs: 0\n"), "\n");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nSFX: 0\n"), "\n");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nRotate: 0\n"), "\n");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nScale: 0\n"), "\n");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nFollow: 0\n"), "\n");
								debugTextContents = std::regex_replace(debugTextContents, std::regex(endingTwo), "\n--");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nMove: 0 / 0"), "");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nRotate: 0 / 0"), "");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nScale: 0 / 0"), "");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nFollow: 0 / 0"), "");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nColOp: 0 / 0"), "");
								if (debugTextContents.compare(debugTextContents.size() - ending.size(), ending.size(), ending) == 0) {
									debugTextContents = std::regex_replace(debugTextContents, std::regex(ending), "\n");
								}
							}
							if (Utils::get("addPlayerInfo")) {
								if (m_fields->manager->isDualsTime) {
									debugTextContents = std::regex_replace(
										debugTextContents,
										std::regex("\n-- Audio --"),
										fmt::format("\nP1 Status: {}\nP2 Status: {}\n-- Audio --", status, statusTwo)
									);
								} else {
									debugTextContents = std::regex_replace(
										debugTextContents,
										std::regex("\n-- Audio --"),
										fmt::format("\nStatus: {}\n-- Audio --", status)
									);
								}
							}
							if (Utils::get("addLevelTraits")) {
								debugTextContents = std::regex_replace(
									debugTextContents,
									std::regex("\n-- Audio --"),
									fmt::format("\nLevel: {}\n-- Audio --", level)
								);
							}
							if (Utils::get("compactGameplaySection")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nTaps: "), " | Taps: "); // Attempt and Taps
								if (debugTextContents.find("TimeWarp: ") != std::string::npos) {
									debugTextContents = std::regex_replace(debugTextContents, std::regex("\nGravity: "), " | Gravity: "); // TimeWarp and Gravity
								}
								if (debugTextContents.find("Gradients: ") != std::string::npos) {
									debugTextContents = std::regex_replace(debugTextContents, std::regex("\nParticles: "), " | Particles: "); // Gradients and Particles
								}
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nY: "), " | Y: "); // X and Y position
							}
							if (Utils::get("compactAudioSection") && debugTextContents.find("Songs: ") != std::string::npos) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nSFX: "), " | SFX: ");
							}
							if (Utils::get("expandPerformance")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("-- Perf --"), "-- Performance --");
							}
							if (Utils::get("tapsToClicks")) {
								if (theLevel->isPlatformer()) {
									debugTextContents = std::regex_replace(debugTextContents, std::regex("Taps: "), "Actions: ");
								} else {
									debugTextContents = std::regex_replace(debugTextContents, std::regex("Taps: "), "Clicks: ");
								}
							}
							if (Utils::get("fixLevelIDLabel")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("LevelID: "), "Level ID: ");
							}
							if (Utils::get("pluralAttempts")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("Attempt: "), "Attempts: ");
							}
							if (Utils::get("addGameplayHeader")) {
								debugTextContents = std::string("-- Gameplay --\n") + debugTextContents;
							}
							if (Utils::get("logDebugText")) {
								log::info("--- LOGGED DEBUG TEXT [AFTER ERYSEDITS] ---:\n{}", debugTextContents);
							}
							if (Utils::get("blendingDebugText")) {
								debugTextNode->setBlendFunc({GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA}); // Manager::glBlendFuncs[5], Manager::glBlendFuncs[7]
							}
							if (Utils::get("modLoaderInfo")) {
								debugTextContents = debugTextContents +
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
							debugTextNode->setString(debugTextContents.c_str()); // set the string
							debugTextNode->setScale(0.5 * (940.f / 1004.f)); // spaceUK style; capeling doesnt want watermarks for some reason D:<
							debugTextNode->setPositionY(312.5f); // spaceUK style; capeling doesnt want watermarks for some reason D:<
						}
					}
				}
			}
			if (Utils::get("hideLevelCompleteVisuals") && m_fields->manager->isLevelComplete) {
				auto mainNode = getChildByIDRecursive("main-node");
				for (int k = 0; k < mainNode->getChildrenCount(); k++) {
					if (const auto whereEverythingIs = typeinfo_cast<CCLayer*>(mainNode->getChildren()->objectAtIndex(k))) {
						for (int j = 0; j < whereEverythingIs->getChildrenCount(); j++) {
							if (const auto ccCircleWave = typeinfo_cast<CCCircleWave*>(whereEverythingIs->getChildren()->objectAtIndex(j))) {
								ccCircleWave->setVisible(false);
							} else if (const auto ccLightFlash = typeinfo_cast<CCLightFlash*>(whereEverythingIs->getChildren()->objectAtIndex(j))) {
								ccLightFlash->setVisible(false);
							}
						}
					}
				}
			}
		}
	}
};