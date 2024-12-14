#include <SDL2/SDL.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NOT_IMPLEMENTED() \
    fprintf(stderr, "NOT_IMPLEMENTED: %s:%d: %s not implemented\n", __FILE__, __LINE__, __func__)

#define PANIC(msg)                                                                    \
    do {                                                                              \
        fprintf(stderr, "PANIC: %s:%d: %s: %s\n", __FILE__, __LINE__, __func__, msg); \
        exit(EXIT_FAILURE);                                                           \
    } while (0)

#define SDL_PANIC()                                                                                \
    do {                                                                                           \
        fprintf(stderr, "SDL_PANIC: %s:%d: In function '%s' we got the following SDL error: %s\n", \
            __FILE__, __LINE__, __func__, SDL_GetError());                                         \
        SDL_Quit();                                                                                \
        exit(EXIT_FAILURE);                                                                        \
    } while (0)

#define FRAMERATE_TARGET 60
#define FRAMETIME_TARGET_MS (int)(1000 / FRAMERATE_TARGET)

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define WINDOW_POS_X SDL_WINDOWPOS_CENTERED
#define WINDOW_POS_Y SDL_WINDOWPOS_CENTERED

#define GRID_SIZE_X 10
#define GRID_SIZE_Y 20

#define MENU_WIDTH_PCT 0.6

SDL_Window *g_window = NULL;
SDL_Surface *g_surface = NULL;

bool g_is_running = false;
size_t g_frame_counter = 0;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

Color C_BACKGROUND = {255, 90, 120};
Color RED = {255, 0, 0};
Color GREEN = {0, 255, 0};
Color BLUE = {0, 0, 255};

uint32_t map_rgb(const Color color) { return SDL_MapRGB(g_surface->format, color.r, color.g, color.b); }

typedef struct {
    SDL_Rect rect;
    uint32_t color;
} RenderRect;

uint64_t sdl_perf_counter_frequency = 0;

int64_t perf_counter_time_ns(const uint64_t start, const uint64_t end) {
    assert(end >= start);
    return (int64_t)(end - start) * 1000 * 1000 * 1000 / sdl_perf_counter_frequency;
}

int render_rect(const RenderRect rect) {
    return SDL_FillRect(
        g_surface,
        &rect.rect,
        rect.color);
}

void cleanup() {
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    g_surface = NULL;
    SDL_Quit();
}

int sdl_init() {
    sdl_perf_counter_frequency = SDL_GetPerformanceFrequency();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) SDL_PANIC();

    g_window = SDL_CreateWindow(
        "Hello SDL",
        WINDOW_POS_X,
        WINDOW_POS_Y,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!g_window) SDL_PANIC();

    g_surface = SDL_GetWindowSurface(g_window);

    SDL_FillRect(g_surface, NULL, map_rgb(C_BACKGROUND));

    const int menu_width = (int)(MENU_WIDTH_PCT * WINDOW_WIDTH);
    const int menu_co_width = WINDOW_WIDTH - menu_width;
    const int menu_height = WINDOW_HEIGHT;
    const RenderRect rect_menu = {
        menu_co_width,
        0,
        menu_width,
        menu_height,
        map_rgb(GREEN)};
    render_rect(rect_menu);

    const int play_width = menu_co_width;
    const int play_height = WINDOW_HEIGHT;
    const RenderRect rect_play = {
        0,
        0,
        play_width,
        play_height,
        map_rgb(RED)};
    render_rect(rect_play);

    SDL_UpdateWindowSurface(g_window);
    return 0;
}

void sdl_handle_events() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            g_is_running = false;
        }
    }
}

void render() {
}

int main() {
    if (sdl_init() != 0) {
        return EXIT_FAILURE;
    }

    g_is_running = true;
    while (g_is_running) {
        const uint64_t frame_start = SDL_GetPerformanceCounter();
        sdl_handle_events();
        render();
        const uint64_t frame_end = SDL_GetPerformanceCounter();

        const float64_t frame_time_ms = (float64_t)perf_counter_time_ns(frame_start, frame_end) / (1000.0 * 1000.0);
        printf("Finished handling the %zu. frame. It took %.2fms.\n", g_frame_counter, frame_time_ms);
        SDL_Delay(FRAMETIME_TARGET_MS);

        size_t tick_counter = g_frame_counter / 12;

        size_t idx_x = tick_counter % 10;
        size_t idx_y = tick_counter / 10;

        int menu_width = (int)(MENU_WIDTH_PCT * WINDOW_WIDTH);
        int menu_co_width = WINDOW_WIDTH - menu_width;
        int menu_height = WINDOW_HEIGHT;

        int play_width = menu_co_width;
        int play_height = WINDOW_HEIGHT;

        int block_size_x = play_width / GRID_SIZE_X;
        int block_size_y = play_height / GRID_SIZE_Y;

        RenderRect r = {
            idx_x * block_size_x,
            idx_y * block_size_y,
            block_size_x,
            block_size_y,
            map_rgb(BLUE)};
        render_rect(r);
        SDL_UpdateWindowSurface(g_window);
        g_frame_counter += 1;
    }

    cleanup();
    return EXIT_SUCCESS;
}