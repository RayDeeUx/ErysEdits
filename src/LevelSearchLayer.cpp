#ifdef GEODE_IS_WINDOWS
#include <Geode/modify/LevelSearchLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyLevelSearchLayer, LevelSearchLayer) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}
	bool init(int p0) {
		if (!LevelSearchLayer::init(p0)) { return false; }
		if (auto otherFilters = getChildByIDRecursive("other-filter-menu")) {
			if (otherFilters->getChildByIDRecursive("clear-filters-button")) {
				this->defineKeybind("level-search-clear-filters"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("clearFilters")) {
							LevelSearchLayer::confirmClearFilters(nullptr);
						} else { Utils::keybindDisabledGeneric("Clear Search Filters", "clear your search filters"); }
					}
				});
			}
			if (otherFilters->getChildByIDRecursive("advanced-filters-button")) {
				this->defineKeybind("level-search-open-filters"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer") && typeinfo_cast<CCSprite*>(getChildByIDRecursive("other-filter-menu")->getChildByIDRecursive("advanced-filters-button")->getChildren()->objectAtIndex(0))->getColor() == ccColor3B(255, 255, 255)) {
						if (Utils::modEnabled() && Utils::get("openFilters")) {
							LevelSearchLayer::onMoreOptions(nullptr);
						} else { Utils::keybindDisabledGeneric("Open Search Filters", "open advanced search filters"); }
					}
				});
			}
			if (otherFilters->getChildByIDRecursive("lists-button")) {
				this->defineKeybind("level-search-search-mode"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("searchMode")) {
							LevelSearchLayer::onSearchMode(nullptr);
						} else { Utils::keybindDisabledGeneric("Toggle Levels/Lists Mode", "switch between searching for levels and level lists"); }
					}
				});
			}
		}
		if (auto lengthFilterMenu = getChildByIDRecursive("length-filter-menu")) {
			if (lengthFilterMenu->getChildByIDRecursive("tiny-filter-button")) {
				this->defineKeybind("level-search-length-tiny"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("lengthFilter")) {
							LevelSearchLayer::toggleTime(
								getChildByIDRecursive("length-filter-menu")->getChildByIDRecursive("tiny-filter-button")
							);
						} else { Utils::levelLengthDisabled(); }
					}
				});
			}
			if (lengthFilterMenu->getChildByIDRecursive("short-filter-button")) {
				this->defineKeybind("level-search-length-short"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("lengthFilter")) {
							LevelSearchLayer::toggleTime(
								getChildByIDRecursive("length-filter-menu")->getChildByIDRecursive("short-filter-button")
							);
						} else { Utils::levelLengthDisabled(); }
					}
				});
			}
			if (lengthFilterMenu->getChildByIDRecursive("medium-filter-button")) {
				this->defineKeybind("level-search-length-medium"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("lengthFilter")) {
							LevelSearchLayer::toggleTime(
								getChildByIDRecursive("length-filter-menu")->getChildByIDRecursive("medium-filter-button")
							);
						} else { Utils::levelLengthDisabled(); }
					}
				});
			}
			if (lengthFilterMenu->getChildByIDRecursive("long-filter-button")) {
				this->defineKeybind("level-search-length-long"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("lengthFilter")) {
							LevelSearchLayer::toggleTime(
								getChildByIDRecursive("length-filter-menu")->getChildByIDRecursive("long-filter-button")
							);
						} else { Utils::levelLengthDisabled(); }
					}
				});
			}
			if (lengthFilterMenu->getChildByIDRecursive("xl-filter-button")) {
				this->defineKeybind("level-search-length-xl"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("lengthFilter")) {
							LevelSearchLayer::toggleTime(
								getChildByIDRecursive("length-filter-menu")->getChildByIDRecursive("xl-filter-button")
							);
						} else { Utils::levelLengthDisabled(); }
					}
				});
			}
			if (lengthFilterMenu->getChildByIDRecursive("plat-filter-button")) {
				this->defineKeybind("level-search-length-plat"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("lengthFilter")) {
							LevelSearchLayer::toggleTime(
								getChildByIDRecursive("length-filter-menu")->getChildByIDRecursive("plat-filter-button")
							);
						} else { Utils::levelLengthDisabled(); }
					}
				});
			}
			if (lengthFilterMenu->getChildByIDRecursive("star-filter-button")) {
				this->defineKeybind("level-search-rate-filter"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("starToggle")) {
							LevelSearchLayer::toggleStar(nullptr);
						} else { Utils::keybindDisabledGeneric("Star/Moon Rate Filter", "toggle the star/moon rate filter"); }
					}
				});
			}
		}
		if (auto difficultyFilterMenu = getChildByIDRecursive("difficulty-filter-menu")) {
			if (difficultyFilterMenu->getChildByIDRecursive("na-filter-button")) {
				this->defineKeybind("level-search-difficulty-na"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("difficultyFilter")) {
							LevelSearchLayer::toggleDifficulty(
								getChildByIDRecursive("difficulty-filter-menu")->getChildByIDRecursive("na-filter-button")
							);
						} else { Utils::levelDifficultyDisabled(); }
					}
				});
			}
			if (difficultyFilterMenu->getChildByIDRecursive("easy-filter-button")) {
				this->defineKeybind("level-search-difficulty-easy"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("difficultyFilter")) {
							LevelSearchLayer::toggleDifficulty(
								getChildByIDRecursive("difficulty-filter-menu")->getChildByIDRecursive("easy-filter-button")
							);
						} else { Utils::levelDifficultyDisabled(); }
					}
				});
			}
			if (difficultyFilterMenu->getChildByIDRecursive("normal-filter-button")) {
				this->defineKeybind("level-search-difficulty-normal"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("difficultyFilter")) {
							LevelSearchLayer::toggleDifficulty(
								getChildByIDRecursive("difficulty-filter-menu")->getChildByIDRecursive("normal-filter-button")
							);
						} else { Utils::levelDifficultyDisabled(); }
					}
				});
			}
			if (difficultyFilterMenu->getChildByIDRecursive("hard-filter-button")) {
				this->defineKeybind("level-search-difficulty-hard"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("difficultyFilter")) {
							LevelSearchLayer::toggleDifficulty(
								getChildByIDRecursive("difficulty-filter-menu")->getChildByIDRecursive("hard-filter-button")
							);
						} else { Utils::levelDifficultyDisabled(); }
					}
				});
			}
			if (difficultyFilterMenu->getChildByIDRecursive("harder-filter-button")) {
				this->defineKeybind("level-search-difficulty-harder"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("difficultyFilter")) {
							LevelSearchLayer::toggleDifficulty(
								getChildByIDRecursive("difficulty-filter-menu")->getChildByIDRecursive("harder-filter-button")
							);
						} else { Utils::levelDifficultyDisabled(); }
					}
				});
			}
			if (difficultyFilterMenu->getChildByIDRecursive("insane-filter-button")) {
				this->defineKeybind("level-search-difficulty-insane"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("difficultyFilter")) {
							LevelSearchLayer::toggleDifficulty(
								getChildByIDRecursive("difficulty-filter-menu")->getChildByIDRecursive("insane-filter-button")
							);
						} else { Utils::levelDifficultyDisabled(); }
					}
				});
			}
			if (difficultyFilterMenu->getChildByIDRecursive("demon-filter-button")) {
				this->defineKeybind("level-search-difficulty-demon"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("difficultyFilter")) {
							LevelSearchLayer::toggleDifficulty(
								getChildByIDRecursive("difficulty-filter-menu")->getChildByIDRecursive("demon-filter-button")
							);
						} else { Utils::levelDifficultyDisabled(); }
					}
				});
			}
			if (difficultyFilterMenu->getChildByIDRecursive("auto-filter-button")) {
				this->defineKeybind("level-search-difficulty-auto"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer")) {
						if (Utils::modEnabled() && Utils::get("difficultyFilter")) {
							LevelSearchLayer::toggleDifficulty(
								getChildByIDRecursive("difficulty-filter-menu")->getChildByIDRecursive("auto-filter-button")
							);
						} else { Utils::levelDifficultyDisabled(); }
					}
				});
			}
			if (difficultyFilterMenu->getChildByIDRecursive("demon-type-filter-button")) {
				this->defineKeybind("level-search-demon-filter"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && !Utils::isSceneRunningRecursive("DemonFilterSelectLayer") && !Utils::isSceneRunningRecursive("MoreSearchLayer") && getChildByIDRecursive("difficulty-filter-menu")->getChildByIDRecursive("demon-type-filter-button")->isVisible()) {
						if (Utils::modEnabled() && Utils::get("difficultyFilter")) {
							LevelSearchLayer::onSpecialDemon(nullptr);
						} else { Utils::levelDifficultyDisabled(); }
					}
				});
			}
		}
		return true;
	}
};
#endif