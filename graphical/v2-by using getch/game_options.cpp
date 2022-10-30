#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graphics.h"
#include "game_options.h"

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

void score_calculator(char grid[RO][CO], int* number_of_b_marbles, int* number_of_w_marbles) /*will calculate how many marbles of one color we have*/
{
	int i, j,digit;
	char scores[3];
	*number_of_b_marbles = 0;
	*number_of_w_marbles = 0;
	for (i = 1; i<RO; i++)
	{
		for (j = 1; j<CO; j++)
		{
			if (grid[i][j] == 'b')
			{
				*number_of_b_marbles += 1;	 /*count the number of black marbles*/
			}
			if (grid[i][j] == 'w')
			{
				*number_of_w_marbles += 1;	/*count the number of white marbles*/
			}
		}
	}
	printf("======================================\n");  /*this line to line 46 just print scores*/
	printf("=      BLACK      ==      WHITE      =\n");
	printf("=        %d", *number_of_b_marbles);
	if (*number_of_b_marbles>9)
	{
		printf("       ==        ");
	}
	else
	{
		printf("        ==        ");
	}
	printf("%d", *number_of_w_marbles);
	if (*number_of_w_marbles>9)
	{
		printf("       =\n");
	}
	else
	{
		printf("        =\n");
	}
	printf("======================================\n\n");


	if (*number_of_w_marbles > 9)
	{
		digit = (*number_of_w_marbles % 10);
		scores[1] = digit+ 48;
		scores[0] = ((*number_of_w_marbles - digit) / 10) + 48;
		scores[2] = NULL;
	}
	else
	{
		scores[0] = *number_of_w_marbles + 48;
		scores[1] = NULL;
	}
		setbkcolor(COLOR(248, 254, 10));
		outtextxy(420, 42, "    ");
		outtextxy(420, 42, scores);
		scores[1] = (*number_of_w_marbles % 10) + 48;
		scores[0] = ((*number_of_w_marbles - scores[1]) / 10) + 48;
		scores[2] = NULL;

		if (*number_of_b_marbles > 9)
		{
			digit = (*number_of_b_marbles % 10);
			scores[1] = digit + 48;
			scores[0] = ((*number_of_b_marbles - digit) / 10) + 48;
			scores[2] = NULL;
		}
		else
		{
			scores[0] = *number_of_b_marbles + 48;
			scores[1] = NULL;
		}
		outtextxy(160, 42, "    ");
		setbkcolor(COLOR(248, 254, 10));
		outtextxy(160, 42, scores);
}

int possible_choices(char grid[RO][CO], char* turn) /*show and put ~ in cells in which players can put their marble*/
{
	char marble1, marble2;
	int i, j, k, l; /*are used in loops and for going to a direction and check cells*/
	int hastag_counter = 0; /* hashtag here means ~ :) */
	if (*turn == 'b') /*here we set marble1 and marble2 so we dont need to write same codes another time .*/
	{
		marble1 = 'b';
		marble2 = 'w';
	}
	else
	{
		marble2 = 'b';
		marble1 = 'w';
	}
	for (i = 1; i<RO; i++) /*in these lines there is the algorithm that find possible choices */
	{
		for (j = 1; j<CO; j++)
		{
			find_possible_places(grid, i, j, 0, 1, marble1, marble2); /*horizental chek to right */
			find_possible_places(grid, i, j, 1, 0, marble1, marble2);/*vertical check to down*/
			find_possible_places(grid, CO - i, RO - j, -1, 0, marble1, marble2);/*horizontal check to left*/
			find_possible_places(grid, RO - i, CO-j, 0, -1, marble1, marble2);/*vertical check to up*/
			find_possible_places(grid, i, j, 1, 1, marble1, marble2);/*diagonal check to down right*/
			find_possible_places(grid, i, j, -1, 1, marble1, marble2); /*diagonal check to up right*/
			find_possible_places(grid, i, j, 1, -1, marble1, marble2);/*diagonal check to down left*/
			find_possible_places(grid, i, j, -1, -1, marble1, marble2);/*diagonal check to up left*/
		}
	}
	for (i = 1; i<RO; i++)
	{
		for (j = 1; j<CO; j++)
		{
			if (grid[i][j] == '~')
			{
				hastag_counter++; /*conting the number of ~ so if the number is 0 the game is over */
			}
		}
	}
	if (hastag_counter>0) /*if number of ~ is 0 then the game will be ended*/
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void find_possible_places(char grid[RO][CO],int i,int j, int direct_define1, int direct_define2,char marble1,char marble2)
{
	int k, l;
	if (grid[i][j] == '.') /*check in a specific direction*/
	{
		k = j + direct_define2;
		l = i + direct_define1;
		while (grid[l][k] == marble2)
		{
			k+= direct_define2;
			l+= direct_define1;
			if (grid[l][k] == marble1)
			{
				grid[i][j] = '~';
			}
		}
	}
}