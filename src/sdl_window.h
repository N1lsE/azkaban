#include "SDL.h"
#include "SDL_ttf.h"
#include "stdbool.h"

/** Function that initializes the window
 *
 * @return true if OK or false if failed
 *
 * @param window a uninizialised SDL_Window which gets initialized
 * @param renderer also gets initialized
 * @param win_width self explainatory
 * @param win_height self explainatory
 */
bool init(SDL_Window **window, SDL_Renderer **renderer, int win_width,
          int win_height);
