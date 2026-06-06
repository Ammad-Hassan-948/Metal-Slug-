#include "Collectibles.h"

Collectibles::Collectibles(float posX, float posY) : Entity(posX, posY, 0.0f, 0.0f, 0.6f, 32, 32, 0, 0, ColliderType::Collectibles), timer(10.0f) {}

void Collectibles::update(float passedTime)
{
	applyGravity();

	positionY += velocityY;

	animator->update(passedTime);

	hitbox.updateCoordinates(positionX, positionY);

	if (timer == -1.0f)
		return;

	timer -= passedTime;

	if (timer <= 0.0f)
		isAlive = false;
}

void Collectibles::interact(PlayerSoldier* p)
{
	// i will override this in pow prisinor to apply the thankyou animation otherwise apply effect simply
	applyEffect(p);
	isAlive = false;
}

bool Collectibles::needsInput() const
{
	// override this in pow prisinor so that it does not disappear on screen
	return false;
}

void Collectibles::render(RenderWindow& window, Camera& cam)
{
	sprite.setPosition(positionX - cam.getOffsetX(), positionY - cam.getOffsetY());
	window.draw(sprite);
}
