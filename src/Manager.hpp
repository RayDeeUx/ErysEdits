#pragma once

// Manager.hpp structure by acaruso
// reused with explicit permission and strong encouragement

using namespace geode::prelude;

class Manager {

protected:
	static Manager* instance;
public:

	bool isDualsTime = false;
	bool isLevelComplete = false;
	bool originalShowProgressBarValue = false;
	bool originalShowPercentageValue = false;

	bool canCall = false;

	bool fourGBChecked = false;
	bool isFourGB = false;

	int installedMods = 0;
	int loadedMods = 0;
	int disabledMods = 0;
	int problems = 0;
	std::string geodeVer = "";
	std::string gameVer = "";
	std::string platform = "";
	std::string forwardCompat = "";
	std::string fourGBStatus = "";

	const std::map<std::string, std::string> miscToSetting = {
		{ "edit_ePulseBtn_001.png", "disablePulse" },
		{ "edit_eAreaTintBtn_001.png", "disableAreaTint" },
		{ "edit_eShakeBtn_001.png", "disableShake" },
		{ "edit_eSFXBtn_001.png", "disableSFX" },
		{ "edit_eEditSFXBtn_001.png", "disableEditSFX" }
	};

	const std::map<int, std::string> miscIDToSetting = {
		{ 1006, "disablePulse" },
		{ 3010, "disableAreaTint" },
		{ 1520, "disableShake" },
		{ 3602, "disableSFX" },
		{ 3603, "disableEditSFX" }
	};

	bool isShiftKeyDown = false;
	
	bool isPlayerDead = false;
	
	const std::list<std::string> vanillaSFX = { "achievement_01.ogg", "buyItem01.ogg", "buyItem03.ogg", "chest07.ogg", "chest08.ogg", "chestClick.ogg", "chestLand.ogg", "chestOpen01.ogg", "counter003.ogg", "crystal01.ogg", "door001.ogg", "door01.ogg", "door02.ogg", "endStart_02.ogg", "explode_11.ogg", "gold01.ogg", "gold02.ogg", "grunt01.ogg", "grunt02.ogg", "grunt03.ogg", "highscoreGet02.ogg", "magicExplosion.ogg", "playSound_01.ogg", "quitSound_01.ogg", "reward01.ogg", "secretKey.ogg", "unlockPath.ogg" };
	
	const std::list<std::string> badSFX = { "achievement_01.ogg", "magicExplosion.ogg", "gold02.ogg", "secretKey.ogg" };

	std::string lastPlayedSong = "N/A";
	#ifndef __APPLE__
	std::string lastPlayedEffect = "N/A";
	#else
	std::string lastPlayedEffect = "[MacOS issue]";
	#endif
	
	#ifndef __APPLE__
	int currentChannel = 0;
	#endif
	
	bool isInSavedLevels = false;
	
	#ifdef GEODE_IS_WINDOWS
	int currentGauntletPage = 0;
	#endif
	
	bool hasCalledAlready = false;
	std::string modsInfo = "";
	std::string modsInfoForClipboard = "";
	std::string modsListMode = "N/A";
	
	bool isBreakingPlatforming = false;
	
	// GLenum glBlendFuncs[] = {GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA, GL_SRC_ALPHA_SATURATE };

	static Manager* getSharedInstance() {
		if (!instance) {
			instance = new Manager();
		}
		return instance;
	}

};