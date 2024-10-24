#include <iostream>
#include <fstream>
#include "windows.h"
#include <vector>
#include <string>
using namespace std;

struct body {
	int xPos = 1;
	int yPos = 1;
	int size = 1;
	char symbol = 'o';
	char food = 'x';
};

BOOL gotoxy(const WORD x, const WORD y) {
	COORD xy;
	xy.X = x;
	xy.Y = y;
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
		xy);
}
int load(vector <string>& map) {
	int foodCount = 0;
	cout << "Enter Map Name" << endl;
	string filename, line;
	getline(cin, filename);
	ifstream infile(filename);
	if (infile) {
		while (getline(infile, line)) {
			map.push_back(line);
			for (char c : line) {
				if (tolower(c) == 'x') {
					foodCount++;
				}
			}
		}
		infile.close();
	}
	else {
		cout << "file not open" << endl;
	}
	return foodCount;
}
void displayMap(vector <string>& map) {
	for (string s : map) {
		cout << s << endl;
	}
}
void snakeBodyMove(vector<string>& map, vector<body>& snake) {


	for (int i = snake.at(0).size; i > 0; i--) {

		snake.at(i) = snake.at(i - 1);
		map.at(snake.at(i).yPos).at(snake.at(i).xPos) = snake.at(i).symbol;
	}

}

void snakeMove(vector<string>& map, vector <body>& snake, int xMove, int yMove, bool& game_running) {


	switch (map.at(snake.at(0).yPos + yMove).at(snake.at(0).xPos + xMove)) {

	case ' ':
		map.at(snake.at(0).yPos).at(snake.at(0).xPos) = ' ';
		snakeBodyMove(map, snake);
		map.at((snake.at(snake.at(0).size)).yPos).at(snake.at(snake.at(0).size).xPos) = ' ';
		snake.at(0).xPos += xMove;
		snake.at(0).yPos += yMove;
		map.at(snake.at(0).yPos).at(snake.at(0).xPos) = snake.at(0).symbol;

		break;
	case 'x':
		snake.at(0).size += 1;
		map.at(snake.at(0).yPos).at(snake.at(0).xPos) = ' ';
		snakeBodyMove(map, snake);
		map.at((snake.at(snake.at(0).size)).yPos).at(snake.at(snake.at(0).size).xPos) = ' ';
		snake.at(0).xPos += xMove;
		snake.at(0).yPos += yMove;
		map.at(snake.at(0).yPos).at(snake.at(0).xPos) = snake.at(0).symbol;
		break;
	case 'o':

		game_running = false;
		break;

	}


}
int main() {
	vector <string> map;



	int total_food = load(map);
	vector <body> snake(total_food + 2);



	system("cls");
	bool game_running = true;
	do {
		gotoxy(0, 0);
		displayMap(map);
		system("pause>nul");
		if (GetAsyncKeyState(VK_DOWN)) {
			snakeMove(map, snake, 0, 1, game_running);

		}
		if (GetAsyncKeyState(VK_UP)) {
			snakeMove(map, snake, 0, -1, game_running);
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			snakeMove(map, snake, 1, 0, game_running);
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			snakeMove(map, snake, -1, 0, game_running);
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			game_running = false;
		}
	} while (game_running);
	system("cls");
	cout << "GAME OVER";
	return 0;
}


