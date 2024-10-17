#include "game.h"

// Dessine la tete du serpent à une position (x et y) avec une couleur distincte
void draw_snake_head(SDL_Renderer *renderer, int x, int y) {
    SDL_Rect head_rect = {x, y, SNAKE_SIZE, SNAKE_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 80, 80, 255);
    SDL_RenderFillRect(renderer, &head_rect);
}

// Initialise la longueur du serpent à 5 et la position au centre
void init_snake(SnakeSegment snake[], int* snake_length) {
    *snake_length = 5;
    for (int i = 0; i < *snake_length; ++i) {
        snake[i].x = GRID_WIDTH / 2 - i;
        snake[i].y = GRID_HEIGHT / 2;
    }
}

// Dessine le serpent, en premier la tete et après le corps
void draw_snake(SDL_Renderer* renderer, SnakeSegment snake[], int snake_length){ 

    draw_snake_head(renderer, snake[0].x * GRID_SIZE, snake[0].y * GRID_SIZE);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 1; i < snake_length; ++i) {
        SDL_Rect segment = { snake[i].x * GRID_SIZE, snake[i].y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
        SDL_RenderFillRect(renderer, &segment);
    }
}

// Déplace le serpent avec une position (x et y)
void move_snake(SnakeSegment snake[], int* snake_length, int dir_x, int dir_y) {
    
    for (int i = *snake_length - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
    }

    snake[0].x += dir_x;
    snake[0].y += dir_y;
}

// Dessine une grille selon la taille de l'écran
void draw_grid(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            SDL_Rect cell = { x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

// Génére de la nourriture à une position aléatoire
void generate_food(Food* food, Bad_Food* bad_food, SnakeSegment snake[], int snake_length) {
    int valid = 0;

    while (!valid) {
        valid = 1;
        food->x = rand() % GRID_WIDTH;
        food->y = rand() % GRID_HEIGHT;
        bad_food->x = rand() % GRID_WIDTH;
        bad_food->y = rand() % GRID_HEIGHT;

        for (int i = 0; i < snake_length; i++) {
            if (snake[i].x == food->x && snake[i].y == food->y && snake[i].x == bad_food->x && snake[i].y == bad_food->y) {
                valid = 0;
                break;
            }
        }
    }
}

// Dessine la nourriture qui augmente le serpent de + 1
void draw_food(SDL_Renderer* renderer, Food food) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect fruit = { food.x * GRID_SIZE, food.y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
    SDL_RenderFillRect(renderer, &fruit);
}

// Dessine la nourriture qui diminue le serpent de - 1
void draw_bad_food(SDL_Renderer* renderer, Bad_Food bad_food) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect fruit = { bad_food.x * GRID_SIZE, bad_food.y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
    SDL_RenderFillRect(renderer, &fruit);
}