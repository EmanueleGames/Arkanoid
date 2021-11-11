#include "clPlayState.h"

using namespace std;

clPlayState::clPlayState()
{
    //Load cage textures
    if (!mBackground.createFromFile(gRenderer, "data/background02.png"))
    {
        cout << "Background image loading failed!" << endl;
    }
    //Load cage textures
    if (!mCage.createFromFile(gRenderer, "data/cage.png"))
    {
        cout << "Cage image loading failed!" << endl;
    }
    //Load lives textures
    if (!mLifeTexture.createFromFile(gRenderer, "data/ship01_mini.png"))
    {
        cout << "SpaceShip image loading failed!" << endl;
    }

    //Open LIVES and POINTS text font
    mFontSmaller = TTF_OpenFont("data/jabjai_light.ttf", 30);
    if (mFontSmaller == NULL)
    {
        cout << "Failed to load jabjai_light small font for Play screen! SDL_ttf Error: " << TTF_GetError() << endl;
    }
    mFontPoints = TTF_OpenFont("data/orange_juice2.ttf", 30);
    if (mFontSmaller == NULL)
    {
        cout << "Failed to load orange_juice2 small font for Play screen! SDL_ttf Error: " << TTF_GetError() << endl;
    }


    string messageAuthor = "LIVES";
    if (!mTextLives.createFromText(gRenderer, mFontSmaller, messageAuthor.c_str(), textColorWhite))
    {
        cout << "Unable to render LIVES text texture!" << endl;
    }

    string messageEnter = "POINTS";
    if (!mTextPoints.createFromText(gRenderer, mFontSmaller, messageEnter.c_str(), textColorWhite))
    {
        cout << "Unable to render POINTS text texture!" << endl;
    }

    //Load sound effects
    mLifeLost = Mix_LoadWAV("data/life_lost.wav");
    if (mLifeLost == NULL)
    {
        cout << "Failed to load Disk sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
    }
    else
    {
        Mix_VolumeChunk(mLifeLost, 20);
    }

    //Set the brick wall
    initialize_bricks();

    ticksCounter = 0;
    mNewBall = true;

    mLives = STARTING_LIVES;
    gPoints = 0;

}

clPlayState::~clPlayState()
{
    mBackground.freeTexture();
    mCage.freeTexture();
    mLifeTexture.freeTexture();

    TTF_CloseFont(mFontSmaller);
    mFontSmaller = NULL;
    mTextLives.freeTexture();
    mTextPoints.freeTexture();

    Mix_FreeChunk(mLifeLost);
    mLifeLost = NULL;
}

void clPlayState::handle_events()
{
    //Polling for a new event
    while (SDL_PollEvent(&gEvent))
    {
        //User requests to exit
        if (gEvent.type == SDL_QUIT)
        {
            set_next_state(eGameStates::STATE_EXIT);
        }
        
        //mBall.handleEvent(gEvent);
        mShip.handleEvent(gEvent);
    }
}

void clPlayState::logic()
{

    bool ball_lost = false;
    string string_points;

    //Calculate create texture for FPS
    calc_and_texture_FPS();

    //gives the player time before starting a new ball
    if (mNewBall)
    {
        if (ticksCounter > DELAY * 2)
        {
            mNewBall = false;
            ticksCounter = 0;
        }
        else
        {
            ticksCounter++;
        }
    }
    else
    {
        //Move the ball and check collision
        mBall.move(mShip.getHitbox(), mBricks, ball_lost);
        //Move the ship
        mShip.move();
        //update points
        string_points = std::to_string(gPoints);

        if (!mPointsNumber.createFromText(gRenderer, mFontPoints, string_points.c_str(), textColorWhite))
        {
            cout << "Unable to render Points value texture!" << endl;
        }

        //full clear
        if (gPoints >= 750)
        {
            set_next_state(eGameStates::STATE_GAME_OVER);
        }

        //life lost
        if (ball_lost)
        {
            mLives--;

            //play brick effect
            Mix_PlayChannel(-1, mLifeLost, 0);

            if (mLives == 0)
            {
                set_next_state(eGameStates::STATE_GAME_OVER);
            }
            else
            {
                mBall.reset();
                mShip.reset();

                // wait some time before resuming
                mNewBall = true;
            }
        }
    }
}

void clPlayState::render()
{
    //Clear the window (white color)
    SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 255);  //almost white
    SDL_RenderClear(gRenderer);

    //Show the background
    mBackground.render(gRenderer, 0, 0);

    //Show the cage
    mCage.render(gRenderer, CAGE_LEFT_MARGIN, 0);

    //Show the bricks
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            mBricks[i][j].render();
        }
    }

    //Show the ball
    mBall.render();
    //Show the player
    mShip.render();

    //Render Lives
    mTextLives.render(gRenderer, WINDOW_WIDTH - mTextLives.getWidth() - 10, 10);
    for (int i = 1; i <= mLives; i++)
    {
        mLifeTexture.render(gRenderer, WINDOW_WIDTH - 10 - (i * mLifeTexture.getWidth()), 50);
    }

    //Render Points
    mTextPoints.render(gRenderer, WINDOW_WIDTH - mTextPoints.getWidth() - 10, 95);
    mPointsNumber.render(gRenderer, WINDOW_WIDTH - mPointsNumber.getWidth() - 10, 135);

    //Average FPS
    gFPSTextTexture.render(gRenderer, 2, 0);
}

void clPlayState::initialize_bricks() {

    eBrickType type;
    Uint8 red;
    Uint8 green;
    Uint8 blue;

    for (int i = 0; i < 5; i++)
    {
        switch (i)
        {
        case 0:
            type = eBrickType::BRICK_METAL;
            red   = 200;
            green = 200;
            blue  = 200;
            break;
        case 1:
            type = eBrickType::BRICK_GREEN;
            red = 80;
            green = 200;
            blue = 80;
            break;
        case 2:
            type = eBrickType::BRICK_LIGHT_BLUE;
            red = 140;
            green = 140;
            blue = 200;
            break;
        case 3:
            type = eBrickType::BRICK_RED;
            red = 200;
            green = 100;
            blue = 100;
            break;
        case 4:
            type = eBrickType::BRICK_YELLOW;
            red = 230;
            green = 230;
            blue = 100;
            break;
        }

        for (int j = 0; j < 15; j++)
        {
            mBricks[i][j].set_parameters(MIN_X_POS + (j * 40), 100 + (i * 20), type, red, green, blue);
        }
    }
}