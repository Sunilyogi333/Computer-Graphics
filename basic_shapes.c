// Title: Implementation of Basic Shapes (Circle, Rectangle, Polygon) with SDL2

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Function to plot a point
void plotPoint(SDL_Renderer *renderer, int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

// Function to draw a circle using the circle equation
void drawCircle(SDL_Renderer *renderer, int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r;

    // Drawing the circle using symmetry in all octants
    while (x <= y) {
        plotPoint(renderer, xc + x, yc + y);
        plotPoint(renderer, xc - x, yc + y);
        plotPoint(renderer, xc + x, yc - y);
        plotPoint(renderer, xc - x, yc - y);
        plotPoint(renderer, xc + y, yc + x);
        plotPoint(renderer, xc - y, yc + x);
        plotPoint(renderer, xc + y, yc - x);
        plotPoint(renderer, xc - y, yc - x);

        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

// Function to draw a rectangle using two diagonal corners
void drawRectangle(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y1); // Top side
    SDL_RenderDrawLine(renderer, x2, y1, x2, y2); // Right side
    SDL_RenderDrawLine(renderer, x2, y2, x1, y2); // Bottom side
    SDL_RenderDrawLine(renderer, x1, y2, x1, y1); // Left side
}

// Function to draw a polygon with n vertices
void drawPolygon(SDL_Renderer *renderer, int n, int *points) {
    for (int i = 0; i < n - 1; i++) {
        SDL_RenderDrawLine(renderer, points[2 * i], points[2 * i + 1], points[2 * (i + 1)], points[2 * (i + 1) + 1]);
    }
    // Closing the polygon by connecting the last vertex to the first
    SDL_RenderDrawLine(renderer, points[2 * (n - 1)], points[2 * (n - 1) + 1], points[0], points[1]);
}

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow(
        "Basic Shapes (Circle, Rectangle, Polygon)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
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

    // Set render draw color for shapes (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Draw a circle (center (250, 250), radius 100)
    drawCircle(renderer, 250, 250, 100);

    // Draw a rectangle (top-left (50, 50), bottom-right (450, 400))
    drawRectangle(renderer, 50, 50, 450, 400);

    // Draw a polygon (triangle with vertices (100, 100), (400, 100), (250, 400))
    int points[] = {100, 100, 400, 100, 250, 400};
    drawPolygon(renderer, 3, points);

    // Present the renderer (display the shapes)
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
// gcc -o basic_shapes basic_shapes.c -lSDL2

//explanation: -lSDL2: Links the SDL2 library.


// Command to Execute:
// ./basic_shapes
