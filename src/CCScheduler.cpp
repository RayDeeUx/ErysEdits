#include <Geode/modify/CCScheduler.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

class $modify(MyCCScheduler, CCScheduler) {
    void update(float dt) {
        CCScheduler::update(dt);
        if (PlayLayer::get() && Utils::getBool("includeFPS")) {
            Manager::getSharedInstance()->fps = static_cast<int>(CCScheduler::get()->getTimeScale() / dt) + 1;
        }
    }
};