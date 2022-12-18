#include "game.h"
#include "pacman.h"
#include "enemy.h"
#include <ncurses.h>
#include <stdio.h>

int inputkey(void) {
    char ch = getch();

    switch (ch) {
        case 'w':
            return 0;
            break;
        case 'd':
            return 1;
            break;
        case 'a':
            return 2;
            break;
        case 's':
            return 3; 
            break;
        case 'q':
            return 100; 
            break;
    }
    return -1; 
}

int main(void) {
    initscr();
    cbreak();
    nodelay(stdscr, TRUE);
    game_init();
    Direction input_dir = LEFT;
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_GREEN);
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLUE, COLOR_GREEN);
    init_pair(3, COLOR_RED, COLOR_GREEN);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_GREEN);
    while (!(game.end)) {
        erase();
        int input = inputkey();
        if (input == 100) {
            break; 
        }
        spawn_enemy();
        for (int i = 0; i < 3; i++) {
            if (game.enemies[i].visible) move_enemy(&(game.enemies[i]));
        }
        if (input >= 0 && input <= 3) input_dir = (Direction) input;
        move_pacman(input_dir);
        if (game.reset) {
            reset();
        }

        render();
        //mvprintw(0, 0, "%d, %d", game.enemies[0].target_x, game.enemies[0].target_y);
        //mvprintw(0, 0, "%d", game.enemies[0].dir);
        refresh();
        napms(180);
    }
    endwin();
    printf("Score: %d", game.points);
    return 0;
}