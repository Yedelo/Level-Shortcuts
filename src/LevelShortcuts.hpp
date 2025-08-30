#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

#define ONLINE 1

#define STRINGIFY(x) #x
#define STRING(x) STRINGIFY(x)
#define DATA_FOR_TYPE(type) "data-for-type-" STRING(type)

inline void setShortcut(int type, auto data) {
    Mod::get()->setSavedValue("shortcut-type", type);
    Mod::get()->setSavedValue(DATA_FOR_TYPE(ONLINE), data);
    FLAlertLayer::create(
        "Level Shortcut Saved",
        fmt::format("Saved this level as the level shortcut! (shortcut type {} -> {})", type, data),
        "OK"
    )->show();
};