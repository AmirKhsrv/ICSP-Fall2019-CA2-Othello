#include<stdio.h>
#include<stdlib.h>
#include "graphics.h"
#include "end_game.h"
#include "game_options.h"
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

void winner_identifier(char grid[RO][CO], int* number_of_b_marbles, int* number_of_w_marbles)  /*will check which player has more marbles and then will show that he or she is the winner*/
{
	system("@cls||clear");
	score_calculator(grid, number_of_b_marbles, number_of_w_marbles); /*will calculate scores*/
	if (*number_of_b_marbles>*number_of_w_marbles)
	{
		setbkcolor(COLOR(255, 90, 2));
		//settextstyle(3, 0, 4);
		outtextxy(100, 540, "WINNER IS BLACK ----->");
		outtextxy(75, 1, "If you want to play again press 'a' and if you want to exit game press 'e' .");
		setcolor(DARKGRAY);
		circle(TURN_BOX_X + TURN_DEFINER_RADIOS + 2, TURN_BOX_Y + TURN_DEFINER_RADIOS + 502, TURN_DEFINER_RADIOS);
		setfillstyle(SOLID_FILL, BLACK);
		floodfill(TURN_BOX_X + TURN_DEFINER_RADIOS + 2, TURN_BOX_Y + TURN_DEFINER_RADIOS + 502, DARKGRAY);
		setcolor(RED);
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		printf("@@  player BLACK is the WINNER  @@\n");
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
	}
	if (*number_of_b_marbles<*number_of_w_marbles)
	{
		setbkcolor(COLOR(255, 90, 2));
		//settextstyle(3, 0, 4);
		outtextxy(100, 540, "WINNER IS WHITE ----->");
		outtextxy(75, 1, "If you want to play again press 'a' and if you want to exit game press 'e' .");
		setcolor(DARKGRAY);
		circle(TURN_BOX_X + TURN_DEFINER_RADIOS + 2, TURN_BOX_Y + TURN_DEFINER_RADIOS + 502, TURN_DEFINER_RADIOS);
		setfillstyle(SOLID_FILL, WHITE);
		floodfill(TURN_BOX_X + TURN_DEFINER_RADIOS + 2, TURN_BOX_Y + TURN_DEFINER_RADIOS + 502, DARKGRAY);
		setcolor(RED);
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		printf("@@  player WHITE is the WINNER  @@\n");
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
	}
	if (*number_of_b_marbles == *number_of_w_marbles)
	{
		setbkcolor(COLOR(255, 90, 2));
		outtextxy(100, 540, "THE GAME HAD NO WINNER !");
		//setfillstyle(SOLID_FILL, GREEN);
		outtextxy(75, 1, "If you want to play again press 'a' and if you want to exit game press 'e' .");
		setcolor(RED);
		printf("\n##############################\n");
		printf("##  the game has NO WINNER  ##\n");
		printf("##############################\n\n");
	}
}

int ask_play_again()
{
	char again_or_exit = 'w';
	while ((again_or_exit != 'a') && (again_or_exit != 'e')) /*we use this loop to get input from players untill they enter a true input .*/
	{
		printf("If you want to play again press 'a' and if you want to exit game press 'e' .");
		fflush(stdin);
		//scanf("%c", &again_or_exit);
		again_or_exit = getchar();
		if ((again_or_exit != 'a') && (again_or_exit != 'e'))
		{
			printf("!!! You can just enter 'a' or 'e' .\n");
		}
	}
	if (again_or_exit == 'a')
	{
		return 1; /*if return is 1 the main loop of the game will be continued .*/
	}
	if (again_or_exit == 'e') /*if input means exit */
	{
		system("@cls||clear");
		printf("$$  THANKS FOR PLAYING THIS GAME  $$\n\n");
		printf("%%@@  Amirmohammad Khosravi  @@%%\n\n");
		return 0;
	}
}
