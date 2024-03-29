#include <geode.custom-keybinds/include/Keybinds.hpp>
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
	Mod::get()->addCustomSetting<SectionSettingValue>("navigation", "none");
	#endif
	Mod::get()->addCustomSetting<SectionSettingValue>("misc", "none");
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
}
#endif