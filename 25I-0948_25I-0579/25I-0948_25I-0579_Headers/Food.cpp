#include "Food.h"

Food::Food(float posX, float posY, int replenishAmmount) : Collectibles(posX, posY), replenishAmmount(replenishAmmount) {

	if (replenishAmmount == 3) {
		texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Turkey.png");
		setTexture(texture);
		int frames[] = { 1 };
		float timers[] = { 0.2f };
		animator = new Animator(&sprite, 1, frames, timers, 64);
	}
	else {
		texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Food.png");
		sprite.setTexture(texture);
		int frames[] = { 1 };
		float timers[] = { 0.2f };
		animator = new Animator(&sprite, 1, frames, timers, 32);
	}

	sprite.setScale(2, 2);

	animationRow[AnimationState::IDLE] = 0;

}

void Food::applyEffect(PlayerSoldier* p)
{
	if (p != nullptr)
		p->addSaturation(replenishAmmount);
}



