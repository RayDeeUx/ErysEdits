#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/ShardsPage.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyShardsPage, ShardsPage) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("ShardsPage::init", INT32_MIN + 1);
	}
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	bool init() {
		if (!ShardsPage::init()) { return false; }
		if (getChildByIDRecursive("arrow-buttons-menu")->getChildByIDRecursive("prev-button")) {
			this->defineKeybind("garage-previous-page"_spr, [this]() {
				if (Utils::modEnabled() && Utils::get("garageNavigation")) {
					ShardsPage::onSwitchPage(
						getChildByIDRecursive("arrow-buttons-menu")->getChildByIDRecursive("prev-button")
					);
				} else { Utils::garageNavigationDisabled(); }
			});
		}
		if (getChildByIDRecursive("arrow-buttons-menu")->getChildByIDRecursive("next-button")) {
			this->defineKeybind("garage-next-page"_spr, [this]() {
				if (Utils::modEnabled() && Utils::get("garageNavigation")) {
					ShardsPage::onSwitchPage(
						getChildByIDRecursive("arrow-buttons-menu")->getChildByIDRecursive("next-button")
					);
				} else { Utils::garageNavigationDisabled(); }
			});
		}
		return true;
	}
};
#endif