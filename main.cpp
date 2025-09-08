#include <SDL2/SDL.h>

//2:3 height to length ratio
#define WIN_HEIGHT 300 
#define WIN_LENGTH 450

enum GameState {
    MAIN_MENU,
    FIGHT_MENU,
    ITEM_MENU,
    TURN_EXECUTION,
    GAME_OVER
};

bool isInside(int x, int y, SDL_Rect rect) {
    return x >= rect.x && x <= rect.x + rect.w &&
           y >= rect.y && y <= rect.y + rect.h;
}

SDL_Rect fightButton;
SDL_Rect itemButton;
SDL_Rect backButton;


int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    SDL_Window* window = SDL_CreateWindow("My SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIN_LENGTH, WIN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    GameState current_state = FIGHT_MENU;
    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_MOUSEBUTTONDOWN){
                int mouseX = e.button.x;
                int mouseY = e.button.y;
                if(isInside(mouseX, mouseY, fightButton) && current_state == MAIN_MENU){
                    current_state = FIGHT_MENU;
                }else if(isInside(mouseX, mouseY, itemButton) && current_state == MAIN_MENU){
                    current_state = ITEM_MENU;
                }else if(isInside(mouseX,mouseY, backButton) && (current_state == FIGHT_MENU || current_state == ITEM_MENU)){
                    current_state = MAIN_MENU;
                }
            }
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
            fightButton = {WIN_LENGTH/9, (3*WIN_HEIGHT)/4 + WIN_HEIGHT/24, WIN_LENGTH/3, WIN_HEIGHT/6};
            SDL_RenderFillRect(renderer, &fightButton);

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for item button
            itemButton = {5*WIN_LENGTH/9, (3*WIN_HEIGHT)/4 + WIN_HEIGHT/24, WIN_LENGTH/3, WIN_HEIGHT/6};
            SDL_RenderFillRect(renderer, &itemButton);
        }else if(current_state == FIGHT_MENU || current_state == ITEM_MENU){
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            backButton = {WIN_LENGTH/18, (3*WIN_HEIGHT)/4 + (2*WIN_HEIGHT)/24, WIN_LENGTH/9, (2*WIN_HEIGHT)/24};
            SDL_RenderFillRect(renderer, &backButton);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
