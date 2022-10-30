
#include<stdio.h>
#include<stdlib.h>
#include "graphics.h"
#include "game_options.h"
#include "end_game.h"
#include "game_play.h"
#include "display.h"

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
/*int update_board(char[RO][CO]);
int draw_board(char[RO][CO]);
void get_and_set(char[RO][CO], char*);
void marble_reverser(char[RO][CO], char*, int, int);
void score_calculator(char[RO][CO], int*, int*);
int possible_choices(char[RO][CO], char*);
void winner_identifier(char[RO][CO], int*, int*);
int ask_play_again();
void print_board(char[RO][CO], int*, int*);
void initial_game(char[RO][CO]);
*/
int main()
{
	char turn = 'b';/*This will be used to change turns*/
	char grid[RO][CO];
	int number_of_b_marbles = 0;/*We will save number of black marbles here.*/
	int number_of_w_marbles = 0; /*We will save number of white marbles here.*/
	//system("color e1"); /* the background color of console :) */
	do /*This loop is the main loop of the game that help to play again after the end of one round */
	{
		turn = 'b';
		initial_game(grid); /*This function will reinitial the grid and features of the game*/
		initwindow(BOARD_LENGTH, BOARD_LENGTH, "OTHELLO", 300, 20);
		draw_board(grid);
		possible_choices(grid, &turn); /*This function will show which cells you can put your marble with ~ in the board*/
		while (possible_choices(grid, &turn)) /*This loop is for continue playing round by round*/
		{ /*If possible_choices cant find a cell to place marble it will return 0 though the loop will be broken*/
			print_board(grid, &number_of_b_marbles, &number_of_w_marbles);/*Score calculator will be called in this function too so we get number of marbles as arguments*/
			get_and_set(grid, &turn);/*Will get input and then set the input in aright place*/
		}
		draw_board(grid);
		print_board(grid, &number_of_b_marbles, &number_of_w_marbles);/*After finishing game we will show board one more time*/
		winner_identifier(grid, &number_of_b_marbles, &number_of_w_marbles);/*Tell the winner according to number of each players marbles*/
	} while (ask_play_again());/*Will ask if players want to play again or exit*/
	int a;
	draw_board(grid);
	a = getch();
	return 0;
}

