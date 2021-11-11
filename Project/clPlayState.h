#pragma once

#include "clGameState.h"
#include "clBall.h"
#include "clSpaceShip.h"
#include "clBrick.h"

class clPlayState : public clGameState
{
    private:
        
        //Playing screen resources and variables
        clTexture   mBackground;
        clTexture   mCage;
        clTexture   mLifeTexture;

        TTF_Font* mFontSmaller;
        clTexture mTextLives;
        clTexture mTextPoints;
        TTF_Font* mFontPoints;
        clTexture mPointsNumber;
        int mLives;

        clBall      mBall;
        clSpaceShip mShip;
        clBrick     mBricks[5][15];

        bool mNewBall;
        Uint32 ticksCounter;

        //utility functions
        void initialize_bricks();

        //Sounds
        Mix_Chunk* mLifeLost;

        /*
        Uint32 ticksCounter;

        //Play functions
        bool checkGameOver(eWinner& winner, int winningSlotsXY[]);
        */

    public:

        //Load State assets
        clPlayState();
        //Free State assets
        ~clPlayState();

        //Main loop functions
        void handle_events();
        void logic();
        void render();
};

