#include <Geode/modify/LevelCell.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyLevelCell, LevelCell) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	static void onModify(auto & self)
	{
		(void) self.setHookPriority("LevelCell::onClick", 9999);
	}
	void onLevelDesc(CCObject* sender) {
		const auto theLevel = this->m_level;
		std::string levelDesc = theLevel->getUnpackedLevelDescription();
		if (strcmp(levelDesc.c_str(), "") == 0) {
			if (Utils::isSceneRunning("provider-popup") || Utils::isSceneRunning("dogotrigger.level_history/provider-popup")) {
				levelDesc = "(No description available. You're probably viewing this level from a level history mod; there's not much more you can do from here.)";
			} else if (m_fields->manager->isInSavedLevels || Utils::isSceneRunning("LevelListLayer")) {
				levelDesc = "(No description visible. Try downloading the level, then exit and re-enter this menu to view this level's description again.)";
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
			const auto scene = CCScene::create();
			scene->addChild(EditLevelLayer::create(m_level));
			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
		} else { LevelCell::onClick(sender); }
	}
	void loadLocalLevelCell() {
		LevelCell::loadLocalLevelCell();
		if (!(Utils::modEnabled() && Utils::get("compactEditorLevels"))) { return; }
		if (const auto localLevelname = typeinfo_cast<CCLabelBMFont*>(getChildByIDRecursive("level-name"))) { localLevelname->limitLabelWidth(200.f, .6f, .01f); }
		if (const auto mainLayer = typeinfo_cast<CCLayer*>(getChildByIDRecursive("main-layer"))) { mainLayer->setPositionY(-3.5f); }
	}
	void loadCustomLevelCell() {
		LevelCell::loadCustomLevelCell();
		if (!(Utils::modEnabled() && Utils::get("levelDescFromList"))) { return; }
		if (const auto viewButton = getChildByIDRecursive("view-button")) {
			const auto infoButton = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
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
				if (const auto mainLayer = getChildByID("main-layer")) {
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