#include <stdio.h>
#include <math.h>

#define WIDTH 80
#define HEIGHT 25
#define RACKET_SIZE 3
#define REGULAR_SPEED 5
#define SLOW_SPEED 1
#define LEFT_BORDER_X -40
#define RIGHT_BORDER_X 40
#define TOP_BORDER_Y 13
#define BOTTOM_BORDER_X -12



// RACKETS
int leftRacketX = 2;
int leftRacketY = HEIGHT / 2;
int rightRacketX = WIDTH - 1;
int rightRacketY = HEIGHT / 2;

// BALL
int ballIntX = 2 + 1;
int ballIntY = HEIGHT / 2 + 1;
double ballX = 2 + 1;
double ballY = HEIGHT / 2 + 1;
double alpha = -M_PI / 4;
double speed = REGULAR_SPEED;

int sign(int value) {
    if (value < 0) {
        return -1;
    } else if (value > 0) {
        return 1;
    }
    return 0;
}

void moveBall() {
    ballX += cos(alpha) * speed;
    ballY += sin(alpha) * speed;

    ballIntX = (int)ballX;
    ballIntY = (int)ballY;

    // Если мячик вылетает за пределы
    if (ballIntX < 1) {
        ballIntX = 1;
        ballX = 1;
    }
    if (ballIntX > WIDTH) {
        ballIntX = WIDTH;
        ballX = WIDTH;
    }
    if (ballIntY < 1) {
        ballIntY = 1;
        ballY = 1;
    }
    if (ballIntY > HEIGHT) {
        ballIntY = HEIGHT;
        ballY = HEIGHT;
    }

    // В отдельную функцию
    // Отражение от вертикальных границ
    if (ballIntY == 1 || ballIntY == HEIGHT) {
        alpha *= -1;
    }

    // Если коснулись горизонтальных стен - отражаем, и меняем скорость
    // В отдельную функцию
    if (ballIntX == 1 || ballIntX == WIDTH) {
        alpha += alpha > 0 ? -M_PI / 2 : M_PI / 2;
        speed *= -1;
    }

    // Касание ракеток
    if (ballIntX == leftRacketX && leftRacketY <= ballIntY && ballIntY <= (leftRacketY + RACKET_SIZE - 1)) {
        alpha += alpha > 0 ? -M_PI / 2 : M_PI / 2;
        speed *= -1;
    }

    if (ballIntX == rightRacketX && rightRacketY <= ballIntY && ballIntY <= (rightRacketY + RACKET_SIZE - 1)) {
        alpha += alpha > 0 ? -M_PI / 2 : M_PI / 2;
        speed *= -1;
    }
}

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
            } else if (x == ballIntX && y == ballIntY) { 
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
    if (1 <= leftRacketY + delta && leftRacketY + delta + (RACKET_SIZE - 1) <= HEIGHT) {
        leftRacketY += delta;
    }
}

void moveRightRacket(int delta) {
    if (1 <= rightRacketY + delta && rightRacketY + delta + (RACKET_SIZE - 1) <= HEIGHT) {
        rightRacketY += delta;
    }
}

void clearScreen() {
    // printf("\e[1;1H\e[2J");
    printf("\033[2J\033[1;1H");
}

// TODO:
// - мб игроки должны шагать по очереди
// - замедлять скорость, когда мяч у ракеток
// - первый игрок может смещаться с мячом
// - ПРОПАДАЕТ МЯЧ, когда касается ракатеки
// - СЧЕТ

void info() {
    printf("Управление:\n\n");
    printf("Левый игрок: A/a - вверх, Z/z - вниз\t\t\tПравый игрок: K/k - вверх, M/m - вниз\n\n\n");
}

void run() {
    char userInput;
    while(1) {
        clearScreen();
        info();
        draw();

        userInput = getchar();
        while (getchar() != '\n'); // Очищаем буфер

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

        moveBall();

        // Замедляем скорость близ ракеток
        // Эту 10-ку в дефайн
        if (0 <= ballIntX && ballIntX <= 10 || WIDTH - 10 <= ballIntX && ballIntX <= WIDTH) {
            printf("HERE");
            speed = sign(speed) * SLOW_SPEED;
        } else {
            speed = sign(speed) * REGULAR_SPEED;
        }
    }
}

int main () {
    printf("%lf\n", cos(alpha));
    run();    
}