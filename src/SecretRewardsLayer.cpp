#ifndef GEODE_IS_MACOS
#include <Geode/modify/SecretRewardsLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MySecretRewardsLayer, SecretRewardsLayer) {
	void onShop(cocos2d::CCObject* sender) {
		if (Utils::shiftDown()) { SecretRewardsLayer::onShop(sender); }
	}
};
#endif