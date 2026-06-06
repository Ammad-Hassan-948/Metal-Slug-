#include "LevelManager.h"
#include "Helpers.h"
#include <iostream>
#include <fstream>
#include "RebelSoldier.h"
#include "ShieldedSoldier.h"
#include "Zombie.h"
#include "MummyWarrior.h"
#include "FlyingTara.h"
#include "MartianAir.h"
#include "MartianGround.h"
#include "PowPrisoner.h"
#include "EnemySub.h"
#include "BazookaSoldier.h"
#include "GrenadeSoldier.h"
#include "MetalSlug.h"
#include "SlugFlyer.h"
#include "SlugMariner.h"
#include"EntityManager.h"
#include"M15ABradley.h"
#include"Food.h"

void LevelManager::generateDesign(char** lvl, const char* fileName, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm) {
    clearLevel(lvl);
    if (!fileName || fileName[0] == '\0') return;

    std::ifstream file;
    
    // Attempt to open the file directly first
    file.open(fileName);
    
    // If it failed, try to find the filename by looking for the last slash
    if (!file.is_open()) {
        int lastSlash = -1;
        int len = getLength(fileName);
        for (int i = 0; i < len; i++) {
            if (fileName[i] == '/' || fileName[i] == '\\') {
                lastSlash = i;
            }
        }
        if (lastSlash != -1) {
            file.open(fileName + lastSlash + 1);
        }
    }

    // fallback to testing.txt if still not open
    if (!file.is_open()) {
        file.open("25I-0948_25I-0579/25I-0948_25I-0579_misc/testing.txt");
    }

    if (!file.is_open()) {
        std::cout << "LevelManager: FAILED to find " << fileName << std::endl;
        return;
    }

    std::cout << "LevelManager: Successfully loaded level design" << std::endl;

    char line[512];
    int row = 0;
    spawnCol = 3; // Default spawn
    spawnRow = 10;
    
    // Hardcoded cell size for coordinate calculation
    const float CELL_SIZE = 64.0f;

    while (file.getline(line, 512) && row < LVL_HEIGHT) {
        int lineLen = getLength(line);
        for (int col = 0; col < LVL_WIDTH; col++) {
            if (col < lineLen) {
                char c = line[col];
                float x = (float)col * CELL_SIZE;
                float y = (float)row * CELL_SIZE;

                if (c == 'P') {
                    spawnCol = col;
                    spawnRow = row;
                    lvl[row][col] = ' '; // Player is not a tile
                }
                else if (c == 'g' || c == 's' || c == '~' || c == '#') {
                    lvl[row][col] = c;
                }
                else if (c == 'R') {
                    if ((col > 0 && lvl[row][col - 1] == '~') || (row > 0 && lvl[row - 1][col] == '~')) {
                        lvl[row][col] = '~';
                    }
                    else {
                        lvl[row][col] = ' ';
                    }
                    RebelSoldier::spawn(x, y, player, mgr, pm, false);
                }
                else if (c == 'r') { // lowercase r for paratrooper
                    lvl[row][col] = ' ';
                    RebelSoldier::spawn(x, y, player, mgr, pm, true);
                }
                else if (c == 'n') { // lowercase g for paratrooper
                    if ((col > 0 && lvl[row][col - 1] == '~') || (row > 0 && lvl[row - 1][col] == '~')) {
                        lvl[row][col] = '~';
                    }
                    else {
                        lvl[row][col] = ' ';
                    }
                    GrenadeSoldier::spawn(x, y, player, mgr, pm, true);
                }
                else if (c == 'z') { // lowercase g for paratrooper
                    if ((col > 0 && lvl[row][col - 1] == '~') || (row > 0 && lvl[row - 1][col] == '~')) {
                        lvl[row][col] = '~';
                    }
                    else {
                        lvl[row][col] = ' ';
                    }
                    BazookaSoldier::spawn(x, y, player, mgr, pm, true);
                }
                else if (c == 'F') {
                    lvl[row][col] = ' ';
                    FlyingTara::spawn(x, y, player, mgr, pm);
                }
                else if (c == 'N') {
                    lvl[row][col] = '~';
                    EnemySub::spawn(x, y, player, mgr, pm);
                }
                else if (c == 'S') {
                    if ((col > 0 && lvl[row][col - 1] == '~') || (row > 0 && lvl[row - 1][col] == '~')) {
                        lvl[row][col] = '~';
                    }
                    else {
                        lvl[row][col] = ' ';
                    }
                    ShieldedSoldier::spawn(x, y, player, mgr, pm, false);
                }
                else if (c == 'Z') {
                    if ((col > 0 && lvl[row][col - 1] == '~') || (row > 0 && lvl[row - 1][col] == '~')) {
                        lvl[row][col] = '~';
                    }
                    else {
                        lvl[row][col] = ' ';
                    }
                    Zombie::spawn(x, y, player, mgr, pm);
                }
                else if (c == 'M') {
                    lvl[row][col] = ' ';
                    MummyWarrior::spawn(x, y, player, mgr, pm);
                }
                else if (c == 'T') {
                    lvl[row][col] = ' ';
                    FlyingTara::spawn(x, y, player, mgr, pm);
                }
                else if (c == 'A') {
                    lvl[row][col] = ' ';
                    MartianAir::spawn(x, y, player, mgr, pm);
                }
                else if (c == 'G') {
                    lvl[row][col] = ' ';
                    MartianGround::spawn(x, y, player, mgr, pm);
                }
                else if (c == 'B') {
                    lvl[row][col] = ' ';
                    BazookaSoldier::spawn(x, y, player, mgr, pm, false);
                }
                else if (c == 'V') {
                    lvl[row][col] = ' ';
                    GrenadeSoldier::spawn(x, y, player, mgr, pm, false);
                }
                else if (c == 'U') {
                    if ((col > 0 && lvl[row][col - 1] == '~') || (row > 0 && lvl[row - 1][col] == '~')) {
                        lvl[row][col] = '~'; 
                    }
                    else {
                        lvl[row][col] = ' ';
                    }
                    EnemySub::spawn(x, y, player, mgr, pm);
                }
                else if (c == 'X') { // P for Prisoner, renamed to X to avoid conflict with Player spawn
                    if ((col > 0 && lvl[row][col - 1] == '~') || (row > 0 && lvl[row - 1][col] == '~')) {
                        lvl[row][col] = '~';
                    }
                    else {
                        lvl[row][col] = ' ';
                    }
                    PowPrisoner::spawn(x, y, player, mgr);
                }
                else if (c == 't') {
                    lvl[row][col] = ' ';
                    MetalSlug* tank = new MetalSlug(x, y);
                    tank->setProjectileManager(pm);
                    mgr->add(tank);
                }
                else if (c == 'f') {
                    lvl[row][col] = ' ';
                    SlugFlyer* flyer = new SlugFlyer(x, y);
                    flyer->setProjectileManager(pm);
                    mgr->add(flyer);
                }
                else if (c == 'd') {
                    lvl[row][col] = ' ';
                    Food* food = new Food(x, y, 3);
                    mgr->add(food);
                }
                else if (c == 'r') {
                    lvl[row][col] = ' ';
                    Food* food = new Food(x, y, 2);
                    mgr->add(food);
                    }
                else if (c == 'b') {
                    if ((col > 0 && lvl[row][col - 1] == '~') || (row > 0 && lvl[row - 1][col] == '~')) {
                        lvl[row][col] = '~'; 
                    }
                    else {
                        lvl[row][col] = ' '; 
                    }
                    SlugMariner* sub = new SlugMariner(x, y);
                    sub->setProjectileManager(pm);
                    mgr->add(sub);
                }
                else if (c == 'm') {
                    lvl[row][col] = ' ';
                    M15ABradley* m = new M15ABradley(x, y, player);
                    m->setProjectileManager(pm);
                    mgr->add(m);
                }
                else {
                    lvl[row][col] = ' '; // everthing else is space
                }
            } 
            
            
            else {
                lvl[row][col] = ' ';
            }
        }
        row++;
    }
    file.close();
}

void LevelManager::generateLevel(int levelNum, char** lvl, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm) {
    clearLevel(lvl);

    const char* path = "25I-0948_25I-0579/25I-0948_25I-0579_misc/testing.txt";

    if (levelNum == 1) path = "25I-0948_25I-0579/25I-0948_25I-0579_misc/level1.txt";

    else if (levelNum == 2) path = "25I-0948_25I-0579/25I-0948_25I-0579_misc/level2.txt";

    else if (levelNum == 3) path = "25I-0948_25I-0579/25I-0948_25I-0579_misc/level3.txt";



    else if (levelNum == 4) path = "25I-0948_25I-0579/25I-0948_25I-0579_misc/Boss corrected.txt";

    generateDesign(lvl, path, player, mgr, pm);
}

void LevelManager::clearLevel(char** lvl) {
    for (int i = 0; i < LVL_HEIGHT; i++) {
        for (int j = 0; j < LVL_WIDTH; j++) {
            lvl[i][j] = ' ';
        }
    }
}

