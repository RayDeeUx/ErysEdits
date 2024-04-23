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
	Mod::get()->addCustomSetting<SectionSettingValue>("gameplay", "none");
	#ifdef GEODE_IS_WINDOWS
	Mod::get()->addCustomSetting<SectionSettingValue>("levelEditor", "none");
	Mod::get()->addCustomSetting<SectionSettingValue>("navigation", "none");
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
		Category::EDITOR
	});
	/*
	BindManager::get()->registerBindable({
		"save-and-play-editor"_spr,
		"Save and Play Editor Level",
		"Saves and playtests your editor level <cy>without a confirmation</c>.",
		{ Keybind::create(KEY_S, Modifier::Shift | Modifier::Alt | Modifier::Control) },
		Category::EDITOR
	});
	*/
	BindManager::get()->registerBindable({
		"save-and-exit-editor"_spr,
		"Save and Exit Editor Level",
		"Saves and exits your editor level <cy>without a confirmation</c>.",
		{ Keybind::create(KEY_S, Modifier::Shift | Modifier::Control) },
		Category::EDITOR
	});
	BindManager::get()->registerBindable({
		"resume-editor"_spr,
		"Resume Editor",
		"Enables a keybind (set to Shift + 1 by default) to resume editing a level.",
		{ Keybind::create(KEY_One, Modifier::Shift) },
		Category::EDITOR
	});
	BindManager::get()->registerBindable({
		"new-editor-level"_spr,
		"Create New Level/List",
		"Enables a keybind (set to Ctrl + N by default) to create a new level/list.",
		{ Keybind::create(KEY_N, Modifier::Control) },
		Category::EDITOR
	});
	BindManager::get()->registerBindable({
		"toggle-level-lists"_spr,
		"Toggle Levels/Lists Mode",
		"Enables a keybind (set to Shift + Ctrl + L by default) to toggle between viewing local editor levels and local level lists.",
		{ Keybind::create(KEY_L, Modifier::Control | Modifier::Shift) },
		Category::EDITOR
	});
	BindManager::get()->registerBindable({
		"view-uploaded"_spr,
		"View Uploaded Levels/Lists",
		"Enables a keybind (set to Shift + Ctrl + Alt + L by default) (set to Shift + Ctrl + Alt + L by default) to view uploaded levels/level lists.",
		{ Keybind::create(KEY_L, Modifier::Control | Modifier::Shift | Modifier::Alt) },
		Category::EDITOR
	});
	BindManager::get()->registerBindable({
		"refresh-page"_spr,
		"Refresh Page",
		"Enables a keybind (set to Ctrl + R by default) to refresh the layer you're on.\n<cy>Use this keybind with caution; abusing/spamming this keybind can get you rate-limited or banned from RobTop's servers. By using this keybind for any reason, you agree to hold harmless the mod developer (RayDeeUx) or any lead developer of Geode and assume all responsibility for any consequences.</c>",
		{ Keybind::create(KEY_R, Modifier::Control) },
		Category::GLOBAL
	});
	BindManager::get()->registerBindable({
		"previous-page"_spr,
		"Go To Previous Page",
		"Enables a keybind (set to Alt + Left Arrow by default) to go to the previous page.\n\nBecause RobTop's infinite wisdom allowed him to implement this feature with the main levels (and level browsing menus) <cr>and literally nowhere else</c> in Geometry Dash.\n\n<cj>No, I'm not mad about this. What makes you think that?</c>",
		{ Keybind::create(KEY_Left, Modifier::Alt) },
		Category::GLOBAL
	});
	BindManager::get()->registerBindable({
		"next-page"_spr,
		"Go To Next Page",
		"Enables a keybind (set to Alt + Right Arrow by default) to go to the next page.\n\nBecause RobTop's infinite wisdom allowed him to implement this feature with the main levels (and level browsing menus) <cr>and literally nowhere else</c> in Geometry Dash.\n\n<cj>No, I'm not mad about this. What makes you think that?</c>",
		{ Keybind::create(KEY_Right, Modifier::Alt) },
		Category::GLOBAL
	});
	BindManager::get()->registerBindable({
		"first-page"_spr,
		"Go To First Page",
		"Enables a keybind (set to Shift + Left Arrow by default) to go to the first page.",
		{ Keybind::create(KEY_Left, Modifier::Shift) },
		Category::GLOBAL
	});
	BindManager::get()->registerBindable({
		"last-page"_spr,
		"Go To Last Page",
		"Enables a keybind (set to Shift + Right Arrow by default) to go to the last <cy>(estimated)</c> page.\n\n<cy>Results may be inaccurate.</c>",
		{ Keybind::create(KEY_Right, Modifier::Shift) },
		Category::GLOBAL
	});
	BindManager::get()->registerBindable({
		"like"_spr,
		"Like Content",
		"Enables a keybind (set to Left Arrow by default) to like content.",
		{ Keybind::create(KEY_Left) },
		Category::GLOBAL
	});
	BindManager::get()->registerBindable({
		"dislike"_spr,
		"Dislike Content",
		"Enables a keybind (set to Right Arrow by default) to dislike content.",
		{ Keybind::create(KEY_Right) },
		Category::GLOBAL
	});
	BindManager::get()->registerBindable({
		"comments"_spr,
		"View Comments",
		"Enables a keybind (set to Shift + C by default) to view comments (either for a specific profile or for a level).",
		{ Keybind::create(KEY_C, Modifier::Shift) },
		Category::GLOBAL
	});
	BindManager::get()->registerBindable({
		"erysedits-settings"_spr,
		"ErysEdits Settings",
		"Enables a keybind (set to Shift + Alt + Ctrl + E by default) to open the settings menu for ErysEdits.",
		{ Keybind::create(KEY_E, Modifier::Shift | Modifier::Alt | Modifier::Control) },
		Category::GLOBAL
	});
	BindManager::get()->registerBindable({
		"geode-mods-list"_spr,
		"Geode Mods List",
		"Enables a keybind (set to Shift + Alt + Ctrl + G by default) to open the Geode mods list.",
		{ Keybind::create(KEY_G, Modifier::Shift | Modifier::Alt | Modifier::Control) },
		Category::GLOBAL
	});
	BindManager::get()->registerBindable({
		"custom-keybinds"_spr,
		"Custom Keybinds",
		"Enables a keybind (set to Shift + Alt + Ctrl + K by default) to open your custom keybinds.",
		{ Keybind::create(KEY_K, Modifier::Shift | Modifier::Alt | Modifier::Control) },
		Category::GLOBAL
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
}
#endif