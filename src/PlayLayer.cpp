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
		GameManager* gameManager = GameManager::get();
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
	std::string buildPlayerStatusString(PlayerObject* thePlayer) {
		std::string status = "Unknown";
		bool isPlat = m_level->isPlatformer();
		bool compactDirs = Utils::getBool("compactDirections");
		if (thePlayer->m_isShip) {
			if (!isPlat) { status = "Ship"; }
			else { status = "Jetpack"; }
		}
		else if (thePlayer->m_isDart) {
			if (!isPlat) { status = "Wave"; }
			else {
				if (GEODE_COMP_GD_VERSION > 22050) { status = "Wave?"; }
				else { status = "Wave*"; }
			}
		}
		else if (thePlayer->m_isSwing) {
			if (!isPlat) { status = "Swing"; }
			else {
				if (GEODE_COMP_GD_VERSION > 22050) { status = "Swing?"; }
				else { status = "Swing*"; }
			}
		}
		else if (thePlayer->m_isBall) { status = "Ball"; }
		else if (thePlayer->m_isBird) { status = "UFO"; }
		else if (thePlayer->m_isRobot) { status = "Robot"; }
		else if (thePlayer->m_isSpider) { status = "Spider"; }
		else { status = "Cube"; }

		if (thePlayer->m_vehicleSize == .6f) { status = "Mini " + status; }
		else if (thePlayer->m_vehicleSize != 1.f) { status = status + " of strange size"; }

		if (thePlayer->m_isPlatformer) {
			if (thePlayer->m_isUpsideDown) {
				if (thePlayer->m_isSideways) {
					if (compactDirs) {status = "->] " + status;}
					else { status = "Rightwards " + status; }
				}
				else { status = "Flipped " + status; }
			} else if (thePlayer->m_isSideways) {
				if (compactDirs) {status = "[<- " + status;}
				else { status = "Leftwards " + status; }
			}
		} else {
			if (thePlayer->m_isUpsideDown) { status = "Flipped " + status; }
			if (thePlayer->m_isSideways) {
				if (thePlayer->m_isGoingLeft) {
					if (compactDirs) {status = "\\/ " + status;}
					else { status = "Downwards " + status; }
				}
				else {
					if (compactDirs) {status = "/\\ " + status;}
					else { status = "Upwards " + status; }
				}
			} else if (thePlayer->m_isGoingLeft) {
				if (compactDirs) {status = "<- " + status;}
				else { status = "Reversed " + status; }
			}
		}

		if (thePlayer->m_isDashing) { status = "<" + status + ">"; }

		if (thePlayer != m_player2) {
			if (m_fields->manager->isDualsTime) { status = status + " [Dual]"; }

			if (m_isPracticeMode) { status = status + " {Practice}"; }
			else if (m_isTestMode) { status = status + " {Testmode}"; }
		}

		if (thePlayer->m_isDead) { status = status + " (Dead)"; }

		return fmt::format("{:.1f}x ", thePlayer->m_playerSpeed) + status;
	}
	std::string buildLevelTraitsString() {
		std::string level = "Unknown";
		if (m_level->isPlatformer()) {
			level = "Platformer";
		} else {
			level = "Classic";
			if (m_level->m_levelLength == 0.f) { level = level + " [Tiny]"; }
			else if (m_level->m_levelLength == 1.f) { level = level + " [Short]"; }
			else if (m_level->m_levelLength == 2.f) { level = level + " [Medium]"; }
			else if (m_level->m_levelLength == 3.f) { level = level + " [Long]"; }
			else { level = level + " [XL]"; }
		}

		if (m_level->m_levelType == GJLevelType::Editor) {
			if (m_level->m_isVerifiedRaw) { level = level + " (Verified)";}
			else { level = level + " (Unverified)"; }
		} else {
			if (m_level->m_levelType == GJLevelType::Saved) { level = level + " (Online)"; }
			else if (m_level->m_levelType == GJLevelType::Local) { level = level + " (Official)"; }
			else { level = level + " (Unknown)"; }
		}

		if (m_level->m_twoPlayerMode) { level = level + " {2P}"; }

		if (
			(m_level->m_accountID.value() == 13950148 && m_level->m_levelType == GJLevelType::Saved)
			|| m_fields->gameManager->m_playerUserID.value() == 128138354 && m_level->m_levelType != GJLevelType::Saved
		) { level = level + " <HOMOPHOBIC>"; }

		if (m_fields->manager->isLevelComplete) { level = level + " <Completed>"; }

		return level;
	}
	void levelComplete() {
		PlayLayer::levelComplete();
		Utils::restoreOrigGMGVs(GameManager::get());
		if (Utils::modEnabled() && Utils::getBool("hideLevelCompleteVisuals")) { m_fields->manager->isLevelComplete = true; }
	}
	void onQuit() {
		Utils::restoreOrigGMGVs(GameManager::get(), true, false);
		if (Utils::modEnabled() && Utils::getBool("hideLevelCompleteVisuals")) { m_fields->manager->isLevelComplete = false; }
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
			if (m_fields->miscIDToSetting.contains(theObject->m_objectID) && Utils::getBool(m_fields->miscIDToSetting.find(theObject->m_objectID)->second)) { dontSkip = false; }
			#endif
			if (m_level->m_levelType == GJLevelType::Saved && theObject->m_isHighDetail && m_fields->gameManager->getGameVariable("0108") && (Utils::getInt("alwaysLDM") == 3 || (Utils::getInt("alwaysLDM") == 2 && m_level->m_stars.value() != 0) || (Utils::getInt("alwaysLDM") == 1 && m_level->m_stars.value() == 0))) {
				dontSkip = false;
			}
			if (Utils::getBool("forceVisibleEffect") && theObject->m_hasNoEffects) {
				theObject->m_hasNoEffects = false;
			}
			if (Utils::getBool("forceAudioScale") && theObject->m_hasNoAudioScale && (!m_fields->manager->isBreakingPlatforming || !m_level->isPlatformer())) {
				theObject->m_hasNoAudioScale = false;
			}
		}
		if (dontSkip) { PlayLayer::addObject(theObject); }
	}
	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);
		if (!Utils::modEnabled() || !Utils::getBool("debugTextToggle")) {
			// in case either softtoggle is disabled mid-session, restore original colors
			if (const auto debugText = getChildByID("debug-text")) {
				if (const auto debugTextNode = typeinfo_cast<CCLabelBMFont*>(debugText)) {
					debugTextNode->setColor(ccColor3B({255, 255, 255}));
					debugTextNode->setOpacity(150);
				}
			}
		} else if (Utils::modEnabled()) {
			if (const auto debugText = getChildByID("debug-text")) {
				if (Utils::getBool("debugTextToggle")) {
					std::string status = MyPlayLayer::buildPlayerStatusString(m_player1);
					std::string statusTwo = "";
					if (m_fields->manager->isDualsTime) { statusTwo = MyPlayLayer::buildPlayerStatusString(m_player2); }
					std::string level = MyPlayLayer::buildLevelTraitsString();
					
					std::string ending = "\n-- Area --\n";

					if (const auto debugTextNode = typeinfo_cast<CCLabelBMFont*>(debugText)) {
						if (debugTextNode->isVisible()) {
							if (!Utils::getBool("chromaDebugText")) {
								debugTextNode->setColor({255, 255, 255}); // ensure that node color is white in case someone turns off chroma mode mid-session
							}
							if (Utils::getBool("maxAlphaDebugText")) {
								debugTextNode->setOpacity(255);
							} else {
								debugTextNode->setOpacity(Utils::getInt("debugTextAlpha"));
							}
							std::string debugTextContents = debugTextNode->getString();
							if (Utils::getBool("logDebugText")) {
								log::info("--- LOGGED DEBUG TEXT [BEFORE ERYSEDITS] ---:\n{}", debugTextContents);
							}
							#ifndef __APPLE__
							if (Utils::getBool("addCurrentChannel")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\n-- Audio --"), fmt::format("\nChannel: {}\n\r-- Audio --", m_gameState.m_currentChannel));
							}
							#endif
							if (Utils::getBool("lastPlayedSong")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\n(\r)?-- Audio --\nSongs: "), fmt::format("\n-- Audio --\nLast Song: {}\nLast SFX: {}\nSongs: ", m_fields->manager->lastPlayedSong, m_fields->manager->lastPlayedEffect));
							}
							if (Utils::getBool("includeJumps")) {
								std::smatch match;
								if (std::regex_search(debugTextContents, match, tapsCountRegex)) {
									debugTextContents = std::regex_replace(debugTextContents, std::regex("Taps: \\d+\nTimeWarp: "), fmt::format("Taps: {} [{}]\nTimeWarp: ", match[1].str(), m_fields->jumps)); // jump
								}
							}
							if (Utils::getBool("accuratePosition")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nX: (\\d)+\n"), fmt::format("\nX: {:.{}f}\n", m_player1->m_position.x, 4));
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nY: (\\d)+\n"), fmt::format("\nY: {:.{}f}\n", m_player1->m_position.y, 4));
							}
							if (Utils::getBool("conditionalValues")) {
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
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\n-- Perf --\n--"), "\n--");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nMove: 0 / 0"), "");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nRotate: 0 / 0"), "");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nScale: 0 / 0"), "");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nFollow: 0 / 0"), "");
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nColOp: 0 / 0"), "");
								if (debugTextContents.compare(debugTextContents.size() - ending.size(), ending.size(), ending) == 0) {
									debugTextContents = std::regex_replace(debugTextContents, std::regex(ending), "\n");
								}
							}
							if (Utils::getBool("addPlayerInfo")) {
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
							if (Utils::getBool("addLevelTraits")) {
								debugTextContents = std::regex_replace(
									debugTextContents,
									std::regex("\n-- Audio --"),
									fmt::format("\nLevel: {}\n-- Audio --", level)
								);
							}
							if (Utils::getBool("compactGameplaySection")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nTaps: "), " | Taps: "); // Attempt and Taps
								if (debugTextContents.find("TimeWarp: ") != std::string::npos) {
									debugTextContents = std::regex_replace(debugTextContents, std::regex("\nGravity: "), " | Gravity: "); // TimeWarp and Gravity
								}
								if (debugTextContents.find("Gradients: ") != std::string::npos) {
									debugTextContents = std::regex_replace(debugTextContents, std::regex("\nParticles: "), " | Particles: "); // Gradients and Particles
								}
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nY: "), " | Y: "); // X and Y position
							}
							if (Utils::getBool("compactAudioSection") && debugTextContents.find("Songs: ") != std::string::npos) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("\nSFX: "), " | SFX: ");
							}
							if (Utils::getBool("expandPerformance")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("-- Perf --"), "-- Performance --");
							}
							if (Utils::getBool("tapsToClicks")) {
								if (m_level->isPlatformer()) {
									debugTextContents = std::regex_replace(debugTextContents, std::regex("Taps: "), "Actions: ");
								} else {
									debugTextContents = std::regex_replace(debugTextContents, std::regex("Taps: "), "Clicks: ");
								}
							}
							if (Utils::getBool("fixLevelIDLabel")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("LevelID: "), "Level ID: ");
							}
							if (Utils::getBool("pluralAttempts")) {
								debugTextContents = std::regex_replace(debugTextContents, std::regex("Attempt: "), "Attempts: ");
							}
							if (Utils::getBool("includeFPS")) {
								debugTextContents = fmt::format("FPS: {}\n", m_fields->manager->fps) + debugTextContents;
							}
							if (Utils::getBool("addGameplayHeader")) {
								debugTextContents = std::string("-- Gameplay --\n") + debugTextContents;
							}
							if (Utils::getBool("logDebugText")) {
								log::info("--- LOGGED DEBUG TEXT [AFTER ERYSEDITS] ---:\n{}", debugTextContents);
							}
							if (Utils::getBool("blendingDebugText")) {
								debugTextNode->setBlendFunc({GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA}); // Manager::glBlendFuncs[5], Manager::glBlendFuncs[7]
							}
							if (Utils::getBool("modLoaderInfo")) {
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

			if (Utils::getBool("hideLevelCompleteVisuals") && m_fields->manager->isLevelComplete) {
				/*
				forgor what this was used for

				update: sike, i just remembered.
				sometimes they aren't children of "main-node"
				but rather direct children of playlayer itself,
				so a second for loop is necessary.
				apparently i had it under the wrong toggle this whole time, oops!
				*/
				for (unsigned int i = getChildrenCount(); i-- > 0; ) {
					auto theObject = getChildren()->objectAtIndex(i);
					if (const auto ccCircleWave = typeinfo_cast<CCCircleWave*>(theObject)) {
						ccCircleWave->setVisible(false);
					}
				}
				if (const auto mainNode = getChildByIDRecursive("main-node")) {
					for (CCNode* mainNodeChild : CCArrayExt<CCNode*>(mainNode->getChildren())) {
						if (const auto whereEverythingIs = typeinfo_cast<CCLayer*>(mainNodeChild)) {
							for (CCNode* childTwo : CCArrayExt<CCNode*>(whereEverythingIs->getChildren())) {
								if (const auto ccCircleWave = typeinfo_cast<CCCircleWave*>(childTwo)) {
									ccCircleWave->setVisible(false);
								} else if (const auto ccLightFlash = typeinfo_cast<CCLightFlash*>(childTwo)) {
									ccLightFlash->setVisible(false);
								}
							}
						}
					}
				}
			}
		}
	}
};