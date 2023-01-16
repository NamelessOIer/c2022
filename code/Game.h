#ifndef _GAME_H
#define _GAME_H
#include "Geometry.h"

extern const int INF;

class Game{
    void DrawGameOver();
    void DrawPause();

public:
	int gameState;
    // 0: not started
    // 1: running
    // 2: paused
	bool mouseState;

    Game();

    void genRat();
    void genDog();
    void genSword();
    void genHeart();

    void run();
    void print();

    void GameStart();
    void GameOver();

    void pause();
    void resume();

};

Point randPoint();
void paintTextCentered(int siz, int y, char *str);

int heartwaittime();
int swordwaittime();
int bosswaittime();

#endif