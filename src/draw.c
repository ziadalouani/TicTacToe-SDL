#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "draw.h"
#include "logic.h"
void draw_grid(game_t *game)
{
    switch (game->state)
    {
    case RUNNING_STATE:
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        break;
    case PLAYER_X_WON_STATE:
        SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        break;
    case PLAYER_O_WON_STATE:
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
        break;
    case TIE_STATE:
        SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        break;
    default:
        break;
    }
    SDL_RenderDrawLine(game->renderer, SCREEN_WIDTH / 3, 0, SCREEN_WIDTH / 3, SCREEN_HEIGHT);
    SDL_RenderDrawLine(game->renderer, 2 * SCREEN_WIDTH / 3, 0, 2 * SCREEN_WIDTH / 3, SCREEN_HEIGHT);
    SDL_RenderDrawLine(game->renderer, 0, SCREEN_HEIGHT / 3, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
    SDL_RenderDrawLine(game->renderer, 0, 2 * SCREEN_HEIGHT / 3, SCREEN_WIDTH, 2 * SCREEN_HEIGHT / 3);
}

int SDL_RenderDrawCircle(game_t *game, Center center)
{
    int offsetx, offsety, d;
    int status;
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

    offsetx = 0;
    offsety = RADIUS;
    d = RADIUS - 1;
    status = 0;

    while (offsety >= offsetx)
    {
        status += SDL_RenderDrawPoint(game->renderer, center.posx + offsetx, center.posy + offsety);
        status += SDL_RenderDrawPoint(game->renderer, center.posx + offsety, center.posy + offsetx);
        status += SDL_RenderDrawPoint(game->renderer, center.posx - offsetx, center.posy + offsety);
        status += SDL_RenderDrawPoint(game->renderer, center.posx - offsety, center.posy + offsetx);
        status += SDL_RenderDrawPoint(game->renderer, center.posx + offsetx, center.posy - offsety);
        status += SDL_RenderDrawPoint(game->renderer, center.posx + offsety, center.posy - offsetx);
        status += SDL_RenderDrawPoint(game->renderer, center.posx - offsetx, center.posy - offsety);
        status += SDL_RenderDrawPoint(game->renderer, center.posx - offsety, center.posy - offsetx);

        if (status < 0)
        {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx)
        {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (RADIUS - offsety))
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int SDL_Draw_X(game_t *game, Center center)
{
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(game->renderer, center.posx - 0.6 * SCREEN_WIDTH / 6, center.posy - 0.6 * SCREEN_HEIGHT / 6, center.posx + 0.6 * SCREEN_WIDTH / 6, center.posy + 0.6 * SCREEN_HEIGHT / 6);
    SDL_RenderDrawLine(game->renderer, center.posx + 0.6 * SCREEN_WIDTH / 6, center.posy - 0.6 * SCREEN_HEIGHT / 6, center.posx - 0.6 * SCREEN_WIDTH / 6, center.posy + 0.6 * SCREEN_HEIGHT / 6);
    return EXIT_SUCCESS;

}

void draw_game(game_t *game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);
    draw_grid(game);
    int i = 0;
    Center centre;
    for (i = 0; i < N * N; i++)
    {
        centre = get_center(i);
        switch (game->board[i])
        {
        case X_STATE:
            SDL_Draw_X(game, centre);
            break;
        case O_STATE:
            SDL_RenderDrawCircle(game, centre);
            break;
        default:
            break;
        }
    }

    SDL_RenderPresent(game->renderer);
}