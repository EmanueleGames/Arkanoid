#pragma once

#include "constants.h"
#include "globals.h"

enum class eBrickType
{
	BRICK_INACTIVE,
	BRICK_YELLOW,
	BRICK_RED,
	BRICK_LIGHT_BLUE,
	BRICK_GREEN,
	BRICK_METAL,
	BRICK_METAL_CRACKED,
};

class clBrick
{
	private:

		//The X and Y position of the Brick
		int mPosX, mPosY;
		//The Brick type
		eBrickType mType;
		//The Brick color
		int mRed, mGreen, mBlue;
		//Ball's collision box
		SDL_Rect mBrickHitbox;

		//static texture for all the bricks
		static clTexture mBrickTexture;

	public:

		//Constructor
		clBrick();
		//Destructor
		~clBrick();

		//utility functions
		bool isActive();
		SDL_Rect getHitbox();
		void set_inactive();
		void set_parameters(int newX, int newY, eBrickType newType, int newRed, int newGreen, int newBlue);

		//Handling functions
		void render();
};

