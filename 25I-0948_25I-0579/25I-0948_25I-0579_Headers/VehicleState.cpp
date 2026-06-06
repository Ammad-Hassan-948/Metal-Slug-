#include "VehicleState.h"
#include "Vehicle.h"
#include "Soldier.h"
#include "NormalState.h"

using namespace sf;

VehicleState::VehicleState(Vehicle* v) : vehicle(v) {}

void VehicleState::enter(Soldier* soldier) {
    soldier->setVisible(false);

    // First i make the player invisible then make its coordinates same as those of the vehicle
    soldier->setPositionX(vehicle->getPositionX());
    soldier->setPositionY(vehicle->getPositionY());
}

void VehicleState::exit(Soldier* soldier) {
    soldier->setVisible(true);
    
    // exit the player from vehicle by making a slight jump effect
    soldier->setVelocityY(-10.0f);
    soldier->setOnGround(false);
}

void VehicleState::update(Soldier* soldier, float passedTime) {

    // In update i keep updating the soldier with respect to the location of vehicle
    if (vehicle != nullptr) {
        soldier->setPositionX(vehicle->getPositionX());
        soldier->setPositionY(vehicle->getPositionY());
        soldier->setVelocityX(0);
        soldier->setVelocityY(0);

        // Also to check for keys being pressed
        movement(soldier, passedTime);

        if (Keyboard::isKeyPressed(Keyboard::J)) {
            vehicle->attack();
        }
        if (Keyboard::isKeyPressed(Keyboard::K)) {
            vehicle->secondaryAttack();
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            jump(soldier);
        }
    }
}

void VehicleState::movement(Soldier* soldier, float passedTime) {

    // for the movement i have to pass directions of both x and y into the function of vehicle to move
    float dirX = 0, dirY = 0;
    if (Keyboard::isKeyPressed(Keyboard::A)) 
        dirX = -1;
    if (Keyboard::isKeyPressed(Keyboard::D)) 
        dirX = 1;
    if (Keyboard::isKeyPressed(Keyboard::W)) 
        dirY = -1;
    if (Keyboard::isKeyPressed(Keyboard::S)) 
        dirY = 1;
    
    vehicle->move(dirX, dirY, passedTime);
}

void VehicleState::attack(Soldier* soldier) {
    // I simply call the attack function of vehicle
    vehicle->attack();
}

void VehicleState::jump(Soldier* soldier) {
    // I am using the Up and a jump trick to leave the vehicle but if it is not pressing button for up the vehcile jumps simply if it can
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        // exit with normal state
        vehicle->leave();
        soldier->changeState(new NormalState());

    } else {
        vehicle->jump();
    }
}

void VehicleState::throwGrenade(Soldier* soldier) {
    // I am going to use this for vehicles which can attack in two ways
    vehicle->secondaryAttack();
}

void VehicleState::handleMouse(Soldier* s, Vector2f worldPos)
{
    if (vehicle != nullptr) {
        vehicle->updateMouse(worldPos);

    }
}



