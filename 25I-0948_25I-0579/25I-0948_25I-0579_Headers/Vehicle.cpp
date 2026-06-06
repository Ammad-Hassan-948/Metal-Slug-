#include "Vehicle.h"
#include "PlayerSoldier.h"
#include "VehicleState.h"
#include "ProjectileManager.h"
#include"NormalState.h"

Vehicle::Vehicle(float startX, float startY, float width, float height, float gravity, int hp, const char* name)
    : DamagableEntity(startX, startY, 0.0f, 0.0f, gravity, width, height, 0.0f, -40.0f, ColliderType::Vehicle, hp, name),
      driver(nullptr), isOccupied(false), baseFireRate(1.0f), fireRateTimer(0.1f), secFireRateTimer(0.6f), damageState(0), damageTimer(1.0f) { }

void Vehicle::update(float passedTime) 
{
    if (isDying) {
        if (animator) {
            animator->update(passedTime);
            if (animator->isLastFrame()) {
                isAlive = false;
            }
        }
        return;
    }

    fireRateTimer -= passedTime;
    secFireRateTimer -= passedTime;

    if (damageState > 0) {
        damageTimer -= passedTime;

        if (damageTimer <= 0.0f) {
            damageState = 0;
        }
    }

    hitbox.updateCoordinates(positionX, positionY);

    positionX += velocityX;
    positionY += velocityY;

    if (animator) {
        if (direction == -1)
            animator->setFlipDir(true);
        else
            animator->setFlipDir(false);

        animator->update(passedTime);
    }
    
    // if the vehicle is occupied and has a driver it should update the player with it
    if (isOccupied && driver) {
        driver->setPositionX(positionX);
        driver->setPositionY(positionY);
    }
}

void Vehicle::render(RenderWindow& window, Camera& cam) 
{
    if (!visible) return;
    sprite.setPosition(positionX - cam.getOffsetX(), positionY - cam.getOffsetY());
    window.draw(sprite);
}

void Vehicle::updateMouse(sf::Vector2f targetPos)
{
    float centreX = positionX + hitbox.getWidth() / 2.0f;
    float centreY = positionY + hitbox.getHeight() / 2.0f;

    // now for distance from the target position on the mouse
    float distanceX = targetPos.x - centreX;
    float distanceY = targetPos.y - centreY;

    // for the perfect aim angle, using -distanceY as screen and math coordinates are different
    aimAngle = atan2(-distanceY, distanceX) * (180.0f / 3.14159f);
}

void Vehicle::getOn(PlayerSoldier* p)
{
    if (!isOccupied && !isDying) {
        driver = p;
        isOccupied = true;
        
        // Apply character bonuses
        this->fireRate = baseFireRate * p->getVehicleFireRateMultiplier();
       
        // Change player state to vehicle state
        p->changeState(new VehicleState(this));
    }
}

void Vehicle::leave() 
{
    if (isOccupied && driver) {
        isOccupied = false;
        // The driver's state will be changed back to NormalState by VehicleState::exit
        driver = nullptr;
    }
}

bool Vehicle::getIsOccupied() const
{
    return isOccupied;
}

void Vehicle::setDriver(PlayerSoldier* p)
{
    driver = p;
    if (p == nullptr)
        isOccupied = false;
    else
        isOccupied = true;
}

void Vehicle::setProjectileManager(ProjectileManager* pm)
{
    // This is a base implementation, child classes like MetalSlug 
    // will override this or we can add weapon members here if needed.
}

int Vehicle::getDamageState() const
{
    return damageState;
}

void Vehicle::takeDamage(int amount, bool meleeAttack)
{
    if (isDying) return;

    damageState++;
    damageTimer = 1.0f;

    if (damageState > 2) {
        die();
    }
}

void Vehicle::die()
{
    if (!isDying) {
        isDying = true;
        doAnimation(AnimationState::DIE);
        if (isOccupied && driver) {
            driver->changeState(new NormalState());
            leave();
        }
    }
}

