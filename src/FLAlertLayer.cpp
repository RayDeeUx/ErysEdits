#include <Geode/modify/FLAlertLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyFLAlertLayer, FLAlertLayer) {
	bool init(FLAlertLayerProtocol* delegate, char const* title, gd::string desc, char const* btn1, char const* btn2, float width, bool scroll, float height, float textScale) {
		if (Utils::modEnabled()) {
			// apparently i can't use nullptr delegate here
			std::string titleString = title;
			if (titleString.find("T&^JKIU*HBJUDRFGCHU&^TRDFCGVBJHU*^%RDF") != std::string::npos) {
				auto manager = Manager::getSharedInstance();
				return FLAlertLayer::init(
					delegate,
					fmt::format(
						"{} mods, {} disabled, {} problems",
						manager->installedMods,
						manager->disabledMods,
						manager->problems
					).c_str(),
					desc,
					btn1,
					btn2,
					420.f,
					true,
					height,
					1.f
				);
			} else {
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
			}
		} else {
			return FLAlertLayer::init(delegate, title, desc, btn1, btn2, width, scroll, height, textScale);
		}
	}
};
