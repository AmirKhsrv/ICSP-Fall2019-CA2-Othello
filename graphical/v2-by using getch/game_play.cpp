#include<stdio.h>
#include<stdlib.h>
#include "graphics.h"
#include "game_play.h"
#include "display.h"
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

void get_and_set(char grid[RO][CO], char* turn) /*getting input untill user enter a right input*/
{
	int indcator_x = 1, indcator_y = 1, flag = 0, check_space = 0,counter=0,temp;
	int i, j,l=1,k=1;
	char direction = 'o';
	for (i = 1; i < RO; i++)
	{
		for (j = 1; j < CO; j++)
		{
			if (grid[i][j] == '~')
			{
				grid[i][j] = '#';
				flag++;
				break;
			}
		}
		if (flag > 0)
		{
			break;
		}
	}
	indcator_x = i;
	indcator_y = j;
	update_board(grid);
	flag = 0;
	while (flag==0)
	{
		direction = 'o';
		while ((direction != ' ') && (grid[indcator_x][indcator_y] != '~'))
		{
			direction = getch();
			if (direction == 'w')
			{
				check_space = 0;
				grid[indcator_x][indcator_y] = '.';
				if (indcator_x == 1)
				{
					indcator_x = 9;
				}
				jumper(grid, &indcator_x, &indcator_y, -1,0, 0, 8, &check_space);
			}
			if (direction == 's')
			{
				check_space = 0;
				grid[indcator_x][indcator_y] = '.';
				if (indcator_x == 8)
				{
					indcator_x = 0;
				}
				jumper(grid, &indcator_x, &indcator_y, 1,0, 9, 1, &check_space);
			}
			if (direction == 'd')
			{
				check_space = 0;
				grid[indcator_x][indcator_y] = '.';
				if (indcator_y == 8)
				{
					indcator_y = 0;
				}
				jumper(grid, &indcator_x, &indcator_y, 0,1,9 , 1, &check_space);
			}
			if (direction == 'a')
			{
				check_space = 0;
				grid[indcator_x][indcator_y] = '.';
				if (indcator_y == 1)
				{
					indcator_y = 9;
				}
				jumper(grid, &indcator_x, &indcator_y, 0,-1, 0, 8, &check_space);
			}
			if (direction == 'n')
			{
				grid[i][j] == '~';
				check_space = 0;
				grid[indcator_x][indcator_y] = '.';
				temp = l;
				for (l ; (l < RO) && (flag <= 0); l++)
				{
					if(temp!=l)
					k = 1;
					for (k; k < CO; k++)
					{
						if (grid[l][k] == '~')
						{
							indcator_x = l;
							indcator_y = k;
							grid[l][k] = '#';
							flag++;
							break;
						}
					}
				}
				l--;
				if ((l == RO - 1) && (k == CO))
				{
					l = 1;
					k = 1;
					temp = l;
					for (l; (l < RO) && (flag <= 0); l++)
					{
						if (temp != l)
							k = 1;
						for (k; k < CO; k++)
						{
							if (grid[l][k] == '~')
							{
								indcator_x = l;
								indcator_y = k;
								grid[l][k] = '#';
								flag++;
								break;
							}
						}
					}
					l--;
				}
				flag--;
				check_space++;
			}
			possible_choices(grid, turn);
			update_board(grid);
		}
		if ((indcator_x == i) && (indcator_y == j))check_space++;
		if (check_space>0)
		{
			grid[indcator_x][indcator_y] = *turn;
			flag++;
		}
		else
		{
			check_space = 0;
			printf("You cannot place your marble here !!\n");
		}
	}
	marble_reverser(grid, turn, indcator_x, indcator_y);
	possible_choices(grid, turn);

	for (i = 1; i < RO; i++)
	{
		for (j = 1; j < CO; j++)
		{
			if (grid[i][j] == '~')
			{
				grid[i][j] = '.';
			}
		}
	}

	if (*turn == 'b') /*here we switch turns*/
	{
		setcolor(DARKGRAY);
		circle(TURN_BOX_X + TURN_DEFINER_RADIOS + 2, TURN_BOX_Y + TURN_DEFINER_RADIOS + 2, TURN_DEFINER_RADIOS);
		setfillstyle(SOLID_FILL, WHITE);
		floodfill(TURN_BOX_X + TURN_DEFINER_RADIOS + 2, TURN_BOX_Y + TURN_DEFINER_RADIOS + 2, DARKGRAY);
		setcolor(RED);
		*turn = 'w';
	}
	else
	{
		setcolor(LIGHTGRAY);
		circle(TURN_BOX_X + TURN_DEFINER_RADIOS + 2, TURN_BOX_Y + TURN_DEFINER_RADIOS + 2, TURN_DEFINER_RADIOS);
		setfillstyle(SOLID_FILL, BLACK);
		floodfill(TURN_BOX_X + TURN_DEFINER_RADIOS + 2, TURN_BOX_Y + TURN_DEFINER_RADIOS + 2, LIGHTGRAY);
		setcolor(RED);
		*turn = 'b';
	}
}

void marble_reverser(char grid[RO][CO], char* turn, int i, int j) /*will reverse marbles between to other conflicting marbles */
{
	int k, l; /*just used to go in a direction */
	char marble1, marble2;
	if (*turn == 'b')
	{
		marble1 = 'b';
		marble2 = 'w';
	}
	else
	{
		marble2 = 'b';
		marble1 = 'w';
	}
	seek_check_reverse(grid, marble1, marble2, i, j, 0, 1); /*reverse horizontal to right*/
	seek_check_reverse(grid, marble1, marble2, i, j, 1, 0);/*reverse vertical to down*/
	seek_check_reverse(grid, marble1, marble2, i, j, -1, 0); /* reverse vertical to up*/
	seek_check_reverse(grid, marble1, marble2, i, j, 0, -1);/*reverse horizontal to left*/
	seek_check_reverse(grid, marble1, marble2, i, j, 1, 1); /* reverse diagonal to down right*/
	seek_check_reverse(grid, marble1, marble2, i, j, -1, 1); /*reverse diagonal up right*/
	seek_check_reverse(grid, marble1, marble2, i, j, 1, -1);/*reverse diagonal down left*/
	seek_check_reverse(grid, marble1, marble2, i, j, -1, -1);/*reverse diagonal up left*/
}

void seek_check_reverse(char grid[RO][CO],char marble1, char marble2,int i,int j,int direct_define1, int direct_define2)
{
	int k, l;
	if (grid[i][j] == marble1) /* reverse in different direction*/
	{
		k = j + direct_define2;
		l = i + direct_define1;
		while (grid[l][k] == marble2)
		{
			k+= direct_define2;
			l+= direct_define1;
			if (grid[l][k] == marble1)
			{
				if (direct_define2 == 0)
				{
					for (l; l != i; l-= direct_define1)
					{
						grid[l][j] = marble1;
					}
				}
				if (direct_define1 == 0)
				{
					for (k; k != j; k-= direct_define2)
					{
						grid[i][k] = marble1;
					}
				}
				else if(direct_define1*direct_define2!=0)
				{
					for (k, l; (k != j) && (l != i); k -= direct_define2, l -= direct_define1)
					{
						grid[l][k] = marble1;
					}
				}
			}
		}
	}
}

void jumper(char grid[RO][CO],int* indcator_x, int* indcator_y,int i,int j,int end,int begining,int* check_space)
{
	*indcator_x += i;
	*indcator_y += j;
	while ((grid[*indcator_x][*indcator_y] == 'w') || (grid[*indcator_x][*indcator_y] == 'b'))
	{
		*indcator_x += i;
		*indcator_y += j;
	}
	if (j != 0)
	{
		if (*indcator_y == end)
		{
			*indcator_y = begining;
		}
	}
	if (i != 0)
	{
		if (*indcator_x == end)
		{
			*indcator_x = begining;
		}
	}
	while ((grid[*indcator_x][*indcator_y] == 'w') || (grid[*indcator_x][*indcator_y] == 'b'))
	{
		*indcator_x += i;
		*indcator_y += j;
	}
	if (grid[*indcator_x][*indcator_y] == '~')*check_space+=1;
	grid[*indcator_x][*indcator_y] = '#';
}