#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "render.hpp"

int nodeAtPos(std::vector<SDL_Point> points, SDL_Point mousePos, int tolerance) {
    for (int i = 0; i < points.size(); i++){
        SDL_Point upperLeft = {points[i].x - tolerance, points[i].y - tolerance};
        SDL_Point bottomRight = {points[i].x + tolerance, points[i].y + tolerance};
        if (mousePos.x > upperLeft.x && mousePos.x < bottomRight.x &&
            mousePos.y > upperLeft.y && mousePos.y < bottomRight.y) {
                return i;
        }
    }
    for (auto &point: points) {
        
    }
    return -1;
}

#define WIDTH 600
#define HEIGHT 600

std::vector<SDL_Point> points = {};
SDL_Window *window = SDL_CreateWindow("Bezier Curve", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

int main(int argc, char** argv) {
    int selectedPoint = -1;
    int curveSteps = 200;

    bool running = true;
    SDL_Event event;

    #define FPS 60
    #define FRAME_DELAY 1000 / FPS
    uint32_t frameStart;
    int frameTime;

    while(running) {
        frameStart = SDL_GetTicks();

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        SDL_Point mousePos = {event.button.x, event.button.y};
                        selectedPoint = nodeAtPos(points, mousePos, 15);

                        if(selectedPoint == -1) {
                            points.push_back(mousePos);
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        selectedPoint = -1;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (selectedPoint != -1) {
                        points[selectedPoint] = {event.motion.x, event.motion.y};
                    }
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_w:
                            curveSteps++;
                            break;
                        case SDLK_s:
                            if (curveSteps > 3) {
                                curveSteps--;
                            }
                            break;
                        case SDLK_e:
                            points.clear();
                            break;
                        case SDLK_q:
                            if (selectedPoint != - 1) {
                                points.erase(points.begin() + selectedPoint);
                                selectedPoint = -1;
                            }
                            break;
                    }
            }
        }


        #define BG_COLOR 41, 47, 54, 255
        #define GUIDE_COLOR 255, 230, 109, 255
        #define CURVE_COLOR 78, 205, 196, 255

        #define NODE_RADIUS 3
        #define CURVE_DOT_RADIUS 5

        SDL_SetRenderDrawColor(renderer, BG_COLOR);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, GUIDE_COLOR);
        drawGuideLines(renderer, points, NODE_RADIUS);

        SDL_SetRenderDrawColor(renderer, CURVE_COLOR);
        drawCurve(renderer, points, curveSteps, CURVE_DOT_RADIUS);

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 0;
}