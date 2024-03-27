#include <Geode/modify/SetIDPopup.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MySetIDPopup, SetIDPopup) {
	bool init(int p0, int p1, int p2, gd::string p3, gd::string p4, bool p5, int p6, float p7, bool p8, bool p9) {
		if (!SetIDPopup::init(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9)) { return false; }
		return true;
	}
};