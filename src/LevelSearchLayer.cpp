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
		if (const auto otherFilters = getChildByIDRecursive("other-filter-menu")) {
			if (otherFilters->getChildByIDRecursive("clear-filters-button")) {
				this->defineKeybind("level-search-clear-filters"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::get("clearFilters")) {
							LevelSearchLayer::confirmClearFilters(nullptr);
						} else { Utils::keybindDisabledGeneric("Clear Search Filters", "clear your search filters"); }
					}
				});
			}
			if (otherFilters->getChildByIDRecursive("advanced-filters-button")) {
				this->defineKeybind("level-search-open-filters"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse() && typeinfo_cast<CCSprite*>(getChildByIDRecursive("other-filter-menu")->getChildByIDRecursive("advanced-filters-button")->getChildren()->objectAtIndex(0))->getColor() == ccColor3B({255, 255, 255})) {
						if (Utils::modEnabled() && Utils::get("openFilters")) {
							LevelSearchLayer::onMoreOptions(nullptr);
						} else { Utils::keybindDisabledGeneric("Open Search Filters", "open advanced search filters"); }
					}
				});
			}
			if (otherFilters->getChildByIDRecursive("lists-button")) {
				this->defineKeybind("level-search-search-mode"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::get("searchMode")) {
							LevelSearchLayer::onSearchMode(nullptr);
						} else { Utils::keybindDisabledGeneric("Toggle Levels/Lists Mode", "switch between searching for levels and level lists"); }
					}
				});
			}
		}
		if (const auto lengthFilterMenu = getChildByIDRecursive("length-filter-menu")) {
			if (lengthFilterMenu->getChildByIDRecursive("tiny-filter-button")) {
				this->defineKeybind("level-search-length-tiny"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
						if (Utils::modEnabled() && Utils::get("starToggle")) {
							LevelSearchLayer::toggleStar(nullptr);
						} else { Utils::keybindDisabledGeneric("Star/Moon Rate Filter", "toggle the star/moon rate filter"); }
					}
				});
			}
		}
		if (const auto difficultyFilterMenu = getChildByIDRecursive("difficulty-filter-menu")) {
			if (difficultyFilterMenu->getChildByIDRecursive("na-filter-button")) {
				this->defineKeybind("level-search-difficulty-na"_spr, [this]() {
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
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
					if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse() && getChildByIDRecursive("difficulty-filter-menu")->getChildByIDRecursive("demon-type-filter-button")->isVisible()) {
						if (Utils::modEnabled() && Utils::get("difficultyFilter")) {
							LevelSearchLayer::onSpecialDemon(nullptr);
						} else { Utils::levelDifficultyDisabled(); }
					}
				});
			}
		}
		if (getChildByIDRecursive("most-downloaded-button")) {
			this->defineKeybind("level-search-quick-downloads"_spr, [this]() {
				if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("quickSearch")) {
						LevelSearchLayer::onMostDownloaded(nullptr);
					} else { Utils::quickSearchDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("trending-button")) {
			this->defineKeybind("level-search-quick-trending"_spr, [this]() {
				if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("quickSearch")) {
						LevelSearchLayer::onTrending(nullptr);
					} else { Utils::quickSearchDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("awarded-button")) {
			this->defineKeybind("level-search-quick-awarded"_spr, [this]() {
				if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("quickSearch")) {
						LevelSearchLayer::onLatestStars(nullptr);
					} else { Utils::quickSearchDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("most-liked-button")) {
			this->defineKeybind("level-search-quick-likes"_spr, [this]() {
				if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("quickSearch")) {
						LevelSearchLayer::onMostLikes(nullptr);
					} else { Utils::quickSearchDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("recent-button")) {
			this->defineKeybind("level-search-quick-recent"_spr, [this]() {
				if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("quickSearch")) {
						LevelSearchLayer::onMostRecent(nullptr);
					} else { Utils::quickSearchDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("followed-button")) {
			this->defineKeybind("level-search-quick-following"_spr, [this]() {
				if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("quickSearch")) {
						LevelSearchLayer::onFollowed(nullptr);
					} else { Utils::quickSearchDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("sent-button")) {
			this->defineKeybind("level-search-quick-sent"_spr, [this]() {
				if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("quickSearch")) {
						LevelSearchLayer::onSuggested(nullptr);
					} else { Utils::quickSearchDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("magic-button")) {
			this->defineKeybind("level-search-quick-magic"_spr, [this]() {
				if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("quickSearch")) {
						LevelSearchLayer::onMagic(nullptr);
					} else { Utils::quickSearchDisabled(); }
				}
			});
		}
		if (getChildByIDRecursive("friends-button")) {
			this->defineKeybind("level-search-quick-friends"_spr, [this]() {
				if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("quickSearch")) {
						LevelSearchLayer::onFriends(nullptr);
					} else { Utils::quickSearchDisabled(); }
				}
			});
		}
		/*
		mod.json:
		"focusUnfocusSearch": {
			"name": "Focus Search Bar",
			"description": "Enables a keybind (set to Shift + L by default) to focus the level search menu's search bar.",
			"type": "bool",
			"platforms": ["windows"],
			"default": true
		},
		
		if (getChildByIDRecursive("search-bar")) {
			this->defineKeybind("level-search-focus-search"_spr, [this]() {
				if (Utils::isSceneRunning("LevelSearchLayer") && Utils::nothingElse()) {
					if (Utils::modEnabled() && Utils::get("focusUnfocusSearch")) {
						if (!m_searchInput->m_selected) {
							m_searchInput->onClickTrackNode(true);
						}
					} else { Utils::keybindDisabledGeneric("Focus Search Bar", "to focus the level search menu's search bar"); }
				}
			});
		}
		*/
		return true;
	}
};
#endif