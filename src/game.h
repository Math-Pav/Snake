#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h> 

#define GRID_SIZE 20
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WIDTH 800
#define HEIGHT 600
#define GRID_WIDTH (SCREEN_WIDTH / GRID_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / GRID_SIZE)
#define SNAKE_SIZE 20
#define WINNING_LENGTH (GRID_WIDTH * GRID_HEIGHT)
#define VERSION_MALU_WINNING_LENTGH ((SCREEN_WIDTH / GRID_SIZE) * (SCREEN_HEIGHT / GRID_SIZE) - 2)

typedef struct {
    int x, y;
} SnakeSegment;

typedef struct {
    int x, y;
} Food;

typedef struct {
    int x, y;
}Bad_Food;

void draw_snake_head(SDL_Renderer *renderer, int x, int y);
void generate_food(Food* food, Bad_Food* bad_food, SnakeSegment snake[], int snake_length);
void draw_food(SDL_Renderer* renderer, Food food);
void draw_bad_food(SDL_Renderer* renderer, Bad_Food bad_food);
void init_snake(SnakeSegment snake[], int* snake_length);
void draw_snake(SDL_Renderer* renderer, SnakeSegment snake[], int snake_length);
void move_snake(SnakeSegment snake[], int* snake_length, int dir_x, int dir_y);
void draw_grid(SDL_Renderer* renderer);

#endif