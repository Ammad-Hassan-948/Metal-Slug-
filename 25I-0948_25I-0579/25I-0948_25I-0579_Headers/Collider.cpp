#include "Collider.h"

Collider::Collider(float x, float y, float width, float height, float offsetX, float offsetY, int t): x(x), y(y), width(width),
height(height), offsetX(offsetX), offsetY(offsetY), colliderType(t) { }

float Collider::getX() const
{
	return x;
}

float Collider::getY() const
{
	return y;
}

float Collider::getWidth() const
{
	return width;
}

float Collider::getHeight() const
{
	return height;
}

float Collider::getOffsetX() const
{
	return offsetX;
}

float Collider::getOffsetY() const
{
	return offsetY;
}


int Collider::getType() const
{
	return colliderType;
}

void Collider::updateCoordinates(float changedX, float changedY)
{
	// take the changed x and y and save them by applying the offset to them
	x = changedX + offsetX;
	y = changedY + offsetY;
}


void Collider::resizeCollider(float newX, float newY, float newWidth, float newHeight, float newOffsetX, float newOffsetY, int t)
{
	x = newX;
	y = newY;
    width = newWidth;
	height = newHeight;
	offsetX = newOffsetX;
	offsetY = newOffsetY;
	colliderType = t;
}


bool Collider::checkCollision(const Collider& other) const
{
	// is my left edge to the left of right edge of other and if my right edge is to right of left edge of other
	bool collissionX = this->x < (other.x + other.width) && (this->x + this->width) > other.x;
	// is my top edge above the bottom edge of other and is my bottom edge below the top edge of other
	bool collissionY = this->y < (other.y + other.height) && (this->y + this->height) > other.y;
	// if both these conditions are fulfilled it means they are overlapping 
	return collissionX && collissionY;
}

void Collider::getIntersectionDepth(const Collider& other, float& overlappedX, float& overlappedY)
{
	// first find the x and y centres of both
	float thisCentreX = this->x + this->width / 2.0f;
	float thisCentreY = this->y + this->height / 2.0f;
	float otherCentreX = other.x + other.width / 2.0f;
	float otherCentreY = other.y + other.height / 2.0f;

	// now find the difference between their centres
	float distanceX = thisCentreX - otherCentreX;
	float distanceY = thisCentreY - otherCentreY;

	// now we also calculate the minimum safe ditance till which collission can be avoided
	float minDistanceX = this->width / 2.0f + other.width / 2.0f;
	float minDistanceY = this->height / 2.0f + other.height / 2.0f;

	// now to check if they are actually overlapping we compare our difference with found minimum distance
	if (abs(distanceX) < minDistanceX && abs(distanceY) < minDistanceY) {
		// this means they will be overlapping
		overlappedX = minDistanceX - abs(distanceX);
		overlappedY = minDistanceY - abs(distanceY);

		// also for the sign we will apply correct signs so we can move player on base of sign
		if (distanceX < 0)
			overlappedX = -overlappedX;
		if (distanceY < 0)
			overlappedY = -overlappedY;

	}
	else {
		// means they are not overlapping and our var will be 0
		overlappedX = 0.0f;
		overlappedY = 0.0f;
	}
}


