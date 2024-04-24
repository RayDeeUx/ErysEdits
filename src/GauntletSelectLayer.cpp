#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/GauntletSelectLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyGauntletSelectLayer, GauntletSelectLayer) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	bool init(int p0) {
		if (!GauntletSelectLayer::init(p0)) { return false; }
		this->defineKeybind("next-gauntlet"_spr, [this]() {
			if (Utils::modEnabled()) { //  && Utils::get("refreshAnywhere")
				GauntletSelectLayer::onNext(nullptr);
			} else { Utils::refreshKeybindDisabled(); }
		});
		this->defineKeybind("previous-gauntlet"_spr, [this]() {
			if (Utils::modEnabled()) { //  && Utils::get("refreshAnywhere")
				GauntletSelectLayer::onPrev(nullptr);
			} else { Utils::refreshKeybindDisabled(); }
		});
		return true;
	}
};
#endif