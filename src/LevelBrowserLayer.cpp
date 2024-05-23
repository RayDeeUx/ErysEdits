#include <Geode/modify/LevelBrowserLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyLevelBrowserLayer, LevelBrowserLayer) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
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
			m_fields->manager->isInSavedLevels = true;
		} else {
			m_fields->manager->isInSavedLevels = false;
		}
		if (searchObject->m_searchType == SearchType::MyLevels && Utils::modEnabled() && Utils::getBool("compactEditorLevels")) {
			if (const auto deleteMenu = getChildByIDRecursive("delete-menu")) {
				// hide the deletion checkboxes because every level in the list has been cast to BoomListType::Level4
				deleteMenu->setVisible(false);
				getChildByIDRecursive("select-all-text")->setVisible(false);
			}
		}
		#ifdef GEODE_IS_WINDOWS
		else if (getChildByIDRecursive("refresh-button")) {
			this->defineKeybind("refresh-page"_spr, [this]() {
				if (Utils::isSceneRunning("LevelBrowserLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::getBool("refreshAnywhere")) {
						LevelBrowserLayer::onRefresh(nullptr);
					} else { Utils::refreshKeybindDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("prev-page-button")) {
			this->defineKeybind("first-page"_spr, [this]() {
				if (Utils::isSceneRunning("LevelBrowserLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::getBool("pageNavAnywhere")) {
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
					if (Utils::modEnabled() && Utils::getBool("pageNavAnywhere")) {
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
		if (getChildByIDRecursive("new-level-menu")) {
			this->defineKeybind("new-editor-level"_spr, [this]() {
				if (Utils::isSceneRunning("LevelBrowserLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::getBool("newEditorLevel")) {
						LevelBrowserLayer::onNew(nullptr);
					} else { Utils::keybindDisabledGeneric("Create New Level/List", "create a new level/list"); }
				}
			});
			this->defineKeybind("toggle-level-lists"_spr, [this]() {
				if (Utils::isSceneRunning("LevelBrowserLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::getBool("toggleLevelLists")) {
						LevelBrowserLayer::onLocalMode(nullptr);
					} else { Utils::keybindDisabledGeneric("Toggle Levels/Lists Mode", "toggle between viewing local editor levels and local level lists"); }
				}
			});
		}
		if (getChildByIDRecursive("my-levels-button")) {
			this->defineKeybind("view-uploaded"_spr, [this]() {
				if (Utils::isSceneRunning("LevelBrowserLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::getBool("viewUploaded")) {
						LevelBrowserLayer::onMyOnlineLevels(nullptr);
					} else { Utils::keybindDisabledGeneric("View Uploaded Levels/Lists", "view uploaded levels/level lists"); }
				}
			});
		}
		#endif
		return true;
	}
};