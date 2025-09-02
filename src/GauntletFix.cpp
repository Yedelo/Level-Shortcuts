#include "GauntletFix.hpp"

std::map<int, bool>* GauntletFix::levelMap = new std::map<int, bool>;

bool GauntletFix::isOpenedFromShortcut(int levelID) {
    return levelMap->contains(levelID) ? levelMap->at(levelID) : false;
}

void GauntletFix::setOpenedFromShortcut(int levelID, bool openedFromShortcut) {
    levelMap->insert_or_assign(levelID, openedFromShortcut);
};    