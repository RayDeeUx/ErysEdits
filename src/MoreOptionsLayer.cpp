#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/MoreOptionsLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyMoreOptionsLayer, MoreOptionsLayer) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	bool init() {
		if (!MoreOptionsLayer::init()) { return false; }
		this->defineKeybind("next-options-page"_spr, [this]() {
			if (Utils::isSceneRunning("MoreOptionsLayer")) {
				if (Utils::modEnabled() && Utils::get("moreOptions")) {
					MoreOptionsLayer::onNextPage(nullptr);
				} else { Utils::moreOptionsDisabled(); }
			}
		});
		this->defineKeybind("previous-options-page"_spr, [this]() {
			if (Utils::isSceneRunning("MoreOptionsLayer")) {
				if (Utils::modEnabled() && Utils::get("moreOptions")) {
					MoreOptionsLayer::onPrevPage(nullptr);
				} else { Utils::moreOptionsDisabled(); }
			}
		});
		return true;
	}
};
#endif