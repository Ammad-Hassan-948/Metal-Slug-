#pragma once

class BlockType {
public:
    static const int AIR = 0;
    static const int BEDROCK = 1;
    static const int STONE = 2;
    static const int DIRT = 3;
    static const int GRASS = 4;
    static const int SAND = 5;
    static const int WATER = 6;
    static const int SNOW = 7;
    static const int COUNT = 8;
};

class Biome {
public:
    static const int AERIAL = 0;
    static const int PLAINS = 1;
    static const int AQUATIC = 2;
};

class ProfileKind {
public:
    static const int NORMAL = 0;
    static const int AMPLIFIED = 1;
    static const int FLAT = 2;
};

class EnemyType {
public:
    static const int REBEL_SOLDIER = 0;
    static const int SHIELDED_SOLDIER = 1;
    static const int BAZOOKA_SOLDIER = 2;
    static const int GRENADE_SOLDIER = 3;
    static const int MUMMY = 4;
    static const int ZOMBIE = 5;
    static const int MARTIAN = 6;
    static const int FLYING_TARA = 7;
    static const int ENEMY_SUB = 8;
    static const int IRON_NOKANA = 9;
    static const int M15A_BRADLEY = 10;
    static const int PARATROOPER = 11;
    static const int COUNT = 12;
};

class VehicleType {
public:
    static const int METAL_SLUG = 0;
    static const int SLUG_FLYER = 1;
    static const int SLUG_MARINER = 2;
    static const int AMPHIBIOUS_SLUG = 3;
    static const int COUNT = 4;
};


class CampaignConstants {
public:
    static const int CHUNK_WIDTH = 32;
    static const int WORLD_HEIGHT = 60;
    static const int SEA_LEVEL = 22;
    static const int VIEW_RADIUS = 6;
    static const int MAX_LOADED_CHUNKS = 15; //view radius
    static const int CELL_SIZE = 64;
    static const int ENEMY_KILL_QUOTA = 5;
    static const int VEHICLE_KILL_QUOTA = 3;
    static const int BLOCK_SIZE_PIXELS = 64;
};
