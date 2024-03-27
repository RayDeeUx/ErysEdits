#include <Geode/modify/GameManager.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

/*
	restore the original values of the gamevars found during game launch (intended for game restart)
	{especially weebify's restart buttons mod as the keystroke can be activated anywehre}
	yes, i can just make a PR to prevent the restart keybind from triggering game restart while inside a level
	but that doesnt solve the actual problem. and what if another mod chooses to cause similar circumstances?
	so restoring gamevar values it is
*/
class $modify(MyGameManager, GameManager) {
// first idea that comes to mind is hooking gamemanager encodedatato
	void encodeDataTo(DS_Dictionary* p0) {
		// and resetting the value to what its supposed to be
		if (Utils::modEnabled() && Utils::get("unverifiedPercent")) {
			m_showProgressBar = Manager::getSharedInstance()->originalShowProgressBarValue; // [or in this case, what i want it to be]
			setGameVariable("0040", Manager::getSharedInstance()->originalShowPercentageValue); // [or in this case, what i want it to be]
		}

		// before calling the original
		GameManager::encodeDataTo(p0);

		// ty cvolton for the assistance
	}
};