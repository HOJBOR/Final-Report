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
