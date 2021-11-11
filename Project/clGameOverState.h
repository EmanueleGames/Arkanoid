#pragma once

#include "clGameState.h"

class clGameOverState : public clGameState
{
    private:
        
        //Game Over screen resources and variables
        TTF_Font* mFontGameOver;
        clTexture mTextGameOver;
        clTexture mTextFinalPoints;
        clTexture mTextPlayAgain;
        
    public:

        //Load State assets
        clGameOverState();
        //Free State assets
        ~clGameOverState();

        //Game loop functions
        void handle_events();
        void logic();
        void render();

};

