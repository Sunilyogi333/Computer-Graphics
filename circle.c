#include <SDL2/SDL.h>
#include <stdio.h>

// Function to draw pixels for all octants
void drawCircle(SDL_Renderer *renderer, int xc, int yc, int x, int y) {
    SDL_RenderDrawPoint(renderer, xc + x, yc + y);
    SDL_RenderDrawPoint(renderer, xc - x, yc + y);
    SDL_RenderDrawPoint(renderer, xc + x, yc - y);
    SDL_RenderDrawPoint(renderer, xc - x, yc - y);
    SDL_RenderDrawPoint(renderer, xc + y, yc + x);
    SDL_RenderDrawPoint(renderer, xc - y, yc + x);
    SDL_RenderDrawPoint(renderer, xc + y, yc - x);
    SDL_RenderDrawPoint(renderer, xc - y, yc - x);
}

// Function to draw a circle using the Midpoint Algorithm
void midpointCircle(SDL_Renderer *renderer, int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r;

    drawCircle(renderer, xc, yc, x, y);

    while (x < y) {
        if (p < 0) {
            x++;
            p += 2 * x + 1;
        } else {
            x++;
            y--;
            p += 2 * x - 2 * y + 1;
        }
        drawCircle(renderer, xc, yc, x, y);
    }
}

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow(
        "Midpoint Circle Algorithm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        500, 500, SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set render draw color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White circle

    // Draw the circle
    midpointCircle(renderer, 250, 250, 100);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Wait for 5 seconds
    SDL_Delay(5000);

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
