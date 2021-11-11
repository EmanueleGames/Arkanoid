#include "clSpaceShip.h"

clSpaceShip::clSpaceShip()
{
    //Initialize the position
    mPosX = SHIP_STARTING_POS_X;
    mPosY = SHIP_STARTING_POS_Y;

    //Set collision box position and dimension
    mShipHitbox.x = mPosX;
    mShipHitbox.y = mPosY;
    mShipHitbox.w = SHIP_WIDTH;
    mShipHitbox.h = SHIP_HEIGHT;

    //Initialize the velocity
    mVelX = 0;

    if (!mShipTexture.createFromFile(gRenderer, "data/ship01.png"))
    {
        cout << "SpaceShip image loading failed!" << endl;
    }
}

clSpaceShip::~clSpaceShip()
{
    //Free texture if it exists
    mShipTexture.freeTexture();

    //Set collision box dimension
    mShipHitbox.x = mPosX;
    mShipHitbox.y = mPosY;
    mShipHitbox.w = SHIP_WIDTH;
    mShipHitbox.h = SHIP_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
}

void clSpaceShip::handleEvent(SDL_Event& event)
{
    //If a key was pressed
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        //Adjust the velocity
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT: mVelX -= SHIP_VEL; break;
        case SDLK_RIGHT: mVelX += SHIP_VEL; break;
        }
    }
    //If a key was released
    else if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        //Adjust the velocity
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT: mVelX += SHIP_VEL; break;
        case SDLK_RIGHT: mVelX -= SHIP_VEL; break;
        }
    }
}

void clSpaceShip::move()
{
    //Move the ball left or right
    mPosX += mVelX;
    mShipHitbox.x = mPosX;

    //If the ball collided or went too far to the left or right
    if ((mPosX < MIN_X_POS) || (mPosX + SHIP_WIDTH > MAX_X_POS))// || checkCollision(mCollider, wall))
    {
        //Move back
        mPosX -= mVelX;
        mShipHitbox.x = mPosX;
    }
}

void clSpaceShip::render()
{
    //Show the Ball
    mShipTexture.render(gRenderer, mPosX, mPosY);
}

void clSpaceShip::reset()
{
    //Initialize the position
    mPosX = SHIP_STARTING_POS_X;
    mPosY = SHIP_STARTING_POS_Y;

    //Set collision box position and dimension
    mShipHitbox.x = mPosX;
    mShipHitbox.y = mPosY;
    mShipHitbox.w = SHIP_WIDTH;
    mShipHitbox.h = SHIP_HEIGHT;
}

void clSpaceShip::free()
{
    this->~clSpaceShip();
}

SDL_Rect clSpaceShip::getHitbox()
{
    return mShipHitbox;
}