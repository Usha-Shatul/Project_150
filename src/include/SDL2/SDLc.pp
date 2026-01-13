
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