#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
class $modify(LSLevelInfoLayer, LevelInfoLayer) {
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;

		if (CCMenu* leftSideMenu = geode::cast::typeinfo_cast<CCMenu*>(getChildByID("left-side-menu"))) {
			CCSprite* setShortcutSprite = CCSprite::create("setShortcut.png"_spr);
			CCMenuItemSpriteExtra* setShortcutButton = CCMenuItemSpriteExtra::create(setShortcutSprite, this, menu_selector(LSLevelInfoLayer::setShortcut));
			setShortcutButton->setID("set-shortcut-button"_spr);
			leftSideMenu->addChild(setShortcutButton);
			leftSideMenu->updateLayout();
		}

		return true;
	}

	void setShortcut(CCObject* sender) {
		log::info("setShortcut");
	}
};