#include <Geode/modify/GJBaseGameLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyGJBaseGameLayer, GJBaseGameLayer) {
	void update(float dt) {
		GJBaseGameLayer::update(dt);
		auto manager = Manager::getSharedInstance();
		#ifndef __APPLE__
		manager->currentChannel = m_gameState.m_currentChannel;
		#endif
		if (Utils::get("debugTextToggle") && Utils::get("chromaDebugText") && !manager->chromaStarted) {
			if (auto pl = PlayLayer::get()) {
				if (auto debugTextNode = pl->getChildByID("debug-text")) {
					if (typeinfo_cast<CCLabelBMFont*>(debugTextNode) && debugTextNode->isVisible()) {
						/*
							original code by itzkiba in formattedplatformertime
							reused and adapted with permission
							proof of consent: https://discord.com/channels/911701438269386882/911702535373475870/1239386870253752320
						*/
						auto chromaSpeed = Utils::getDouble("chromaDebugTextSpeed");
						auto tintOne = CCTintTo::create(chromaSpeed, 255, 128, 128);
						auto tintTwo = CCTintTo::create(chromaSpeed, 255, 255, 128);
						auto tintThree = CCTintTo::create(chromaSpeed, 128, 255, 128);
						auto tintFour = CCTintTo::create(chromaSpeed, 128, 255, 255);
						auto tintFive = CCTintTo::create(chromaSpeed, 128, 128, 255);
						auto tintSix = CCTintTo::create(chromaSpeed, 255, 128, 128);
						auto sequence = CCSequence::create(tintOne, tintTwo, tintThree, tintFour, tintFive, tintSix, nullptr);
						auto repeat = CCRepeatForever::create(sequence);
						debugTextNode->runAction(repeat);
						manager->chromaStarted = true;
					}
				}
			}
		}
	}
	void toggleDualMode(GameObject * p0, bool p1, PlayerObject * p2, bool p3) {
		GJBaseGameLayer::toggleDualMode(p0, p1, p2, p3);
		if (Utils::modEnabled()) {
			auto manager = Manager::getSharedInstance();
			if (Utils::get("addPlayerInfo")) { manager->isDualsTime = p1; }
			// i've had horror stories of hooking playlayer onentertransitiondidfinish so im hooking it here instead
			if (Utils::get("hideLevelCompleteVisuals")) { manager->isLevelComplete = false; }
			manager->isPlayerDead = false;
		}
	}
};