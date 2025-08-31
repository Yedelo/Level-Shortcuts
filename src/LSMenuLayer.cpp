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
            case ONLINE: {
                int levelID = Mod::get()->getSavedValue(DATA_FOR_TYPE(ONLINE), 0);
                if (!levelID) {
                    showError("No level ID was found! What.");
                    return;
                }
                GJGameLevel* level = GameLevelManager::get()->getSavedLevel(levelID);
                if (!level) {
                    showError(fmt::format("No online level with ID {} was found! Perhaps the level was deleted?", levelID));
                    return;
                }
                switchToScene(LevelInfoLayer::create(level, false));
                break;
            }
            case EDITOR: {
                int levelIndex = Mod::get()->getSavedValue(DATA_FOR_TYPE(EDITOR), -1);
                if (levelIndex == -1) {
                    showError("No level index was found! What.");
                    return;
                } 
                GJGameLevel* level = geode::cast::typeinfo_cast<GJGameLevel*>(LocalLevelManager::get()->m_localLevels->objectAtIndex(levelIndex));
                if (!level) {
                    showError(fmt::format("No local level with index {} was found! Perhaps the level was deleted?", levelIndex));
                    return;
                }
                switchToScene(EditLevelLayer::create(level));
                break;
            }
        }
    
    }
};

void showError(std::string error) {
    FLAlertLayer::create(
        "No Shortcut Found",
        error,
        "OK"
    )->show();
}