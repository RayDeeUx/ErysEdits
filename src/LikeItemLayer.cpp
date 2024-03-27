#ifndef GEODE_IS_MOBILE
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
			#ifndef GEODE_IS_MACOS
			if (Utils::modEnabled() && Utils::get("likeDislikeShortcut")) {
				LikeItemLayer::onLike(nullptr);
			} else {
				Utils::likeDislikeShortcutDisabled();
			}
			#else
			FLAlertLayer::create(
				"Like/Dislike Shortcut Disabled!",
				"Due to incomplete Geode bindings, navigating profile page comments/posts via keybind is unavailable for macOS at this time.",
				"OK"
			);
			#endif
		});
		this->defineKeybind("dislike"_spr, [this]() {
			#ifndef GEODE_IS_MACOS
			if (Utils::modEnabled() && Utils::get("likeDislikeShortcut")) {
				LikeItemLayer::onDislike(nullptr);
			} else {
				Utils::likeDislikeShortcutDisabled();
			}
			#else
			FLAlertLayer::create(
				"Like/Dislike Shortcut Disabled!",
				"Due to incomplete Geode bindings, navigating profile page comments/posts via keybind is unavailable for macOS at this time.",
				"OK"
			);
			#endif
		});
		return true;
	}
};
#endif