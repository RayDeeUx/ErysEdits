#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include "Manager.hpp"
#include "Utils.hpp"
#include "Settings.hpp"

using namespace geode::prelude;
using namespace keybinds;

SettingNode* SectionSettingValue::createNode(float width) {
	return SectionSettingNode::create(this, width);
}

$on_mod(Loaded) {
	auto gameManager = GameManager::get();
	auto manager = Manager::getSharedInstance();
	auto geode = Loader::get();

	manager->originalShowProgressBarValue = gameManager->m_showProgressBar;
	manager->originalShowPercentageValue = gameManager->getGameVariable("0040");
	
	manager->geodeVer = geode->getVersion().toString();
	manager->gameVer = fmt::format("{:.3f}", GEODE_GD_VERSION);
	manager->platform = GEODE_PLATFORM_NAME;
	manager->forwardCompat = geode->isForwardCompatMode() ? "True" : "False";
	#ifdef GEODE_IS_WINDOWS
	manager->fourGBStatus = fmt::format("\n4GB Patch: {}", Utils::is4GBPatchEnabled() ? "True" : "False");
	#endif
	manager->canCall = false;
	
	// the following several lines were based on similar lines of code from coopeeo's hide+ mod with full consent
	// proof of consent: https://discord.com/channels/911701438269386882/911702535373475870/1222262244528754819
	Mod::get()->addCustomSetting<SectionSettingValue>("erysedits", "none");
	Mod::get()->addCustomSetting<SectionSettingValue>("debug-text", "none");
	Mod::get()->addCustomSetting<SectionSettingValue>("misc", "none");
	Mod::get()->addCustomSetting<SectionSettingValue>("compact", "none");
	Mod::get()->addCustomSetting<SectionSettingValue>("gameplay", "none");
	#ifdef GEODE_IS_WINDOWS
	Mod::get()->addCustomSetting<SectionSettingValue>("levelEditor", "none");
	Mod::get()->addCustomSetting<SectionSettingValue>("browser", "none");
	Mod::get()->addCustomSetting<SectionSettingValue>("level-search-layer", "none");
	Mod::get()->addCustomSetting<SectionSettingValue>("my-levels", "none");
	Mod::get()->addCustomSetting<SectionSettingValue>("misc-keybinds", "none");
	#endif
	Mod::get()->addCustomSetting<SectionSettingValue>("misc", "none");
	Mod::get()->addCustomSetting<SectionSettingValue>("alert-layers", "none");
	// the above several lines were based on similar lines of code from coopeeo's hide+ mod with full consent
	// proof of consent: https://discord.com/channels/911701438269386882/911702535373475870/1222262244528754819
}

#ifdef GEODE_IS_WINDOWS
$execute {
	BindManager::get()->registerBindable({
		"save-editor-level"_spr,
		"Save Editing Level",
		"Saves editing your level <cy>without a confirmation</c>, much like saving a file wherever else you can imagine.",
		{ Keybind::create(KEY_S, Modifier::Control) },
		"Editor/ErysEdits"
	});
	/*
	BindManager::get()->registerBindable({
		"save-and-play-editor"_spr,
		"Save and Play Editor Level",
		"Saves and playtests your editor level <cy>without a confirmation</c>.",
		{ Keybind::create(KEY_S, Modifier::Shift | Modifier::Alt | Modifier::Control) },
		"Editor/ErysEdits"
	});
	*/
	BindManager::get()->registerBindable({
		"save-and-exit-editor"_spr,
		"Save and Exit Editor Level",
		"Saves and exits your editor level <cy>without a confirmation</c>.",
		{ Keybind::create(KEY_S, Modifier::Shift | Modifier::Control) },
		"Editor/ErysEdits"
	});
	BindManager::get()->registerBindable({
		"resume-editor"_spr,
		"Resume Editor",
		"Use this keybind (set to Shift + 1 by default) to resume editing a level.",
		{ Keybind::create(KEY_One, Modifier::Shift) },
		"Editor/ErysEdits"
	});
	BindManager::get()->registerBindable({
		"refresh-page"_spr,
		"Refresh Page",
		"Use this keybind (set to Ctrl + R by default) to refresh the layer you're on.\n<cy>Use this keybind with caution; abusing/spamming this keybind can get you rate-limited or banned from RobTop's servers. By using this keybind for any reason, you agree to hold harmless the mod developer (RayDeeUx) or any lead developer of Geode and assume all responsibility for any consequences.</c>",
		{ Keybind::create(KEY_R, Modifier::Control) },
		"Global/ErysEdits/Browser-like Navigation"
	});
	BindManager::get()->registerBindable({
		"previous-page"_spr,
		"Go To Previous Page",
		"Use this keybind (set to Alt + Left Arrow by default) to go to the previous page.\n\nBecause RobTop's infinite wisdom allowed him to implement this feature with the main levels (and level browsing menus) <cr>and literally nowhere else</c> in Geometry Dash.\n\n<cj>No, I'm not mad about this. What makes you think that?</c>",
		{ Keybind::create(KEY_Left, Modifier::Alt) },
		"Global/ErysEdits/Browser-like Navigation"
	});
	BindManager::get()->registerBindable({
		"next-page"_spr,
		"Go To Next Page",
		"Use this keybind (set to Alt + Right Arrow by default) to go to the next page.\n\nBecause RobTop's infinite wisdom allowed him to implement this feature with the main levels (and level browsing menus) <cr>and literally nowhere else</c> in Geometry Dash.\n\n<cj>No, I'm not mad about this. What makes you think that?</c>",
		{ Keybind::create(KEY_Right, Modifier::Alt) },
		"Global/ErysEdits/Browser-like Navigation"
	});
	BindManager::get()->registerBindable({
		"first-page"_spr,
		"Go To First Page",
		"Use this keybind (set to Shift + Left Arrow by default) to go to the first page.",
		{ Keybind::create(KEY_Left, Modifier::Shift) },
		"Global/ErysEdits/Browser-like Navigation"
	});
	BindManager::get()->registerBindable({
		"last-page"_spr,
		"Go To Last Page",
		"Use this keybind (set to Shift + Right Arrow by default) to go to the last <cy>(estimated)</c> page.\n\n<cy>Results may be inaccurate.</c>",
		{ Keybind::create(KEY_Right, Modifier::Shift) },
		"Global/ErysEdits/Browser-like Navigation"
	});
	BindManager::get()->registerBindable({
		"like"_spr,
		"Like Content",
		"Use this keybind (set to Left Arrow by default) to like content.",
		{ Keybind::create(KEY_Left) },
		"Global/ErysEdits/Browser-like Navigation"
	});
	BindManager::get()->registerBindable({
		"dislike"_spr,
		"Dislike Content",
		"Use this keybind (set to Right Arrow by default) to dislike content.",
		{ Keybind::create(KEY_Right) },
		"Global/ErysEdits/Browser-like Navigation"
	});
	BindManager::get()->registerBindable({
		"comments"_spr,
		"View Comments",
		"Use this keybind (set to Shift + C by default) to view comments (either for a specific profile or for a level).",
		{ Keybind::create(KEY_C, Modifier::Shift) },
		"Global/ErysEdits/Browser-like Navigation"
	});
	BindManager::get()->registerBindable({
		"level-search-focus-search"_spr,
		"Focus Search Bar",
		"Use this keybind (set to Shift + L by default) to focus the level search menu's search bar.",
		{ Keybind::create(KEY_L, Modifier::Shift)},
		"Global/ErysEdits/Level Search Menu Navigation"
	});
	BindManager::get()->registerBindable({
		"level-search-clear-filters"_spr,
		"Clear Search Filters",
		"Use this keybind (set to Shift + Delete by default) to prepare to clear your search filters.",
		{ Keybind::create(KEY_Delete, Modifier::Shift) },
		"Global/ErysEdits/Level Search Menu Navigation"
	});
	BindManager::get()->registerBindable({
		"level-search-open-filters"_spr,
		"Open Search Filters",
		"Use this keybind (set to Shift + Minus by default) to open advanced search filters.",
		{ Keybind::create(KEY_OEMMinus, Modifier::Shift) },
		"Global/ErysEdits/Level Search Menu Navigation"
	});
	BindManager::get()->registerBindable({
		"level-search-search-mode"_spr,
		"Toggle Levels/Lists Mode",
		"Use this keybind (set to Shift + Backspace by default) to switch between searching for levels and level lists.",
		{ Keybind::create(KEY_Backspace, Modifier::Shift) },
		"Global/ErysEdits/Level Search Menu Navigation"
	});
	BindManager::get()->registerBindable({
		"level-search-rate-filter"_spr,
		"Star/Moon Rate",
		"Use this keybind (set to Alt + 0 by default) to toggle the star rate filter.",
		{ Keybind::create(KEY_Zero, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation"
	});
	BindManager::get()->registerBindable({
		"level-search-quick-downloads"_spr,
		"Downloads",
		"Use this keybind (set to Ctrl + D and Alt + D by default) to open the \"Downloads\" Quick Search option.",
		{ Keybind::create(KEY_D, Modifier::Control), Keybind::create(KEY_D, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Quick Search Shortcuts"
	});
	BindManager::get()->registerBindable({
		"level-search-quick-trending"_spr,
		"Trending",
		"Use this keybind (set to Ctrl + T and Alt + T by default) to open the \"Trending\" Quick Search option.",
		{ Keybind::create(KEY_T, Modifier::Control), Keybind::create(KEY_T, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Quick Search Shortcuts"
	});
	BindManager::get()->registerBindable({
		"level-search-quick-awarded"_spr,
		"Awarded",
		"Use this keybind (set to Ctrl + A and Alt + A by default) to open the \"Awarded\" Quick Search option.",
		{ Keybind::create(KEY_A, Modifier::Control), Keybind::create(KEY_A, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Quick Search Shortcuts"
	});
	BindManager::get()->registerBindable({
		"level-search-quick-likes"_spr,
		"Likes",
		"Use this keybind (set to Ctrl + L and Alt + L by default) to open the \"Likes\" Quick Search option.",
		{ Keybind::create(KEY_L, Modifier::Control), Keybind::create(KEY_L, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Quick Search Shortcuts"
	});
	BindManager::get()->registerBindable({
		"level-search-quick-recent"_spr,
		"Recent",
		"Use this keybind (set to Ctrl + R and Alt + R by default) to open the \"Recent\" Quick Search option.",
		{ Keybind::create(KEY_R, Modifier::Control), Keybind::create(KEY_R, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Quick Search Shortcuts"
	});
	BindManager::get()->registerBindable({
		"level-search-quick-following"_spr,
		"Followed",
		"Use this keybind (set to Ctrl + F and Alt + F by default) to open the \"Followed\" Quick Search option.",
		{ Keybind::create(KEY_F, Modifier::Control), Keybind::create(KEY_F, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Quick Search Shortcuts"
	});
	BindManager::get()->registerBindable({
		"level-search-quick-sent"_spr,
		"Sent",
		"Use this keybind (set to Ctrl + S and Alt + S by default) to open the \"Sent\" Quick Search option.",
		{ Keybind::create(KEY_S, Modifier::Control), Keybind::create(KEY_S, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Quick Search Shortcuts"
	});
	BindManager::get()->registerBindable({
		"level-search-quick-magic"_spr,
		"Magic",
		"Use this keybind (set to Ctrl + M and Alt + M by default) to open the \"Magic\" Quick Search option.",
		{ Keybind::create(KEY_M, Modifier::Control), Keybind::create(KEY_M, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Quick Search Shortcuts"
	});
	BindManager::get()->registerBindable({
		"level-search-quick-friends"_spr,
		"Friends",
		"Use this keybind (set to Ctrl + I and Alt + I by default) to open the \"Friends\" Quick Search option.",
		{ Keybind::create(KEY_I, Modifier::Control), Keybind::create(KEY_I, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Quick Search Shortcuts"
	});
	BindManager::get()->registerBindable({
		"level-search-length-tiny"_spr,
		"Tiny",
		"Use this keybind (set to Alt + 1 by default) to toggle the \"Tiny\" level length search filter.",
		{ Keybind::create(KEY_One, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Length Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-length-short"_spr,
		"Short",
		"Use this keybind (set to Alt + 2 by default) to toggle the \"Short\" level length search filter.",
		{ Keybind::create(KEY_Two, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Length Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-length-medium"_spr,
		"Medium",
		"Use this keybind (set to Alt + 3 by default) to toggle the \"Medium\" level length search filter.",
		{ Keybind::create(KEY_Three, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Length Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-length-long"_spr,
		"Long",
		"Use this keybind (set to Alt + 4 by default) to toggle the \"Long\" level length search filter.",
		{ Keybind::create(KEY_Four, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Length Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-length-xl"_spr,
		"XL",
		"Use this keybind (set to Alt + 5 by default) to toggle the \"XL\" level length search filter.",
		{ Keybind::create(KEY_Five, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Length Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-length-plat"_spr,
		"Plat.",
		"Use this keybind (set to Alt + 6 and Alt + 9 by default) to toggle the \"Plat.\" level length search filter.",
		{ Keybind::create(KEY_Six, Modifier::Alt), Keybind::create(KEY_Nine, Modifier::Alt) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Length Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-difficulty-na"_spr,
		"NA",
		"Use this keybind (set to Ctrl + 1 by default) to toggle the \"NA\" level difficulty search filter.",
		{ Keybind::create(KEY_One, Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Difficulty Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-difficulty-easy"_spr,
		"Easy",
		"Use this keybind (set to Ctrl + 2 by default) to toggle the \"Easy\" level difficulty search filter.",
		{ Keybind::create(KEY_Two, Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Difficulty Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-difficulty-normal"_spr,
		"Normal",
		"Use this keybind (set to Ctrl + 3 by default) to toggle the \"Normal\" level difficulty search filter.",
		{ Keybind::create(KEY_Three, Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Difficulty Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-difficulty-hard"_spr,
		"Hard",
		"Use this keybind (set to Ctrl + 4 by default) to toggle the \"Hard\" level difficulty search filter.",
		{ Keybind::create(KEY_Four, Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Difficulty Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-difficulty-harder"_spr,
		"Harder",
		"Use this keybind (set to Ctrl + 5 by default) to toggle the \"Harder\" level difficulty search filter.",
		{ Keybind::create(KEY_Five, Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Difficulty Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-difficulty-insane"_spr,
		"Insane",
		"Use this keybind (set to Ctrl + 6 by default) to toggle the \"Insane\" level difficulty search filter.",
		{ Keybind::create(KEY_Six, Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Difficulty Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-difficulty-demon"_spr,
		"Demon",
		"Use this keybind (set to Ctrl + 7 by default) to toggle the \"Demon\" level difficulty search filter.",
		{ Keybind::create(KEY_Seven, Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Difficulty Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-difficulty-auto"_spr,
		"Auto",
		"Use this keybind (set to Ctrl + 8 by default) to toggle the \"Auto\" level difficulty search filter.",
		{ Keybind::create(KEY_Eight, Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Difficulty Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-demon-filter"_spr,
		"Open Demon Filter",
		"Use this keybind (set to Ctrl + 9 and Ctrl + 0 by default) to toggle the \"Demon\" level difficulty search filter.",
		{ Keybind::create(KEY_Nine, Modifier::Control), Keybind::create(KEY_Zero, Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Level Difficulty Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-all-demons"_spr,
		"Demon",
		"Use this keybind (set to Shift + Ctrl + 1 by default) to toggle the \"Demon\" filter.",
		{ Keybind::create(KEY_One, Modifier::Shift | Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Demon Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-easy-demon"_spr,
		"Easy Demon",
		"Use this keybind (set to Shift + Ctrl + 2 by default) to toggle the \"Easy Demon\" filter.",
		{ Keybind::create(KEY_Two, Modifier::Shift | Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Demon Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-medium-demon"_spr,
		"Medium Demon",
		"Use this keybind (set to Shift + Ctrl + 3 by default) to toggle the \"Medium Demon\" filter.",
		{ Keybind::create(KEY_Three, Modifier::Shift | Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Demon Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-hard-demon"_spr,
		"Hard Demon",
		"Use this keybind (set to Shift + Ctrl + 4 by default) to toggle the \"Hard Demon\" filter.",
		{ Keybind::create(KEY_Four, Modifier::Shift | Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Demon Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-insane-demon"_spr,
		"Insane Demon",
		"Use this keybind (set to Shift + Ctrl + 5 by default) to toggle the \"Insane Demon\" filter.",
		{ Keybind::create(KEY_Five, Modifier::Shift | Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Demon Filters"
	});
	BindManager::get()->registerBindable({
		"level-search-extreme-demon"_spr,
		"Extreme Demon",
		"Use this keybind (set to Shift + Ctrl + 6 by default) to toggle the \"Extreme Demon\" filter.",
		{ Keybind::create(KEY_Six, Modifier::Shift | Modifier::Control) },
		"Global/ErysEdits/Level Search Menu Navigation/Demon Filters"
	});
	BindManager::get()->registerBindable({
		"new-editor-level"_spr,
		"Create New Level/List",
		"Use this keybind (set to Ctrl + N by default) to create a new level/list.",
		{ Keybind::create(KEY_N, Modifier::Control) },
		"Global/ErysEdits/\"My Levels\" Navigation"
	});
	BindManager::get()->registerBindable({
		"toggle-level-lists"_spr,
		"Toggle Levels/Lists Mode",
		"Use this keybind (set to Shift + Ctrl + L by default) to toggle between viewing local editor levels and local level lists.",
		{ Keybind::create(KEY_L, Modifier::Control | Modifier::Shift) },
		"Global/ErysEdits/\"My Levels\" Navigation"
	});
	BindManager::get()->registerBindable({
		"view-uploaded"_spr,
		"View Uploaded Levels/Lists",
		"Use this keybind (set to Shift + Ctrl + Alt + L by default) (set to Shift + Ctrl + Alt + L by default) to view uploaded levels/level lists.",
		{ Keybind::create(KEY_L, Modifier::Control | Modifier::Shift | Modifier::Alt) },
		"Global/ErysEdits/\"My Levels\" Navigation"
	});
	BindManager::get()->registerBindable({
		"next-gauntlet"_spr,
		"Next Gauntlet",
		"Use this keybind (set to Right by default) to view the next gauntlet page.",
		{ Keybind::create(KEY_Right) },
		"Global/ErysEdits/Gauntlets Navigation"
	});
	BindManager::get()->registerBindable({
		"previous-gauntlet"_spr,
		"Previous Gauntlet",
		"Use this keybind (set to Left by default) to view the previous gauntlet page.",
		{ Keybind::create(KEY_Left) },
		"Global/ErysEdits/Gauntlets Navigation"
	});
	BindManager::get()->registerBindable({
		"first-visible-gauntlet"_spr,
		"First Gauntlet",
		"Use this keybind (set to 1 by default) to enter the first visible gauntlet.\n\n<cy>(Disclaimer: Results may not be accurate.)</c>",
		{ Keybind::create(KEY_One) },
		"Global/ErysEdits/Gauntlets Navigation"
	});
	BindManager::get()->registerBindable({
		"second-visible-gauntlet"_spr,
		"Second Gauntlet",
		"Use this keybind (set to 2 by default) to enter the second visible gauntlet.\n\n<cy>(Disclaimer: Results may not be accurate.)</c>",
		{ Keybind::create(KEY_Two) },
		"Global/ErysEdits/Gauntlets Navigation"
	});
	BindManager::get()->registerBindable({
		"third-visible-gauntlet"_spr,
		"Third Gauntlet",
		"Use this keybind (set to 3 by default) to enter the third visible gauntlet.\n\n<cy>(Disclaimer: Results may not be accurate.)</c>",
		{ Keybind::create(KEY_Three) },
		"Global/ErysEdits/Gauntlets Navigation"
	});
	BindManager::get()->registerBindable({
		"more-options-layer"_spr,
		"More Options Shortcuts",
		"Use this keybind (set to Ctrl + O by default) to open your GD settings.",
		{ Keybind::create(KEY_O, Modifier::Control) },
		"Global/ErysEdits/More Options Navigation"
	});
	BindManager::get()->registerBindable({
		"next-options-page"_spr,
		"Next Options Page",
		"Use this keybind (set to Right by default) to view the next Options page.",
		{ Keybind::create(KEY_Right) },
		"Global/ErysEdits/More Options Navigation"
	});
	BindManager::get()->registerBindable({
		"previous-options-page"_spr,
		"Previous Options Page",
		"Use this keybind (set to Left by default) to view the previous Options page.",
		{ Keybind::create(KEY_Left) },
		"Global/ErysEdits/More Options Navigation"
	});
	BindManager::get()->registerBindable({
		"erysedits-settings"_spr,
		"ErysEdits Settings",
		"Use this keybind (set to Shift + Alt + Ctrl + E by default) to open the settings menu for ErysEdits.",
		{ Keybind::create(KEY_E, Modifier::Shift | Modifier::Alt | Modifier::Control) },
		"Global/ErysEdits/Misc. Navigation"
	});
	BindManager::get()->registerBindable({
		"geode-mods-list"_spr,
		"Geode Mods List",
		"Use this keybind (set to Shift + Alt + Ctrl + G by default) to open the Geode mods list.",
		{ Keybind::create(KEY_G, Modifier::Shift | Modifier::Alt | Modifier::Control) },
		"Global/ErysEdits/Misc. Navigation"
	});
	BindManager::get()->registerBindable({
		"custom-keybinds"_spr,
		"Custom Keybinds",
		"Use this keybind (set to Shift + Alt + Ctrl + K by default) to open your custom keybinds.",
		{ Keybind::create(KEY_K, Modifier::Shift | Modifier::Alt | Modifier::Control) },
		"Global/ErysEdits/Misc. Navigation"
	});
	
	new EventListener([=](InvokeBindEvent* event) {
		if (!GJBaseGameLayer::get() && event->isDown()) { // event->isDown() to trigger only once (thank you dankmeme!)
			if (Utils::modEnabled() && Utils::get("erysEditsSettings")) {
				geode::openSettingsPopup(Mod::get());
			} else { Utils::keybindDisabledGeneric("ErysEdits Settings", "open the settings menu for ErysEdits"); }
		}
		return ListenerResult::Propagate;
	}, InvokeBindFilter(nullptr, "erysedits-settings"_spr));
	new EventListener([=](InvokeBindEvent* event) {
		if (!GJBaseGameLayer::get() && event->isDown()) { // event->isDown() to trigger only once (thank you dankmeme!)
			if (Utils::modEnabled() && Utils::get("geodeModsList")) {
				geode::openModsList();
			} else { Utils::keybindDisabledGeneric("Geode Mods List", "open the Geode mods list"); }
		}
		return ListenerResult::Propagate;
	}, InvokeBindFilter(nullptr, "geode-mods-list"_spr));
	new EventListener([=](InvokeBindEvent* event) {
		if (!GJBaseGameLayer::get() && event->isDown()) { // event->isDown() to trigger only once (thank you dankmeme!)
			if (Utils::modEnabled() && Utils::get("customKeybinds")) {
				MoreOptionsLayer::create()->onKeybindings(nullptr); // normally this would just open the vanilla keybinds menu. however since customkeybinds is a required dependency it'll open the one from customkeybinds instead. win-win!
			} else { Utils::keybindDisabledGeneric("Custom Keybinds", "open your custom keybinds"); }
		}
		return ListenerResult::Propagate;
	}, InvokeBindFilter(nullptr, "custom-keybinds"_spr));
	new EventListener([=](InvokeBindEvent* event) {
		if (!GJBaseGameLayer::get() && event->isDown() && !Loader::get()->isModLoaded("raydeeux.moreoptionslayerkeybinds")) { // event->isDown() to trigger only once (thank you dankmeme!)
			if (Utils::modEnabled() && Utils::get("moreOptions")) {
				OptionsLayer::create()->onOptions(nullptr);
			} else { Utils::moreOptionsDisabled(); }
		}
		return ListenerResult::Propagate;
	}, InvokeBindFilter(nullptr, "more-options-layer"_spr));
}
#endif