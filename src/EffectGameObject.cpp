#ifndef GEODE_IS_MACOS
#include <Geode/modify/EffectGameObject.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyEffectGameObject, EffectGameObject) {
	bool init(char const* p0) {
		if (!EffectGameObject::init(p0)) { return false; }
		if (GameManager::sharedState()->getPlayLayer() == nullptr) { return true; }
		if (!Utils::modEnabled()) { return true; }
		auto mTS = Manager::getSharedInstance()->miscToSetting;
		if (mTS.find(p0) != mTS.end() && Utils::get(mTS.find(p0)->second)) { return false; }
		return true;
	}
};
#endif