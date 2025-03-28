#pragma once

enum GameOverStatus
{
	GAME_OVER_EXPLOSION = 1,
	GAME_OVER_INFERNAL_LOCKED,
	GAME_OVER_SPOBS_LOCKED,
	GAME_OVER_ALL_LOCKED,
	GAME_OVER_LUCKY,
	GAME_OVER_LAMPASSO,
	GAME_OVER_ABORT,
	GAME_OVER_NETWORK
};

struct GameState
{
    // Doesnt works if equals to -1, otherwise - storaging ID of gameover.
    int gameoverTrigger = -1;
	
	bool inNetwork = false;
};

extern GameState globalGameState;