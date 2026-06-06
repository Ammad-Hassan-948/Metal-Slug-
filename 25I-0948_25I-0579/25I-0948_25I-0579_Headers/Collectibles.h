#pragma once
#include"Entity.h"
#include"PlayerSoldier.h"

class Collectibles : public Entity
{
protected:
	float timer;
public:
	Collectibles(float posX, float posY);
	void update(float passedTime);
	virtual void interact(PlayerSoldier* p);
	virtual void applyEffect(PlayerSoldier* p) = 0;
	virtual bool needsInput()const;
	void render(RenderWindow& window, Camera& cam)override;
};

