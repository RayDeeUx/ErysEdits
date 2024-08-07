#include <Geode/modify/GJGarageLayer.hpp>
#ifndef GEODE_IS_MACOS
#include <geode.custom-keybinds/include/Keybinds.hpp>
#endif
#include "Utils.hpp"

using namespace geode::prelude;
#ifndef GEODE_IS_MACOS
using namespace keybinds;
#endif

class $modify(MyGJGarageLayer, GJGarageLayer) {
	#ifndef GEODE_IS_MACOS
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	void onShop(cocos2d::CCObject* sender) {
		if (Utils::shiftDown()) { GJGarageLayer::onShop(sender); }
	}
	#endif
	bool init() {
		if (!GJGarageLayer::init()) { return false; }
		if (Utils::modEnabled()) {
			if (const auto floorLine = getChildByIDRecursive("floor-line")) { floorLine->setVisible(!Utils::getBool("slightlyCleanerGarage")); }
			if (const auto usernameLock = getChildByIDRecursive("username-lock")) { usernameLock->setVisible(!Utils::getBool("slightlyCleanerGarage")); }
		}
		#ifndef GEODE_IS_MACOS
		if (getChildByIDRecursive("category-menu")) {
			if (getChildByIDRecursive("cube-button")) {
				this->defineKeybind("garage-cube"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onSelectTab(
								getChildByIDRecursive("category-menu")->getChildByIDRecursive("cube-button")
							);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
			if (getChildByIDRecursive("ship-button")) {
				this->defineKeybind("garage-ship"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onSelectTab(
								getChildByIDRecursive("category-menu")->getChildByIDRecursive("ship-button")
							);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
			if (getChildByIDRecursive("jetpack-button")) {
				this->defineKeybind("garage-jetpack"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onSelectTab(
								getChildByIDRecursive("category-menu")->getChildByIDRecursive("jetpack-button")
							);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
			if (getChildByIDRecursive("ball-button")) {
				this->defineKeybind("garage-ball"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onSelectTab(
								getChildByIDRecursive("category-menu")->getChildByIDRecursive("ball-button")
							);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
			if (getChildByIDRecursive("ufo-button")) {
				this->defineKeybind("garage-ufo"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onSelectTab(
								getChildByIDRecursive("category-menu")->getChildByIDRecursive("ufo-button")
							);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
			if (getChildByIDRecursive("wave-button")) {
				this->defineKeybind("garage-wave"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onSelectTab(
								getChildByIDRecursive("category-menu")->getChildByIDRecursive("wave-button")
							);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
			if (getChildByIDRecursive("robot-button")) {
				this->defineKeybind("garage-robot"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onSelectTab(
								getChildByIDRecursive("category-menu")->getChildByIDRecursive("robot-button")
							);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
			if (getChildByIDRecursive("spider-button")) {
				this->defineKeybind("garage-spider"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onSelectTab(
								getChildByIDRecursive("category-menu")->getChildByIDRecursive("spider-button")
							);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
			if (getChildByIDRecursive("swing-button")) {
				this->defineKeybind("garage-swing"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onSelectTab(
								getChildByIDRecursive("category-menu")->getChildByIDRecursive("swing-button")
							);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
			if (getChildByIDRecursive("trail-button")) {
				this->defineKeybind("garage-trail"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onSelectTab(
								getChildByIDRecursive("category-menu")->getChildByIDRecursive("trail-button")
							);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
			if (getChildByIDRecursive("death-effect-button")) {
				this->defineKeybind("garage-death-effect"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onSelectTab(
								getChildByIDRecursive("category-menu")->getChildByIDRecursive("death-effect-button")
							);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
		}
		if (const auto prevPageMenu = getChildByIDRecursive("prev-page-menu")) {
			if (prevPageMenu->getChildByIDRecursive("prev-button")) {
				this->defineKeybind("garage-previous-page"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse() && getChildByIDRecursive("prev-page-menu")->getChildByIDRecursive("prev-button")->isVisible()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onArrow(
								getChildByIDRecursive("prev-page-menu")->getChildByIDRecursive("prev-button")
							);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
		}
		if (const auto nextPageMenu = getChildByIDRecursive("next-page-menu")) {
			if (nextPageMenu->getChildByIDRecursive("next-button")) {
				this->defineKeybind("garage-next-page"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse() && getChildByIDRecursive("next-page-menu")->getChildByIDRecursive("next-button")->isVisible()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onArrow(
								getChildByIDRecursive("next-page-menu")->getChildByIDRecursive("next-button")
							);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
		}
		#endif
		if (const auto shardsMenu = getChildByIDRecursive("shards-menu")) {
			if (Utils::getDouble("garageShardsMenu") != 1.f) {
				shardsMenu->setScale(Utils::getDouble("garageShardsMenu"));
				shardsMenu->setAnchorPoint({0.5f, static_cast<float>(Utils::getDouble("garageShardsMenu") - .45f)});
			}
			#ifndef GEODE_IS_MACOS
			if (shardsMenu->getChildByIDRecursive("shards-button")) {
				this->defineKeybind("garage-shards-page"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onShards(nullptr);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
			if (shardsMenu->getChildByIDRecursive("color-button")) {
				this->defineKeybind("garage-colors-page"_spr, [this]() {
					if (Utils::isSceneRunning("GJGarageLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::getBool("garageNavigation")) {
							GJGarageLayer::onPaint(nullptr);
						} else { Utils::garageNavigationDisabled(); }
					}
				});
			}
			#endif
		}
		return true;
	}
};