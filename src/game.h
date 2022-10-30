#ifndef __GAME__H
#define __GAME__H
#define N 3
#define SCREEN_WIDTH 640.0
#define SCREEN_HEIGHT 480.0
#define EMPTY 0
#define PLAYER_X 1
#define PLAYER_O 2
#define RUNNING_STATE 0
#define PLAYER_X_WON_STATE 1
#define PLAYER_O_WON_STATE 2
#define TIE_STATE 3
#define QUIT_STATE 4
#define X_STATE 1
#define O_STATE 2
typedef struct color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} color;

typedef struct
{
    int board[N * N];
    int player;
    int state;
    SDL_Renderer *renderer ;
    SDL_Window *window;

} game_t;

#define RADIUS 60
typedef struct Center
{
    int posx;
    int posy;
} Center;

#endif