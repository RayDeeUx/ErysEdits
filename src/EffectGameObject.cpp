#ifndef __APPLE__
#include <Geode/modify/EffectGameObject.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyEffectGameObject, EffectGameObject) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
		const std::map<std::string, std::string> miscToSetting = {
			{ "edit_ePulseBtn_001.png", "disablePulse" },
			{ "edit_eAreaTintBtn_001.png", "disableAreaTint" },
			{ "edit_eShakeBtn_001.png", "disableShake" },
			{ "edit_eSFXBtn_001.png", "disableSFX" },
			{ "edit_eEditSFXBtn_001.png", "disableEditSFX" }
		};
	};
	bool init(char const* p0) {
		if (!EffectGameObject::init(p0)) { return false; }
		if (!PlayLayer::get() || !Utils::modEnabled()) { return true; }
		if (m_fields->miscToSetting.find(p0) != m_fields->miscToSetting.end() && Utils::get(m_fields->miscToSetting.find(p0)->second)) { return false; }
		return true;
	}
};
#endif