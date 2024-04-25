#include <Geode/modify/LevelCell.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyLevelCell, LevelCell) {
	static void onModify(auto & self)
	{
		self.setHookPriority("LevelCell::onClick", 9999);
	}
	void onLevelDesc(CCObject* sender) {
		auto theLevel = this->m_level;
		std::string levelDesc = theLevel->getUnpackedLevelDescription();
		if (strcmp(levelDesc.c_str(), "") == 0) {
			if (Manager::getSharedInstance()->isInSavedLevels || Utils::isSceneRunning("LevelListLayer")) {
				levelDesc = "(No description visible. Try downloading the level, and exit + reenter this menu and view again.)";
			} else {
				levelDesc = "(No description provided)";
			}
		}
		FLAlertLayer::create(
			nullptr,
			std::string(theLevel->m_levelName).c_str(),
			std::string(std::string("Published by ") + std::string(theLevel->m_creatorName) + std::string("\n\n") + std::string(levelDesc)).c_str(),
			"Close",
			nullptr,
			420.f
		)->show();
	}
	void onClick(CCObject* sender) {
		// hooking this function is necessary in order for the "view" button to work while compact mode is active in "my levels"
		if (this->m_level->m_levelType == GJLevelType::Editor && Utils::modEnabled() && Utils::get("compactEditorLevels")) {
			auto scene = CCScene::create();
			scene->addChild(EditLevelLayer::create(m_level));
			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
		} else { LevelCell::onClick(sender); }
	}
	void loadLocalLevelCell() {
		LevelCell::loadLocalLevelCell();
		if (!(Utils::modEnabled() && Utils::get("compactEditorLevels"))) { return; }
		if (auto localLevelname = typeinfo_cast<CCLabelBMFont*>(getChildByIDRecursive("level-name"))) { localLevelname->limitLabelWidth(200.f, .6f, .01f); }
		if (auto mainLayer = typeinfo_cast<CCLayer*>(getChildByIDRecursive("main-layer"))) { mainLayer->setPositionY(-3.5f); }
	}
	void loadCustomLevelCell() {
		LevelCell::loadCustomLevelCell();
		if (!(Utils::modEnabled() && Utils::get("levelDescFromList"))) { return; }
		if (auto viewButton = getChildByIDRecursive("view-button")) {
			auto infoButton = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
			infoButton->setScale(.6f);
			auto descButton = CCMenuItemSpriteExtra::create(infoButton, this, menu_selector(MyLevelCell::onLevelDesc));
			descButton->setID("level-desc-button"_spr);
			#ifndef GEODE_IS_MOBILE
			descButton->setPosition({
				viewButton->getPositionX() + (viewButton->getContentSize().width / 2.f),
				viewButton->getPositionY() - (viewButton->getContentSize().height / 2.f)
			});
			#else
			if (!Utils::isSceneRunningRecursive("DailyLevelPage")) {
				if (auto mainLayer = getChildByID("main-layer")) {
					descButton->setPosition({
						mainLayer->getPositionX() - (mainLayer->getContentSize().width / 2.f) + 7.5f,
						mainLayer->getPositionY() - (mainLayer->getContentSize().height / 2.f) + 7.5f
					});
				}
			} else {
				descButton->setPosition({
					viewButton->getPositionX() + (viewButton->getContentSize().width / 2.f),
					viewButton->getPositionY() - (viewButton->getContentSize().height / 2.f)
				});
			}
			#endif
			getChildByIDRecursive("main-menu")->addChild(descButton);
		}
	}
};