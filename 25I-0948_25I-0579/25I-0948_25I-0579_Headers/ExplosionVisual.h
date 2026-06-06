#pragma once
#include "Entity.h"

class ExplosionVisual : public Entity {
public:
    ExplosionVisual(float x, float y, float radius);
    void update(float passedTime) override;
    void render(sf::RenderWindow& window, Camera& cam) override;
};
