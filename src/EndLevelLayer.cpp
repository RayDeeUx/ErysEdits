#include <Geode/modify/EndLevelLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyEndLevelLayer, EndLevelLayer) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	static void onModify(auto& self) {
		(void) self.setHookPriority("EndLevelLayer::customSetup", INT32_MIN + 1);
	}
	bool doNotShowModsList() {
		return (!Utils::modEnabled() || Utils::getInt("showModsListMode") == 0 || m_fields->manager->modsInfoForClipboard == "N/A");
	}
	void onErysEditsCompleteText(cocos2d::CCObject* sender) {
		if (MyEndLevelLayer::doNotShowModsList()) { return; }
		// apparently i can't use nullptr delegate here, so have a hacky workaround
		clipboard::write(m_fields->manager->modsInfoForClipboard);
		FLAlertLayer::create(
			"BRYCETANKTHRUSTBRYCETANKTHRUSTBRYCETANKTHRUST",
			fmt::format(
				"<cj>[{}]</c>\n{}\n<cj>[{}]</c>",
				m_fields->manager->modsListMode,
				m_fields->manager->modsInfo,
				m_fields->manager->modsListMode
			),
			"Close"
		)->show();
	}
	void onMenu(cocos2d::CCObject* sender) {
		if (Utils::modEnabled() && Utils::get("hideLevelCompleteVisuals")) { m_fields->manager->isLevelComplete = false; }
		EndLevelLayer::onMenu(sender);
	}
	void customSetup() {
		EndLevelLayer::customSetup();
		
		if (MyEndLevelLayer::doNotShowModsList()) { return; }
		
		/*
			original code adapted from sofabeddd's geometry-dash mod.
			adapted with consent.
			conversation starts here:
			https://discord.com/channels/911701438269386882/911702535373475870/1234189720062394509
		*/
		if (const auto lvlCompleteText = getChildByIDRecursive("level-complete-text")) {
			lvlCompleteText->removeFromParent();

			const auto lvlCompleteTextMenu = CCMenu::create();
			lvlCompleteTextMenu->setID("level-complete-text-menu"_spr);
			lvlCompleteTextMenu->updateLayout();
			lvlCompleteTextMenu->setPosition(lvlCompleteText->boundingBox().origin);

			const auto lvlCompleteTextMenuBtn = CCMenuItemSpriteExtra::create(lvlCompleteText, this, menu_selector(MyEndLevelLayer::onErysEditsCompleteText));
			lvlCompleteTextMenuBtn->setPosition(lvlCompleteText->getPosition());
			
			lvlCompleteTextMenu->addChild(lvlCompleteTextMenuBtn);
			getChildByID("main-layer")->addChild(lvlCompleteTextMenu);
		} else if (const auto practiceCompleteText = getChildByIDRecursive("practice-complete-text")) {
			practiceCompleteText->removeFromParent();

			const auto practiceCompleteTextMenu = CCMenu::create();
			practiceCompleteTextMenu->setID("practice-complete-text-menu"_spr);
			practiceCompleteTextMenu->updateLayout();
			practiceCompleteTextMenu->setPosition(practiceCompleteText->boundingBox().origin);

			const auto practiceCompleteTextMenuBtn = CCMenuItemSpriteExtra::create(practiceCompleteText, this, menu_selector(MyEndLevelLayer::onErysEditsCompleteText));
			practiceCompleteTextMenuBtn->setPosition(practiceCompleteText->getPosition());
			
			practiceCompleteTextMenu->addChild(practiceCompleteTextMenuBtn);
			getChildByID("main-layer")->addChild(practiceCompleteTextMenu);
		}
	}
};
