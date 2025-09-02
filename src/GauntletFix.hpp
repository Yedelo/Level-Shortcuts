#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class GauntletFix {
private:
    static std::map<int, bool>* levelMap;
public:
    static bool isOpenedFromShortcut(int levelID);
    static void setOpenedFromShortcut(int levelID, bool openedFromShortcut);
};