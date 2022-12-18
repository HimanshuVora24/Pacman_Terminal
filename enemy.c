#include <stdlib.h>
#include "enemy.h"
#include "game.h"

#define AVAIL_DIR(dirs, dir) (dirs & (1 << dir))

int availdir(Enemy * enemy) {
    char dirs = 15;
    if (chkdir(enemy->x, enemy->y, UP) & WALL) dirs &= ~(1 << UP);
    if (chkdir(enemy->x, enemy->y, LEFT) & WALL) dirs &= ~(1 << LEFT); 
    if (chkdir(enemy->x, enemy->y, RIGHT) & WALL) dirs &= ~(1 << RIGHT); 
    if (chkdir(enemy->x, enemy->y, DOWN) & WALL) dirs &= ~(1 << DOWN); 
    dirs &= ~(1 << opposite_direction(enemy->dir));
    return dirs; 
}

void move_enemy(Enemy * enemy) {
    if (enemy->steps <= 0) {
        if (rand()%3 == 0) {
            enemy->target_x = rand()%25;
            enemy->target_y = rand()%28;
        } else {
            enemy->target_x = game.pacman.x;
            enemy->target_y = game.pacman.y; 
        }
        enemy->steps = rand()%15 + 15; 
    } else {
        enemy->steps--;
    }

    int x_diff = enemy->x - enemy->target_x; 
    int y_diff = enemy->y - enemy->target_y; 
    int dirs = availdir(enemy);
    if (abs(x_diff) > abs(y_diff)) {
        if (x_diff < 0 && AVAIL_DIR(dirs, RIGHT)) {
            enemy->dir = RIGHT;
        } else if (AVAIL_DIR(dirs, LEFT)) {
            enemy->dir = LEFT; 
        } else {
            if (y_diff < 0 && AVAIL_DIR(dirs, DOWN)) {
                enemy->dir = DOWN;
            } else if (AVAIL_DIR(dirs, UP)) {
                enemy->dir = UP;
            } else {
                Direction dir; 
                do {
                    dir = rand()%4; 
                    enemy->dir = dir; 
                } while (AVAIL_DIR(dirs, dir) == 0);
            }
        }
    } else {
        if (y_diff < 0 && AVAIL_DIR(dirs, DOWN)) {
            enemy->dir = DOWN;
        } else if (AVAIL_DIR(dirs, UP)) {
            enemy->dir = UP; 
        } else {
            if (x_diff < 0 && AVAIL_DIR(dirs, RIGHT)) {
                enemy->dir = RIGHT;
            } else if (AVAIL_DIR(dirs, LEFT)) {
                enemy->dir = LEFT;
            } else {
                Direction dir; 
                do {
                    dir = rand()%4; 
                    enemy->dir = dir; 
                } while (AVAIL_DIR(dirs, dir) == 0);
            }
        }
    }

    //int next_block = chkdir(enemy->x, enemy->y, enemy->dir);
    if (board[enemy->y][enemy->x] & PACMAN) {
        if (game.pacman.dir == opposite_direction(enemy->dir)) {
            if (game.pacman.super_st) {
                game.enemies[enemy->type].visible = 0; 
                game.points+=10;
                if (game.respawn == 0) game.respawn = 10;
                game.respawn_number++;
            } else {
                game.pacman.lives--;
                if (game.pacman.lives > 0) {
                    game.reset = 1; 
                } else {
                    game.end = 1; 
                }
            } 
        }
    }

    board[enemy->y][enemy->x] &= ~(1 << (4+enemy->type));
    switch (enemy->dir) {
        case UP:
            enemy->y--;
            break;
        case DOWN:
            enemy->y++;
            break;
        case RIGHT:
            enemy->x++;
            break; 
        case LEFT:
            enemy->x--;
            break; 
    } 

    if (enemy->x >= 28) enemy->x = 0; 
    else if (enemy->x < 0) enemy->x = 27;
    if (enemy->y >= 25) enemy->y = 0;
    else if (enemy->y < 0) enemy->y = 24;

    board[enemy->y][enemy->x] |= (1 << (4+enemy->type));
}