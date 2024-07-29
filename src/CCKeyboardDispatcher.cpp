#ifndef GEODE_IS_MACOS
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyCCKeyboardDispatcher, CCKeyboardDispatcher) {
	bool dispatchKeyboardMSG(cocos2d::enumKeyCodes p0, bool p1, bool p2) {
		if (p0 == enumKeyCodes::KEY_Shift && p1) {
			Manager::getSharedInstance()->isShiftKeyDown = p1;
		} else {
			Manager::getSharedInstance()->isShiftKeyDown = false;
			return CCKeyboardDispatcher::dispatchKeyboardMSG(p0, p1, p2);
		};
		return true;
	}
};
#endif