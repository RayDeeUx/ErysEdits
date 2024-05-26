#include <Geode/modify/PlayerObject.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyPlayerObject, PlayerObject) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
		const std::string globedModID = "dankmeme.globed2";
	};
	static void onModify(auto & self)
	{
		(void) self.setHookPriority("PlayerObject::playerDestroyed", INT32_MAX - 1);
	}
	bool detectGlobed(PlayLayer* pl) {
		if (Utils::getMod(m_fields->globedModID)) {
			if (const auto pingLabel = pl->getChildByIDRecursive(fmt::format("{}/ping-label", m_fields->globedModID))) {
				if (const auto pingLabelBMFont = typeinfo_cast<CCLabelBMFont*>(pingLabel)) {
					std::string pingLabelString = pingLabelBMFont->getString();
					return (pingLabelString != "Not connected" && pingLabelString != "N/A (Local level)");
				}
			} else if (const auto mainNode = pl->getChildByIDRecursive("main-node")) {
				if (const auto batchLayer = mainNode->getChildByIDRecursive("batch-layer")) {
					return MyPlayerObject::findGlobedChildren(batchLayer);
				} else {
					return MyPlayerObject::findGlobedChildren(mainNode);
				}
			}
		}
		return false;
	}
	bool findGlobedChildren(CCNode* node) {
		auto children = CCArrayExt<CCNode*>(node->getChildren());
		for (CCNode* child : children) {
			std::string childID = child->getID(); // normally i'd just put this in the if statement but getID() returns const char*
			if (childID.rfind(fmt::format("{}/remote-player-", m_fields->globedModID), 0) == 0) {
				return true;
			}
		}
		return false;
	}
	void playerDestroyed(bool p0) {
		m_fields->manager->isPlayerDead = true;
		if (Utils::modEnabled() && PlayLayer::get()) {
			if (Utils::getBool("forceStopMusicOnDeath")) {
				const auto pl = PlayLayer::get();
				const bool isGlobed = MyPlayerObject::detectGlobed(pl);
				const auto fmod = FMODAudioEngine::sharedEngine();
				if (!isGlobed) {
					fmod->pauseAllMusic();
				}
				if (this == pl->m_player2 && pl->m_level->m_twoPlayerMode) {
					PlayerObject::playerDestroyed(p0);
					return; // avoid stopping sfx twice -- thank you clicksounds
				} else {
					if (!isGlobed) {
						fmod->stopAllEffects();
					}
				}
			}
		}
		PlayerObject::playerDestroyed(p0);
	}
};