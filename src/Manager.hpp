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

	std::map<std::string, std::string> miscToSetting = {
		{ "edit_ePulseBtn_001.png", "disablePulse" },
		{ "edit_eAreaTintBtn_001.png", "disableAreaTint" },
		{ "edit_eShakeBtn_001.png", "disableShake" },
		{ "edit_eSFXBtn_001.png", "disableSFX" },
		{ "edit_eEditSFXBtn_001.png", "disableEditSFX" }
	};

	bool isShiftKeyDown = false;
	
	bool isLevelDisablingDeathSFX = false;
	
	bool isPlayerDead = false;

	// GLenum glBlendFuncs[] = {GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA, GL_SRC_ALPHA_SATURATE };

	static Manager* getSharedInstance(){

		if (!instance) {
			instance = new Manager();
		};
		return instance;
	}

};