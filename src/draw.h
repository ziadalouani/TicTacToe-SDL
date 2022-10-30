#ifndef __DRAW__H
#define __DRAW__H


void draw_grid(game_t * game);
int SDL_RenderDrawCircle(game_t *game, Center center);
int SDL_Draw_X(game_t * game , Center center);
void draw_game(game_t * game);
#endif