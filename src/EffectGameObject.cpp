#ifndef __APPLE__
#include <Geode/modify/EffectGameObject.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyEffectGameObject, EffectGameObject) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	bool init(char const* p0) {
		if (!EffectGameObject::init(p0)) { return false; }
		if (GameManager::sharedState()->getPlayLayer() == nullptr) { return true; }
		if (!Utils::modEnabled()) { return true; }
		const auto mTS = m_fields->manager->miscToSetting;
		if (mTS.find(p0) != mTS.end() && Utils::get(mTS.find(p0)->second)) { return false; }
		return true;
	}
};
#endif