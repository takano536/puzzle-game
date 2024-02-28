#include <SDL2/SDL.h>

namespace ShapeRenderer {

void aafilledCircleRGBA(SDL_Renderer *renderer, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void aafilledRoundRectRGBA(SDL_Renderer *renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

}  // namespace ShapeRenderer