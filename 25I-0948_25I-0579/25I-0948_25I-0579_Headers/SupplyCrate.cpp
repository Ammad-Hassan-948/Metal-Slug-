#include"SupplyCrate.h"
#include"LaserGun.h"
#include"HeavyMachineGun.h"
#include"FlameShotGun.h"
#include"RocketLauncher.h"

SupplyCrate::SupplyCrate(float posX, float posY) : Collectibles(posX, posY) {

    // to make division on what would be stored inside
    int chance = rand() % 100;
    
    // this is the chance of laser gun being present inside crate
    if (chance < 10) {
        storedWeapon = new LaserGun(500);
    }
    // now we again use rand to check 3 more seperate guns
    else {
        // for all 3 weapons we again use rand and get the weapon       
        int weaponChance = rand() % 3;
        if (weaponChance == 0) 
            storedWeapon = new HeavyMachineGun(700);
        else if (weaponChance == 1) 
            storedWeapon = new FlameShotGun(500);
        else 
            storedWeapon = new RocketLauncher(200);
        
    } 

    grenadeCount = 3;         // base value of 3 use rand for more

    ammoCount = 100 + rand() % 200;

    texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Supply Crate.png");
    setTexture(texture);
    setScale(2.0f, 2.0f);

    int frames[] = { 1 };
    float timers[] = { 0.2f };

    animator = new Animator(&sprite, 1, frames, timers, 64);

    animationRow[AnimationState::IDLE] = 0;

}

SupplyCrate::~SupplyCrate()
{
    if (storedWeapon != nullptr) {
        delete storedWeapon;
        storedWeapon = nullptr;
    }
    isAlive = false;
}

bool SupplyCrate::needsInput() const
{
    return true;
}

void SupplyCrate::replenishAmmo(PlayerSoldier* p)
{
    if(p->getSpecialWeapon() != nullptr)
        p->getSpecialWeapon()->addAmmo(ammoCount);

    // also add grenades
    // now for grenades i will add a random number of grenades
    int numGrenades = grenadeCount + rand() % 3;

    p->addGrenades(numGrenades);

    isAlive = false;
}

void SupplyCrate::applyEffect(PlayerSoldier* p)
{
    if (storedWeapon != nullptr) {

        p->equipWeapon(storedWeapon);
        // make the stored weapon pointer null here
        storedWeapon = nullptr;

        // now for grenades i will add a random number of grenades
        int numGrenades = grenadeCount + rand() % 3;

        p->addGrenades(numGrenades);

        // also add ammo
        if (p->getSpecialWeapon() != nullptr)
            p->getSpecialWeapon()->addAmmo(ammoCount);

    }
    

    isAlive = false;
    
}

