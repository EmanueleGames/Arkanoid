#pragma once

#include "constants.h"
#include "globals.h"

class clSpaceShip
{
	private:

		//The X and Y position of the Ship
		int mPosX, mPosY;
		//The velocity of the Ship
		int mVelX;
		//Ship's texture
		clTexture mShipTexture;
		//Ship's collision box
		SDL_Rect mShipHitbox;

	public:

		//Max axis velocity
		static const int SHIP_VEL = 10;

		//Constructor
		clSpaceShip();
		//Destructor
		~clSpaceShip();

		//utility functions
		SDL_Rect getHitbox();
		void reset();
		void free();

		//Handling functions
		void handleEvent(SDL_Event& event);
		void move();
		void render();
};

