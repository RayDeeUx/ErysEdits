#include <Geode/modify/CommentCell.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyCommentCell, CommentCell) {
	void draw() {
		CommentCell::draw();
		if (Utils::modEnabled() && Utils::get("fixBITranslateOverlap") && getChildByIDRecursive("delete-button") && getChildByIDRecursive("tastyforreal.google-translate/translate-button") && m_listType == BoomListType::Comment2) {
			if (auto biComment = getChildByIDRecursive("cvolton.betterinfo/comments-button")) {
				if (biComment->getPositionX() == -78.5f) biComment->setPositionX(-78.5 - 20); // hooking init and loadFromComment doesn't work, and draw() runs on every frame. hardcoding the position is the only way to go.
			}
		}
	}
};