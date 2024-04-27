#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/InfoLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyInfoLayer, InfoLayer) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	bool init(GJGameLevel* p0, GJUserScore* p1, GJLevelList* p2) {
		if (!InfoLayer::init(p0, p1, p2)) { return false; }
		if (getChildByIDRecursive("refresh-button")) {
			this->defineKeybind("refresh-page"_spr, [this]() {
				if (Utils::isInfoLayer() || Utils::isInfoLayerRecursive()) { // infoLayerRecursive because sometimes it's a child of profilePage
					if (Utils::modEnabled() && Utils::get("refreshAnywhere")) {
						InfoLayer::onRefreshComments(nullptr);
					} else { Utils::refreshKeybindDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("prev-page-button")) {
			this->defineKeybind("previous-page"_spr, [this]() {
				if ((Utils::isInfoLayer() || Utils::isInfoLayerRecursive()) && getChildByIDRecursive("prev-page-button")->isVisible()) {
					if (Utils::modEnabled() && Utils::get("pageNavAnywhere")) {
						InfoLayer::onPrevPage(nullptr);
					} else { Utils::arrowKeyNavDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("next-page-button")) {
			this->defineKeybind("next-page"_spr, [this]() {
				if ((Utils::isInfoLayer() || Utils::isInfoLayerRecursive()) && getChildByIDRecursive("next-page-button")->isVisible()) {
					if (Utils::modEnabled() && Utils::get("pageNavAnywhere")) {
						InfoLayer::onNextPage(nullptr);
					} else { Utils::arrowKeyNavDisabled(); }
				}
			});
		}
		if (auto leftSideMenu = getChildByIDRecursive("left-side-menu")) {
			if (leftSideMenu->getChildByIDRecursive("sort-likes-button")) {
				this->defineKeybind("infolayer-sort-likes"_spr, [this]() {
					if ((Utils::isInfoLayer() || Utils::isInfoLayerRecursive())) {
						if (Utils::modEnabled() && Utils::get("infoLayerNavigation")) {
							InfoLayer::toggleCommentMode(
								getChildByIDRecursive("left-side-menu")->getChildByIDRecursive("sort-likes-button")
							);
						} else { Utils::arrowKeyNavDisabled(); }
					}
				});
			}
			if (leftSideMenu->getChildByIDRecursive("sort-recent-button")) {
				this->defineKeybind("infolayer-sort-recent"_spr, [this]() {
					if ((Utils::isInfoLayer() || Utils::isInfoLayerRecursive())) {
						if (Utils::modEnabled() && Utils::get("infoLayerNavigation")) {
							InfoLayer::toggleCommentMode(
								getChildByIDRecursive("left-side-menu")->getChildByIDRecursive("sort-recent-button")
							);
						} else { Utils::arrowKeyNavDisabled(); }
					}
				});
			}
			if (leftSideMenu->getChildByIDRecursive("extend-button")) {
				this->defineKeybind("infolayer-extend"_spr, [this]() {
					if ((Utils::isInfoLayer() || Utils::isInfoLayerRecursive())) {
						if (Utils::modEnabled() && Utils::get("infoLayerNavigation")) {
							InfoLayer::toggleExtendedMode(nullptr);
						} else { Utils::arrowKeyNavDisabled(); }
					}
				});
			}
			if (leftSideMenu->getChildByIDRecursive("small-mode-button")) {
				this->defineKeybind("infolayer-small-mode"_spr, [this]() {
					if ((Utils::isInfoLayer() || Utils::isInfoLayerRecursive())) {
						if (Utils::modEnabled() && Utils::get("infoLayerNavigation")) {
							InfoLayer::toggleSmallCommentMode(nullptr);
						} else { Utils::arrowKeyNavDisabled(); }
					}
				});
			}
		}
		return true;
	}
};
#endif