#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/LikeItemLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyLikeItemLayer, LikeItemLayer) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	bool init(LikeItemType p0, int p1, int p2) {
		if (!LikeItemLayer::init(p0, p1, p2)) { return false; }
		this->defineKeybind("like"_spr, [this]() {
			if (Utils::modEnabled() && Utils::getBool("likeDislikeShortcut")) {
				LikeItemLayer::onLike(nullptr);
			} else {
				Utils::likeDislikeShortcutDisabled();
			}
		});
		this->defineKeybind("dislike"_spr, [this]() {
			if (Utils::modEnabled() && Utils::getBool("likeDislikeShortcut")) {
				LikeItemLayer::onDislike(nullptr);
			} else {
				Utils::likeDislikeShortcutDisabled();
			}
		});
		return true;
	}
};
#endif