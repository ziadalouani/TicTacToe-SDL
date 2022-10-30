#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "logic.h"
#include "draw.h"

game_t init_game()
{
    game_t game = {
        .renderer = NULL,
        .window = NULL,
        .player = PLAYER_X,
        .board = {EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY},
        .state = RUNNING_STATE

    };

    return game;
}


Center get_center(int index){
    Center centre;
    switch (index)
    {
    case 0:
        /* code */
        centre.posy=SCREEN_HEIGHT/6;
        centre.posx=SCREEN_WIDTH/6;
        break;
    case 1:
        /* code */
        centre.posy=SCREEN_HEIGHT/6;
        centre.posx=SCREEN_WIDTH/2;
        break;
    case 2:
        /* code */
        centre.posy=SCREEN_HEIGHT/6;
        centre.posx=(5*SCREEN_WIDTH)/6;
        break;
    case 3:
        /* code */
        centre.posy=SCREEN_HEIGHT/2;
        centre.posx=SCREEN_WIDTH/6;
        break;
    case 4:
        centre.posy=SCREEN_HEIGHT/2;
        centre.posx=SCREEN_WIDTH/2;
        /* code */
        break;
    case 5:
        centre.posy=SCREEN_HEIGHT/2;
        centre.posx=(5*SCREEN_WIDTH)/6;
        /* code */
        break;
    case 6:
        centre.posy=(5*SCREEN_HEIGHT)/6;
        centre.posx=SCREEN_WIDTH/6;
        /* code */
        break;
    case 7:
        centre.posy=(5*SCREEN_HEIGHT/6);
        centre.posx=SCREEN_WIDTH/2;
      break;
    case 8:
        centre.posy=(5*SCREEN_HEIGHT)/6;
        centre.posx=(5*SCREEN_WIDTH/6);
      break;
        centre.posy=SCREEN_HEIGHT/6;
        centre.posx=SCREEN_WIDTH/6;
    default:
        break;
    }
    return centre;
}

int create_window_and_renderer(game_t *game)
{
    game->window = SDL_CreateWindow("TIC TAC TOE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (NULL == game->window)
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }
    else
    {
        game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (NULL == game->renderer)
        {
            SDL_DestroyWindow(game->window);
            SDL_Quit();
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

void quit_game(game_t *game)
{

    if (NULL != game->renderer)
    {
        SDL_DestroyRenderer(game->renderer);
        SDL_DestroyWindow(game->window);
        SDL_Quit();
    }
    if (NULL != game->window)
    {
        SDL_DestroyWindow(game->window);
        SDL_Quit();
    }
}

void get_mouse_position(int *posx, int *posy)
{
    int x, y;

    SDL_PumpEvents(); // make sure we have the latest mouse state.

    SDL_GetMouseState(&x, &y);
    *posx = x;
    *posy = y;
}

int run_game(game_t *game)
{
    int quit = 0;
    int x = 0;
    int y = 0;
    SDL_Event event;
    while (!quit)
    {
        
        draw_game(game);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                    case SDLK_DOWN:
                        int i =0;
                        game->state=RUNNING_STATE;
                        for (i=0;i<N*N;i++){
                            game->board[i]=EMPTY;
                        }
                        game->player = PLAYER_X;
                }

                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    get_mouse_position(&x, &y);
                    update_game(game,x,y);
                    check_game(game);
                    SDL_Log("Press down key to reset the game");
                    break;
                default:
                    SDL_ShowSimpleMessageBox(0, "Mouse", "Some other button was pressed!", game->window);
                    break;
                }
                break;
            default:
            {
            }

            }
        }
        


    }

    return EXIT_SUCCESS;
}




int get_grid_index(int x_click,int y_click){

    int index;
    if (y_click < SCREEN_HEIGHT/3){

        if (x_click <SCREEN_WIDTH/3){
            index=0;
        }
        else if (x_click<2*SCREEN_WIDTH/3)
        {
            index=1;
        }
        else{
            index=2;

        }
        }
            
        

    
    else if(y_click<2*SCREEN_HEIGHT/3)
    {
        if (x_click <SCREEN_WIDTH/3){
            index=3;
        }
        else if (x_click<2*SCREEN_WIDTH/3)
        {
            index=4;
        }
        else if(x_click>2*SCREEN_WIDTH/3){
           index=5;

        }
        }
    
    else{
        if (x_click <SCREEN_WIDTH/3){
            index=6;
        }
        else if (x_click<2*SCREEN_WIDTH/3)
        {
            index=7;
        }
        else{
            index=8;
        }
    }
    return index;
    }

void update_game(game_t * game,int x,int y){
    int index=get_grid_index(x,y);
    switch (game->board[index])
    {
    case EMPTY:
        game->board[index]=game->player;
        switch (game->player)
        {
        case PLAYER_X:
            game->player=O_STATE;
            break;
        case PLAYER_O:
            game->player=X_STATE;
            break;
        default:
            break;
        }
        break;
    
    default:
        break;
    }

}

int check_game(game_t *game)
{
    
    /* Checking if Player X won  */
    int winning_positions[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

    int i = 0;
    int j = 1;



    for (j = 1; j < 3; j++)
     {
         for (i = 0; i < N * N - 1; i++)
         {
             if (game->board[winning_positions[i][0]] == j && game->board[winning_positions[i][1]] == j && game->board[winning_positions[i][2]] == j)
             {
                 game->state = j;
                 SDL_Log("Player %d won",j);
                 return j;
             }
         }
     }
    for (i = 0; i < N * N; i++)
        {
            if (game->board[i] == EMPTY) {
             return 0;   
            }       
        }

    game->state = TIE_STATE;
    SDL_Log("DRAW");
    return TIE_STATE;
}