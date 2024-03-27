#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/EditorUI.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyEditorUI, EditorUI) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	bool init(LevelEditorLayer* p0) {
		if (!EditorUI::init(p0)) { return false; }
		this->defineKeybind("save-editor-level"_spr, [this]() {
			if (Utils::modEnabled() && Utils::get("saveEditorLevel")) {
				auto editorPauseLayer = EditorPauseLayer::create(this->m_editorLayer);
				if (editorPauseLayer) {
					editorPauseLayer->saveLevel();

					FLAlertLayer::create(
						"Editor Level Saved",
						"Your <cj>level</c> has been <cg>saved</c>.",
						"OK"
					)->show();
				} else {
					FLAlertLayer::create(
						"Editor Level Save Failed!",
						"Your <cj>level</c> <cr>was not</c> saved. Please try again.",
						"OK"
					)->show();
				}
			} else {
				FLAlertLayer::create(
					"Editor Level Save Disabled!",
					"You have either disabled the softtoggle for the ErysEdits mod, or you have disabled the keybind to save an editor level. Please double-check your mod configs and try again.",
					"OK"
				)->show();
			}
		});
		return true;
	}
};
#endif