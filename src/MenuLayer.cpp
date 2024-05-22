#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/SongInfoLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
		GameManager* gameManager = GameManager::get();
	};
	bool init() {
		if (!MenuLayer::init()) { return false; }
		if (m_fields->manager->hasCalledAlready) { return true; }
		m_fields->manager->hasCalledAlready = true;

		m_fields->manager->originalShowProgressBarValue = m_fields->gameManager->m_showProgressBar;
		m_fields->manager->originalShowPercentageValue = m_fields->gameManager->getGameVariable("0040");
		
		const auto geode = Loader::get();
		auto mods = geode->getAllMods();
		
		auto activeMods = 0;
		auto disabledMods = 0;
		auto problems = geode->getProblems().size();
		
		std::string modsString = "";
		std::string modsStringForClipboard = "";
		#ifdef __APPLE__
		std::map<std::string, int> devNameToModCount{};
		#else
		switch (Utils::getInt("showModsListMode")) {
			case 1:
				m_fields->manager->modsListMode = "Mod names only";
				break;
			case 2:
				m_fields->manager->modsListMode = "Mod names + version numbers only";
				break;
			case 3:
				m_fields->manager->modsListMode = "Dev names + mod names only";
				break;
			case 4:
				m_fields->manager->modsListMode = "Dev names, mod names, and version numbers";
				break;
			default:
				m_fields->manager->modsListMode = "You've been naughty.";
				break;
		}
		#endif
		
		std::ranges::for_each(mods, [&](const Mod *mod) {
			std::string isEnabled = "<cg>";
			std::string isEnabledClipboard = "{Enabled}";
			if (!mod->isEnabled()) {
				isEnabled = "<cr>";
				isEnabledClipboard = "{Disabled}";
				disabledMods++;
			} else {
				activeMods++;
			}
			
			modsStringForClipboard = modsStringForClipboard + fmt::format("- {} ({}) {} by {} [{}]\n", isEnabledClipboard, mod->getID(), mod->getName(), mod->getDevelopers()[0], mod->getVersion().toString());

			#ifndef __APPLE__
			if (Utils::getInt("showModsListMode") == 4) { // mod name only
				modsString = modsString + fmt::format("{}{}</c>, ", isEnabled, mod->getName());
			} else if (Utils::getInt("showModsListMode") == 3) { // mod name and ver number only
				modsString = modsString + fmt::format("{}{} [{}]</c>, ", isEnabled, mod->getName(), mod->getVersion().toString());
			} else if (Utils::getInt("showModsListMode") == 2) { // developer name and mod name only
				modsString = modsString + fmt::format("{}{}'s {}</c>, ", isEnabled, mod->getDevelopers()[0], mod->getName());
			} else if (Utils::getInt("showModsListMode") == 1) { // dev name, mod name, ver number
				modsString = modsString + fmt::format("{}{}'s {} [{}]</c>, ", isEnabled, mod->getDevelopers()[0], mod->getName(), mod->getVersion().toString());
			} else { // fallback. because some people need to behave
				modsString = modsString + fmt::format("- {} ({}) {} by {} [{}]\n", isEnabledClipboard, mod->getID(), mod->getName(), mod->getDevelopers()[0], mod->getVersion().toString());
			}
			#else
			if (0 < Utils::getInt("showModsListMode") && Utils::getInt("showModsListMode") < 5) {
				auto modDevName = mod->getDevelopers()[0];
			   if (!devNameToModCount.contains(modDevName)) {
				   devNameToModCount.insert(std::make_pair(modDevName, 1));
			   } else {
				   devNameToModCount.find(modDevName)->second += 1;
			   }
			}
			#endif
		
		});

		#ifdef __APPLE__
		m_fields->manager->modsListMode = "macOS Compat Mode";
		if (0 < Utils::getInt("showModsListMode") && Utils::getInt("showModsListMode") < 5) {
			for (auto const& [modDevName, numMods] : devNameToModCount) {
				modsString.append(fmt::format("{}: {}, ", modDevName, numMods));
			}
		} else if (Utils::getInt("showModsListMode") != 0) {
			modsString = "Installed mods list breakdown currently unavailable.\n<cr>Maybe don't break the settings file next time.</c>, ";
		}
		#endif

		// remove ", " ending
		if (!modsString.empty()) 
		{
			modsString.pop_back();
			modsString.pop_back();
		}
		
		// log::info("FOUND {} INSTALLED MODS (OF WHICH {} ARE ACTIVE and {} ARE DISABLED WITH {} PROBLEMS PRESENT):\n{}", mods.size(), activeMods, disabledMods, problems, modsString);
		
		m_fields->manager->installedMods = mods.size();
		m_fields->manager->loadedMods = activeMods;
		m_fields->manager->disabledMods = disabledMods;
		m_fields->manager->problems = problems;
		
		m_fields->manager->modsInfo = modsString;
		
		m_fields->manager->modsInfoForClipboard = fmt::format("--- {} mods | {} loaded | {} disabled | {} problems ---\n", mods.size(), activeMods, disabledMods, problems) + modsStringForClipboard + fmt::format("--- {} mods | {} loaded | {} disabled | {} problems ---", mods.size(), activeMods, disabledMods, problems);
		
		// log::info("modsInfoForClipboard: {}", m_fields->manager->modsInfoForClipboard);
		
		return true;
	}
};