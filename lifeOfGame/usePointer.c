#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <signal.h>

int WIDTH = 50;
int HEIGHT = 50;
char DEAD = '_';
char LIVE = '0';

char **board;


void FreeBoard(char ***board) {
    for (int i = 0; i < HEIGHT; i++) {
        free((*board)[i]);
    }
    free(*board);
}

void handle_sigint(int sig) {
    FreeBoard(&board);
    printf("\nCleaned up and exiting.\n");
    exit(0);
}

void AllocateBoard(char ***board) {
    *board = (char **)malloc(HEIGHT * sizeof(char *));
    for (int i = 0; i < HEIGHT; i++) {
        (*board)[i] = (char *)malloc(WIDTH * sizeof(char));
    }
}

void InitBoard(char **board) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            board[y][x] = (rand() % 7 == 0) ? LIVE : DEAD;
        }
    }
}

void ShowBoard(char **board) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c ", board[y][x]);
        }
        printf("\n");
    }
}

int CountNeighbors(char **board, int x, int y) {
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

void UpdateBoard(char **board) {
    char **newBoard = (char **)malloc(HEIGHT * sizeof(char *));
    for (int i = 0; i < HEIGHT; i++) {
        newBoard[i] = (char *)malloc(WIDTH * sizeof(char));
    }

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
        free(newBoard[y]);
    }
    free(newBoard);
}

int main() {
	signal(SIGINT, handle_sigint);
    AllocateBoard(&board);
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

