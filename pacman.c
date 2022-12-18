#include "pacman.h"
#include "game.h"


void move_pacman(Direction next_dir) {
    int mov = 1; 
    Pacman * pacman = &(game.pacman);
    if (pacman->super_st) {
        if (pacman->super_timer > 0) {
            pacman->super_timer--;
        } else {
            pacman->super_st = 0; 
        }
    }

    if (board[pacman->y][pacman->x] & PELLET) {
        game.points++;
        board[pacman->y][pacman->x] &= ~(PELLET);
    } else if (board[pacman->y][pacman->x] & POWER_PELLET) {
        game.points+=5;
        board[pacman->y][pacman->x] &= ~(POWER_PELLET);
        pacman->super_st = 1; 
        pacman->super_timer = 30;
    }

    char next_block = chkdir(pacman->x, pacman->y, next_dir);
    if ((next_block & WALL)) {
        next_block = chkdir(pacman->x, pacman->y, pacman->dir);
    } else {
        pacman->dir = next_dir;
    }

    if (next_block & WALL) {
        mov = 0; 
    } else {
        for (int i = 0; i < 3; i++) {
            if (next_block & (1 << (4 + i))) {
                if (pacman->super_st) {
                    game.enemies[i].visible = 0; 
                    game.points+=10;
                    if (game.respawn == 0) game.respawn = 10;
                    game.respawn_number++;
                } else {
                    pacman->lives--;
                    if (pacman->lives > 0) {
                        game.reset = 1; 
                        return;
                    } else {
                        game.end = 1; 
                        return;
                    }
                } 
            }
        }
    }

    if (mov) {
        board[pacman->y][pacman->x] &= ~(PACMAN);
        switch (pacman->dir) {
            case UP:
                pacman->y--;
                break;
            case DOWN:
                pacman->y++;
                break;
            case RIGHT:
                pacman->x++;
                break; 
            case LEFT:
                pacman->x--;
                break; 
        }
        if (pacman->x > 27) pacman->x = 0; 
        else if (pacman->x < 0) pacman->x = 27;
        if (pacman->y >= 25) pacman->y = 0;
        else if (pacman->y < 0) pacman->y = 24;
        board[pacman->y][pacman->x] |= PACMAN;
    } 
    for (int i = 0; i < 3; i++) {
        if ((board[pacman->y][pacman->x] & (1 << (4 + i))) && game.enemies[0].visible) {
            if (pacman->super_st) {
                game.enemies[i].visible = 0; 
                game.points+=10;
                if (game.respawn == 0) game.respawn = 10;
                game.respawn_number++;
            } else {
                pacman->lives--;
                if (pacman->lives > 0) {
                    game.reset = 1; 
                    return;
                } else {
                    game.end = 1; 
                    return;
                }
            } 
        } 
    }
    return;
}

