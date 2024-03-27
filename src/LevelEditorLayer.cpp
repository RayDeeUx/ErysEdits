#include <Geode/modify/LevelEditorLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

// restore the original values of the gamevars found during game launch (entering level editor)
class $modify(MyLevelEditorLayer, LevelEditorLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelEditorLayer::init(p0, p1)) return false;
		Utils::restoreOrigGMGVs(GameManager::get());
		return true;
	}
};