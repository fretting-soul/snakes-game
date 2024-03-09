#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20
#define SNAKE_INITIAL_LENGTH 3
#define EMPTY ' '
#define SNAKE_BODY 'O'
#define FOOD '*'

int snakeX[SNAKE_INITIAL_LENGTH];
int snakeY[SNAKE_INITIAL_LENGTH];
int snakeLength = SNAKE_INITIAL_LENGTH;
char direction = 'd';
int foodX, foodY;

void displayBoard() {
    system("cls");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int isSnakeBody = 0;
            for (int i = 0; i < snakeLength; i++) {
                if (snakeX[i] == x && snakeY[i] == y) {
                    if (i == 0) {
                        printf("X ");
                    } else {
                        printf("%c ", SNAKE_BODY);
                    }
                    isSnakeBody = 1;
                }
            }
            if (!isSnakeBody) {
                if (x == foodX && y == foodY) {
                    printf("%c ", FOOD);
                } else {
                    printf("%c ", EMPTY);
                }
            }
        }
        printf("\n");
    }
}

void moveSnake() {
    int headX = snakeX[0];
    int headY = snakeY[0];
    
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    if (direction == 'w') {
        headY--;
    } else if (direction == 's') {
        headY++;
    } else if (direction == 'a') {
        headX--;
    } else if (direction == 'd') {
        headX++;
    }

    snakeX[0] = headX;
    snakeY[0] = headY;

    if (headX == foodX && headY == foodY) {
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        snakeLength++;
    }
}

int main() {
    srand(time(NULL));
    
    for (int i = 0; i < SNAKE_INITIAL_LENGTH; i++) {
        snakeX[i] = SNAKE_INITIAL_LENGTH - i - 1;
        snakeY[i] = 0;
    }

    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;

    while (1) {
        displayBoard();

        if (_kbhit()) {
            char key = _getch();
            if (key == 'w' || key == 's' || key == 'a' || key == 'd') {
                direction = key;
            }
        }

        moveSnake();

        // Game over conditions
        if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT) {
            printf("Game Over!\n");
            break;
        }

        for (int i = 1; i < snakeLength; i++) {
            if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
                printf("Game Over!\n");
                break;
            }
        }
    }

    return 0;
}
