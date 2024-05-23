#include <Geode/modify/GJBaseGameLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyGJBaseGameLayer, GJBaseGameLayer) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void update(float dt) {
		GJBaseGameLayer::update(dt);
		if (Utils::getBool("debugTextToggle") && Utils::getBool("chromaDebugText") && !m_fields->manager->chromaStarted) {
			if (const auto pl = PlayLayer::get()) {
				if (const auto debugTextNode = pl->getChildByID("debug-text")) {
					if (typeinfo_cast<CCLabelBMFont*>(debugTextNode) && debugTextNode->isVisible()) {
						/*
							original code by itzkiba in formattedplatformertime
							reused and adapted with permission
							proof of consent: https://discord.com/channels/911701438269386882/911702535373475870/1239386870253752320
						*/
						const auto chromaSpeed = Utils::getDouble("chromaDebugTextSpeed");
						const auto tintOne = CCTintTo::create(chromaSpeed, 255, 128, 128);
						const auto tintTwo = CCTintTo::create(chromaSpeed, 255, 255, 128);
						const auto tintThree = CCTintTo::create(chromaSpeed, 128, 255, 128);
						const auto tintFour = CCTintTo::create(chromaSpeed, 128, 255, 255);
						const auto tintFive = CCTintTo::create(chromaSpeed, 128, 128, 255);
						const auto tintSix = CCTintTo::create(chromaSpeed, 255, 128, 128);
						const auto sequence = CCSequence::create(tintOne, tintTwo, tintThree, tintFour, tintFive, tintSix, nullptr);
						const auto repeat = CCRepeatForever::create(sequence);
						debugTextNode->runAction(repeat);
						m_fields->manager->chromaStarted = true;
					}
				}
			}
		}
	}
	void toggleDualMode(GameObject * p0, bool p1, PlayerObject * p2, bool p3) {
		GJBaseGameLayer::toggleDualMode(p0, p1, p2, p3);
		if (Utils::modEnabled()) {
			if (Utils::getBool("addPlayerInfo")) { m_fields->manager->isDualsTime = p1; }
			// i've had horror stories of hooking playlayer onentertransitiondidfinish so im hooking it here instead
			if (Utils::getBool("hideLevelCompleteVisuals")) { m_fields->manager->isLevelComplete = false; }
			m_fields->manager->isPlayerDead = false;
		}
	}
};