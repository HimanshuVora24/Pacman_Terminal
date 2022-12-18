#include <ncurses.h>
#include "game.h"

char board[25][28] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,4,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,0,0,0,0,0,0,0,4,0,0,0,0,0,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

Game game; 

Direction opposite_direction(Direction dir) {
    Direction opposite = UP; 
    switch (dir) {
        case UP:
            opposite = DOWN;
            break;
        case DOWN: 
            opposite = UP;
            break;
        case RIGHT: 
            opposite = LEFT;
            break;
        case LEFT:
            opposite = RIGHT;
            break; 
    }
    return opposite;
}

char chkdir(int x, int y, Direction dir) {
    switch (dir) {
        case UP:
            return board[y-1][x];
            break;
        case DOWN: 
            return board[y+1][x];
            break;
        case RIGHT: 
            return (x < 27) ? board[y][x+1] : board[y][0];
            break;
        case LEFT:
            return (x > 0) ? board[y][x-1] : board[y][27];
            break; 
    }
    return 0;
}

void reset(void) {
    game.respawn = 10; 
    game.respawn_number = 2;
    game.reset = 0; 
    game.end = 0;

    board[game.pacman.y][game.pacman.x] &= ~(PACMAN);
    board[game.pacman.y][game.pacman.x] &= ~(PACMAN);
    board[game.enemies[0].y][game.enemies[0].x] &= ~(RED_ENEMY);
    board[game.enemies[1].y][game.enemies[1].x] &= ~(YELLOW_ENEMY);
    board[game.enemies[2].y][game.enemies[2].x] &= ~(GREEN_ENEMY);
    
    game.enemies[0].x = 12; 
    game.enemies[0].y = 8;
    game.enemies[0].visible = 1; 
    game.enemies[0].steps = 0;
    game.enemies[0].dir = 0; 

   // game.enemies[1].x = 15;
    //game.enemies[1].y = 8;
    game.enemies[1].visible = 0;
    game.enemies[1].steps = 0; 
    game.enemies[1].dir = 0; 

    game.enemies[2].x = 1;
    game.enemies[2].y = 1;
    game.enemies[2].visible = 0; 
    game.enemies[2].steps = 0;
    game.enemies[2].dir = 0; 
    
    game.pacman.x = 12;
    game.pacman.y = 19;
    game.pacman.dir = LEFT;
    board[game.pacman.y][game.pacman.x] |= PACMAN;
}

void spawn_enemy(void) {
    if (game.respawn_number) {
        if (game.respawn > 0) {
            game.respawn--;
        } else {
            for (int i = 0; i < 3; i++) {
                if (game.enemies[i].visible == 0) {
                    game.enemies[i].visible = 1;
                    game.enemies[i].x = 12;
                    game.enemies[i].y = 8;
                    game.respawn_number--;
                    break; 
                }
            }
            if (game.respawn_number) game.respawn = 10;
        }
    }
}

void game_init(void) {
    game.respawn = 10; 
    game.respawn_number = 2;
    game.reset = 0; 
    game.end = 0;

    game.enemies[0].x = 12; 
    game.enemies[0].y = 8;
    game.enemies[0].type = RED;
    game.enemies[0].visible = 1; 
    game.enemies[0].steps = 0;
    game.enemies[0].dir = 0; 

    //game.enemies[1].x = 15;
    //game.enemies[1].y = 8;
    game.enemies[1].type = YELLOW;
    game.enemies[1].visible = 0;
    game.enemies[1].steps = 0; 
    game.enemies[1].dir = 0; 

    //game.enemies[2].x = 1;
    //game.enemies[2].y = 1;
    game.enemies[2].type = GREEN;
    game.enemies[2].visible = 0; 
    game.enemies[2].steps = 0;
    game.enemies[2].dir = 0; 
    
    game.pacman.x = 12;
    game.pacman.y = 19;
    game.pacman.lives = 3;
    game.pacman.dir = LEFT;
    game.pacman.super_st = 0; 
    game.pacman.super_timer = 0; 
    //game.pacman.next_dir = LEFT;

    game.points = 0;


    for (int i = 0; i < 3; i++) {
        board[game.enemies[i].y][game.enemies[i].x] |= (1 << (4 + game.enemies[i].type));
    }

    board[game.pacman.y][game.pacman.x] |= PACMAN;

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 28; j++) {
            if (board[i][j] == 0) {
                if (j%2) {
                    board[i][j] |= PELLET;
                }
            }
        }
    }
}

void render(void) {
    
    for (int i = 0; i < 25; i++) {
        int h_offset = 0; 
        for (int j = 0; j < 28; j++) {
            if (board[i][j] & WALL) {
                attron(COLOR_PAIR(1));
                mvprintw(i, j + h_offset, "o"); 
                attroff(COLOR_PAIR(1));
            } else if ((board[i][j] & GREEN_ENEMY) && (game.enemies[2].visible)) {
                attron(COLOR_PAIR(3));
                mvprintw(i, j + h_offset, "A");
                attroff(COLOR_PAIR(3));
            } else if ((board[i][j] & YELLOW_ENEMY) && (game.enemies[1].visible)) {
                attron(COLOR_PAIR(3));
                mvprintw(i, j + h_offset, "A");
                attroff(COLOR_PAIR(3));
            } else if ((board[i][j] & RED_ENEMY) && (game.enemies[0].visible)) {
                attron(COLOR_PAIR(3));
                mvprintw(i, j + h_offset, "A");
                attroff(COLOR_PAIR(3));
            } else if (board[i][j] & PACMAN) {
                if (game.pacman.super_st) attron(COLOR_PAIR(4));
                else attron(COLOR_PAIR(0));
                mvprintw(i, j + h_offset, "@");
                if (game.pacman.super_st) attroff(COLOR_PAIR(4));
                else attroff(COLOR_PAIR(0));
            } else if (board[i][j] & PELLET) {
                attron(COLOR_PAIR(2));
                mvprintw(i, j + h_offset, "*");
                attroff(COLOR_PAIR(2));
            } else if (board[i][j] & POWER_PELLET) {
                mvprintw(i, j + h_offset, "+");
            } else {
                attron(COLOR_PAIR(6));
                mvprintw(i, j, " ");
                attron(COLOR_PAIR(6));
            }
        }
    }

    mvprintw(0, 0, "Points: %d", game.points);
    mvprintw(27,0, "Lives: %d", game.pacman.lives);
}

