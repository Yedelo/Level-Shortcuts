#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "LevelShortcuts.hpp"

void showError(std::string error);

#include <Geode/modify/MenuLayer.hpp>
class $modify(LSMenuLayer, MenuLayer) {
    $override
    bool init() {
        if (!MenuLayer::init()) return false;
        
        
        if (CCMenu* rightSideMenu = geode::cast::typeinfo_cast<CCMenu*>(getChildByID("right-side-menu"))) {
            CCSprite* openShortcutSprite = CCSprite::create("openShortcut.png"_spr);
            CCMenuItemSpriteExtra* openShortcutButton = CCMenuItemSpriteExtra::create(openShortcutSprite, this, menu_selector(LSMenuLayer::openShortcut));
            openShortcutButton->setID("open-shortcut-button"_spr);
            rightSideMenu->addChild(openShortcutButton);
            rightSideMenu->updateLayout();
        }
        
        return true;
    }
    
    void openShortcut(CCObject* sender) {
        int shortcutType = Mod::get()->getSavedValue("shortcut-type", 0);
        if (!shortcutType) {
            showError("No level shortcut found! Set one by entering a level screen and pressing the <cg>Set Shortcut</c> button.");
            return;
        }
        GJGameLevel* level;
        switch (shortcutType) {
            case ONLINE:
                int levelID = Mod::get()->getSavedValue(DATA_FOR_TYPE(ONLINE), 0);
                if (!levelID) {
                    showError("No level ID was found! What.");
                    return;
                }
                level = GameLevelManager::get()->getSavedLevel(levelID);
                if (!level) {
                    showError(fmt::format("No online level with ID {} was found! Perhaps the level was deleted?", levelID));
                    return;
                }
                break;
        }
        switchToScene(LevelInfoLayer::create(level, false));
    }
};

void showError(std::string error) {
    FLAlertLayer::create(
        "No Shortcut Found",
        error,
        "OK"
    )->show();
}