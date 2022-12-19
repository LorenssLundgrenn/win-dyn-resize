#include <stdio.h>

#include <SDL.h>

#include "constants.hpp"
#include "render.hpp"

bool init_SDL(int screen_width, int screen_height, SDL_Window*& window, SDL_Renderer*& renderer) {
    int init_resp = SDL_Init( SDL_INIT_VIDEO );
    if ( init_resp > 0 ) {
        printf("falied to initialize SDL\n^\t", SDL_GetError());
        return 0;
    }
    
    window = SDL_CreateWindow( "SDL project", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        screen_width, screen_height, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if ( window == NULL ) {
        printf("failed to create window\n^\t", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
    if ( renderer == NULL ) {
        printf("failed to create renderer\n");
        return 0;
    }

    return 1;
}

void destroy(SDL_Window*& window, SDL_Renderer*& renderer) {
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_Quit();
}

void start_game(SDL_Window* window, SDL_Renderer* renderer) {
    int windowWidth, windowHeight;
    resizeWindow(renderer, window, windowWidth, windowHeight);

    SDL_Event event; 
    
    int target_fps = 60;
    int timestamp = SDL_GetTicks();

    bool running = true; 
    while ( running ) { 
        
        int ticks_now = SDL_GetTicks();
        double delta_time = double(ticks_now - timestamp) / 1000 * 60;
        timestamp = ticks_now;

        while ( SDL_PollEvent(&event) ) { 
            if ( event.type == SDL_QUIT ) { 
                running = false; 
            } 
            else if ( event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED ) {
                resizeWindow(renderer, window, windowWidth, windowHeight);
            } 
            else if ( event.type == SDL_KEYDOWN ) {
                if ( event.key.keysym.sym == SDLK_ESCAPE ) {
                    running = false;
                }
            }
        }    

        SDL_RenderClear(renderer);

        //display viewport
        SDL_SetRenderDrawColor(renderer, 18, 255, 18, 255);
        SDL_RenderDrawRect(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, VOID_COLOR.r, VOID_COLOR.g, VOID_COLOR.b, VOID_COLOR.a);

        SDL_RenderPresent(renderer);

        SDL_Delay(1000 / target_fps);
    }
}

int main(int argc, char *argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if ( init_SDL(INITIAL_SCREEN_WIDTH, INITIAL_SCREEN_HEIGHT, window, renderer) ) { 
        start_game(window, renderer);
    } else printf("failed to initialize SDL\n^\t", SDL_GetError());

    destroy(window, renderer);

    return 0;
}