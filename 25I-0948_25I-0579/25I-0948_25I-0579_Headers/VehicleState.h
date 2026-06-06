#pragma once
#include "TransformationState.h"

class Vehicle;

class VehicleState : public TransformationState
{
private:
    Vehicle* vehicle;

public:
    VehicleState(Vehicle* v);
    
    void enter(Soldier* soldier) override;
    void exit(Soldier* soldier) override;
    void update(Soldier* soldier, float passedTime) override;
    void movement(Soldier* soldier, float passedTime) override;
    void attack(Soldier* soldier) override;
    void jump(Soldier* soldier) override;
    void throwGrenade(Soldier* soldier)override;
    void handleMouse(Soldier* s, Vector2f worldPos);
};

