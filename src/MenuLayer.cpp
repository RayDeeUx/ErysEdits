#include <Geode/modify/MenuLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) { return false; }
		auto manager = Manager::getSharedInstance();
		if (manager->hasCalledAlready) { return true; }
		manager->hasCalledAlready = true;
		
		auto geode = Loader::get();
		auto mods = geode->getAllMods();
		
		auto activeMods = 0;
		auto disabledMods = 0;
		auto problems = geode->getProblems().size();
		
		std::string modsString = "";
		
		std::for_each(mods.begin(), mods.end(), [&](const Mod *mod) {
			std::string isEnabled = "Enabled";
			if (!mod->isEnabled()) {
				isEnabled = "Disabled";
				disabledMods++;
			} else {
				activeMods++;
			}
			modsString = modsString + fmt::format("{} by {} [{}] ({})\n", mod->getName(), mod->getDeveloper(), mod->getVersion().toString(), isEnabled);
		});
		
		log::info("FOUND {} INSTALLED MODS (OF WHICH {} ARE ACTIVE and {} ARE DISABLED WITH {} PROBLEMS PRESENT):\n{}", mods.size(), activeMods, disabledMods, problems, modsString);
		
		manager->installedMods = mods.size();
		manager->loadedMods = activeMods;
		manager->disabledMods = disabledMods;
		manager->problems = problems;
		
		manager->modsInfo = modsString;
		
		return true;
	}
};