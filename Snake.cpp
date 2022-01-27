#include <iostream>
#include <windows.h>
using namespace std;

//initialize variables
bool normalGame, mainMenu, snakeGame;
const int width = 25;
const int height = 25;
//user variables
int x, y, spd = 1;
int tailX[100], tailY[100], tailLength; //100 is the maximum number of tails the snake can have
//tail coordinates
int fposX, fposY, sposX, sposY;
//target variables
int targetX, targetY;
//game variables
int score;
enum directions {STOP = 0, UP, DOWN, LEFT, RIGHT};
directions dir;

void game_Over() {
	normalGame = false;
	mainMenu = true;
	tailLength = 0;
	score = 0;
}

void game_Setup() {
	snakeGame = true;
	mainMenu = true; 
}

void main_Menu() {
	system("cls");
	cout << "This Is the Main Menu." << endl;
	cout << "Play the Game." << endl;
	cout << "Options" << endl;
	cout << "End Game" << endl;






	if (GetAsyncKeyState(VK_RETURN)) {
		mainMenu = false;
	}
	else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {
		dir = STOP;
	}
	else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
		dir = STOP;
	}
	else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
		dir = STOP;
	}
	else if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {
		dir = STOP;
	}
	else if (GetAsyncKeyState(VK_RETURN)) {
		return;
	}
}

void normal_Setup() {
	normalGame = true;
	dir = STOP;
	x = rand() % width;
	y = rand() % height;
	targetX = rand() % width;
	targetY = rand() % height;
	//error when target and player are on top
	while (x == targetX && y == targetY) {
		x = rand() % width;
		y = rand() % height;
		targetX = rand() % width;
		targetY = rand() % height;
	}
	score = 0;
}

void game_Window() {
	system("cls");
	//top border
	for (int i = 0; i < width; i++) {
		cout << "*";
	}


	//body
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				cout << "*";
			}
			else if (i == y && j == x) {
				cout << "S";
			}
			else if (i == targetY && j == targetX) {
				cout << "0";
			}
			else {
				bool tail = false;
				for (int k = 0; k < tailLength; k++) {
					if (j == tailX[k] && i == tailY[k]) {
						cout << "s";
						tail = true;
					}
				}
				if (!tail) {
					cout << " ";
				}
			}
			
		}
		cout << endl;
	}


	//bottom border
	for (int i = 0; i < width; i++) {
		cout << "*";
	}
	cout << endl;

	//score board
	cout << "Score: " << score;
}

void game_Input() {
	if (mainMenu == false && normalGame == true) {
		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A') && dir != RIGHT) {
			dir = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D') && dir != LEFT) {
			dir = RIGHT;
		}
		else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S') && dir != UP) {
			dir = DOWN;
		}
		else if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W') && dir != DOWN) {
			dir = UP;
		}
	}
	else if (mainMenu == true && normalGame == false) {
		if (GetAsyncKeyState(VK_RETURN)) {
			mainMenu = false;
		}
	}
}

void game_Program() {
	//snake tail grows
	fposX = tailX[0];
	fposY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailLength; i++) {
		sposX = tailX[i];
		sposY = tailY[i];
		tailX[i] = fposX;
		tailY[i] = fposY;
		fposX = sposX;
		fposY = sposY;
	}

	switch (dir) {
	case LEFT:
		x -= spd;
		break;
	case UP:
		y -= spd;
		break;
	case DOWN:
		y += spd;
		break;
	case RIGHT:
		x += spd;
		break;
	}

	//snake hits borders
	if (x <= 0 || x >= width - 1 || y < 0 || y > height - 1) {
		game_Over();
	}

	//snake tail hit
	for (int i = 0; i < tailLength; i++) {
		if (x == tailX[i] && y == tailY[i]) {
			game_Over();
		}
	}

	//snake hits target
	if (x == targetX && y == targetY) {
		targetX = rand() % width;
		targetY = rand() % height;
		score += 10;
		tailLength++;
	}

}

int main() {
	game_Setup();
	while (snakeGame == true) {
		if (mainMenu == true) {
			main_Menu();
		}
		else if (mainMenu == false) {
			normal_Setup();
			while (normalGame == true) {
				game_Window();
				game_Input();
				game_Program();
				Sleep(30);
			}
		}
	}
	
}