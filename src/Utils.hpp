#pragma once

#include <Geode/Bindings.hpp>
#include "Manager.hpp"

using namespace geode::prelude;
using namespace geode::cocos;

namespace Utils {
	cocos2d::CCNode* getChildBySpriteFrameNameRecursive(cocos2d::CCNode* parent, char const* name);
	
	bool get(std::string setting);
	int64_t getInt(std::string setting);
	double getDouble(std::string setting);
	bool modEnabled();
	
	void keybindDisabledGeneric(std::string titleTemplate, std::string keybindDesc);
	void refreshKeybindDisabled();
	void arrowKeyNavDisabled();
	void likeDislikeShortcutDisabled();
	void viewCommentsDisabled();
	void navigateGauntletsDisabled();
	void moreOptionsDisabled();
	void levelLengthDisabled();
	void levelDifficultyDisabled();
	void demonFilterDisabled();
	
	bool isSceneRunning(std::string sceneName);
	bool isSceneRunningRecursive(std::string sceneName);
	bool isProfilePage();
	bool noProfilePage();
	bool isLevelLeaderboard();
	bool noLevelLeaderboard();
	bool isInfoLayer();
	bool isInfoLayerRecursive();
	bool noInfoLayer();
	bool isMoreOptionsLayer();
	bool noMoreOptionsLayer();
	bool nothingElse();
	void restoreOrigGMGVs(GameManager* gameManager, bool changeCanCall = true, bool isEnteringLevel = false);
	void applyGMGVs(bool isLevelVerified);

	std::string buildPlayerStatusString(PlayerObject* thePlayer, GJGameLevel* theLevel, PlayLayer* playLayer, bool isPlayerTwo);
	std::string buildLevelTraitsString(GJGameLevel* theLevel);

	#ifdef GEODE_IS_WINDOWS
	bool is4GBPatchEnabled();
	#endif

	#ifdef GEODE_IS_WINDOWS
	bool shiftDown();
	#endif
}