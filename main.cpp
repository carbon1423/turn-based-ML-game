#include <SDL2/SDL.h>
#define WIN_HEIGHT 600
#define WIN_LENGTH 900

enum GameState {
    MAIN_MENU,
    MOVE_MENU,
    TURN_EXECUTION,
    GAME_OVER
};


int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    SDL_Window* window = SDL_CreateWindow("My SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIN_LENGTH, WIN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    GameState current_state = MAIN_MENU;
    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // dark gray
        SDL_RenderClear(renderer);


        // Create the menu area (Gray)
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_Rect menuBack = {0, (3*WIN_HEIGHT)/4, WIN_LENGTH, WIN_HEIGHT/4};
        SDL_RenderFillRect(renderer, &menuBack);
        if(current_state == MAIN_MENU){
            // Create the fight button and the item button (red and green for now)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for fight button
            SDL_Rect fightButton = {WIN_LENGTH/9, (3*WIN_HEIGHT)/4 + WIN_HEIGHT/24, WIN_LENGTH/3, WIN_LENGTH/9};
            SDL_RenderFillRect(renderer, &fightButton);

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for item button
            SDL_Rect itemButton = {5*WIN_LENGTH/9, (3*WIN_HEIGHT)/4 + WIN_HEIGHT/24, WIN_LENGTH/3, WIN_LENGTH/9};
            SDL_RenderFillRect(renderer, &itemButton);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
