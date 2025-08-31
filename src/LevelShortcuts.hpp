#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

#define ONLINE 1
#define EDITOR 2

#define STRINGIFY(x) #x
#define STRING(x) STRINGIFY(x)
#define DATA_FOR_TYPE(type) "data-for-type-" STRING(type)

void showError(std::string error);

inline void setShortcut(int type, auto data) {
    Mod::get()->setSavedValue("shortcut-type", type);
    Mod::get()->setSavedValue(fmt::format("data-for-type-{}", type), data);
    FLAlertLayer::create(
        "Level Shortcut Saved",
        fmt::format("Saved this level as the level shortcut! (shortcut type {} -> {})", type, data),
        "OK"
    )->show();
};

inline void openShortcut() {
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

inline void showError(std::string error) {
    FLAlertLayer::create(
        "No Shortcut Found",
        error,
        "OK"
    )->show();
}