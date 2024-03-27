#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/ProfilePage.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyProfilePage, ProfilePage) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	bool init(int p0, bool p1) {
		if (!ProfilePage::init(p0, p1)) return false;
		if (getChildByIDRecursive("refresh-button")) {
			this->defineKeybind("refresh-page"_spr, [this]() {
				if (Utils::isProfilePage()) {
					if (Utils::modEnabled() && Utils::get("refreshAnywhere")) {
						ProfilePage::onUpdate(nullptr);
					} else { Utils::refreshKeybindDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("prev-page-button")) {
			this->defineKeybind("previous-page"_spr, [this]() {
				if (Utils::isProfilePage() && getChildByIDRecursive("prev-page-button")->isVisible()) {
					if (Utils::modEnabled() && Utils::get("pageNavAnywhere")) {
						ProfilePage::onPrevPage(nullptr);
					} else { Utils::arrowKeyNavDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("next-page-button")) {
			this->defineKeybind("next-page"_spr, [this]() {
				if (Utils::isProfilePage() && getChildByIDRecursive("next-page-button")->isVisible()) {
					if (Utils::modEnabled() && Utils::get("pageNavAnywhere")) {
						ProfilePage::onNextPage(nullptr);
					} else { Utils::arrowKeyNavDisabled(); }
				}
			});
		}
		this->defineKeybind("comments"_spr, [this]() {
			if (Utils::isProfilePage() && !Utils::isInfoLayerRecursive() && getChildByIDRecursive("comment-history-button")->isVisible()) {
				if (Utils::modEnabled() && Utils::get("viewCommentsAnywhere")) {
					ProfilePage::onCommentHistory(nullptr);
				} else { Utils::viewCommentsDisabled(); }
			}
		});
		return true;
	}
};
#endif