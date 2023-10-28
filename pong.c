#include <stdio.h>
#include <math.h>

#define WIDTH 80
#define HEIGHT 25
#define RACKET_SIZE 3
#define LEFT_BORDER_X -40
#define RIGHT_BORDER_X 40
#define TOP_BORDER_Y 13
#define BOTTOM_BORDER_X -12

int leftRacketX = 2;
int leftRacketY = HEIGHT / 2;
int rightRacketX = WIDTH - 1;
int rightRacketY = HEIGHT / 2;
int ballX = WIDTH / 2;
int ballY = HEIGHT / 2 + 1;

void draw() {
    int leftRacketPartsPrinted = 0;
    int rightRacketPartsPrinted = 0;

    // Отрисовка верхней границы
    for (int x = 1; x <= WIDTH + 2; ++x) {
        printf("#");
    }

    printf("\n");

    // Отрисовка основной части, поля
    for (int y = 1; y <= HEIGHT; ++y) {
        printf("#");
        for (int x = 1; x <= WIDTH; ++x) {
            
            // Отрисовка ракеток
            if (leftRacketX == x && (leftRacketY + leftRacketPartsPrinted) == y && leftRacketPartsPrinted < RACKET_SIZE) {
                printf("|");
                ++leftRacketPartsPrinted;
            } else if (rightRacketX == x && (rightRacketY + rightRacketPartsPrinted) == y && rightRacketPartsPrinted < RACKET_SIZE) {
                printf("|");
                ++rightRacketPartsPrinted;
            // Отрисовка мяча
            } else if (x == ballX && y == ballY) { 
                printf("@");
            } else {
                printf(" ");
            }


        }
        printf("#\n");
    }

    // Отрисовка нижней границы
    for (int x = 1; x <= WIDTH + 2; ++x) {
        printf("#");
    }

    printf("\n");
}

void moveLeftRacket(int delta) {
    if (1 <= leftRacketY + delta && leftRacketY + delta + 2 <= HEIGHT) {
        leftRacketY += delta;
    }
}

void moveRightRacket(int delta) {
    if (1 <= rightRacketY + delta && rightRacketY + delta + 2 <= HEIGHT) {
        rightRacketY += delta;
    }
}

void clearScreen() {
    printf("\e[1;1H\e[2J");
}

// TODO:
// - мб игроки должны шагать по очереди
// 

void run() {
    char userInput;
    while(1) {
        clearScreen();
        draw();

        scanf("%c", &userInput);

        if (userInput == 'A' || userInput == 'a') {
            moveLeftRacket(-1);
        }
        if (userInput == 'Z' || userInput == 'z') {
            moveLeftRacket(1);
        }
        if (userInput == 'K' || userInput == 'k') {
            moveRightRacket(-1);
        }
        if (userInput == 'M' || userInput == 'm') {
            moveRightRacket(1);
        }
        if (userInput == 'Q' || userInput == 'q') {
            break;
        }
    }
}

int main () {
    run();    
}