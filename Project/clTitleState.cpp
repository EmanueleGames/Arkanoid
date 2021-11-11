#include "clTitleState.h"

using namespace std;

clTitleState::clTitleState()
{
    mFadeOut = false;
    mTextAlpha = 255;

    //Load cage textures
    if (!mTitleBackground.createFromFile(gRenderer, "data/title_background.png"))
    {
        cout << "Background image loading failed!" << endl;
    }

    //Open Title font
    mFontTitle = TTF_OpenFont("data/jabjai_light.ttf", 110);
    if (mFontTitle == NULL)
    {
        cout << "Failed to load jabjai_light font for Title screen! SDL_ttf Error: " << TTF_GetError() << endl;
    }

    string messageIntro = "Arkanoid!";
    if (!mTextTitle.createFromText(gRenderer, mFontTitle, messageIntro.c_str(), textColorWhite))
    {
        cout << "Unable to render Intro message texture!" << endl;
    }
    mTextTitle.setBlendMode(SDL_BLENDMODE_BLEND); //ready to fade out

    //Open Author and Enter message font
    mFontSmaller = TTF_OpenFont("data/jabjai_light.ttf", 40);
    if (mFontSmaller == NULL)
    {
        cout << "Failed to load jabjai_light small font for Title screen! SDL_ttf Error: " << TTF_GetError() << endl;
    }

    string messageAuthor = "by Emanuele Carrino";
    if (!mTextAuthor.createFromText(gRenderer, mFontSmaller, messageAuthor.c_str(), textColorWhite))
    {
        cout << "Unable to render Intro message texture!" << endl;
    }
    mTextAuthor.setBlendMode(SDL_BLENDMODE_BLEND); //ready to fade out

    string messageEnter = "Press Enter";
    if (!mTextEnter.createFromText(gRenderer, mFontSmaller, messageEnter.c_str(), textColorWhite))
    {
        cout << "Unable to render Enter message texture!" << endl;
    }
    mTextEnter.setBlendMode(SDL_BLENDMODE_BLEND); //ready to fade out

}

clTitleState::~clTitleState()
{
    //Free the resources
    TTF_CloseFont(mFontTitle);
    TTF_CloseFont(mFontSmaller);
    mFontTitle = NULL;
    mFontSmaller = NULL;
    mTextTitle.freeTexture();
    mTextAuthor.freeTexture();
    mTextEnter.freeTexture();

}

void clTitleState::handle_events()
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
            if (gEvent.key.keysym.sym == SDLK_RETURN)    // user confirms option
            {
                //Move to the Play screen
                //set_next_state(eGameStates::STATE_PLAY);  //removed to realize fade out
                if (mFadeOut == false)
                {
                    mFadeOut = true;
                }
            }
        }
    }
}

void clTitleState::logic()
{
    //Calculate create texture for FPS
    calc_and_texture_FPS();

    //Fade out
    if (mFadeOut == true)
    {
        mTextAlpha = mTextAlpha - 5;
    }
    if (mTextAlpha == 0)
    {
        //Move to the Play screen
        set_next_state(eGameStates::STATE_PLAY);
    }
}

void clTitleState::render()
{
    //Clear the window
    SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 255);  //almost white
    SDL_RenderClear(gRenderer);

    //Show the background
    mTitleBackground.render(gRenderer, 0, 0);

    //fade out
    mTextTitle.setAlphaModulation(mTextAlpha);
    mTextAuthor.setAlphaModulation(mTextAlpha);
    mTextEnter.setAlphaModulation(mTextAlpha);

    //Average FPS
    gFPSTextTexture.render(gRenderer, 2, 0);

    //Show the Title
    mTextTitle.render(gRenderer, (WINDOW_WIDTH - mTextTitle.getWidth()) / 2, 200);
    mTextAuthor.render(gRenderer, (WINDOW_WIDTH - mTextAuthor.getWidth()) / 2, 310);
    mTextEnter.render(gRenderer, (WINDOW_WIDTH - mTextEnter.getWidth()) / 2, 700);
}