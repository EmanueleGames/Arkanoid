#include "clBall.h"

clBall::clBall()
{
    //Initialize the position
    mPosX = BALL_STARTING_POS_X;
    mPosY = BALL_STARTING_POS_Y;

    //Set collision box position and dimension
    mBallHitbox.x = mPosX;
    mBallHitbox.y = mPosY;
    mBallHitbox.w = BALL_WIDTH;
    mBallHitbox.h = BALL_HEIGHT;

    //Initialize the velocity
    //X velocity between - STARTING_VEL_X_INTERVAL and + STARTING_VEL_X_INTERVAL
    int starting_vel_x;
    srand((unsigned int)time(NULL));
    starting_vel_x = rand() % (STARTING_VEL_X_INTERVAL*2 + 1);
    mVelX = starting_vel_x - STARTING_VEL_X_INTERVAL;
    //Y velocity is fixed
    mVelY = STARTING_VEL_Y;

    if (!mBallTexture.createFromFile(gRenderer, "data/ball.png"))
    {
        cout << "Ball image loading failed!" << endl;
    }

    //Load sound effects
    mBounce = Mix_LoadWAV("data/wall_bounce.wav");
    if (mBounce == NULL)
    {
        cout << "Failed to load Disk sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
    }
    else
    {
        Mix_VolumeChunk(mBounce, 2);
    }

    mBrickHit = Mix_LoadWAV("data/brick_hit.wav");
    if (mBrickHit == NULL)
    {
        cout << "Failed to load Error sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
    }
    else
    {
        Mix_VolumeChunk(mBrickHit, 40);
    }
}

clBall::~clBall()
{
    //Free texture if it exists
    mBallTexture.freeTexture();

    //Initialize the position
    mPosX = 0;
    mPosY = 0;

    //Set collision box dimension
    mBallHitbox.x = mPosX;
    mBallHitbox.y = mPosY;
    mBallHitbox.w = BALL_WIDTH;
    mBallHitbox.h = BALL_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 4;

    Mix_FreeChunk(mBounce);
    Mix_FreeChunk(mBrickHit);
    mBounce = NULL;
    mBrickHit = NULL;
}

void clBall::handleEvent(SDL_Event& event)
{
    // nothing here
}

void clBall::move(SDL_Rect shipHitbox, clBrick brick_grid[5][15], bool& ball_lost)
{
    int hitOffset;
    eBounceDirection direction;

    //Move the ball left or right
    mPosX += mVelX;
    mBallHitbox.x = mPosX;

    //If the ball collided or went too far to the left or right
    if ((mPosX < MIN_X_POS) || (mPosX + BALL_WIDTH > MAX_X_POS))
    {
        //Move back
        mPosX -= mVelX;
        mBallHitbox.x = mPosX;
        //invert velocity for bouncing effect
        mVelX = -mVelX;
        //play bounce effect
        Mix_PlayChannel(-1, mBounce, 0);
    }

    //Move the ball up or down
    mPosY += mVelY;
    mBallHitbox.y = mPosY;

    //If the ball collided or went too far up
    if (mPosY < MIN_Y_POS)
    {
        //Move back
        mPosY -= mVelY;
        mBallHitbox.y = mPosY;
        //invert velocity for bouncing effect
        mVelY = -mVelY;
        //play bounce effect
        Mix_PlayChannel(-1, mBounce, 0);
    }

    //The player missed the ball and lose a life
    if ((mPosY + BALL_HEIGHT > WINDOW_HEIGHT))
    {
        ball_lost = true;
    }

    //The player successfully hit the ball with the ship
    if (checkShipCollision(mBallHitbox, shipHitbox, hitOffset))
        
    {
        //Move back
        mPosY -= mVelY;
        mBallHitbox.y = mPosY;
        //invert velocity for bouncing effect
        mVelY = -mVelY;

        //play bounce effect
        Mix_PlayChannel(-1, mBounce, 0);

        //affect X velocity based on hit offset
        mVelX = mVelX + int(hitOffset / 4);
    }

    //Check the collision with the bricks
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            direction = eBounceDirection::NO_COLLISION;

            if (brick_grid[i][j].isActive() &&
                checkBrickCollision(mBallHitbox, brick_grid[i][j].getHitbox(), direction))
            {
                if (direction == eBounceDirection::BOUNCE_DOWN ||
                    direction == eBounceDirection::BOUNCE_UP)
                {
                    //Move back
                    mPosY -= mVelY;
                    mBallHitbox.y = mPosY;
                    //invert velocity for bouncing effect
                    mVelY = -mVelY;
                    //make the brick disappear
                    brick_grid[i][j].set_inactive();
                    //update points
                    gPoints = gPoints + BRICK_POINT_VALUE;
                    //play brick effect
                    Mix_PlayChannel(-1, mBrickHit, 0);
                }
                if (direction == eBounceDirection::BOUNCE_LEFT ||
                    direction == eBounceDirection::BOUNCE_RIGHT)
                {
                    //Move back
                    mPosX -= mVelX;
                    mBallHitbox.x = mPosX;
                    //invert velocity for bouncing effect
                    mVelX = -mVelX;
                    //make the brick disappear
                    brick_grid[i][j].set_inactive();
                    //update points
                    gPoints = gPoints + BRICK_POINT_VALUE;

                    //play brick effect
                    Mix_PlayChannel(-1, mBrickHit, 0);
                }
            }
        }
    }

    //Limit the horizontal velocity
    limit_velocity(mVelX);
}

void clBall::render()
{
    //Show the Ball
    mBallTexture.render(gRenderer, mPosX, mPosY);
}

void clBall::reset()
{
    //Initialize the position
    mPosX = BALL_STARTING_POS_X;
    mPosY = BALL_STARTING_POS_Y;

    //Set collision box position and dimension
    mBallHitbox.x = mPosX;
    mBallHitbox.y = mPosY;
    mBallHitbox.w = BALL_WIDTH;
    mBallHitbox.h = BALL_HEIGHT;

    //Initialize the velocity
    //X velocity between - STARTING_VEL_X_INTERVAL and + STARTING_VEL_X_INTERVAL
    int starting_vel_x;
    srand((unsigned int)time(NULL));
    starting_vel_x = rand() % (STARTING_VEL_X_INTERVAL * 2 + 1);
    mVelX = starting_vel_x - STARTING_VEL_X_INTERVAL;
    //Y velocity is fixed
    mVelY = STARTING_VEL_Y;
}

void clBall::free()
{
    this->~clBall();
}

bool checkShipCollision(SDL_Rect ballHitbox, SDL_Rect shipHitbox, int& offset)
{
    offset = 0;

    //The sides of the Ball
    int leftBall, rightBall, topBall, lowerBall;
    leftBall    = ballHitbox.x;
    rightBall   = ballHitbox.x + ballHitbox.w;
    topBall     = ballHitbox.y;
    lowerBall   = ballHitbox.y + ballHitbox.h;

    //The sides of the Ship
    int leftShip, rightShip, topShip, lowerShip;
    leftShip    = shipHitbox.x;
    rightShip   = shipHitbox.x + shipHitbox.w;
    topShip     = shipHitbox.y;
    lowerShip   = shipHitbox.y + shipHitbox.h;

    if (leftShip < rightBall - SHIP_TOLERANCE && leftBall + SHIP_TOLERANCE < rightShip)
    {
        if (lowerBall > topShip && (lowerBall - topShip) < 15)
        {
            //we want to know the relative position of the ball when it is hit by the ship
            offset = (leftBall + (ballHitbox.w / 2)) - (leftShip + (shipHitbox.w / 2));
            return true;
        }
    }
    return false;
}

bool checkBrickCollision(SDL_Rect ballHitbox, SDL_Rect brickHitbox, eBounceDirection& direction)
{
    //The sides of the Ball
    int leftBall, rightBall, topBall, lowerBall;
    leftBall = ballHitbox.x;
    rightBall = ballHitbox.x + ballHitbox.w;
    topBall = ballHitbox.y;
    lowerBall = ballHitbox.y + ballHitbox.h;

    //The sides of the Ship
    int leftBrick, rightBrick, topBrick, lowerBrick;
    leftBrick = brickHitbox.x;
    rightBrick = brickHitbox.x + brickHitbox.w;
    topBrick = brickHitbox.y;
    lowerBrick = brickHitbox.y + brickHitbox.h;

    //Check vertical collision
    if (leftBrick < rightBall - BRICK_TOLERANCE && leftBall + BRICK_TOLERANCE < rightBrick)
    {
        if (topBall < lowerBrick && (lowerBrick - topBall) < 10) //ball going up
        {
            direction = eBounceDirection::BOUNCE_DOWN;
            return true;
        }
        if (lowerBall > topBrick && (lowerBall - topBrick) < 10) //ball going down
        {
            direction = eBounceDirection::BOUNCE_UP;
            return true;
        }
    }

    //Check horizontal collision
    if (topBrick < lowerBall - BRICK_TOLERANCE && topBall + BRICK_TOLERANCE < lowerBrick)
    {
        if (leftBall < rightBrick && (rightBrick - leftBall) < 10) //ball going left
        {
            direction = eBounceDirection::BOUNCE_RIGHT;
            return true;
        }
        if (rightBall > leftBrick && (rightBall - leftBrick) < 10) //ball going right
        {
            direction = eBounceDirection::BOUNCE_LEFT;
            return true;
        }
    }


    return false;
}

void limit_velocity(int& velX)
{
    if (velX > MAX_VEL_X)
    {
        velX = MAX_VEL_X;
    }
    if (velX < -MAX_VEL_X)
    {
        velX = -MAX_VEL_X;
    }
}
