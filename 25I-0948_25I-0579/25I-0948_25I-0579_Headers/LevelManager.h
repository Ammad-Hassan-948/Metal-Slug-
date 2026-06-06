#pragma once

class PlayerSoldier;
class EntityManager;
class ProjectileManager;


class LevelManager {
public:
    static const int LVL_HEIGHT = 55;
    static const int LVL_WIDTH = 460;

    void generateLevel(int levelNum, char** lvl, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm);
    void generateDesign(char** lvl, const char* fileName, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm);

    int getSpawnCol() const { return spawnCol; }
    int getSpawnRow() const { return spawnRow; }

private:
    void clearLevel(char** lvl);
    int spawnCol = 0;
    int spawnRow = 0;
};
