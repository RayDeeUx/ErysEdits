
#include <regex>
#include <stdio.h>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::cocos;

namespace Utils {
	cocos2d::CCNode* getChildBySpriteFrameNameRecursive(cocos2d::CCNode* parent, char const* name) {
		return findFirstChildRecursive<cocos2d::CCNode>(parent, [=](auto* spr) {
			return isSpriteFrameName(spr, name);
		});
	}
	
	bool get(std::string setting) { return Mod::get()->getSettingValue<bool>(setting); }
	
	int64_t getInt(std::string setting) { return Mod::get()->getSettingValue<int64_t>(setting); }
	
	double getDouble(std::string setting) { return Mod::get()->getSettingValue<double>(setting); }
	
	bool modEnabled() { return Utils::get("enabled"); }
	
	void keybindDisabledGeneric(std::string titleTemplate, std::string keybindDesc) {
		FLAlertLayer::create(
			fmt::format("{} Disabled!", titleTemplate).c_str(),
			fmt::format("You have either disabled the softtoggle for the ErysEdits mod, or you have disabled the keybind to {}. Please double-check your mod configs and try again.", keybindDesc),
			"OK"
		)->show();
	}

	void refreshKeybindDisabled() { keybindDisabledGeneric("Refresh Page", "refresh this page"); }
	
	void arrowKeyNavDisabled() { keybindDisabledGeneric("Arrow Key Page Navigation", "navigate between pages"); }
	
	void likeDislikeShortcutDisabled() { keybindDisabledGeneric("Like/Dislike Shortcut", "like/dislike content"); }
	
	void viewCommentsDisabled() { keybindDisabledGeneric("View Comments Shortcut", "view level comments/user comment history"); }
	
	void navigateGauntletsDisabled() { keybindDisabledGeneric("Navigate Gauntlets", "navigate the Gauntlets"); }
	
	void moreOptionsDisabled() { keybindDisabledGeneric("More Options Shortcuts", "open your GD settings"); }

	bool isSceneRunning(std::string sceneName) { return CCDirector::get()->getRunningScene()->getChildByID(sceneName.c_str()); }
	
	bool isSceneRunningRecursive(std::string sceneName) { return CCDirector::get()->getRunningScene()->getChildByIDRecursive(sceneName.c_str()); }

	bool isProfilePage() { return isSceneRunning("ProfilePage"); }

	bool noProfilePage() { return !isProfilePage(); }

	bool isLevelLeaderboard() { return isSceneRunning("LevelLeaderboard"); }

	bool noLevelLeaderboard() { return !isLevelLeaderboard(); }

	bool isInfoLayer() { return isSceneRunning("InfoLayer"); }

	bool isInfoLayerRecursive() { return isSceneRunningRecursive("InfoLayer"); }

	bool noInfoLayer() { return !isInfoLayer(); }
	
	bool nothingElse() { return noProfilePage() && noInfoLayer() && noLevelLeaderboard(); }

	void restoreOrigGMGVs(GameManager* gameManager, bool changeCanCall, bool isEnteringLevel) {
		auto manager = Manager::getSharedInstance();
		
		if (Utils::modEnabled() && Utils::get("unverifiedPercent")) {
			gameManager->m_showProgressBar = manager->originalShowProgressBarValue;
			gameManager->setGameVariable("0040", manager->originalShowPercentageValue);
		}
		if (changeCanCall) { manager->canCall = true; }
	}

	void applyGMGVs(bool isLevelVerified) {
		auto manager = Manager::getSharedInstance();
		auto gameManager = GameManager::get();
		if (Utils::modEnabled() && Utils::get("unverifiedPercent")) {
			if (isLevelVerified) {
				gameManager->m_showProgressBar = manager->originalShowProgressBarValue;
				gameManager->setGameVariable("0040", manager->originalShowPercentageValue);
			} else {
				gameManager->m_showProgressBar = false;
				gameManager->setGameVariable("0040", false);
			}
		}
		manager->canCall = true;
	}

	std::string buildPlayerStatusString(PlayerObject* thePlayer, GJGameLevel* theLevel, PlayLayer* playLayer, bool isPlayerTwo) {
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
			if (Manager::getSharedInstance()->isDualsTime) { status = status + " [Dual]"; }

			if (playLayer->m_isPracticeMode) { status = status + " {Practice}"; }
			else if (playLayer->m_isTestMode) { status = status + " {Testmode}"; }
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
		
		if ((theLevel->m_accountID.value() == 13950148 && theLevel->m_levelType == GJLevelType::Saved)
		|| GameManager::get()->m_playerUserID.value() == 128138354 && theLevel->m_levelType != GJLevelType::Saved) { level = level + " <HOMOPHOBIC>"; }

		if (Manager::getSharedInstance()->isLevelComplete) { level = level + " <Completed>"; }
		
		return level;
	}
	
	#ifdef GEODE_IS_WINDOWS
	// 4GB Patch detection code written by cvolton
	// code reuse consent implied from here: https://discord.com/channels/911701438269386882/911702535373475870/1221183808708153444

	bool is4GBPatchEnabled() {
		auto manager = Manager::getSharedInstance();
		if (manager->fourGBChecked) { return manager->isFourGB; }
		wchar_t result[MAX_PATH];
		GetModuleFileNameW(NULL, result, MAX_PATH);

		if(!std::filesystem::exists(result)) { return true; }
			
		std::ifstream file(result, std::ios::binary);
		std::vector<char> buffer(std::istreambuf_iterator<char>(file), {});

		PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)buffer.data();
		PIMAGE_NT_HEADERS imageNTHeaders = (PIMAGE_NT_HEADERS)((DWORD)buffer.data() + dosHeader->e_lfanew);
		auto characteristics = imageNTHeaders->FileHeader.Characteristics;
		manager->isFourGB = characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE;
		manager->fourGBChecked = true;
		return manager->isFourGB;
	}
	#endif
	
	#ifdef GEODE_IS_WINDOWS
	bool shiftDown() {
		return (Manager::getSharedInstance()->isShiftKeyDown || !(Utils::modEnabled() && Utils::get("shiftForVault")));
	}
	#endif
}