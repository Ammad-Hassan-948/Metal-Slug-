#pragma once
#include "DamagableEntity.h"

class PlayerSoldier;
class ProjectileManager;

class Vehicle : public DamagableEntity
{
protected:
    PlayerSoldier* driver;
    bool isOccupied;
    float baseFireRate;
    float fireRateTimer;
    float secFireRateTimer;
    float damageTimer;
    int damageState;
public:
    Vehicle(float startX, float startY, float width, float height, float gravity, int hp, const char* name);
    virtual ~Vehicle() {}
    virtual void update(float passedTime) override;
    virtual void render(RenderWindow& window, Camera& cam) override;
    // to make it generic and calling jump and move on vehicle pointers easily regardeless of which vehicle
    virtual void jump() {}
    // This will also give a generic move logic with y movement for aerial enemies
    virtual void move(float dirX, float dirY, float passedTime) = 0;
  
    virtual void attack() = 0;
    virtual void secondaryAttack() = 0;
    
    virtual void updateMouse(sf::Vector2f targetPos);

    // to interect with the vehicle for player
    virtual void getOn(PlayerSoldier* p);
    virtual void leave();
    bool getIsOccupied()const;
    void setDriver(PlayerSoldier* p);
    void setProjectileManager(ProjectileManager* pm);

    int getDamageState()const;

    void takeDamage(int amount, bool meleeAttack = false) override;
    void die() override;
};
