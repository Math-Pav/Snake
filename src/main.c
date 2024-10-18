#include "game.h"

int main(int argc, char* argv[]){
    
    int mode = 0;

    printf("Choisissez le mode de jeu :\n");  // Choix du mode de Jeu
    printf("0 - Mode Normal\n");
    printf("1 - Mode avec différents fruits\n");
    printf("Entrez votre choix : ");
    scanf("%d", &mode);

    SnakeSegment snake[100];
    int snake_length;
    init_snake(snake, &snake_length); // Appel la fonction pour initialiser le serpent

    Food food;
    Bad_Food bad_food;
    generate_food(&food, &bad_food, snake, snake_length, mode); // Appel la fonction pour générer la nourriture 

    int dir_x = 1, dir_y = 0; 

    int running = 1;
    SDL_Event event;
    srand(time(NULL));

    // Initialisation de SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { 
        printf("Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }

    //Initialisation de SDL_TTF
    if (TTF_Init() == -1) {
        printf("Erreur lors de l'initialisation de SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
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

    // Création de la police de texte
    TTF_Font* font = TTF_OpenFont("COMICATE.TTF", 24);
    if (!font) {
        printf("Erreur lors du chargement de la police: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
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
            if (snake_length < WINNING_LENGTH) {
                if (food.type == Apple_food || food.type == Banana_food) {
                    snake_length++;

                    // Fruit pour le changement de direction
                    if (mode == 1 && food.type == Banana_food) {
                        if (rand() % 2 == 0) {
                            int temp = dir_x;
                            dir_x = -dir_y;
                            dir_y = temp;
                        } else {
                            int temp = dir_x;
                            dir_x = dir_y;
                            dir_y = -temp;
                        }
                        printf("Vous avez mangé une banane, direction changée !!\n");
                    }
                    generate_food(&food, &bad_food, snake, snake_length, mode);
                }
            
            // Fruit pour la téléportation
            else if (mode == 1 && food.type == Coco_food) {
                int new_x = rand() % GRID_WIDTH;
                int new_y = rand() % GRID_HEIGHT;

                int offset_x = new_x - snake[0].x;
                int offset_y = new_y - snake[0].y;

                for (int i = 0; i < snake_length; i++) {
                    snake[i].x += offset_x;
                    snake[i].y += offset_y;
                }
                snake_length++;

                printf("Vous avez mangé une coco, BOUM téléportation !!\n");
                generate_food(&food, &bad_food, snake, snake_length, mode);
                }
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
            generate_food(&food, &bad_food, snake, snake_length, mode);
        }

        // Test la condition de victoire pour le mode malus
        if (mode == 1 && snake_length == VERSION_MALU_WINNING_LENTGH) {
            printf("Bravo, vous êtes le BOSS du snake !!!\n");
            running = 0;
        }
        
        // Test si le serpent touche un mur
        if (snake[0].x < 0 || snake[0].x >= GRID_WIDTH || snake[0].y < 0 || snake[0].y >= GRID_HEIGHT) {
            running = 0;
        }

        // Test si le serpent touche la barre de score
        if (snake[0].y >= GRID_HEIGHT) {
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
        
        draw_score_bar(renderer);
        draw_score(renderer, snake_length, font);
        
        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    // Fontion pour fermer le programme sans allouer de la mémoire
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}