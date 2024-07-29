
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
	
	bool getBool(std::string setting) { return Mod::get()->getSettingValue<bool>(setting); }
	
	int64_t getInt(std::string setting) { return Mod::get()->getSettingValue<int64_t>(setting); }
	
	double getDouble(std::string setting) { return Mod::get()->getSettingValue<double>(setting); }

	std::string getString(std::string setting) { return Mod::get()->getSettingValue<std::string>(setting); }

	ccColor3B getColor(std::string setting) { return Mod::get()->getSettingValue<ccColor3B>(setting); }

	ccColor4B getColorAlpha(std::string setting) { return Mod::get()->getSettingValue<ccColor4B>(setting); }

	bool modEnabled() { return Utils::getBool("enabled"); }
	
	void keybindDisabledGeneric(std::string titleTemplate, std::string keybindDesc) {
		FLAlertLayer::create(
			fmt::format("{} Disabled!", titleTemplate).c_str(),
			fmt::format("You have either disabled the softtoggle for the ErysEdits mod, or you have disabled the keybind(s) to {}. Please double-check your mod configs and try again.", keybindDesc),
			"OK"
		)->show();
	}

	void refreshKeybindDisabled() { keybindDisabledGeneric("Refresh Page", "refresh this page"); }
	
	void arrowKeyNavDisabled() { keybindDisabledGeneric("Arrow Key Page Navigation", "navigate between pages"); }
	
	void likeDislikeShortcutDisabled() { keybindDisabledGeneric("Like/Dislike Shortcut", "like/dislike content"); }
	
	void viewCommentsDisabled() { keybindDisabledGeneric("View Comments Shortcut", "view level comments/user comment history"); }
	
	void navigateGauntletsDisabled() { keybindDisabledGeneric("Navigate Gauntlets", "navigate the Gauntlets"); }
	
	void moreOptionsDisabled() { keybindDisabledGeneric("More Options Shortcuts", "open your GD settings"); }
	
	void levelLengthDisabled() { keybindDisabledGeneric("Level Length Filters", "toggle level length search filters"); }
	
	void levelDifficultyDisabled() { keybindDisabledGeneric("Level Difficulty Filters", "toggle level difficulty search filters"); }
	
	void demonFilterDisabled() { keybindDisabledGeneric("Demon Filters", "toggle demon search filters"); }
	
	void quickSearchDisabled() { keybindDisabledGeneric("Quick Search Shortcuts", "open a quick search option"); }
	
	void garageNavigationDisabled() { keybindDisabledGeneric("Icon Kit Navigation", "navigate the icon kit"); }

	bool isSceneRunning(std::string sceneName) { return CCDirector::get()->getRunningScene()->getChildByID(sceneName.c_str()); }
	
	bool isSceneRunningRecursive(std::string sceneNameRecursive) { return CCDirector::get()->getRunningScene()->getChildByIDRecursive(sceneNameRecursive.c_str()); }

	bool isProfilePage() { return isSceneRunning("ProfilePage"); }

	bool noProfilePage() { return !isProfilePage(); }

	bool isLevelLeaderboard() { return isSceneRunning("LevelLeaderboard"); }

	bool noLevelLeaderboard() { return !isLevelLeaderboard(); }

	bool isInfoLayer() { return isSceneRunning("InfoLayer"); }

	bool isInfoLayerRecursive() { return isSceneRunningRecursive("InfoLayer"); }

	bool noInfoLayer() { return !isInfoLayer(); }
	
	bool isMoreOptionsLayer() { return isSceneRunning("MoreOptionsLayer"); }
	
	bool noMoreOptionsLayer() { return !isMoreOptionsLayer(); }
	
	bool nothingElse() { return noProfilePage() && noInfoLayer() && noLevelLeaderboard() && noMoreOptionsLayer() && !isSceneRunningRecursive("DemonFilterSelectLayer") && !isSceneRunningRecursive("MoreSearchLayer") && !isSceneRunningRecursive("ShardsPage") && !isSceneRunningRecursive("CharacterColorPage"); }

	void restoreOrigGMGVs(GameManager* gameManager, bool changeCanCall, bool isEnteringLevel) {
		// do NOT touch isEnteringLevel param. it is unused but i don't want to remove it and break everything
		Manager* manager = Manager::getSharedInstance();
		
		if (Utils::modEnabled() && Utils::getBool("unverifiedPercent")) {
			gameManager->m_showProgressBar = manager->originalShowProgressBarValue;
			gameManager->setGameVariable("0040", manager->originalShowPercentageValue);
		}
		if (changeCanCall) { manager->canCall = true; }
		
		if (const auto breakingPlatforming = Utils::getMod("raydeeux.breakingplatforming")) {
			if (breakingPlatforming->getSettingValue<bool>("enabled")) {
				manager->isBreakingPlatforming = true;
			} else {
				manager->isBreakingPlatforming = false;
			}
		} else {
			manager->isBreakingPlatforming = false;
		}
		if (manager->chromaStarted) {
			manager->chromaStarted = false;
		}
	}

	void applyGMGVs(const bool isLevelVerified) {
		Manager* manager = Manager::getSharedInstance();
		GameManager* gameManager = GameManager::get();
		if (Utils::modEnabled() && Utils::getBool("unverifiedPercent")) {
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
	
#ifndef GEODE_IS_MACOS
	bool shiftDown() {
		return (Manager::getSharedInstance()->isShiftKeyDown || !(Utils::modEnabled() && Utils::getBool("shiftForVault")));
	}
#endif
	
	Mod* getMod(std::string modID) { return Loader::get()->getLoadedMod(modID); }

	std::string getModVersion(Mod* mod) { return mod->getVersion().toVString(); }
}