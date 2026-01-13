#include <SDL2/SDL.h>
#include <iostream>

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Circle parameters
int circleRadius = 30;
int initialRadius = 30;
int circleX = SCREEN_WIDTH / 2;
int circleY = SCREEN_HEIGHT / 2;

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;

// Initializes SDL and creates a window
bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("Resizable Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL)
        {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0, 100, 50, 255);
            }
        }
    }

    return success;
}

// Frees media and shuts down SDL
void close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();
}

// Draw circle on screen
void drawCircle()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 80, 255);
    SDL_RenderDrawPoint(gRenderer, circleX, circleY);

    for (int w = 0; w < circleRadius * 2; w++)
    {
        for (int h = 0; h < circleRadius * 2; h++)
        {
            int dx = circleRadius - w; // horizontal offset
            int dy = circleRadius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (circleRadius * circleRadius))
            {
                SDL_RenderDrawPoint(gRenderer, circleX + dx, circleY + dy);
            }
        }
    }
}

int main(int argc, char* args[])
{
    if (!init())
    {
        std::cout << "Failed to initialize!" << std::endl;
    }
    else
    {
        bool quit = false;
        SDL_Event e;

        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }

            // Increase the radius
            circleRadius++;

            // Check collision with window boundaries
            if ((circleX + circleRadius >= SCREEN_WIDTH) || (circleY + circleRadius >= SCREEN_HEIGHT))
            {
                circleRadius = initialRadius;
            }

            SDL_SetRenderDrawColor(gRenderer, 255, 100, 50, 255);
            SDL_RenderClear(gRenderer);

            // Draw circle
            drawCircle();

            // Update screen
            SDL_RenderPresent(gRenderer);
        }
    }

    close();

    return 0;
}