#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"Collider.h"
#include"Animator.h"
#include "Camera.h"

using namespace sf;
using namespace std;



// I have made this anim to do animations effectively i have given state to everything possible
// I had initially used enums but then i replaced them with static const ints so i do not need to change my other logic alot and this will act as 
// a shared memory for all entities to look for their animations if i had use const ints it would have created different memory for all entities
struct AnimationState {
	static const int IDLE = 0;
	static const int MOVE = 1;             // walking, flying, or sailing for other enemies
	static const int SHOOT = 2;            // simple horizontal shooting
	static const int SHOOT_UP = 3;
	static const int SHOOT_DOWN = 4;
	static const int MELEE = 5;            // melee attack 
	static const int THROW_GRENADE = 6;
	static const int SPECIAL_1 = 7;        // mummy respawn, prisoner free, submarine turn
	static const int SPECIAL_2 = 8;        // POW prisinor leaving gift, Energy beams
	static const int DIE = 9;              // Death or Vehicle Destroyed
	static const int CELEBRATE = 10;
	static const int PARATROOPER = 11;       // for the paratrooper state
	static const int TOTAL_STATES = 12;     // The size of our array!
};

class PlayerSoldier;


class EntityManager;

class Entity
{
protected:
	float positionX;
	float positionY;
	float velocityX;
	float velocityY;
	float gravity;
	float baseSpeed;
	
	//bool playerEntity;
	bool isAlive;
	bool onGround;
	bool visible;
	bool isDying;     // for death animation
	bool playerEntity;
	bool isMummy;

	Texture texture;
	Sprite sprite;
	// I have made a collider object directly as i will have all the data reuired to make it instantly and i can make an object for
	// it but in the case of animator i will not have all those arrays etc so i am making an Animator* and will make an object using
	// new later.
	Collider hitbox;
	Animator* animator;
	// now to keep a track of animation states i am making an array to hold all the info
	// this will use the integar value stored in my struct Animation State at TOTAL_STATES
	int animationRow[AnimationState::TOTAL_STATES];
	int currentAnimRow;
	// i am adding this to make sure that every new entity i make also goes in the manager
	EntityManager* manager;
public:
	Entity(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType);
	virtual ~Entity();
	bool getIsAlive()const;
	float getPositionX()const;
	float getPositionY()const;
	float getVelocityX()const;
	float getVelocityY()const;
	bool getOnGround()const;
	bool getVisible()const;
	Animator* getAnimator();
	float getBaseSpeed()const;
	void setOnGround(bool g);
	void setIsAlive(bool a);
	void setVisible(bool v);
	void setPositionX(float pos);
	void setPositionY(float pos);
	void setVelocityX(float vel);
	void setVelocityY(float vel);
	void setEntityManager(EntityManager* e);
	virtual void update(float passedTime) = 0;
	virtual void render(RenderWindow& window, Camera& cm) = 0;
	virtual void takeDamage(int amount, bool meleeAttack = false) {}
	virtual void setPlayer(PlayerSoldier* p) {};
	void applyGravity();
	void setTexture(const Texture& tex);
	void setScale(float scaleX, float scaleY);
	Collider& getHitbox();
	void doAnimation(int state);
	bool isPlayer();
	bool getIsMummy();
};

