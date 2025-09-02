#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "LevelShortcuts.hpp"

#include <Geode/modify/LevelInfoLayer.hpp>
class $modify(LSLevelInfoLayer, LevelInfoLayer) {
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;
		
		if (Mod::get()->getSettingValue<bool>("enabled")) {
			if (CCMenu* leftSideMenu = geode::cast::typeinfo_cast<CCMenu*>(getChildByID("left-side-menu"))) {
				CCSprite* setShortcutSprite = CCSprite::create("setShortcut.png"_spr);
				CCMenuItemSpriteExtra* setShortcutButton = CCMenuItemSpriteExtra::create(setShortcutSprite, this, menu_selector(LSLevelInfoLayer::onSetShortcut));
				setShortcutButton->setID("set-shortcut-button"_spr);
				leftSideMenu->addChild(setShortcutButton);
				leftSideMenu->updateLayout();
			}
		}
		
		return true;
	}
	
	void onSetShortcut(CCObject* sender) {
		if (int dailyWeeklyEventID = m_level->m_dailyID.value()) {
			setShortcut(DAILY_WEEKLY_EVENT);
			Mod::get()->setSavedValue("dailyWeeklyEventID", dailyWeeklyEventID);
		}
		else {
			setShortcut(m_level->m_gauntletLevel ? GAUNTLET : ONLINE);
			Mod::get()->setSavedValue("levelID", m_level->m_levelID.value());
		}
	}
};