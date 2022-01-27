#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

//initialize variables
bool snakeGame;
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

void game_Setup() {
	snakeGame = true;
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
	cout << score;
}

void game_Input() {
	if (_kbhit()) {
		switch (_getch()) {
			case 'a':                     //moves snake to the left
				if (dir != RIGHT) {
					dir = LEFT;
				}
				break;
			case 's':                     //moves snake to the bottom
				if (dir != UP) {
					dir = DOWN;
				}
				break;
			case 'd':                    //moves snake to the right
				if (dir != LEFT) {
					dir = RIGHT;
				}
				break;
			case 'w':                    //moves snake to the top
				if (dir != DOWN) {
					dir = UP;
				}
				break;
			case '0':
				snakeGame = false;
				break;
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
	if (x < 0 || x >= width - 1 || y < 0 || y >= height - 1) {
		snakeGame = false;
	}

	//snake tail hit
	for (int i = 0; i < tailLength; i++) {
		if (x == tailX[i] && y == tailY[i]) {
			snakeGame = false;
		}
	}

	//snake hits target
	if (x == targetX && y == targetY) {
		targetX = rand() % width;
		targetY = rand() % height;
		score++;
		tailLength++;
	}

}

int main() {
	game_Setup();
	while (snakeGame == true){
		game_Window();
		game_Input();
		game_Program();
		Sleep(30);
	}
}