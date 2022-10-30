#include<stdio.h>
#include<stdlib.h>
#include "graphics.h"
#define CO 9
#define RO 9
#define BOARD_LENGTH 600 
#define SCORE_BOX_X 100
#define SCORE_BOX_Y 25
#define MARBLES_RADIOS 23
#define BOARD_START_X 100
#define BOARD_END_X 500
#define BOARD_START_Y 100
#define BOARD_END_Y 500
#define TURN_BOX_X 270
#define TURN_BOX_Y 20
#define TURN_DEFINER_RADIOS 28
int update_board(char[RO][CO]);
int draw_board(char[RO][CO]);
void initial_game(char[RO][CO]);
void console_to_graph(int, int, int, int,char,int);
void print_board(char[RO][CO], int*, int*);