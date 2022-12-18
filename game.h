#ifndef GAME_H
#define GAME_H

#define WALL 1 << 0
#define PELLET 1 << 1
#define POWER_PELLET 1 << 2
#define PACMAN 1 << 3
#define RED_ENEMY 1 << 4
#define YELLOW_ENEMY 1 << 5
#define GREEN_ENEMY 1 << 6

extern char board[25][28];

typedef enum Direction {
    UP = 0, RIGHT, LEFT, DOWN 
} Direction; 

typedef enum EnemyType {
    RED = 0, YELLOW, GREEN 
} EnemyType; 

typedef struct Pacman {
	int x;
	int y;
	Direction dir; 
	int lives;
    char super_st; 
    int super_timer; 
} Pacman;

typedef struct Enemy {
	int x;
	int y;
    Direction dir; 
	EnemyType type;
    int steps; 
    int target_x;
    int target_y;
	char visible; 
} Enemy;

typedef struct Game {
    Pacman pacman; 
    Enemy enemies[3];
    int points; 
    int respawn; 
    int respawn_number;
    char reset;
    char end; 
} Game; 

extern Game game; 

Direction opposite_direction(Direction dir); 
char chkdir(int x, int y, Direction dir);
void game_init(void);
void render(void);
void reset(void);
void spawn_enemy(void);

#endif
