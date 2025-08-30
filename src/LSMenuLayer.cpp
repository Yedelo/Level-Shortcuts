#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(LSMenuLayer, MenuLayer) {
    $override
    bool init() {
        if (!MenuLayer::init()) return false;
        
    
		if (CCMenu* rightSideMenu = geode::cast::typeinfo_cast<CCMenu*>(getChildByID("right-side-menu"))) {
			CircleButtonSprite* openShortcutSprite = CircleButtonSprite::createWithSprite("logo.png"_spr);
			CCMenuItemSpriteExtra* openShortcutButton = CCMenuItemSpriteExtra::create(openShortcutSprite, this, menu_selector(LSMenuLayer::openShortcut));
			openShortcutButton->setID("open-shortcut-button"_spr);
			rightSideMenu->addChild(openShortcutButton);
			rightSideMenu->updateLayout();
		}

        return true;
    }

    void openShortcut(CCObject* sender) {

    }
};