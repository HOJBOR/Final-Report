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
