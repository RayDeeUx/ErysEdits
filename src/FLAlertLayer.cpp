#include <Geode/modify/FLAlertLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyFLAlertLayer, FLAlertLayer) {
	bool init(FLAlertLayerProtocol* delegate, char const* title, gd::string desc, char const* btn1, char const* btn2, float width, bool scroll, float height, float textScale) {
		std::string titleString = title;
		std::string descString = desc;
		bool shouldBeScrollable = (titleString == "Always Active LDM (READ!)" || titleString.find("Show/Copy Mods List") != std::string::npos);
		if (!Utils::modEnabled()) {
			if (shouldBeScrollable) {
				descString = "<cy>(Please enable the softtoggle for the ErysEdits mod; your screen won't fit this setting's description.)</c>";
			}
			return FLAlertLayer::init(delegate, titleString.c_str(), descString.c_str(), btn1, btn2, width, scroll, height, textScale);
		}
		/*
		log::info("title: {}", title);
		log::info("desc: {}", desc);
		if (btn1) log::info("btn1: {}", btn1);
		if (btn2) log::info("btn2: {}", btn2);
		log::info("width: {}", width);
		log::info("scroll: {}", scroll);
		log::info("height: {}", height);
		log::info("textScale: {}", textScale);
		*/
		// apparently i can't use nullptr delegate here, so have a hacky workaround
		bool isFromLevelEndModsList = titleString.find("BRYCETANKTHRUSTBRYCETANKTHRUSTBRYCETANKTHRUST") != std::string::npos;
		bool desiredScroll = scroll;
		float desiredScale = textScale;
		float desiredWidth = width;
		float desiredHeight = height;
		if (isFromLevelEndModsList || shouldBeScrollable) {
			if (isFromLevelEndModsList) {
				auto manager = Manager::getSharedInstance();
				titleString = fmt::format(
					"{} mods, {} disabled, {} problems",
					manager->installedMods,
					manager->disabledMods,
					manager->problems
				);
			}
			desiredScroll = true;
			desiredScale = 1.f;
			desiredWidth = 420.f;
			desiredHeight = 300.f;
		} else {
			if (Utils::getInt("textScroll") < 1) {
				if (!desiredScroll) {
					desiredScale = static_cast<float>(Utils::getDouble("textScale"));
				} else {
					desiredHeight = 300.f;
				}
				if (width <= 420.f) {
					desiredWidth = static_cast<float>(width * Utils::getDouble("flAlertWidthMultiplier"));
					if (desiredWidth >= 420.f) { desiredWidth = 420.f; }
				}
			} else {
				desiredWidth = 420.f;
				desiredScroll = (Utils::getInt("textScroll") != -1);
			}
		}
		/*
		log::info("titleString: {}", titleString);
		log::info("descString: {}", descString);
		if (btn1) log::info("btn1: {}", btn1);
		if (btn2) log::info("btn2: {}", btn2);
		log::info("desiredWidth: {}", desiredWidth);
		log::info("desiredScroll: {}", desiredScroll);
		log::info("desiredHeight: {}", desiredHeight);
		log::info("desiredScale: {}", desiredScale);
		*/
		return FLAlertLayer::init(delegate, titleString.c_str(), descString.c_str(), btn1, btn2, desiredWidth, desiredScroll, desiredHeight, desiredScale);
	}
};