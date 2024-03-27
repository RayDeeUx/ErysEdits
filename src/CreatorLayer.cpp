#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/CreatorLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyCreatorLayer, CreatorLayer) {
	void onSecretVault(cocos2d::CCObject* sender) {
		if (Utils::shiftDown()) {
			// why do i need to do all of this? I DONT KNOW
			// but ty to SpaghettDev for finding the memory address!
			if (GameManager::sharedState()->getUGV("5")) {
				auto scene = CCScene::create();
				scene->addChild(SecretLayer2::create());
				CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
			} else { CreatorLayer::onSecretVault(sender); }
		}
	}
	void onTreasureRoom(cocos2d::CCObject* sender) {
		if (Utils::shiftDown()) { CreatorLayer::onTreasureRoom(sender); }
	}
};
#endif