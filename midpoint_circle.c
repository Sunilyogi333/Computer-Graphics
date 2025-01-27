// Title: To Draw a Circle Using Bresenham's Midpoint Circle Drawing Algorithm with SDL2

#include <SDL2/SDL.h>
#include <stdio.h>

// Function to plot a point in all octants using symmetry
void plotPoint(SDL_Renderer *renderer, int xc, int yc, int x, int y) {
    SDL_RenderDrawPoint(renderer, xc + x, yc + y);
    SDL_RenderDrawPoint(renderer, xc - x, yc + y);
    SDL_RenderDrawPoint(renderer, xc + x, yc - y);
    SDL_RenderDrawPoint(renderer, xc - x, yc - y);
    SDL_RenderDrawPoint(renderer, xc + y, yc + x);
    SDL_RenderDrawPoint(renderer, xc - y, yc + x);
    SDL_RenderDrawPoint(renderer, xc + y, yc - x);
    SDL_RenderDrawPoint(renderer, xc - y, yc - x);
}

// Function to draw a circle using Bresenham's Midpoint Circle Algorithm
void drawCircle(SDL_Renderer *renderer, int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 3 - 2 * r;

    // Plot the initial point
    plotPoint(renderer, xc, yc, x, y);

    // Use Bresenham's algorithm to plot the circle
    while (x <= y) {
        if (p < 0) {
            p = p + 4 * x + 6;
        } else {
            p = p + 4 * (x - y) + 10;
            y--;
        }
        x++;
        plotPoint(renderer, xc, yc, x, y);
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
        "Bresenham's Midpoint Circle Algorithm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
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

    // Set render draw color (black background)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Set render draw color for the circle (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Draw a circle with center (250, 250) and radius 100
    drawCircle(renderer, 250, 250, 100);

    // Present the renderer (display the circle)
    SDL_RenderPresent(renderer);

    // Wait for 5 seconds
    SDL_Delay(5000);

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// Command to Compile:
// gcc -o midpoint_circle midpoint_circle.c -lSDL2


// Command to Execute:
// ./midpoint_circle
