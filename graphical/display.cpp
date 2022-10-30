#include<stdio.h>
#include<stdlib.h>
#include "graphics.h"
#include "display.h"
#include "game_options.h"

#define CO 9
#define RO 9
#define BOARD_LENGTH 600 
#define SCORE_BOX_X 100
#define TURN_BOX_X 270
#define TURN_BOX_Y 20
#define SCORE_BOX_Y 25
#define MARBLES_RADIOS 23
#define TURN_DEFINER_RADIOS 28
#define BOARD_START_X 100
#define BOARD_END_X 500
#define BOARD_START_Y 100
#define BOARD_END_Y 500
int draw_board(char grid[RO][CO])
{
	int marble_place_x = 25, marble_place_y = 25;
	int i, j;
	setcolor(RED);
	console_to_graph(-10, -10, GREEN, RED, 'r', 420);/*green cader*/
	console_to_graph(-10, -10, GREEN, RED, 'r', 420);/*box turn*/
	console_to_graph(200, -50, BLACK, LIGHTGRAY, 'c', 0);/*turn circle black*/

	setcolor(RED);
	rectangle(SCORE_BOX_X-10, SCORE_BOX_Y-10, SCORE_BOX_X + 410, SCORE_BOX_Y + 60);
	rectangle(SCORE_BOX_X - 10, SCORE_BOX_Y + 490, SCORE_BOX_X + 410, SCORE_BOX_Y + 560);

	setfillstyle(SOLID_FILL, COLOR(248, 254, 10));
	floodfill(SCORE_BOX_X -2, SCORE_BOX_Y -2, RED);
	setfillstyle(SOLID_FILL, COLOR(248, 254, 10));
	floodfill(SCORE_BOX_X - 2, SCORE_BOX_Y +505, RED);

	for (i = BOARD_START_X; i <= BOARD_END_X - 50; i += 50)
	{
		for (j = BOARD_START_Y; j <= BOARD_END_Y - 50; j += 50)
		{
			rectangle(i, j, i + 50, j + 50);
			setfillstyle(SOLID_FILL, LIGHTGREEN);
			floodfill(i + 1, j + 1, RED);
		}
	}
	console_to_graph(175, 175, WHITE, DARKGRAY, 'c', 0);/*white first circle*/
	console_to_graph(225, 225, WHITE, DARKGRAY, 'c', 0);/*white first circle*/
	console_to_graph(225, 175, BLACK, LIGHTGRAY, 'c', 0);/*black first circle*/
	console_to_graph(175, 225, BLACK, LIGHTGRAY, 'c', 0);/*black first circle*/
	console_to_graph(25, -50, BLACK, LIGHTGRAY, 'c', 0);/*white score circle*/
	console_to_graph(375, -50, WHITE, DARKGRAY, 'c', 0);/*black score circle*/

	for (i = 1; i <= CO; i++)
	{
		marble_place_x = 25;
		for (j = 1; j <= RO; j++)
		{
			if (grid[i][j] == 'w')
			{
				console_to_graph(marble_place_x, marble_place_y, WHITE, DARKGRAY, 'c', 0);
			}
			if (grid[i][j] == 'b')
			{
				console_to_graph(marble_place_x, marble_place_y, BLACK, LIGHTGRAY, 'c', 0);
			}
			if (grid[i][j] == '~')
			{
				console_to_graph(marble_place_x-5, marble_place_y-5, GREEN, BLUE, 'r', 10);
			}
			if (grid[i][j] == '#')
			{
				console_to_graph(marble_place_x-10, marble_place_y-10, LIGHTRED, BLUE, 'r', 20);
			}
			marble_place_x += 50;

		}
		marble_place_y += 50;
	}
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	floodfill(1, 1, RED);
	return 0;
}

void initial_game(char grid[RO][CO]) /*will reinitialize first features of the game*/
{
	int i = 1; /*just for next loops*/
	int j = 1; /*just for next loops*/
	for (i = 1; i<RO; i++)
	{
		for (j = 1; j<CO; j++)
		{
			grid[i][j] = '.'; /*put dot in all cells again . */
		}
	}
	grid[4][4] = 'w'; /*first cells that are white and black*/
	grid[5][5] = 'w';
	grid[4][5] = 'b';
	grid[5][4] = 'b';
}

void print_board(char grid[RO][CO], int* number_of_b_marbles, int* number_of_w_marbles) /*will print the board and we will call score_calculator in this function*/
{
	system("@cls||clear");
	score_calculator(grid, number_of_b_marbles, number_of_w_marbles);
	int i = 0; /*just for next loops*/
	int j = 0; /*just for next loops*/
	printf("   |   1   2   3   4   5   6   7   8\n");
	printf("___|_________________________________\n   |\n");
	for (i = 1; i<RO; i++)
	{
		printf("%d |", i * 10);
		for (j = 1; j<CO; j++)
		{
			printf("   %c", grid[i][j]); /*print the board . print data's that are in grid[i][j] .*/
		}
		printf("\n   |\n");
	}
	printf("\n");
}

int update_board(char grid[RO][CO])
{
	int marble_place_x = 25, marble_place_y = 25;
	int i, j;
	for (i = 1; i <= CO; i++)
	{
		marble_place_x = 25;
		for (j = 1; j <= RO; j++)
		{
			if (grid[i][j] == 'w')
			{
				console_to_graph(marble_place_x, marble_place_y, WHITE, DARKGRAY,'c',0);
			}
			if (grid[i][j] == 'b')
			{
				console_to_graph(marble_place_x, marble_place_y, BLACK, LIGHTGRAY, 'c', 0);
			}
			if (grid[i][j] == '~')
			{
				console_to_graph(marble_place_x, marble_place_y, LIGHTGREEN, RED, 'r', 0);
				console_to_graph(marble_place_x-5, marble_place_y-5, GREEN, BLUE, 'r', 10);
			}
			if (grid[i][j] == '#')
			{
				console_to_graph(marble_place_x , marble_place_y , LIGHTGREEN, RED, 'r', 0);
				console_to_graph(marble_place_x-10, marble_place_y-10, LIGHTRED, GREEN, 'r', 20);
			}
			if (grid[i][j] == '.')
			{
				console_to_graph(marble_place_x , marble_place_y , LIGHTGREEN, RED, 'r', 0);
			}
			marble_place_x += 50;

		}
		marble_place_y += 50;
	}
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	floodfill(1, 1, RED);
	return 0;
}

void console_to_graph(int marble_start_x, int marble_start_y,int fill_color,int line_color,char shape,int length)
{
	setcolor(line_color);
	if (shape == 'r')
	{
		rectangle(BOARD_START_X + marble_start_x, BOARD_START_Y + marble_start_y, BOARD_START_X + marble_start_x+ length, BOARD_START_Y + marble_start_y+ length);
	}
	else
	{
		circle(BOARD_START_X + marble_start_x, BOARD_START_Y + marble_start_y, MARBLES_RADIOS);
	}
	setfillstyle(SOLID_FILL, fill_color);
	floodfill(BOARD_START_X + marble_start_x+1, BOARD_START_Y + marble_start_y+1, line_color);
}