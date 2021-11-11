#pragma once

#include "clGameState.h"

class clTitleState : public clGameState
{

    private:
        
        //Title screen resources and variables
        clTexture mTitleBackground;
        TTF_Font* mFontTitle;
        clTexture mTextTitle;
        TTF_Font* mFontSmaller;
        clTexture mTextAuthor;
        clTexture mTextEnter;

        bool mFadeOut;
        Uint8 mTextAlpha;
        
    public:

        //Load State assets
        clTitleState();
        //Free State assets
        ~clTitleState();

        //Game loop functions
        void handle_events();
        void logic();
        void render();
};

