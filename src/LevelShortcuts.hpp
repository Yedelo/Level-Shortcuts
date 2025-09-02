#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

#define ONLINE 1
#define EDITOR 2
#define DAILY_WEEKLY_EVENT 3
#define GAUNTLET 4

#include "GauntletFix.hpp"

void showError(std::string error);

inline void setShortcut(int type) {
    Mod::get()->setSavedValue("shortcut-type", type);
    FLAlertLayer::create(
        "Level Shortcut Saved",
        fmt::format("Saved this level as the level shortcut! (shortcut type {})", type),
        "OK"
    )->show();
};

inline void openShortcut() {
    int shortcutType = Mod::get()->getSavedValue("shortcut-type", -1);
        if (shortcutType == -1) {
            showError("No level shortcut found! Set one by entering a level screen and pressing the <cg>Set Shortcut</c> button.");
            return;
        }
        switch (shortcutType) {
            case ONLINE: {
                int levelID = Mod::get()->getSavedValue("levelID", -1);
                if (levelID == -1) {
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
                int levelIndex = Mod::get()->getSavedValue("editorLevelIndex", -1);
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
            case DAILY_WEEKLY_EVENT: {
                int dailyWeeklyEventID = Mod::get()->getSavedValue("dailyWeeklyEventID", -1);
                if (dailyWeeklyEventID == -1) {
                    showError("No daily/weekly/event ID was found! What.");
                    return;
                }
                GJGameLevel* level = GameLevelManager::get()->getSavedDailyLevel(dailyWeeklyEventID);
                if (!level) {
                    showError(fmt::format("No daily/weekly/event level with id {} was found!", dailyWeeklyEventID));
                    return;
                }
                switchToScene(LevelInfoLayer::create(level, false));
                break;
            }
            case GAUNTLET: {
                int levelID = Mod::get()->getSavedValue("levelID", -1);
                if (levelID == -1) {
                    showError("No level ID was found! What.");
                    return;
                }
                GJGameLevel* level = GameLevelManager::get()->getSavedGauntletLevel(levelID);
                if (!level) {
                    showError(fmt::format("No gauntlet level found with ID {}!", levelID));
                }
                LevelInfoLayer* layer = LevelInfoLayer::create(level, false);
                doGauntletFix(layer);
                switchToScene(layer);
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