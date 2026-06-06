#include "PowPrisoner.h"
#include"EntityManager.h"
#include"SupplyCrate.h"

PowPrisoner::PowPrisoner(float posX, float posY) : Collectibles(posX, posY) {
	// as it needs to stay in the game and does not dissapear after 15 seconds
	timer = -1.0f;

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Pow Prisoner.png");
	setTexture(texture);
	setScale(2.0f, 2.0f);

	int frames[] = { 5, 5, 4, 4 };
	float timers[] = { 0.2f, 0.3f, 0.3f, 0.3f };

	animator = new Animator(&sprite, 4, frames, timers, 64);

	animationRow[AnimationState::IDLE] = 0;       // tied up
	animationRow[AnimationState::SPECIAL_1] = 1;  // breaking the rope
	animationRow[AnimationState::SPECIAL_2] = 2;  // reaching to give gift
	animationRow[AnimationState::MOVE] = 3;       // running away

	currentAnimRow = AnimationState::IDLE;

}

void PowPrisoner::interact(PlayerSoldier* p)
{

	// here i will first do the thanking animation then call apply effect
	if (currentAnimRow == AnimationState::IDLE) {
		this->doAnimation(AnimationState::SPECIAL_1);
	}
}

void PowPrisoner::applyEffect(PlayerSoldier* p)
{

	// here i will do animation and then spawn a supply crate
	this->doAnimation(AnimationState::SPECIAL_2);


}

bool PowPrisoner::needsInput() const
{
	return true;
}

void PowPrisoner::spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr)
{
	PowPrisoner* p = new PowPrisoner(x, y);
	mgr->add(p);
}

void PowPrisoner::update(float passedTime)
{
	Collectibles::update(passedTime); // This handles gravity and lifespan

	if (animator == nullptr) return;

	// if the rope has broken and is on the last frame i will move it to animation 2 to gift
	if (currentAnimRow == AnimationState::SPECIAL_1 && animator->isLastFrame()) {

		this->doAnimation(AnimationState::SPECIAL_2);

		// here i will spawn the crate
		if (manager != nullptr) {
			manager->add(new SupplyCrate(positionX + 20, positionY));
		}
	}

	// now when the gift is given and animation is ended the player runs away
	else if (currentAnimRow == AnimationState::SPECIAL_2 && animator->isLastFrame()) {
		this->doAnimation(AnimationState::MOVE);
	}

	// If running animation is done diappear the prisoner making isAlive = false
	else if (currentAnimRow == AnimationState::MOVE) {
		positionX += 150.0f * passedTime; 
		if (animator->isLastFrame()) isAlive = false;
	}
}

