#include "ExplosionVisual.h"
#include <iostream>

ExplosionVisual::ExplosionVisual(float x, float y, float radius) :
    Entity(x - radius, y - radius, 0.0f, 0.0f, 0.0f, radius * 2.0f, radius * 2.0f, 0.0f, 0.0f, ColliderType::World) {
    
    if (!texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Fire Bomb Explosive.png")) {
        std::cout << "ExplosionVisual: Failed to load texture" << std::endl;
    }
    sprite.setTexture(texture);
    
    // setting the scale of this sprite according to the blast radius
    float scale = (radius * 2.0f) / 64.0f; 
    sprite.setScale(scale, scale);

    int frames[] = { 5 }; // 10 frames for explosion
    float timers[] = { 0.1f };

    animator = new Animator(&sprite, 1, frames, timers, 64);
    
    animationRow[AnimationState::IDLE] = 0;
    currentAnimRow = AnimationState::IDLE;
    
    animator->setState(0);
}

void ExplosionVisual::update(float passedTime) {
    if (animator) {

        // update the animations and check for last frame
        animator->update(passedTime);
        
        if (animator->isLastFrame()) {

            setIsAlive(false);
        }
    }
}

void ExplosionVisual::render(sf::RenderWindow& window, Camera& cam) {

    sprite.setPosition(positionX - cam.getOffsetX(), positionY - cam.getOffsetY());
    window.draw(sprite);

}

