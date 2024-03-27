#include <Geode/modify/CustomListView.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

// original code by cvolton, re-used for "my levels" list
// and now reused for profile comments yayy
// proof of consent of code reuse: https://discord.com/channels/911701438269386882/911702535373475870/1220117410988953762

class $modify(MyCustomListView, CustomListView) {
	static CustomListView* create(cocos2d::CCArray* a, TableViewCellDelegate* b, float c, float d, int e, BoomListType f, float g) {
		if (Utils::modEnabled()) {
			if (f == BoomListType::Level2 && Utils::get("compactEditorLevels")) { f = BoomListType::Level4; }
			if (f == BoomListType::Comment4 && Utils::get("compactProfileComments")) { f = BoomListType::Comment2; }
		}
		return CustomListView::create(a, b, c, d, e, f, g);
	}
};