/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <core/core.h>
# include <gba/video.h>
# include <gba/interrupt.h>
# include <modules/module.h>
# include <mmu/mmu.h>
# include <mmu/trigger.h>
# include <SDL.h>

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;

static void gpu_init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        panic("SDL initialization failed");
    }

    window   = SDL_CreateWindow(
                    NULL, //"GenesisBack",
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    480,
                    320,
                    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
            );
    if (!window) {
        panic("SDL window creation failed");
    }

    renderer = SDL_CreateRenderer(
                window,
                -1,
                0// SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
            );
    if (!renderer) {
        panic("SDL renderer creation failed");
    }

    texture  = SDL_CreateTexture(
                    renderer,
                    SDL_PIXELFORMAT_BGRA8888,
                    SDL_TEXTUREACCESS_STREAMING,
                    240,
                    160
            );
    if (!texture) {
        panic("SDL texture creation failed");
    }
    SDL_RenderPresent(renderer);
}

static void gpu_exit(void)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

static void gpu_reset(void)
{
    gpu_exit();
    gpu_init();
}

static void gpu_info(void) {}

static void gpu_start(void)
{
    SDL_RenderPresent(renderer);
}

REGISTER_MODULE(
    gpu,
    "Render the video",
    MODULE_HOOK_GBA,
    gpu_init,
    gpu_exit,
    gpu_reset,
    NULL,
    NULL,
    gpu_info
);