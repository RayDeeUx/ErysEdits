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
				Utils::keybindDisabledGeneric("Editor Level Save", "save an editor level");
			}
		});
		/*
			this->defineKeybind("save-and-play-editor"_spr, [this]() {
				if (Utils::modEnabled() && Utils::get("saveAndPlay")) {
					auto editorPauseLayer = EditorPauseLayer::create(this->m_editorLayer);
					if (editorPauseLayer) {
						editorPauseLayer->onSaveAndPlay(nullptr);
					} else {
						FLAlertLayer::create(
							"Editor Save and Play Failed!",
							"Your <cj>level</c> <cr>could not</c> be saved and playtested. Please try again.",
							"OK"
						)->show();
					}
				} else {
					Utils::keybindDisabledGeneric("Editor Save and Play", "save and play an editor level");
				}
			});
		*/
		this->defineKeybind("save-and-exit-editor"_spr, [this]() {
			if (Utils::modEnabled() && Utils::get("saveAndExit")) {
				auto editorPauseLayer = EditorPauseLayer::create(this->m_editorLayer);
				if (editorPauseLayer) {
					editorPauseLayer->onSaveAndExit(nullptr);
				} else {
					FLAlertLayer::create(
						"Editor Save and Exit Failed!",
						"Your <cj>level</c> <cr>could not</c> be saved and exited from. Please try again.",
						"OK"
					)->show();
				}
			} else {
				Utils::keybindDisabledGeneric("Editor Save and Exit", "save and exit from an editor level");
			}
		});
		return true;
	}
};
#endif