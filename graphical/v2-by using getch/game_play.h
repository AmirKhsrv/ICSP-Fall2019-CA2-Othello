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
void get_and_set(char[RO][CO], char*);
void marble_reverser(char[RO][CO], char*, int, int);
void seek_check_reverse(char[RO][CO], char, char, int, int, int, int);
void jumper(char[RO][CO], int*, int*, int, int,int, int, int*);