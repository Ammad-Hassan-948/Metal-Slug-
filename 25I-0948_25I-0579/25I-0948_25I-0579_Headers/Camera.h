#pragma once

class Camera {

	float screenWidth; float screenHeight;//the screen's fixed resolution
	float worldWidth; float worldHeight;//total level dimensions in pixels
	float offsetX; float offsetY;//the quantity the view needs to move to place a thing inside the screen

public:

	Camera(float screenW, float screenH, float worldW, float worldH) {
		offsetX = 0; offsetY = 0;
		screenHeight = screenH;
		screenWidth = screenW;
		worldHeight = worldH;
		worldWidth = worldW;
	}
	
	void follow(float targetX, float targetY) {
		offsetX = targetX - screenWidth / 2;
		offsetY = targetY - screenHeight / 2;
		//subtracting half screenHeight and width to shift the camera's view window 
		// so the player stays at the centre
		if (offsetX < 0) {
			offsetX = 0;
		}
		if (offsetY < 0) {
			offsetY = 0;
		}
		if (offsetX > worldWidth - screenWidth) {
			offsetX = worldWidth - screenWidth;
		}
		if (offsetY > worldHeight - screenHeight) {
			offsetY = worldHeight - screenHeight;
		}
	}

	float getOffsetX() const {
		return offsetX;

	}
	float getOffsetY() const {
		return offsetY;
	}

};
