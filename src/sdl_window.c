#include "SDL.h"
#include "SDL_ttf.h"
#include "stdbool.h"

// Function to initialize SDL components
bool init(SDL_Window **window, SDL_Renderer **renderer, int win_width,
          int win_height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  // Initialize SDL_ttf for text rendering
  if (TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
    return false;
  }

  *window = SDL_CreateWindow("SDL Button Example", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, win_width, win_height,
                             SDL_WINDOW_SHOWN);
  if (!*window) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
  if (!*renderer) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  return true;
}
