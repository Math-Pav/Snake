#include "game.h"

// Dessine la tete du serpent à une position (x et y) avec une couleur distincte
void draw_snake_head(SDL_Renderer *renderer, int x, int y) {
    SDL_Rect head_rect = {x, y, SNAKE_SIZE, SNAKE_SIZE};
    SDL_SetRenderDrawColor(renderer, 17, 138, 178, 255);
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
    SDL_SetRenderDrawColor(renderer, 7, 59, 76, 255);
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

        int random_value = rand() % 6;
        if (random_value == 0 || random_value == 1) {
            food->type = Banana_food;
        }else if (random_value == 2) {
            food->type = Coco_food;
        }else{
            food->type = Apple_food;
        }
        
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

// Dessine la nourriture
void draw_food(SDL_Renderer* renderer, Food food) {
    if (food.type == Banana_food) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    } else if (food.type == Coco_food) {
        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); 
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }

    SDL_Rect fruit = { food.x * GRID_SIZE, food.y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
    SDL_RenderFillRect(renderer, &fruit);
}

// Dessine la nourriture qui diminue le serpent de - 1
void draw_bad_food(SDL_Renderer* renderer, Bad_Food bad_food) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect fruit = { bad_food.x * GRID_SIZE, bad_food.y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
    SDL_RenderFillRect(renderer, &fruit);
}

// Dessine le score au milieu de la barre
void draw_score(SDL_Renderer* renderer, int score, TTF_Font* font) {
    SDL_Color color = {255, 255, 255, 255};
    char score_text[50];
    sprintf(score_text, "Score: %d", score);

    // Créer une surface à partir du texte
    SDL_Surface* surface = TTF_RenderText_Solid(font, score_text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Calculer la position pour centrer le texte
    int x_position = (SCREEN_WIDTH - surface->w) / 2;
    SDL_Rect score_rect = {x_position, GRID_HEIGHT * GRID_SIZE + (SCORE_BAR_HEIGHT - surface->h) / 2, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &score_rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// Dessine la barre en bas de l'écran pour le score
void draw_score_bar(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect score_bar = {0, GRID_HEIGHT * GRID_SIZE, SCREEN_WIDTH, SCORE_BAR_HEIGHT}; // Position de la barre
    SDL_RenderFillRect(renderer, &score_bar);
}