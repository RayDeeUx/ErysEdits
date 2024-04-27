#ifndef __APPLE__
#include <Geode/modify/EndLevelLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyEndLevelLayer, EndLevelLayer) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("EndLevelLayer::customSetup", INT64_MIN + 1);
	}
	void onMenu(cocos2d::CCObject* sender) {
		if (Utils::modEnabled() && Utils::get("hideLevelCompleteVisuals")) { Manager::getSharedInstance()->isLevelComplete = false; }
		EndLevelLayer::onMenu(sender);
	}
	void onErysEditsCompleteText(cocos2d::CCObject* sender) {
		// apparently i can't use nullptr delegate here
		if (!Utils::modEnabled() || !Utils::get("showModsList")) { return; }
		FLAlertLayer::create(
			"T&^JKIU*HBJUDRFGCHU&^TRDFCGVBJHU*^%RDF",
			fmt::format(
				"{}\n[Brought to you by ErysEdits]",
				Manager::getSharedInstance()->modsInfo
			),
			"Close"
		)->show();
	}
	void customSetup() {
		EndLevelLayer::customSetup();
		
		if (!Utils::modEnabled() || !Utils::get("showModsList")) { return; }
		
		if (auto lvlCompleteText = getChildByIDRecursive("level-complete-text")) {
			lvlCompleteText->removeFromParent();
		
			auto lvlCompleteTextMenu = CCMenu::create();
			lvlCompleteTextMenu->setID("level-complete-text-menu"_spr);
			lvlCompleteTextMenu->updateLayout();
			lvlCompleteTextMenu->setPosition(lvlCompleteText->boundingBox().origin);
			
			auto lvlCompleteTextMenuBtn = CCMenuItemSpriteExtra::create(lvlCompleteText, this, menu_selector(MyEndLevelLayer::onErysEditsCompleteText));
			lvlCompleteTextMenuBtn->setPosition(lvlCompleteText->getPosition());
			
			lvlCompleteTextMenu->addChild(lvlCompleteTextMenuBtn);
			addChild(lvlCompleteTextMenu);
		} else if (auto practiceCompleteText = getChildByIDRecursive("practice-complete-text")) {
			practiceCompleteText->removeFromParent();
		
			auto practiceCompleteTextMenu = CCMenu::create();
			practiceCompleteTextMenu->setID("practice-complete-text-menu"_spr);
			practiceCompleteTextMenu->updateLayout();
			practiceCompleteTextMenu->setPosition(practiceCompleteText->boundingBox().origin);
			
			auto practiceCompleteTextMenuBtn = CCMenuItemSpriteExtra::create(practiceCompleteText, this, menu_selector(MyEndLevelLayer::onErysEditsCompleteText));
			practiceCompleteTextMenuBtn->setPosition(practiceCompleteText->getPosition());
			
			practiceCompleteTextMenu->addChild(practiceCompleteTextMenuBtn);
			addChild(practiceCompleteTextMenu);
		}
	}
};
#endif