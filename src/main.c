#include "game.h"

int main(int argc, char* argv[]){
    
    int mode = 0;

    printf("Choisissez le mode de jeu :\n");  // Choix du mode de Jeu
    printf("0 - Mode Normal\n");
    printf("1 - Mode avec fruit malus\n");
    printf("Entrez votre choix : ");
    scanf("%d", &mode);

    SnakeSegment snake[100];
    int snake_length;
    init_snake(snake, &snake_length); // Appel la fonction pour initialiser le serpent

    Food food;
    Bad_Food bad_food;
    generate_food(&food, &bad_food, snake, snake_length); // Appel la fonction pour générer la nourriture 

    int dir_x = 1, dir_y = 0; 

    int running = 1;
    SDL_Event event;
    srand(time(NULL));

    // Initialisation de SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { 
        printf("Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenetre
    SDL_Window* window = SDL_CreateWindow("Snake SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création de la Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur lors de la création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // Boucle principale du jeu
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

        // Test pour ajouter de la longueur au serpent (mode normal)
        if (snake[0].x == food.x && snake[0].y == food.y) {
            if (snake_length < WINNING_LENGTH)
            {
                snake_length++;
                generate_food(&food, &bad_food, snake, snake_length);
            }
        }

        // Test la condition de victoire pour le mode normal
        if (snake_length == WINNING_LENGTH) {
            printf("Bravo, vous êtes le BOSS du snake !!!\n");
            running = 0; 
        }

        // Test pour enlever de la longueur au serpent (mode malus)
        if (mode == 1 && snake[0].x == bad_food.x && snake[0].y == bad_food.y) {
            snake_length--;
            generate_food(&food, &bad_food, snake, snake_length);
        }

        // Test la condition de victoire pour le mode malus
        if (mode == 1 && snake_length == VERSION_MALU_WINNING_LENTGH)
        {
            printf("Bravo, vous êtes le BOSS du snake !!!\n");
            running = 0;
        }
        
        // Test si le serpent touche un mur
        if (snake[0].x < 0 || snake[0].x >= GRID_WIDTH || snake[0].y < 0 || snake[0].y >= GRID_HEIGHT) {
            running = 0;
        }

        // Test si le serpent se mort 
        for (int i = 1; i < snake_length; i++) {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                running = 0;
            }
        }

        // Gestion de SDL et de fonction pour le jeu
        SDL_SetRenderDrawColor(renderer, 253, 240, 213, 255);
        SDL_RenderClear(renderer);

        draw_grid(renderer);
        draw_snake(renderer, snake, snake_length);
        draw_food(renderer, food);
        
        if (mode == 1){
            draw_bad_food(renderer, bad_food);
        }
        
        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    // Détruit le renderer, la window et quitte SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}