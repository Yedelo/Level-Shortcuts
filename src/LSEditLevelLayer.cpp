#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "LevelShortcuts.hpp"

#include <Geode/modify/EditLevelLayer.hpp>
class $modify(LSEditLevelLayer, EditLevelLayer) {
    $override
    bool init(GJGameLevel* p0) {
        if (!EditLevelLayer::init(p0)) return false;
        
        if (Mod::get()->getSettingValue<bool>("enabled")) {
            if (CCMenu* folderMenu = geode::cast::typeinfo_cast<CCMenu*>(getChildByID("folder-menu"))) {
                CircleButtonSprite* setShortcutSprite = CircleButtonSprite::createWithSprite("setShortcut.png"_spr);
                setShortcutSprite->setScale(1 / 1.26);
                CCMenuItemSpriteExtra* setShortcutButton = CCMenuItemSpriteExtra::create(setShortcutSprite, this, menu_selector(LSEditLevelLayer::onSetShortcut));
                setShortcutButton->setID("set-shortcut-button"_spr);
                folderMenu->addChild(setShortcutButton);
                folderMenu->updateLayout();
            }
        }
        
        return true;
    }
    
    void onSetShortcut(CCObject* sender) {
        setShortcut(EDITOR);
        Mod::get()->setSavedValue("editorLevelIndex", LocalLevelManager::get()->m_localLevels->indexOfObject(m_level));
    }
};