#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NOT_IMPLEMENTED() \
fprintf(stderr, "NOT_IMPLEMENTED: %s:%d: %s not implemented\n", __FILE__, __LINE__, __func__)

#define PANIC(msg) \
do { \
fprintf(stderr, "PANIC: %s:%d: %s: %s\n", __FILE__, __LINE__, __func__, msg); \
exit(EXIT_FAILURE); \
} while (0)

#define SDL_PANIC(msg) \
do { \
fprintf(stderr, "SDL_PANIC: %s:%d: %s - SDL_Error: %s\n", \
__FILE__, __LINE__, msg, SDL_GetError()); \
SDL_Quit(); \
exit(EXIT_FAILURE); \
} while (0)

#define FRAMERATE_TARGET 60
#define FRAMETIME_TARGET_MS (int)(1000 / FRAMERATE_TARGET)

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define WINDOW_POS_X SDL_WINDOWPOS_CENTERED
#define WINDOW_POS_Y SDL_WINDOWPOS_CENTERED

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) SDL_PANIC("SDL_Init failed");

    SDL_Window *window = SDL_CreateWindow(
        "Hello SDL",
        WINDOW_POS_X,
        WINDOW_POS_Y,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window) SDL_PANIC("SDL_CreateWindow failed");

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 90, 120));
    SDL_UpdateWindowSurface(window);

    bool is_running = true;
    SDL_Event e;
    while (is_running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                is_running = false;
            }
        }

        SDL_Delay(FRAMETIME_TARGET_MS);
    }

    SDL_DestroyWindow(window);
    window = NULL;
    surface = NULL;
    SDL_Quit();
    return 0;
}