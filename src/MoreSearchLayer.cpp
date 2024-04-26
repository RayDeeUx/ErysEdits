#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/MoreSearchLayer.hpp>

using namespace geode::prelude;

class $modify(MyMoreSearchLayer, MoreSearchLayer) {
	bool init() {
		if (!MoreSearchLayer::init()) { return false; }
		this->setID("MoreSearchLayer");
		return true;
	}
};
#endif