#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/DemonFilterSelectLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyDemonFilterSelectLayer, DemonFilterSelectLayer) {
	static void onModify(auto& self) {
		self.setHookPriority("DemonFilterSelectLayer::init", INT64_MIN + 1);
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
		if (!DemonFilterSelectLayer::init()) { return false; }
		this->setID("DemonFilterSelectLayer");
		if (auto ccLayer = getChildOfType<CCLayer>(this, 0)) {
			ccLayer->setID("main-menu");
			auto ccLayerChildren = ccLayer->getChildren();
			for (int i = ccLayer->getChildrenCount(); i-- > 0; ) {
				if (auto ccMenu = typeinfo_cast<CCMenu*>(ccLayerChildren->objectAtIndex(i))) {
					ccMenu->setID("demon-filters");
				}
			}
		} else {
			return true;
		}
		if (auto demonFilters = getChildByIDRecursive("demon-filters")) {
			auto demonFiltersChildren = demonFilters->getChildren();
			if (auto child = demonFiltersChildren->objectAtIndex(0)) {
				if (child->getTag() == 0) typeinfo_cast<CCMenuItemSpriteExtra*>(child)->setID("all-demon-filter-button");
			}
			if (auto child = demonFiltersChildren->objectAtIndex(1)) {
				if (child->getTag() == 7) typeinfo_cast<CCMenuItemSpriteExtra*>(child)->setID("easy-demon-filter-button");
			}
			if (auto child = demonFiltersChildren->objectAtIndex(2)) {
				if (child->getTag() == 8) typeinfo_cast<CCMenuItemSpriteExtra*>(child)->setID("medium-demon-filter-button");
			}
			if (auto child = demonFiltersChildren->objectAtIndex(3)) {
				if (child->getTag() == 6) typeinfo_cast<CCMenuItemSpriteExtra*>(child)->setID("hard-demon-filter-button");
			}
			if (auto child = demonFiltersChildren->objectAtIndex(4)) {
				if (child->getTag() == 9) typeinfo_cast<CCMenuItemSpriteExtra*>(child)->setID("insane-demon-filter-button");
			}
			if (auto child = demonFiltersChildren->objectAtIndex(5)) {
				if (child->getTag() == 10) typeinfo_cast<CCMenuItemSpriteExtra*>(child)->setID("extreme-demon-filter-button");
			}
			if (auto child = demonFiltersChildren->objectAtIndex(6)) {
				typeinfo_cast<CCMenuItemSpriteExtra*>(child)->setID("close-button");
			}
		} else {
			return true;
		}
		this->defineKeybind("level-search-all-demons"_spr, [this]() {
			if (Utils::modEnabled() && Utils::get("demonFilter")) {
				DemonFilterSelectLayer::selectRating(getChildByIDRecursive("all-demon-filter-button"));
			} else { Utils::demonFilterDisabled(); }
		});
		this->defineKeybind("level-search-easy-demon"_spr, [this]() {
			if (Utils::modEnabled() && Utils::get("demonFilter")) {
				DemonFilterSelectLayer::selectRating(getChildByIDRecursive("easy-demon-filter-button"));
			} else { Utils::demonFilterDisabled(); }
		});
		this->defineKeybind("level-search-medium-demon"_spr, [this]() {
			if (Utils::modEnabled() && Utils::get("demonFilter")) {
				DemonFilterSelectLayer::selectRating(getChildByIDRecursive("medium-demon-filter-button"));
			} else { Utils::demonFilterDisabled(); }
		});
		this->defineKeybind("level-search-hard-demon"_spr, [this]() {
			if (Utils::modEnabled() && Utils::get("demonFilter")) {
				DemonFilterSelectLayer::selectRating(getChildByIDRecursive("hard-demon-filter-button"));
			} else { Utils::demonFilterDisabled(); }
		});
		this->defineKeybind("level-search-insane-demon"_spr, [this]() {
			if (Utils::modEnabled() && Utils::get("demonFilter")) {
				DemonFilterSelectLayer::selectRating(getChildByIDRecursive("insane-demon-filter-button"));
			} else { Utils::demonFilterDisabled(); }
		});
		this->defineKeybind("level-search-extreme-demon"_spr, [this]() {
			if (Utils::modEnabled() && Utils::get("demonFilter")) {
				DemonFilterSelectLayer::selectRating(getChildByIDRecursive("extreme-demon-filter-button"));
			} else { Utils::demonFilterDisabled(); }
		});
		return true;
	}
};
#endif