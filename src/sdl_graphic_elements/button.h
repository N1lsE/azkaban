#include "SDL.h"
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_ttf.h"

/** struct Button
 *
 * @param button - the button gets initializes into this
 *
 * @param button_text - button text
 *
 * @param button_rect - button size, hight, width and position
 *
 * @param button_color - main color shown
 *
 * @param hover_color - hover  color shown
 * not used when you don't use it
 *
 * @param font_color - font color shown
 *
 * @param font_hover_color - font hover color shown
 * not used when you don't use it
 *
 * @param (*update)(struct Button *self)
 * this is a function, that can be run. it could be anything that you want but i
 * want to use this to run every loop
 */
typedef struct Button {
  SDL_Rect *button_rect;
  SDL_Texture *button_text;
  SDL_Color *button_color;
  SDL_Color *hover_color;
  SDL_Color *font_color;
  SDL_Color *font_hover_color;
  void (*update)(struct Button *self);
} Button;

/** Function initializes a button
 *
 * @retrun void
 *
 *
 * @param button - the button gets initializes into this
 *
 * @param button_text - button text
 *
 * @param button_rect - button size, hight, width and position
 *
 * @param button_color - main color shown
 *
 * @param hover_color - hover  color shown
 * not used when you don't use it
 *
 * @param font_color - font color shown
 *
 * @param font_hover_color - font hover color shown
 * not used when you don't use it
 *
 * @param renderer
 */
void button_init(Button *button, char *button_text, SDL_Rect *button_rect,
                 SDL_Color *button_color, SDL_Color *hover_color,
                 SDL_Color *font_color, SDL_Color *font_hover_color,
                 SDL_Renderer *renderer);

/** Function renders the button to the renderer
 *
 *
 */
void button_render(Button *button, SDL_Renderer *renderer);

void button_replace_text(Button *button, char *new_text,
                         SDL_Renderer *renderer);
void button_destroy(Button *button);
