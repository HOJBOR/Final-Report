#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define WIDTH 10
#define HEIGHT 15
#define MAX_METEOR 10

typedef struct {
    int x, y;
    int active;
} Meteor;

typedef struct {
    int x, y;
} Dino;

void gotoxy(int x, int y) {
    COORD c = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hide_cursor() {
    CONSOLE_CURSOR_INFO info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void draw(Dino *dino, Meteor meteors[], int meteor_count, int score) {
    gotoxy(0, 0);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int printed = 0;
            if (dino->x == x && dino->y == y) {
                printf("D");
                printed = 1;
            }
            for (int m = 0; m < meteor_count; m++) {
                if (meteors[m].active && meteors[m].x == x && meteors[m].y == y) {
                    printf("*");
                    printed = 1;
                }
            }
            if (!printed) printf(" ");
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
    printf("Move: ← → or a d, ESC to exit\n");
}

int check_collision(Dino *dino, Meteor meteors[], int meteor_count) {
    for (int m = 0; m < meteor_count; m++) {
        if (meteors[m].active && meteors[m].x == dino->x && meteors[m].y == dino->y)
            return 1;
    }
    return 0;
}

int main() {
    Dino dino = {WIDTH / 2, HEIGHT - 1};
    Meteor meteors[MAX_METEOR];
    int score = 0, speed = 200, tick = 0;
    int meteor_count = 1; // Start with 1 meteor
    DWORD last_add_time = GetTickCount();
    srand((unsigned)time(NULL));
    hide_cursor();

    // Initialize meteors
    for (int m = 0; m < MAX_METEOR; m++) {
        meteors[m].active = 0;
    }
    // Activate the first meteor
    meteors[0].x = rand() % WIDTH;
    meteors[0].y = 0;
    meteors[0].active = 1;

    while (1) {
        // Add a new meteor every 2 seconds, up to MAX_METEOR
        if (meteor_count < MAX_METEOR && GetTickCount() - last_add_time >= 2000) {
            meteors[meteor_count].x = rand() % WIDTH;
            meteors[meteor_count].y = 0;
            meteors[meteor_count].active = 1;
            meteor_count++;
            last_add_time = GetTickCount();
        }

        // Control
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 27) break; // ESC
            if (ch == 'a' || ch == 75) { // Left
                if (dino.x > 0) dino.x--;
            }
            if (ch == 'd' || ch == 77) { // Right
                if (dino.x < WIDTH - 1) dino.x++;
            }
        }

        // Meteor falling
        if (tick % (speed / 20) == 0) {
            for (int m = 0; m < meteor_count; m++) {
                if (meteors[m].active) {
                    meteors[m].y++;
                    if (meteors[m].y >= HEIGHT) {
                        meteors[m].active = 0;
                        meteors[m].x = rand() % WIDTH;
                        meteors[m].y = 0;
                        meteors[m].active = 1;
                        score++;
                        if (score % 10 == 0 && speed > 60) speed -= 10;
                    }
                }
            }
        }

        draw(&dino, meteors, meteor_count, score);

        if (check_collision(&dino, meteors, meteor_count)) {
            gotoxy(0, HEIGHT + 2);
            printf("Game Over! Final Score: %d\n", score);
            break;
        }

        Sleep(20);
        tick++;
    }

    gotoxy(0, HEIGHT + 4);
    system("pause");
    return 0;
}
