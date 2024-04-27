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
			std::string isEnabled = "<cg>";
			if (!mod->isEnabled()) {
				isEnabled = "<cr>";
				disabledMods++;
			} else {
				activeMods++;
			}
			
			if (Utils::getInt("showModsListMode") == 4) { // mod name only
			    manager->modsListMode = "Mod names only";
				modsString = modsString + fmt::format("{}{}</c>, ", isEnabled, mod->getName());
			} else if (Utils::getInt("showModsListMode") == 3) { // mod name and ver number only
			    manager->modsListMode = "Mod names + version numbers only";
				modsString = modsString + fmt::format("{}{} [{}]</c>, ", isEnabled, mod->getName(), mod->getVersion().toString());
			} else if (Utils::getInt("showModsListMode") == 2) { // developer name and mod name only
			    manager->modsListMode = "Dev names + mod names only";
				modsString = modsString + fmt::format("{}{}'s {}</c>, ", isEnabled, mod->getDeveloper(), mod->getName());
			} else if (Utils::getInt("showModsListMode") == 1) { // dev name, mod name, ver number
			    manager->modsListMode = "Dev names, mod names, and version numbers";
				modsString = modsString + fmt::format("{}{}'s {} [{}]</c>, ", isEnabled, mod->getDeveloper(), mod->getName(), mod->getVersion().toString());
			}
		
		});
		
		// remove ", " ending
		if (!modsString.empty()) 
		{
			modsString.pop_back();
			modsString.pop_back();
		}
		
		// log::info("FOUND {} INSTALLED MODS (OF WHICH {} ARE ACTIVE and {} ARE DISABLED WITH {} PROBLEMS PRESENT):\n{}", mods.size(), activeMods, disabledMods, problems, modsString);
		
		manager->installedMods = mods.size();
		manager->loadedMods = activeMods;
		manager->disabledMods = disabledMods;
		manager->problems = problems;
		
		manager->modsInfo = modsString;
		
		// log::info("modsString: {}", modsString);
		
		return true;
	}
};