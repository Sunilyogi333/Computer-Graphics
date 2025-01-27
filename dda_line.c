// Title: Drawing a Line Using Digital Differential Analyzer (DDA) Algorithm with SDL2

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

// Function to plot a point
void plotPoint(SDL_Renderer *renderer, int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

// Function to draw a line using the DDA algorithm
void ddaLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy); // Calculate the number of steps
    float xIncrement = dx / (float)steps; // Calculate the increment for x
    float yIncrement = dy / (float)steps; // Calculate the increment for y

    float x = x1;
    float y = y1;

    // Plot the points
    for (int i = 0; i <= steps; i++) {
        plotPoint(renderer, round(x), round(y)); // Round to the nearest integer
        x += xIncrement;
        y += yIncrement;
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
        "DDA Line Algorithm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
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

    // Draw the line using the DDA algorithm
    ddaLine(renderer, 50, 50, 400, 300); // Example coordinates

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
// gcc -o dda_line dda_line.c -lSDL2 -lm

//explanation: 
// -lSDL2: Links the SDL2 library.
// -lm: Links the math library for the round() function used in the algorithm.

// Command to Execute:
// ./dda_line

