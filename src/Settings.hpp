// this entire file was yoinked from coopeeo's hide+ mod with full consent
// with applicable revision in comments that involve first person pronouns
// proof of consent: https://discord.com/channels/911701438269386882/911702535373475870/1222262244528754819
#pragma once

#include <Geode/loader/SettingNode.hpp>

using namespace geode::prelude;

class SectionSettingValue;

class SectionSettingValue : public SettingValue {
protected:
	std::string m_placeholder;
public:
	// lines 5, 8, 11, and 12 are copied from GDUtils by coopeeo
	SectionSettingValue(std::string const& key, std::string const& modID, std::string const& placeholder)
	  : SettingValue(key, modID), m_placeholder(placeholder) {}
	bool load(matjson::Value const& json) override {return true;}
	bool save(matjson::Value& json) const override {return true;}
	SettingNode* createNode(float width) override;
};

class SectionSettingNode : public SettingNode {
protected:
	bool init(SectionSettingValue* value, float width) {
		if (!SettingNode::init(value))
			return false;
		this->setContentSize({ width, 40.f });
		// line 19 is the ONLY line coopeeo copied from GDUtils (Thanks Jouca and Firee)
		std::string name = Mod::get()->getSettingDefinition(value->getKey())->get<CustomSetting>()->json->get<std::string>("name");

		auto theMenu = CCMenu::create();
		auto theLabel = CCLabelBMFont::create(name.c_str(),"bigFont.fnt");

		// copied a bit from viper
		theLabel->setScale(.75);
		theLabel->setPositionX(0);
		theMenu->addChild(theLabel);
		theMenu->setPosition(width / 2, 18.f);
		
		this->addChild(theMenu);



		return true;
	}

public:
	void commit() override {
		this->dispatchCommitted();
	}
	bool hasUncommittedChanges() override {
		return false;
	}
	bool hasNonDefaultValue() override {
		return true;
	}
	void resetToDefault() override {}

	static SectionSettingNode* create(SectionSettingValue* value, float width) {
		auto ret = new SectionSettingNode();
		if (ret && ret->init(value, width)) {
			ret->autorelease();
			return ret;
		}
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
};