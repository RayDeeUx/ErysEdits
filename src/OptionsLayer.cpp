#ifndef GEODE_IS_MACOS
#include <Geode/modify/OptionsLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyOptionsLayer, OptionsLayer) {
	void onSecretVault(cocos2d::CCObject* sender) {
		if (Utils::shiftDown()) { OptionsLayer::onSecretVault(sender); }
	}
};
#endif