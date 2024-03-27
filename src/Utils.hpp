#pragma once


#include <Geode/Bindings.hpp>
#include "Manager.hpp"

using namespace geode::prelude;
using namespace geode::cocos;

namespace Utils {
	cocos2d::CCNode* getChildBySpriteFrameNameRecursive(cocos2d::CCNode* parent, char const* name);
	
	bool get(std::string setting);
	bool modEnabled();
	
	void keybindDisabledGeneric(std::string titleTemplate, std::string keybindDesc);
	void refreshKeybindDisabled();
	void arrowKeyNavDisabled();
	void likeDislikeShortcutDisabled();
	void viewCommentsDisabled();
	
	bool isSceneRunning(std::string sceneName);
	bool isSceneRunningRecursive(std::string sceneName);
	bool isProfilePage();
	bool noProfilePage();
	bool isLevelLeaderboard();
	bool noLevelLeaderboard();
	bool isInfoLayer();
	bool isInfoLayerRecursive();
	bool noInfoLayer();
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
	
	void decompLevelDisablesSFX(gd::string levelString);
	
	bool isRandDeathSounds();
}