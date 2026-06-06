#pragma once
#include<iostream>


// I have used a struct collider type to keep track of which type of entity is this to do colliding effectively

struct ColliderType {
	static const int Player = 0;
	static const int Enemy = 1;
	static const int PlayerBullet = 2;
	static const int EnemyBullet = 3;
	static const int World = 4;
	static const int Collectibles = 5;
	static const int Vehicle = 6;
	static const int FirePool = 7;
};


class Collider
{
private:
	float x;
	float y;
	float width;
	float height;
	float offsetX;
	float offsetY;
	int colliderType;

public:
	Collider(float x, float y, float width, float height, float offsetX, float offsetY, int t);
	float getX()const;
	float getY()const;
	float getWidth()const;
	float getHeight()const;
	float getOffsetX() const;
	float getOffsetY() const;
	int getType()const;
	void updateCoordinates(float changedX, float changedY);
	void resizeCollider(float newX, float newY, float newWidth, float newHeight, float newOffsetX, float newOffsetY, int t);
	bool checkCollision(const Collider& other)const;
	// this function is to make sure that our player get does not stuck in the blocks or walls, if it does this function gets 
	// the exact coordinates that have overlapped and stores them in these two variables
	void getIntersectionDepth(const Collider& other, float& overlappedX, float& overlappedY);
};

