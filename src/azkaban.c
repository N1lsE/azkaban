#include "SDL.h"
#include "db_manager.h"
#include "entry.h"
#include "sdl_graphic_elements/button.h"
#include "sdl_window.h"
#include "stdbool.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

// Function to handle rendering a button
void renderButton(SDL_Renderer *renderer, SDL_Rect buttonRect,
                  SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &buttonRect);
}

// Function to check if mouse is over button
bool isMouseOverButton(int mouseX, int mouseY, SDL_Rect buttonRect) {
  if (mouseX > buttonRect.x && mouseX < buttonRect.x + buttonRect.w &&
      mouseY > buttonRect.y && mouseY < buttonRect.y + buttonRect.h) {
    return true;
  }
  return false;
}

int main(int argc, char *argv[]) {
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Event event;
  bool app_is_quitting = false;

  int rc;
  rc = init(&window, &renderer, 800, 600);
  if (rc == false) {
    fprintf(stderr, "window init failed!\n");
    return EXIT_FAILURE;
  }

  SDL_Rect buttonRect = {0, 0, 150, 50};           // x, y, width, height
  SDL_Color buttonColor = {200, 200, 200, 255};    // Light Gray
  SDL_Color hoverColor = {150, 150, 150, 255};     // Gray
  SDL_Color font_color = {0, 0, 0, 255};           // Black
  SDL_Color font_hover_color = {255, 255, 0, 255}; // Yellow
  Button button;
  button_init(&button, "Hello World", &buttonRect, &buttonColor, &hoverColor,
              &font_color, &font_hover_color, renderer);

  while (!app_is_quitting) {
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
      case SDL_QUIT:
        app_is_quitting = true;
        break;
      case SDL_MOUSEBUTTONDOWN:
        printf("Mouse Button %d pressed at (%d, %d)\n", event.button.button,
               event.button.x, event.button.y);
        break;
      }
    }

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Render Button
    button_render(&button, renderer);

    // Update screen
    SDL_RenderPresent(renderer);
  }

  button_destroy(&button);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
