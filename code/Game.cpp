#include "Game.h"
#include "acllib.h"
#include "userObject.h"
#include "bossObject.h"
#include "Sword.h"
#include "heart.h"

using namespace std;

const int INF = 1e9;

int winWidth;
int winHeight;
const int objWidth = 100;
const int objHeight = 100;

Point Area;
Point AreaImg;

ACL_Image tomL, tomR;
ACL_Image tomSwordL, tomSwordR;
ACL_Image jerryL, jerryR;
ACL_Image dogL, dogR;
ACL_Image duckL, duckR;
ACL_Image tomHead;
ACL_Image sword;
ACL_Image heart;
ACL_Sound bgmSound;
ACL_Sound menuSound;
ACL_Sound dieSound;
ACL_Sound moneySound;
ACL_Sound swordSound;
ACL_Sound heartSound;
ACL_Sound dogSound;

Game *game = NULL;
userObject *user = NULL;

int countRat;
int countDog;

unordered_set<baseObject*> ALL;
unordered_set<bossObject*> DOG;

int swordtime;
int defaultswordexisttime = 10;
int bosstime;
int hearttime;

const double dt = 0.02;

extern ACL_Image tomHead;

Game::Game(){
	// DrawGameOver();
    GameStart();
}

void Game::genRat(){
	int score = user -> getScore();
	if(countRat < 20){
		Point Pos = randPoint();
		if(score == 0 || rand() % 3 == 0 || rand() % score < 5 * sqrt(score)){
			Vec V = Point(rand() % 360 / (2.0 * PI)) * (min(1000, score * 10 + 100));
			baseObject *x = new normalObject(Pos, V);
		}
		else{
			Vec V = Point(rand() % 360 / (2.0 * PI)) * (min(1000, score * 3 + 100));
			baseObject *x = new avoidObject(Pos, V, 400);
		}
	}
}

void Game::genDog(){
	if(bosstime){
		if(countDog <= min(3, user -> getScore() / 10))--bosstime;
	}
	else{
		if(countDog <= min(3, user -> getScore() / 10)){
			Point Pos = randPoint();
			double dis = countDog * 200 + 300;
			int tim = 10;
			while(tim-- && norm(Pos - user -> getPosition()) < 800){
				Pos = randPoint();
			}
			Vec V = Point(rand() % 360 / (2.0 * PI)) * (rand() % 200 + 400);
			baseObject *x = new bossObject(Pos, V, dis);
			bosstime = bosswaittime();
		}
	}
}

void Game::genSword(){
	if(swordtime){
		if(swordtime != INF)--swordtime;
	}
	else{
		if(user -> getState() == 1){
			// cerr << "Sword disappear" << endl;
			user -> setState(0);
			swordtime = swordwaittime();
		}
		else{
			Sword *x = new Sword(randPoint());
			swordtime = INF;
		}
	}
}

void Game::genHeart(){
	if(hearttime){
		--hearttime;
	}
	else{
		Heart *x = new Heart(randPoint());
		hearttime = heartwaittime();
	}
}

void Game::run(){
	if(gameState != 1) return ;
	for(auto x:ALL){
		x -> update(dt);
	}
	vector<baseObject*>tmp;
	for(auto x:ALL){
		if(gameState != 1) return ;
		if(x == user) continue;
		if(collision(user, x)){
			if(x -> effect()){
				tmp.push_back(x);
			}
		}
	}
	for(auto &x:tmp){
		delete x;
	}
	print();
}

void Game::print(){
	if(gameState != 1) return ;
	beginPaint();
	clearDevice();
	
	char score[15];
	sprintf(score, "Score: %d", user -> getScore());
	paintText(10, 10, score);

	char life[15];
	sprintf(life, "Life:");
	setTextSize(24);
	paintText(10, 40, life);
	for(int i = 0; i < user -> getLife(); ++i){
		putImageTransparent(&tomHead, 80 + 35 * i, 40, 30, 30, WHITE);
	}

	if(user -> getState() == 1){
		char sword[30];
		sprintf(sword, "sword left time: %ds", swordtime);
		paintText(10, 70, sword);
	}

	if(countDog < min(3, user -> getScore() / 10) && bosstime <= 5){
		char boss[30];
		sprintf(boss, "A dog is comming in %ds", bosstime);
		paintTextCentered(24, 10, boss);
	}

	for(auto &x:ALL){
		x -> print();
	}

	endPaint();
}

void Game::GameStart(){
	user = new userObject(Area / 2, Point(0, 0));
	for(int i = 0; i < 5; ++i){
		genRat();
	}
	gameState = 1;
	mouseState = 0;
	countRat = 0;
	countDog = 0;
	startTimer(0, dt*1000);
	bosstime = bosswaittime();
	startTimer(1, 1000);
	swordtime = swordwaittime();
	startTimer(2, 1000);
	hearttime = heartwaittime();
	startTimer(3, 1000);
	stopSound(menuSound);
	playSound(bgmSound, 1);
}

void Game::GameOver(){
	stopSound(bgmSound);
	playSound(menuSound, 1);
	DrawGameOver();
	cancelTimer(0);
	cancelTimer(1);
	cancelTimer(2);
	cancelTimer(3);
	gameState = 0;
	for(auto &x:ALL){
		delete x;
	}
	// cerr << "ALL.size = " << ALL.size() << endl;
	// cerr << "DOG.size = " << DOG.size() << endl;
}


void Game::pause(){
	// cerr << "PAUSE" << endl;
	// cerr << user -> getState() << endl;
	assert(gameState == 1);
	cancelTimer(0);
	cancelTimer(1);
	cancelTimer(2);
	cancelTimer(3);
	gameState = 2;
	// cerr << "gameState = " << gameState << endl;
	DrawPause();
}

void Game::resume(){
	// cerr << "RESUME" << endl;
	assert(gameState == 2);
	startTimer(0, dt*1000);
	startTimer(1, 1000);
	startTimer(2, 1000);
	startTimer(3, 1000);
	gameState = 1;
	// cerr << "gameState = " << gameState << endl;
}

void Game::DrawGameOver(){
	// cerr << "DrawGameOver" << endl;
	beginPaint();
	clearDevice();

	char score[15];
	sprintf(score, "%d", user == NULL ? 0 : user -> getScore());
	paintTextCentered(120, winHeight / 2 - 250, score);
	paintTextCentered(120, winHeight / 2 - 100, "GAME OVER");
	paintTextCentered(24, winHeight / 2 + 50, "Press [ R ] to play again.");
	endPaint();
}

void Game::DrawPause(){
	beginPaint();
	paintTextCentered(150, winHeight / 2 - 150, "PAUSE");
	paintTextCentered(24, winHeight / 2 + 50, "Press [ SPACE ] to continue play.");
	endPaint();
}

Point randPoint(){
	int x = rand() % (winWidth - objWidth);
	int y = rand() % (winHeight - objHeight);
	return Point(x + objWidth / 2, y + objHeight / 2);
}

void paintTextCentered(int siz, int y, char *str){
	setTextSize(siz);
	paintText(winWidth / 2 - strlen(str) * siz / 4, y, str);
}

int swordwaittime(){
	return user -> getScore() / 10 + 30;
}

int heartwaittime(){
	return user -> getScore() / 30 + 40;
}

int bosswaittime(){
	return max(13, 38 - user -> getScore() / 30);
}
