#include <Geode/modify/GJGarageLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyGJGarageLayer, GJGarageLayer) {
	bool init() {
		if (!GJGarageLayer::init()) { return false; }
		if (!Utils::modEnabled()) { return true; }
		if (auto soggy = Utils::getChildBySpriteFrameNameRecursive(this, "capeling.soggy-mod/GJ_soggyBtn_001.png")) { soggy->setVisible(false); }
		return true;
	}
	void onShop(cocos2d::CCObject* sender) {
		if (Utils::shiftDown()) { GJGarageLayer::onShop(sender); }
	}
};