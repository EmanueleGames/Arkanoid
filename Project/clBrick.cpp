#include "clBrick.h"

clTexture clBrick::mBrickTexture;

clBrick::clBrick()
{
	//The X and Y position of the Brick
	mPosX = 0;
	mPosY = 0;

	//The Brick Type
	mType = eBrickType::BRICK_INACTIVE;  //defines also color

	//The Brick color
	mRed = 0;
	mGreen = 0;
	mBlue = 0;

	//Brick's collision box
	mBrickHitbox.x = mPosX;
	mBrickHitbox.y = mPosY;
	mBrickHitbox.w = BRICK_WIDTH;
	mBrickHitbox.h = BRICK_HEIGHT;

	//Load brick textures
	if (!clBrick::mBrickTexture.createFromFile(gRenderer, "data/brick_outlined_40x20.png"))
	{
		cout << "Brick image loading failed!" << endl;
	}
}

clBrick::~clBrick()
{
	mBrickTexture.freeTexture();
}

void clBrick::render()
{
	if (mType != eBrickType::BRICK_INACTIVE)
	{
		mBrickTexture.setColorModulation(mRed, mGreen, mBlue);
		mBrickTexture.render(gRenderer, mPosX, mPosY);
	}
}

bool clBrick::isActive()
{
	if (mType == eBrickType::BRICK_INACTIVE)
		return false;

	return true;
}

SDL_Rect clBrick::getHitbox()
{
	return mBrickHitbox;
}

void clBrick::set_inactive()
{
	mType = eBrickType::BRICK_INACTIVE;
}

void clBrick::set_parameters(int newX, int newY, eBrickType newType, int newRed, int newGreen, int newBlue)
{
	mPosX = newX;
	mPosY = newY;

	mType = newType;

	mRed   = newRed;
	mGreen = newGreen;
	mBlue  = newBlue;

	mBrickHitbox.x = mPosX;
	mBrickHitbox.y = mPosY;
	mBrickHitbox.w = BRICK_WIDTH;
	mBrickHitbox.h = BRICK_HEIGHT;
}

