#include <Geode/modify/FLAlertLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyFLAlertLayer, FLAlertLayer) {
	bool init(FLAlertLayerProtocol* delegate, char const* title, gd::string desc, char const* btn1, char const* btn2, float width, bool scroll, float height, float textScale) {
		if (Utils::modEnabled()) {
			bool desiredScroll = scroll;
			float desiredScale = textScale;
			float desiredWidth = width;
			if (Utils::getInt("textScroll") < 1) {
				if (!desiredScroll) { desiredScale = Utils::getDouble("textScale"); }
				if (width <= 420.f) {
					desiredWidth = width * Utils::getDouble("flAlertWidthMultiplier");
					if (desiredWidth >= 420.f) { desiredWidth = 420.f; }
				}
			} else {
				desiredWidth = 420.f;
				desiredScroll = (Utils::getInt("textScroll") != -1);
			}
			return FLAlertLayer::init(delegate, title, desc, btn1, btn2, desiredWidth, desiredScroll, height, desiredScale);
		} else {
			return FLAlertLayer::init(delegate, title, desc, btn1, btn2, width, scroll, height, textScale);
		}
	}
};
