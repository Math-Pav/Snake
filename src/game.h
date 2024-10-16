#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h> 

// Taille de la grille
#define GRID_SIZE 20
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WIDTH 800
#define HEIGHT 600
#define GRID_WIDTH (SCREEN_WIDTH / GRID_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / GRID_SIZE)
#define SNAKE_SIZE 20

typedef struct {
    int x, y;
} SnakeSegment;

typedef struct {
    int x, y;
} Food;

void draw_snake_head(SDL_Renderer *renderer, int x, int y);
void generate_food(Food* food, SnakeSegment snake[], int snake_length);
void draw_food(SDL_Renderer* renderer, Food food);
void init_snake(SnakeSegment snake[], int* snake_length);
void draw_snake(SDL_Renderer* renderer, SnakeSegment snake[], int snake_length);
void move_snake(SnakeSegment snake[], int* snake_length, int dir_x, int dir_y);
void draw_grid(SDL_Renderer* renderer);

#endif
