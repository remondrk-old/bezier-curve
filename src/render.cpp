#include <SDL2/SDL.h>
#include <vector>
#include "curve.hpp"

void drawFillRect(SDL_Renderer *renderer, SDL_Point point, int radius) {
    SDL_Rect rect = {point.x - radius, point.y - radius, 2 * radius + 1, 2 * radius + 1};
    SDL_RenderFillRect(renderer, &rect);
}

void drawGuideLines(SDL_Renderer *renderer, std::vector<SDL_Point> points, int radius) {
    if (!points.size())
        return;

    SDL_RenderDrawLines(renderer, &points[0], points.size());
    for(const auto &point: points) {
        drawFillRect(renderer, point, radius);
    }
}

void drawCurve(SDL_Renderer *renderer, std::vector<SDL_Point> points, int steps, int radius) {
    float timeIncr = 1.0f / steps;
    for(float t = 0; t <= 1; t += timeIncr) {
        SDL_Point point = bezierCurve(points, t);
        drawFillRect(renderer, point, radius);
    }
}