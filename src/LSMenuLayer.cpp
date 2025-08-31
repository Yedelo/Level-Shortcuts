#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "LevelShortcuts.hpp"

#include <Geode/modify/MenuLayer.hpp>
class $modify(LSMenuLayer, MenuLayer) {
    $override
    bool init() {
        if (!MenuLayer::init()) return false;
        
        if (Mod::get()->getSettingValue<bool>("enabled")) {
            if (CCMenu* rightSideMenu = geode::cast::typeinfo_cast<CCMenu*>(getChildByID("right-side-menu"))) {
                CCSprite* openShortcutSprite = CCSprite::create("openShortcut.png"_spr);
                CCMenuItemSpriteExtra* openShortcutButton = CCMenuItemSpriteExtra::create(openShortcutSprite, this, menu_selector(LSMenuLayer::onOpenShortcut));
                openShortcutButton->setID("open-shortcut-button"_spr);
                rightSideMenu->addChild(openShortcutButton);
                rightSideMenu->updateLayout();
            }
        }
        
        return true;
    }
    
    void onOpenShortcut(CCObject* sender) {
        openShortcut();
    }
};

