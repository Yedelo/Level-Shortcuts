# Level Shortcuts

Adds a shortcut to access different levels

## Developing

not much really
not anything at all
i learned that you can do this to open a level

```c++
int id = ...;
GJGameLevel* level = GameLevelManager::get()->getSavedLevel(id);
switchToScene(LevelInfoLayer::create(level, false));
```

i also used saved levels
and i had to use reverse engineering for a bit
also used a class properly (?) for the first time
that is about it
