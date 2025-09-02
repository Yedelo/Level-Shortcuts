#pragma once

class GauntletFix {
private:
    static std::map<int, bool>* levelMap;
public:
    static bool isOpenedFromShortcut(int levelID);
    static void setOpenedFromShortcut(int levelID, bool openedFromShortcut);
};