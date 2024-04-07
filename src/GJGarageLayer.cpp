#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/GJGarageLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyGJGarageLayer, GJGarageLayer) {
	void onShop(cocos2d::CCObject* sender) {
		if (Utils::shiftDown()) { GJGarageLayer::onShop(sender); }
	}
};
#endif