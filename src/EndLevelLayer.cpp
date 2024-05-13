#ifndef __APPLE__
#include <Geode/modify/EndLevelLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyEndLevelLayer, EndLevelLayer) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("EndLevelLayer::customSetup", INT32_MIN + 1);
	}
	void onMenu(cocos2d::CCObject* sender) {
		if (Utils::modEnabled() && Utils::get("hideLevelCompleteVisuals")) { Manager::getSharedInstance()->isLevelComplete = false; }
		EndLevelLayer::onMenu(sender);
	}
	void onErysEditsCompleteText(cocos2d::CCObject* sender) {
		if (!Utils::modEnabled() || Utils::getInt("showModsListMode") == 0) { return; }
		auto manager = Manager::getSharedInstance();
		// apparently i can't use nullptr delegate here, so have a hacky workaround
		clipboard::write(manager->modsInfoForClipboard);
		FLAlertLayer::create(
			"T&^JKIU*HBJUDRFGCHU&^TRDFCGVBJHU*^%RDF",
			fmt::format(
				"<cj>[{}]</c>\n{}\n<cj>[{}]</c>",
				manager->modsListMode,
				manager->modsInfo,
				manager->modsListMode
			),
			"Close"
		)->show();
	}
	void customSetup() {
		EndLevelLayer::customSetup();
		
		if (!Utils::modEnabled() || Utils::getInt("showModsListMode") == 0) { return; }
		
		/*
			original code adapted from sofabeddd's geometry-dash mod.
			adapted with consent.
			conversation starts here:
			https://discord.com/channels/911701438269386882/911702535373475870/1234189720062394509
		*/
		if (auto lvlCompleteText = getChildByIDRecursive("level-complete-text")) {
			lvlCompleteText->removeFromParent();
		
			auto lvlCompleteTextMenu = CCMenu::create();
			lvlCompleteTextMenu->setID("level-complete-text-menu"_spr);
			lvlCompleteTextMenu->updateLayout();
			lvlCompleteTextMenu->setPosition(lvlCompleteText->boundingBox().origin);
			
			auto lvlCompleteTextMenuBtn = CCMenuItemSpriteExtra::create(lvlCompleteText, this, menu_selector(MyEndLevelLayer::onErysEditsCompleteText));
			lvlCompleteTextMenuBtn->setPosition(lvlCompleteText->getPosition());
			
			lvlCompleteTextMenu->addChild(lvlCompleteTextMenuBtn);
			getChildByID("main-layer")->addChild(lvlCompleteTextMenu);
		} else if (auto practiceCompleteText = getChildByIDRecursive("practice-complete-text")) {
			practiceCompleteText->removeFromParent();
		
			auto practiceCompleteTextMenu = CCMenu::create();
			practiceCompleteTextMenu->setID("practice-complete-text-menu"_spr);
			practiceCompleteTextMenu->updateLayout();
			practiceCompleteTextMenu->setPosition(practiceCompleteText->boundingBox().origin);
			
			auto practiceCompleteTextMenuBtn = CCMenuItemSpriteExtra::create(practiceCompleteText, this, menu_selector(MyEndLevelLayer::onErysEditsCompleteText));
			practiceCompleteTextMenuBtn->setPosition(practiceCompleteText->getPosition());
			
			practiceCompleteTextMenu->addChild(practiceCompleteTextMenuBtn);
			getChildByID("main-layer")->addChild(practiceCompleteTextMenu);
		}
	}
};
#endif