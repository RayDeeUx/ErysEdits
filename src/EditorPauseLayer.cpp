#include <Geode/modify/EditorPauseLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

// apply the appropriate values to the gamevars for local levels (from "save and play" in level editor)
class $modify(MyEditorPauseLayer, EditorPauseLayer) {
	#ifndef GEODE_IS_MACOS
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	bool init(LevelEditorLayer* p0) {
		if (!EditorPauseLayer::init(p0)) { return false; }
		if (getChildByIDRecursive("resume-button")) {
			this->defineKeybind("resume-editor"_spr, [this]() {
				if (Utils::modEnabled() && Utils::getBool("resumeShortcut")) {
					EditorPauseLayer::onResume(nullptr);
				} else { Utils::keybindDisabledGeneric("Resume Editor", "resume editing a level"); }
			});
		}
		return true;
	}
	#endif
	void onSaveAndPlay(CCObject* sender) {
		Utils::applyGMGVs(m_editorLayer->m_level->m_isVerifiedRaw);
		EditorPauseLayer::onSaveAndPlay(sender);
	}
};