#pragma once

//Window resolution
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

//Assets dimension
const int CAGE_LEFT_MARGIN = 192;
const int BALL_WIDTH  = 10;
const int BALL_HEIGHT = 10;
const int SHIP_WIDTH  = 60;
const int SHIP_HEIGHT = 20;
const int BRICK_WIDTH  = 40;
const int BRICK_HEIGHT = 20;

//Ball and Ship Movement boundries
const int BALL_STARTING_POS_X = (WINDOW_WIDTH / 2);
const int BALL_STARTING_POS_Y = 320;
const int SHIP_STARTING_POS_X = (WINDOW_WIDTH / 2) - (SHIP_WIDTH / 2);
const int SHIP_STARTING_POS_Y = 720;
const int MIN_X_POS = 212;
const int MAX_X_POS = 812;
const int MIN_Y_POS = 20;

//Velocity
const int STARTING_VEL_X_INTERVAL = 6;
const int STARTING_VEL_Y = 5;
const int MAX_VEL_X = 15;
const int MAX_VEL_Y = 10;

//Game Settings
const int STARTING_LIVES = 3;
const int BRICK_POINT_VALUE = 10;
//Hit Tolerance-Precision. Lower the number, less contact is needed to register an hit
const int SHIP_TOLERANCE = -2;
const int BRICK_TOLERANCE = 1;

//Delay before starting and after losing a ball
const int DELAY = 40;

//FPS limit
const int MAX_FPS = 60;
const int MAX_TICKS_PER_FRAME = 1000 / MAX_FPS;
const int FPS_DECIMAL_DIGIT = 2;

//Game states
enum class eGameStates
{
    STATE_NULL,
    STATE_TITLE,
    STATE_PLAY,
    STATE_GAME_OVER,
    STATE_EXIT,
};