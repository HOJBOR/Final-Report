int check_collision(Dino *dino, Meteor meteors[], int meteor_count) {
    for (int m = 0; m < meteor_count; m++) {
        if (meteors[m].active && meteors[m].x == dino->x && meteors[m].y == dino->y)
            return 1;
    }
    return 0;
}
