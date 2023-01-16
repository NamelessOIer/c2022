#include <bits/stdc++.h>
#include <Windows.h>
#include "Game.h"
#include "userObject.h"
#include "acllib.h"

using namespace std;

extern int winWidth;
extern int winHeight;
extern const int objWidth = 100;
extern const int objHeight = 100;

extern Point Area;
extern Point AreaImg;

extern ACL_Image tomL, tomR;
extern ACL_Image tomSwordL, tomSwordR;
extern ACL_Image jerryL, jerryR;
extern ACL_Image dogL, dogR;
extern ACL_Image duckL, duckR;
extern ACL_Image tomHead;
extern ACL_Image sword;
extern ACL_Image heart;
extern ACL_Sound bgmSound;
extern ACL_Sound menuSound;
extern ACL_Sound dieSound;
extern ACL_Sound moneySound;
extern ACL_Sound swordSound;
extern ACL_Sound heartSound;
extern ACL_Sound dogSound;

extern Game *game;
extern userObject *user;

void timerEvent(int tid);
void MouseEvent(int x, int y, int button, int event);
void KeyEvent(int key, int event);

int Setup()
{
	DEVMODE dm;
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
	winWidth=dm.dmPelsWidth + 10;
	winHeight=dm.dmPelsHeight - 20;
	Area = Point(winWidth, winHeight);
	AreaImg = Point(objWidth, objHeight);
	// cerr << winWidth << " " << winHeight << endl;

	srand((unsigned)time(NULL));

	initConsole();
	initWindow("Sprite Game", -5, 0, winWidth, winHeight);

	loadImage("./pic/tomL.bmp", &tomL);
	loadImage("./pic/tomR.bmp", &tomR);
	loadImage("./pic/tomSwordL.bmp", &tomSwordL);
	loadImage("./pic/tomSwordR.bmp", &tomSwordR);
	loadImage("./pic/jerryL.bmp", &jerryL);
	loadImage("./pic/jerryR.bmp", &jerryR);
	loadImage("./pic/dogL.bmp", &dogL);
	loadImage("./pic/dogR.bmp", &dogR);
	loadImage("./pic/duckL.jpg", &duckL);
	loadImage("./pic/duckR.jpg", &duckR);
	loadImage("./pic/TomHead.bmp", &tomHead);
	loadImage("./pic/Sword.bmp", &sword);
	loadImage("./pic/Heart.bmp", &heart);

	loadSound("./bgm/bgm.mp3", &bgmSound);
	loadSound("./bgm/menu.mp3", &menuSound);
	loadSound("./bgm/die.mp3", &dieSound);
	loadSound("./bgm/money.mp3", &moneySound);
	loadSound("./bgm/sword.mp3", &swordSound);
	loadSound("./bgm/heart.mp3", &heartSound);
	loadSound("./bgm/dog.mp3", &dogSound);
	
	registerTimerEvent(timerEvent);
	registerMouseEvent(MouseEvent);
	registerKeyboardEvent(KeyEvent);

	game = new Game();
	// DrawGameOver();
	return 0;
}

void timerEvent(int tid){
	switch(tid){
		case 0:{
			game -> run();
			break;
		}
		case 1:{
			game -> genRat();
			game -> genDog();
			break;
		}
		case 2:{
			game -> genSword();
		}
		case 3:{
			game -> genHeart();
		}
	}
	// cerr << "timerEvent: tid = " << tid << endl;
}

void MouseEvent(int x, int y, int button, int event){
	if(!game -> gameState) return;
	// cerr << "MouseEvent: " << x << " " << y << " " << button << " " << event << endl;
	// cerr << mouseState << endl;
	if(button == LEFT_BUTTON){
		if (event == BUTTON_DOWN){
			// cerr << "state = 1" << endl;
			game -> mouseState = 1;
			user -> setTarget(Point(x, y));
		}
		if (event == BUTTON_UP){
			// cerr << "state = 0" << endl;
			game -> mouseState = 0;
			user -> setTarget(Point(-1, -1));
		}
	}
	if (game -> mouseState && event == MOUSEMOVE) {
		user -> setTarget(Point(x, y));
	}
}

void KeyEvent(int key, int event){
	// cerr << "gameState: " << game -> gameState << " key: " << key << " event: " << event << endl;
	if (game -> gameState == 0){
		if(key == 'R' && event == KEY_DOWN){
			game -> GameStart();
		}
	}
	if (game -> gameState != 0){
		if((key == 'A' || key == 37)){
			if(event == KEY_DOWN)user -> onLEFT();
			else user -> offLEFT(); 
		}
		if((key == 'W' || key == 38)){
			if(event == KEY_DOWN)user -> onUP();
			else user -> offUP(); 
		}
		if((key == 'D' || key == 39)){
			if(event == KEY_DOWN)user -> onRIGHT();
			else user -> offRIGHT(); 
		}
		if((key == 'S' || key == 40)){
			if(event == KEY_DOWN)user -> onDOWN();
			else user -> offDOWN(); 
		}
	}
	if(game -> gameState == 1){
		if(key == ' ' && event == KEY_DOWN){
			game -> pause();
		}
	}
	else if(game -> gameState == 2){
		if(key == ' ' && event == KEY_DOWN){
			game -> resume();
		}
	}
}