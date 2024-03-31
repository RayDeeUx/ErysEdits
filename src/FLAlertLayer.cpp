#include <Geode/modify/FLAlertLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyFLAlertLayer, FLAlertLayer) {
	bool init(FLAlertLayerProtocol* delegate, char const* title, gd::string desc, char const* btn1, char const* btn2, float width, bool scroll, float height, float textScale) {
        // if (!FLAlertLayer::init(delegate, title, desc, btn1, btn2, width, scroll, height, textScale)) return false;
        if (Utils::modEnabled()) {
            float desiredWidth = width * Mod::get()->getSettingValue<double>("flAlertWidthMultiplier");
            if (desiredWidth >= 420.f) desiredWidth = 420.f;
            return FLAlertLayer::init(delegate, title, desc, btn1, btn2, desiredWidth, scroll, height, textScale);
        } else {
            return FLAlertLayer::init(delegate, title, desc, btn1, btn2, width, scroll, height, textScale);
        }
	}
};