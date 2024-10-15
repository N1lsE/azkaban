#include "button.h"
#include "SDL.h"
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "stdbool.h"
#include <stdlib.h>

// Function to create text texture
SDL_Texture *create_text_texture(SDL_Renderer *renderer, char *text,
                                 SDL_Color textColor) {
  // Load font
  TTF_Font *font = TTF_OpenFont("../FiraCodeNerdFontMono-Regular.ttf",
                                24); // Make sure you have this font file
  if (!font) {
    printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
  SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, textColor);
  if (textSurface == NULL) {
    printf("Unable to render text surface! SDL_ttf Error: %s\n",
           TTF_GetError());
    return NULL;
  }
  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(renderer, textSurface);
  if (textTexture == NULL) {
    printf("Unable to create texture from rendered text! SDL Error: %s\n",
           SDL_GetError());
  }
  SDL_FreeSurface(textSurface);
  return textTexture;
}

void button_init(Button *button, char *button_text, SDL_Rect *button_rect,
                 SDL_Color *button_color, SDL_Color *hover_color,
                 SDL_Color *font_color, SDL_Color *font_hover_color,
                 SDL_Renderer *renderer) {
  // TODO: Implement safty checks
  button->button_text = create_text_texture(renderer, button_text, *font_color);
  button->button_rect = button_rect;
  button->button_color = button_color;
  button->hover_color = hover_color;
  button->font_color = font_color;
  button->font_hover_color = font_hover_color;
}

bool is_button_hovered(SDL_Rect buttonRect) {
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);

  if (mouseX > buttonRect.x && mouseX < buttonRect.x + buttonRect.w &&
      mouseY > buttonRect.y && mouseY < buttonRect.y + buttonRect.h) {
    return true;
  }
  return false;
}

void button_render(Button *button, SDL_Renderer *renderer) {
  // render button box
  if (is_button_hovered(*button->button_rect) && button->hover_color != NULL) {
    SDL_SetRenderDrawColor(renderer, button->hover_color->r,
                           button->hover_color->g, button->hover_color->b,
                           button->hover_color->a);
  } else {
    SDL_SetRenderDrawColor(renderer, button->button_color->r,
                           button->button_color->g, button->button_color->b,
                           button->button_color->a);
  }
  SDL_RenderFillRect(renderer, button->button_rect);

  // render buton text
  int textW = 0, textH = 0;
  SDL_QueryTexture(button->button_text, NULL, NULL, &textW, &textH);
  textH -= textH * 0.05;
  textW -= textW * 0.3;

  SDL_Rect textRect = {
      button->button_rect->x + (button->button_rect->w - textW) / 2,
      button->button_rect->y + (button->button_rect->h - textH) / 2,
      textW - (textW * 0.05), textH - (textH * 0.05)};
  SDL_RenderCopy(renderer, button->button_text, NULL, &textRect);
}
void button_replace_text(Button *button, char *new_text,
                         SDL_Renderer *renderer) {
  button->button_text =
      create_text_texture(renderer, new_text, *button->font_color);
}

void button_destroy(Button *button) {
  // TODO: Destroy Button
  exit(EXIT_FAILURE);
}
