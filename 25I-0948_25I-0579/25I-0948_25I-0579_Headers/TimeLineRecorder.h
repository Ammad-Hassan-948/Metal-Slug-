#pragma once

struct GameSnapShot {
	float playerX; 
	float playerY;
	int playerHp;

	//need to add more here
};

class TimeLineRecorder {
	GameSnapShot* buffer;
	int writeIndex;
	static const int Capacity = 600;

public:
	TimeLineRecorder() {
		buffer = new GameSnapShot[Capacity];
		writeIndex = 0;
	}

	~TimeLineRecorder() {
		delete[] buffer;
	}

	void recordFrame(const GameSnapShot& snap) {
		buffer[writeIndex] = snap;
		writeIndex = (writeIndex + 1) % Capacity;
	}


	//need to add rewind/ branching later
};