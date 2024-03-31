#include <Geode/modify/LevelBrowserLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyLevelBrowserLayer, LevelBrowserLayer) {
	#ifdef GEODE_IS_WINDOWS
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	#endif
	bool init(GJSearchObject* searchObject) {
		if (!LevelBrowserLayer::init(searchObject)) { return false; }
		if (getChildByIDRecursive("saved-menu")) {
			Manager::getSharedInstance()->isInSavedLevels = true;
		} else {
			Manager::getSharedInstance()->isInSavedLevels = false;
		}
		if (searchObject->m_searchType == SearchType::MyLevels && Utils::modEnabled() && Utils::get("compactEditorLevels")) {
			if (auto deleteMenu = getChildByIDRecursive("delete-menu")) {
				// hide the deletion checkboxes because every level in the list has been cast to BoomListType::Level4
				deleteMenu->setVisible(false);
				getChildByIDRecursive("select-all-text")->setVisible(false);
			}
		}
		#ifdef GEODE_IS_WINDOWS
		else if (getChildByIDRecursive("refresh-button")) {
			this->defineKeybind("refresh-page"_spr, [this]() {
				if (Utils::isSceneRunning("LevelBrowserLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("refreshAnywhere")) {
						LevelBrowserLayer::onRefresh(nullptr);
					} else { Utils::refreshKeybindDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("prev-page-button")) {
			this->defineKeybind("first-page"_spr, [this]() {
				if (Utils::isSceneRunning("LevelBrowserLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("pageNavAnywhere")) {
						LevelBrowserLayer::setIDPopupClosed(
							SetIDPopup::create(
								1,
								1, 999999, "Go to Page", "Go", true, 1, 60, false, false
							),
							1
						);
					} else { Utils::arrowKeyNavDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("next-page-button")) {
			this->defineKeybind("last-page"_spr, [this]() {
				if (Utils::isSceneRunning("LevelBrowserLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("pageNavAnywhere")) {
					float lastPage = ceil(m_itemCount / (float) m_pageEndIdx);
						LevelBrowserLayer::setIDPopupClosed(
							SetIDPopup::create(
								lastPage,
								1, 999999, "Go to Page", "Go", true, 1, 60, false, false
							),
							lastPage
						);
					} else { Utils::arrowKeyNavDisabled(); }
				}
			});
		}
		#endif
		return true;
	}
};