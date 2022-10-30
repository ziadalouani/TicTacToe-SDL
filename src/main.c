/*##################################################################################################
*#  Author:	Ziad Alouani
*#  Version: 1.0
*#  Desc: Basic tic tac toe game using sdl
##################################################################################################*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "logic.h"
#include <unistd.h>
int main(int argc, char *argv[])
{
    game_t game = init_game();
    create_window_and_renderer(&game);
    run_game(&game);
    quit_game(&game);
    return EXIT_SUCCESS;
}