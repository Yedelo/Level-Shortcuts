#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "LevelShortcuts.hpp"
#include "GauntletFix.hpp"

#include <Geode/modify/LevelInfoLayer.hpp>
class $modify(LSLevelInfoLayer, LevelInfoLayer) {
	$override
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;
		
		if (Mod::get()->getSettingValue<bool>("enabled")) {
			if (CCMenu* leftSideMenu = geode::cast::typeinfo_cast<CCMenu*>(getChildByID("left-side-menu"))) {
				CircleButtonSprite* setShortcutSprite = CircleButtonSprite::createWithSprite("setShortcut.png"_spr);
				CCMenuItemSpriteExtra* setShortcutButton = CCMenuItemSpriteExtra::create(setShortcutSprite, this, menu_selector(LSLevelInfoLayer::onSetShortcut));
				setShortcutButton->setID("set-shortcut-button"_spr);
				leftSideMenu->addChild(setShortcutButton);
				leftSideMenu->updateLayout();
			}
		}
		
		return true;
	}

	$override
	void onBack(CCObject* sender) {
		if (m_level->m_gauntletLevel && GauntletFix::isOpenedFromShortcut(m_level->m_levelID)) {
			m_level->m_gauntletLevel = false;
			LevelInfoLayer::onBack(sender);
			m_level->m_gauntletLevel = true;
			GauntletFix::setOpenedFromShortcut(m_level->m_levelID, false);
		}
		else {
			LevelInfoLayer::onBack(sender);
		}
	}
	
	void onSetShortcut(CCObject* sender) {
		if (int dailyWeeklyEventID = m_level->m_dailyID.value()) {
			setShortcut(DAILY_WEEKLY_EVENT);
			Mod::get()->setSavedValue("daily-weekly-event-id", dailyWeeklyEventID);
		}
		else {
			setShortcut(m_level->m_gauntletLevel ? GAUNTLET : ONLINE);
			Mod::get()->setSavedValue("level-id", m_level->m_levelID.value());
		}
	}
};