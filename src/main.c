#include "game.h"

int main(int argc, char* argv[]) {
    
    SnakeSegment snake[100];
    int snake_length;
    init_snake(snake, &snake_length);

    Food food;
    generate_food(&food, snake, snake_length);

    int dir_x = 1, dir_y = 0; 

    int running = 1;
    SDL_Event event;
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Snake SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur lors de la création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:    dir_x = 0; dir_y = -1; break;
                    case SDLK_DOWN:  dir_x = 0; dir_y = 1; break;
                    case SDLK_LEFT:  dir_x = -1; dir_y = 0; break;
                    case SDLK_RIGHT: dir_x = 1; dir_y = 0; break;
                }
            }
        }

        move_snake(snake, &snake_length, dir_x, dir_y);

        if (snake[0].x == food.x && snake[0].y == food.y) {
            snake_length++;
            generate_food(&food, snake, snake_length);
        }

        if (snake[0].x < 0 || snake[0].x >= GRID_WIDTH || snake[0].y < 0 || snake[0].y >= GRID_HEIGHT) {
            running = 0;
        }

        for (int i = 1; i < snake_length; i++) {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 96, 63, 38, 255);
        SDL_RenderClear(renderer);

        draw_grid(renderer);
        draw_snake(renderer, snake, snake_length);
        draw_food(renderer, food);

        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}