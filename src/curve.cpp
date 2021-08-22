#include <SDL2/SDL.h>
#include <vector>

SDL_Point linearInterpolation(SDL_Point a, SDL_Point b, float time) {
    int x = (b.x - a.x) * time + a.x;
    int y = (b.y - a.y) * time + a.y;

    return {x, y};
}

SDL_Point bezierCurve(std::vector<SDL_Point> points, float time) {
    if(!points.size())
        return {-10, -10};
        
    while (points.size() > 1) {
        for(int i = 0; i < points.size() - 1; i++) {
            points[i] = linearInterpolation(points[i], points[i + 1], time);
        }
        points.pop_back();
    }

    return points[0];
}
