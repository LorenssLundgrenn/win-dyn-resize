#ifndef SDL_RENDERER_FUNCS
#define SDL_RENDERER_FUNCS

void updateViewport(SDL_Renderer* renderer, int windowWidth, int windowHeight);

void resizeWindow(SDL_Renderer* renderer, SDL_Window* window, int windowWidth, int windowHeight);

#endif