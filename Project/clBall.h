#pragma once

#include <time.h>

#include "constants.h"
#include "globals.h"
#include "clBrick.h"

enum class eBounceDirection
{
	NO_COLLISION,
	BOUNCE_UP,
	BOUNCE_DOWN,
	BOUNCE_LEFT,
	BOUNCE_RIGHT,
};

//Avoid having a ball moving too fast
void limit_velocity(int& velX);
//Ship collision detector
bool checkShipCollision(SDL_Rect ballHitbox, SDL_Rect shipHitbox, int& offset);
//Brick collision detector
bool checkBrickCollision(SDL_Rect ballHitbox, SDL_Rect brickHitbox, eBounceDirection& direction);

class clBall
{
	private:

		//The X and Y position of the Ball
		int mPosX, mPosY;
		//The velocity of the Ball
		int mVelX, mVelY;
		//Ball's texture
		clTexture mBallTexture;
		//Ball's collision box
		SDL_Rect mBallHitbox;

		//Sounds
		Mix_Chunk* mBounce;
		Mix_Chunk* mBrickHit;

	public:

		//Constructor
		clBall();
		//Destructor
		~clBall();

		//utility functions
		void reset();
		void free();

		//Handling functions
		void handleEvent(SDL_Event& event);
		void move(SDL_Rect shipHitbox, clBrick brick_grid[5][15], bool& ball_lost);
		void render();

};

