#include <stdio.h>

#include <SDL.h>

#include "constants.hpp"
#include "render.hpp"

void updateViewport(SDL_Renderer* renderer, int windowWidth, int windowHeight) {
    //match viewport to aspect ratio
    long double viewportWidth = ASPECT_RATIO.w;
    long double viewportHeight = ASPECT_RATIO.h;
    
    //fit viewport within window
    bool viewportWidthclosest = ( windowWidth / viewportWidth ) < ( windowHeight / viewportHeight );
    double closestViewportSide = viewportWidthclosest ? viewportWidth : viewportHeight;
    double matchingWindowSide = viewportWidthclosest ? windowWidth : windowHeight;
    double transformScale = matchingWindowSide / closestViewportSide;
    viewportWidth *= transformScale;
    viewportHeight *= transformScale;

    SDL_Rect renderViewport;
    renderViewport.x = (windowWidth - viewportWidth) / 2;
    renderViewport.y = (windowHeight - viewportHeight) / 2;
    renderViewport.w = viewportWidth;
    renderViewport.h = viewportHeight;

    SDL_RenderSetViewport(renderer, &renderViewport);
}

void resizeWindow(SDL_Renderer* renderer, SDL_Window* window, int windowWidth, int windowHeight) {
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    updateViewport(renderer, windowWidth, windowHeight);
}
