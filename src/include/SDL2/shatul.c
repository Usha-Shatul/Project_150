#include <SDL2/SDL.h>
#include <stdio.h>
#include <cmath>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 520

// Global variables
bool gameIsRunning = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int redColorCode = 0;
Uint32 startTime;
Uint32 currentTime;

bool initializeWindow(void)
{
    // Initialize SDL with video support
    // Automatically initializes the Event Handling, File I/O and Threading subsystems
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }

    // Create an SDL window
    window = SDL_CreateWindow(
        "SDL Introduction",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0);

    if (!window)
    {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }

    // Create an SDL renderer for rendering graphics in the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }
    return true;
}

void process_input(void)
{
    // Poll SDL events (e.g., window close)
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            gameIsRunning = false; // Exit the game loop
            break;

        default:
            break;
        }
    }
}

void drawCircle(int centerX, int centerY, int radius)
{
    // Set the render draw color to white (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int x = radius;
    int y = 0;
    int xChange = 1 - (radius << 1);
    int yChange = 0;
    int radiusError = 0;

    while (x >= y)
    {
        for (int i = centerX - x; i <= centerX + x; i++)
        {
            SDL_RenderDrawPoint(renderer, i, centerY + y);
            SDL_RenderDrawPoint(renderer, i, centerY - y);
        }

        for (int i = centerX - y; i <= centerX + y; i++)
        {
            SDL_RenderDrawPoint(renderer, i, centerY + x);
            SDL_RenderDrawPoint(renderer, i, centerY - x);
        }

        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
}



void draw()
{
    // Set the render draw color (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, redColorCode, 20, 205, 255);

    // Clear the renderer with the specified draw color
    SDL_RenderClear(renderer);

    // Draw a circle in the center of the window
    int circleRadius = 40;
    int circleCenterX = SCREEN_WIDTH / 2;
    int circleCenterY = SCREEN_HEIGHT / 2;
    drawCircle(circleCenterX, circleCenterY, circleRadius);

    // Present the renderer (draw the frame to the window)
    SDL_RenderPresent(renderer);
}

void destroyWindow(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char **argv)
{
    // The game loop control variable
    gameIsRunning = initializeWindow();
    startTime = SDL_GetTicks();

    // Game loop: keep the application running until 'running' is set to false
    while (gameIsRunning)
    {
        // Continuously polls for SDL events
        process_input();

        // Draw the rendered window
        draw();
    }

    // Clean up and exit the application
    destroyWindow();

    return 0;
}