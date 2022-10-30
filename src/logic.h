#ifndef __LOGIC__H
#define __LOGIC__H
game_t init_game();
int create_window_and_renderer(game_t * game);
void quit_game(game_t *game);
int run_game(game_t * game);
Center get_center(int index);
void update_game(game_t * game,int x,int y);
int check_game(game_t *game);
#endif