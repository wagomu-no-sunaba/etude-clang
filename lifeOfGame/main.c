#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

int WIDTH = 50;
int HEIGHT = 50;
char DEAD = '_';
char LIVE = '0';

void InitBoard(char board[HEIGHT][WIDTH]) {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			board[y][x] = (rand() % 7 == 0) ? LIVE : DEAD;
		}
	}
}

void ShowBoard(char board[HEIGHT][WIDTH]) {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			printf("%c ", board[y][x]);
		}
		printf("\n");
	}
}

int CountNeighbors(char board[HEIGHT][WIDTH], int x, int y) {
	int count = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
			int newX = x + i;
			int newY = y + j;
			if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT) {
				if (board[newY][newX] == LIVE) {
					count++;
				}
			}
		}
	}
	return count;
}

void UpdateBoard(char board[HEIGHT][WIDTH]) {
	char newBoard[HEIGHT][WIDTH];

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			int liveNeighbors = CountNeighbors(board, x, y);

			if (board[y][x] == LIVE) {
				if (liveNeighbors < 2 || liveNeighbors > 3) {
					newBoard[y][x] = DEAD;
				} else {
					newBoard[y][x] = LIVE;
				}
			} else {
				if (liveNeighbors == 3) {
					newBoard[y][x] = LIVE;
				} else {
					newBoard[y][x] = DEAD;
				}
			}
		}
	}

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			board[y][x] = newBoard[y][x];
		}
	}
}

int main() {
	char board[HEIGHT][WIDTH];
	srand((unsigned int)time(NULL));
	InitBoard(board);

	while (1) {
		system("cls");
		ShowBoard(board);
		UpdateBoard(board);
		Sleep(800);
	}

	return 0;
}

