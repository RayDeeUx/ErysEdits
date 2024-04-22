#include <Geode/modify/EditorPauseLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

// apply the appropriate values to the gamevars for local levels (from "save and play" in level editor)
class $modify(MyEditorPauseLayer, EditorPauseLayer) {
	void onSaveAndPlay(CCObject* sender) {
		auto gameManager = GameManager::get();
		Utils::applyGMGVs(m_editorLayer->m_level->m_isVerifiedRaw);
		EditorPauseLayer::onSaveAndPlay(sender);
	}
};