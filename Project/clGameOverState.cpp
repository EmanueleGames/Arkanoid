#include "clGameOverState.h"

using namespace std;

clGameOverState::clGameOverState()
{
    //Game Over font
    mFontGameOver = TTF_OpenFont("data/jabjai_light.ttf", 60);
    if (mFontGameOver == NULL)
    {
        cout << "Failed to load jabjai_light font for GameOver screen! SDL_ttf Error: " << TTF_GetError() << endl;
    }

    string messageGameOver = "Game Over!";
    if (!mTextGameOver.createFromText(gRenderer, mFontGameOver, messageGameOver.c_str(), textColorWhite))
    {
        cout << "Unable to create Outcome message texture!" << endl;
    }

    string stringFinalPoints = std::to_string(gPoints);
    if (!mTextFinalPoints.createFromText(gRenderer, mFontGameOver, stringFinalPoints.c_str(), textColorWhite))
    {
        cout << "Unable to create Outcome message texture!" << endl;
    }

    string messagePlayAgain = "Press ENTER to play again!";
    if (!mTextPlayAgain.createFromText(gRenderer, mFontGameOver, messagePlayAgain.c_str(), textColorWhite))
    {
        cout << "Unable to create PlayAgain message texture!" << endl;
    }
}

clGameOverState::~clGameOverState()
{
    //Free the resources
    TTF_CloseFont(mFontGameOver);
    mFontGameOver = NULL;

    mTextGameOver.freeTexture();
    mTextPlayAgain.freeTexture();
}

void clGameOverState::handle_events()
{
    //Polling for a new event
    while (SDL_PollEvent(&gEvent))
    {
        //User requests to exit
        if (gEvent.type == SDL_QUIT)
        {
            set_next_state(eGameStates::STATE_EXIT);
        }
        //Key press
        else if ((gEvent.type == SDL_KEYDOWN))
        {
            if (gEvent.key.keysym.sym == SDLK_RETURN)
            {
                //Move to the Play screen
                set_next_state(eGameStates::STATE_PLAY);
            }
        }
    }
}

void clGameOverState::logic()
{
    //Calculate create texture for FPS
    calc_and_texture_FPS();
}

void clGameOverState::render()
{
    //Clear the window
    SDL_SetRenderDrawColor(gRenderer, 20, 20, 20, 255);  //almost black
    SDL_RenderClear(gRenderer);

    //Average FPS
    gFPSTextTexture.render(gRenderer, 2, 0);

    //Show the Match result
    mTextGameOver.render(gRenderer, (WINDOW_WIDTH - mTextGameOver.getWidth()) / 2, 200);
    mTextFinalPoints.render(gRenderer, (WINDOW_WIDTH - mTextFinalPoints.getWidth()) / 2, 300);
    mTextPlayAgain.render(gRenderer, (WINDOW_WIDTH - mTextPlayAgain.getWidth()) / 2, 600);
}