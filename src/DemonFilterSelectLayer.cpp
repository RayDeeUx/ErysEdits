#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/DemonFilterSelectLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyDemonFilterSelectLayer, DemonFilterSelectLayer) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	bool init() {
		if (!DemonFilterSelectLayer::init()) { return false; }
		if (getChildByIDRecursive("all-demon-filter-button")) {
			this->defineKeybind("level-search-all-demons"_spr, [this]() {
				if (Utils::modEnabled() && Utils::getBool("demonFilter")) {
					DemonFilterSelectLayer::selectRating(getChildByIDRecursive("all-demon-filter-button"));
				} else { Utils::demonFilterDisabled(); }
			});
		}
		if (getChildByIDRecursive("easy-demon-filter-button")) {
			this->defineKeybind("level-search-easy-demon"_spr, [this]() {
				if (Utils::modEnabled() && Utils::getBool("demonFilter")) {
					DemonFilterSelectLayer::selectRating(getChildByIDRecursive("easy-demon-filter-button"));
				} else { Utils::demonFilterDisabled(); }
			});
		}
		if (getChildByIDRecursive("medium-demon-filter-button")) {
			this->defineKeybind("level-search-medium-demon"_spr, [this]() {
				if (Utils::modEnabled() && Utils::getBool("demonFilter")) {
					DemonFilterSelectLayer::selectRating(getChildByIDRecursive("medium-demon-filter-button"));
				} else { Utils::demonFilterDisabled(); }
			});
		}
		if (getChildByIDRecursive("hard-demon-filter-button")) {
			this->defineKeybind("level-search-hard-demon"_spr, [this]() {
				if (Utils::modEnabled() && Utils::getBool("demonFilter")) {
					DemonFilterSelectLayer::selectRating(getChildByIDRecursive("hard-demon-filter-button"));
				} else { Utils::demonFilterDisabled(); }
			});
		}
		if (getChildByIDRecursive("insane-demon-filter-button")) {
			this->defineKeybind("level-search-insane-demon"_spr, [this]() {
				if (Utils::modEnabled() && Utils::getBool("demonFilter")) {
					DemonFilterSelectLayer::selectRating(getChildByIDRecursive("insane-demon-filter-button"));
				} else { Utils::demonFilterDisabled(); }
			});
		}
		if (getChildByIDRecursive("extreme-demon-filter-button")) {
			this->defineKeybind("level-search-extreme-demon"_spr, [this]() {
				if (Utils::modEnabled() && Utils::getBool("demonFilter")) {
					DemonFilterSelectLayer::selectRating(getChildByIDRecursive("extreme-demon-filter-button"));
				} else { Utils::demonFilterDisabled(); }
			});
		}
		return true;
	}
};
#endif