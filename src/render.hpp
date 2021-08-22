#include <SDL2/SDL.h>
#include <vector>

void drawGuideLines(SDL_Renderer *renderer, std::vector<SDL_Point> points, int radius);

void drawCurve(SDL_Renderer *renderer, std::vector<SDL_Point> points, int steps, int radius);