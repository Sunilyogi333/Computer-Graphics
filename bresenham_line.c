// Title: Drawing a Line Using Bresenham's Line Algorithm with SDL2
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Function to plot a point
void plotPoint(SDL_Renderer *renderer, int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

// Function to draw a line using Bresenham's Line Algorithm
void bresenhamLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;  // Step in x direction
    int sy = (y1 < y2) ? 1 : -1;  // Step in y direction
    int err = dx - dy;

    while (1) {
        plotPoint(renderer, x1, y1);  // Plot the current point
        if (x1 == x2 && y1 == y2) break; // Stop if the end point is reached
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
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
        "Bresenham's Line Algorithm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
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

    // Set render draw color (white line)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Draw the line using Bresenham's algorithm
    bresenhamLine(renderer, 50, 50, 400, 300); // Example coordinates

    // Present the renderer (display the line)
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
// gcc -o bresenham_line bresenham_line.c -lSDL2
//explanation: -lSDL2: Links the SDL2 library.

//Command to Execute:
// ./bresenham_line


