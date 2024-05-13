#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/GauntletSelectLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyGauntletSelectLayer, GauntletSelectLayer) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	void findCurrentGauntletPageUsing(CCNode* pageButtons) {
		for (int i = 0; i < pageButtons->getChildrenCount(); i++) {
			if (auto ccSprite = typeinfo_cast<CCSprite*>(pageButtons->getChildren()->objectAtIndex(i))) {
				if (ccSprite->getDisplayedColor() == ccColor3B({255, 255, 255})) {
					m_fields->manager->currentGauntletPage = (i + 1);
				}
			}
		}
	}
	void setupGauntlets() {
		GauntletSelectLayer::setupGauntlets();
		if (auto pageButtons = getChildByIDRecursive("page-buttons")) {
			MyGauntletSelectLayer::findCurrentGauntletPageUsing(pageButtons);
		}
		this->defineKeybind("next-gauntlet"_spr, [this]() {
			if (Utils::modEnabled() && Utils::get("navigateGauntlets") && Utils::nothingElse()) {
				GauntletSelectLayer::onNext(nullptr);
			} else { Utils::navigateGauntletsDisabled(); }
		});
		this->defineKeybind("previous-gauntlet"_spr, [this]() {
			if (Utils::modEnabled() && Utils::get("navigateGauntlets") && Utils::nothingElse()) {
				GauntletSelectLayer::onPrev(nullptr);
			} else { Utils::navigateGauntletsDisabled(); }
		});
		this->defineKeybind("first-visible-gauntlet"_spr, [this]() {
			if (Utils::modEnabled() && Utils::get("navigateGauntlets") && Utils::nothingElse()) {
				std::string nodeID = fmt::format("gauntlet-page-{}", m_fields->manager->currentGauntletPage);
				if (auto theGauntlet = getChildByIDRecursive(nodeID)->getChildByIDRecursive("gauntlet-button-1")) {
					GauntletSelectLayer::onPlay(theGauntlet);
				}
			} else { Utils::navigateGauntletsDisabled(); }
		});
		this->defineKeybind("second-visible-gauntlet"_spr, [this]() {
			if (Utils::modEnabled() && Utils::get("navigateGauntlets") && Utils::nothingElse()) {
				std::string nodeID = fmt::format("gauntlet-page-{}", m_fields->manager->currentGauntletPage);
				if (auto theGauntlet = getChildByIDRecursive(nodeID)->getChildByIDRecursive("gauntlet-button-2")) {
					GauntletSelectLayer::onPlay(theGauntlet);
				}
			} else { Utils::navigateGauntletsDisabled(); }
		});
		this->defineKeybind("third-visible-gauntlet"_spr, [this]() {
			if (Utils::modEnabled() && Utils::get("navigateGauntlets") && Utils::nothingElse()) {
				std::string nodeID = fmt::format("gauntlet-page-{}", m_fields->manager->currentGauntletPage);
				if (auto theGauntlet = getChildByIDRecursive(nodeID)->getChildByIDRecursive("gauntlet-button-3")) {
					GauntletSelectLayer::onPlay(theGauntlet);
				}
			} else { Utils::navigateGauntletsDisabled(); }
		});
	}
	void scrollLayerWillScrollToPage(BoomScrollLayer* p0, int p1) {
		GauntletSelectLayer::scrollLayerWillScrollToPage(p0, p1);
		if (auto pageButtons = getChildByIDRecursive("page-buttons")) {
			MyGauntletSelectLayer::findCurrentGauntletPageUsing(pageButtons);
		}
	}
	void onBack(cocos2d::CCObject* sender){
		m_fields->manager->currentGauntletPage = 0;
		GauntletSelectLayer::onBack(sender);
	}
};
#endif