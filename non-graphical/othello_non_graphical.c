#include<stdio.h>
#include<stdlib.h>
#define CO 9
#define RO 9
void print_board(char[RO][CO],int*,int*);
void get_and_set(char[RO][CO],char*);
void score_calculator(char[RO][CO],int*,int*);
void marble_reverser(char [RO][CO],char* ,int,int);
int possible_choices(char[RO][CO],char*);
void winner_identifier(char [RO][CO],int* ,int* ,char* );
void initial_game(char[RO][CO]);
int ask_play_again();

int main()
{
	char turn='b';
	char grid[RO][CO];
	int number_of_b_marbles=0;
 	int number_of_w_marbles=0;	
	do
	{
		turn='b';
		initial_game(grid);
		possible_choices(grid,&turn);
		while(possible_choices(grid,&turn))
		{
			print_board(grid,&number_of_b_marbles,&number_of_w_marbles);
			get_and_set(grid,&turn);
		}
		print_board(grid,&number_of_b_marbles,&number_of_w_marbles);
		winner_identifier(grid,&number_of_b_marbles,&number_of_w_marbles,&turn);
	}
	while(ask_play_again());
	return 0;
}

void initial_game(char grid[RO][CO])
{
	int i=1;
	int j=1;
	for(i=1;i<RO;i++)
	{
		for(j=1;j<CO;j++)
		{
			grid[i][j]='.';
		}
	}	
	grid[4][4]='w';
	grid[5][5]='w';
	grid[4][5]='b';
	grid[5][4]='b';
}

void print_board(char grid[RO][CO],int* number_of_b_marbles,int* number_of_w_marbles)
{
	system("@cls||clear");
	score_calculator(grid,number_of_b_marbles,number_of_w_marbles);
	int i=0;
	int j=0;
	printf("   |   1   2   3   4   5   6   7   8\n");
	printf("___|_________________________________\n   |\n");
	for(i=1;i<RO;i++)
	{
		printf("%d |",i*10);
		for(j=1;j<CO;j++)
		{
			printf("   %c",grid[i][j]);
		}
		printf("\n   |\n");
	}	
	printf("\n");
}

void get_and_set(char grid[RO][CO],char* turn)
{
	int flag1=0,flag2=0;
	int i,j,k,l;
	float pos_input;
	while(flag1==0)
	{
		flag2=0;
		if(*turn=='b')
		{
			printf("BLACK player's turn :\nPlease choose the place you want to put your marble -----> ");
		}
		else 
		{
			printf("WHITE player's turn :\nPlease choose the place you want to put your marble -----> ");			
		}
		scanf("%f",&pos_input);
		for(i=1;i<RO;i++)
		{
			for(j=1;j<CO;j++)
			{
				if(pos_input==(i*10)+j)
				{
					if(grid[i][j]=='w'||grid[i][j]=='b')
					{
						printf("\n\aThis place is full ! Please choose another one .\n\n");
						flag2++;
					}
					if(grid[i][j]=='~')
					{
						grid[i][j]=*turn;
						marble_reverser(grid,turn,i,j);		
						flag1++;
						for(k=1;k<RO;k++)
						{
							for(l=1;l<CO;l++)
							{
								if(grid[k][l]=='~')
								{
									grid[k][l]='.';
								}
							}
						}
					}
					if(grid[i][j]=='.')
					{
						printf("\n\aYou can not place your marble here because it wont reverse any other marbles .\n\n");
						flag2++;
					}
				}
			}
		}	
		if(flag1==0&&flag2==0)
		{
			printf("\n\aYou can just choose an integer from 11 to 88 .\n\n");
			fflush(stdin);
		}
	}
	if(*turn=='b')
	{
		*turn='w';
	}
	else
	{
		*turn='b';
	}
}

void score_calculator(char grid[RO][CO],int* number_of_b_marbles,int* number_of_w_marbles)
{
	int i,j;
	*number_of_b_marbles=0;
 	*number_of_w_marbles=0;	
	for(i=1;i<RO;i++)
	{
		for(j=1;j<CO;j++)
		{
			if(grid[i][j]=='b')
			{
				*number_of_b_marbles+=1;		
			} 
			if(grid[i][j]=='w')
			{
				*number_of_w_marbles+=1;	
			} 
		}
	}
	printf("======================================\n");
	printf("=      BLACK      ==      WHITE      =\n");
	printf("=        %d",*number_of_b_marbles);
	if(*number_of_b_marbles>9)
	{
		printf("       ==        ");
	}
	else
	{
		printf("        ==        ");
	}
	printf("%d",*number_of_w_marbles);
	if(*number_of_w_marbles>9)
	{
		printf("       =\n");
	}
	else
	{
		printf("        =\n");
	}
	printf("======================================\n\n");
	
}

void marble_reverser(char grid[RO][CO],char* turn,int i,int j)
{
	int k,l;
	char marble1,marble2;
	if(*turn=='b')
	{
		marble1='b';
		marble2='w';
	}
	else
	{
		marble2='b';
		marble1='w';
	}
	if(grid[i][j]==marble1)
	{
		k=j+1;
		while(grid[i][k]==marble2)
		{
			k++;
			if(grid[i][k]==marble1)
			{
				for(k;k!=j;k--)
				{
					grid[i][k]=marble1;
				}
			}
		}
	}
	if(grid[i][j]==marble1)
	{
		k=i+1;
		while(grid[k][j]==marble2)
		{
			k++;
			if(grid[k][j]==marble1)
			{
				for(k;k!=i;k--)
				{
					grid[k][j]=marble1;
				}				
			}
		}
	}
	if(grid[i][j]==marble1)
	{
		k=i-1;
		while(grid[k][j]==marble2)
		{
			k--;
			if(grid[k][j]==marble1)
			{
				for(k;k!=i;k++)
				{
					grid[k][j]=marble1;
				}		
			}
		}
	}
	if(grid[i][j]==marble1)
	{
		k=j-1;
		while(grid[i][k]==marble2)
		{
			k--;
			if(grid[i][k]==marble1)
			{
				for(k;k!=j;k++)
				{
					grid[i][k]=marble1;
				}		
			}
		}
	}
	if(grid[i][j]==marble1)
	{
		k=j+1;
		l=i+1;
		while(grid[l][k]==marble2)
		{
			k++;
			l++;
			if(grid[l][k]==marble1)
			{
				for(k,l;(k!=j)&&(l!=i);k--,l--)
				{
					grid[l][k]=marble1;
				}		
			}
		}
	}
	if(grid[i][j]==marble1)
	{
		k=j+1;
		l=i-1;
		while(grid[l][k]==marble2)
		{
			k++;
			l--;
			if(grid[l][k]==marble1)
			{
				for(k,l;(k!=j)&&(l!=i);k--,l++)
				{
					grid[l][k]=marble1;
				}			
			}
		}
	}
	if(grid[i][j]==marble1)
	{
		k=j-1;
		l=i+1;
		while(grid[l][k]==marble2)
		{
			k--;
			l++;
			if(grid[l][k]==marble1)
			{
				for(k,l;(k!=j)&&(l!=i);l--,k++)
				{
					grid[l][k]=marble1;
				}				
			}
		}
	}
	if(grid[i][j]==marble1)
	{
		k=j-1;
		l=i-1;
		while(grid[l][k]==marble2)
		{
			k--;
			l--;
			if(grid[l][k]==marble1)
			{
				for(k,l;(k!=j)&&(l!=i);k++,l++)
				{
						grid[l][k]=marble1;
				}					
			}
		}
	}
}

int possible_choices(char grid[RO][CO],char* turn)
{
	char marble1,marble2;
	int i,j,k,l;
	int hastag_counter=0;
	if(*turn=='b')
	{
		marble1='b';
		marble2='w';
	}
	else
	{
		marble2='b';
		marble1='w';
	}
	for(i=1;i<RO;i++)
	{
		for(j=1;j<CO;j++)
		{
			if(grid[i][j]=='.')
			{
				k=j+1;
				while(grid[i][k]==marble2)
				{
					k++;
					if(grid[i][k]==marble1)
					{
						grid[i][j]='~';
					}
				}
			}
			if(grid[j][i]=='.')
			{
				k=j+1;
				while(grid[k][i]==marble2)
				{
					k++;
					if(grid[k][i]==marble1)
					{
						grid[j][i]='~';
					}
				}
			}
			if(grid[RO-j][CO-i]=='.')
			{
				k=RO-j-1;
				while(grid[k][CO-i]==marble2)
				{
					k--;
					if(grid[k][CO-i]==marble1)
					{
						grid[RO-j][CO-i]='~';
					}
				}
			}
			if(grid[RO-i][CO-j]=='.')
			{
				k=CO-j-1;
				while(grid[RO-i][k]==marble2)
				{
					k--;
					if(grid[RO-i][k]==marble1)
					{
						grid[RO-i][CO-j]='~';
					}
				}
			}
			if(grid[i][j]=='.')
			{
				k=j+1;
				l=i+1;
				while(grid[l][k]==marble2)
				{
					k++;
					l++;
					if(grid[l][k]==marble1)
					{
						grid[i][j]='~';
					}
				}
			}
			if(grid[i][j]=='.')
			{
				k=j+1;
				l=i-1;
				while(grid[l][k]==marble2)
				{
					k++;
					l--;
					if(grid[l][k]==marble1)
					{
						grid[i][j]='~';
					}
				}
			}
			if(grid[i][j]=='.')
			{
				k=j-1;
				l=i+1;
				while(grid[l][k]==marble2)
				{
					k--;
					l++;
					if(grid[l][k]==marble1)
					{
						grid[i][j]='~';
					}
				}
			}
			if(grid[i][j]=='.')
			{
				k=j-1;
				l=i-1;
				while(grid[l][k]==marble2)
				{
					k--;
					l--;
					if(grid[l][k]==marble1)
					{
						grid[i][j]='~';
					}
				}
			}
		}
	}
	for(i=1;i<RO;i++)
	{
		for(j=1;j<CO;j++)
		{
			if(grid[i][j]=='~')
			{
				hastag_counter++;
			}
		}
	}
	if(hastag_counter>0)
	{
		return 1; 
	}
	else
	{
		return 0;
	}
}

void winner_identifier(char grid[RO][CO],int* number_of_b_marbles,int* number_of_w_marbles,char* turn)
{
	int i,j,dot_counter=0;
	for(i=1;i<RO;i++)
	{
		for(j=1;j<CO;j++)
		{
			if(grid[i][j]=='.')
			{
				dot_counter++;
			}
		}
	}
	if(dot_counter==0)
	{
		system("@cls||clear");
		score_calculator(grid,number_of_b_marbles,number_of_w_marbles);
		if(*number_of_b_marbles>*number_of_w_marbles)
		{
			printf("\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
			printf("@@  player BLACK is the WINNER  @@\n");
			printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		}
		if(*number_of_b_marbles<*number_of_w_marbles)
		{
			printf("\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
			printf("@@  player WHITE is the WINNER  @@\n");
			printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");		}
		if(*number_of_b_marbles==*number_of_w_marbles)
		{
			printf("\n\n##################################\n");
			printf("##  player black is the winner  ##\n");
			printf("##################################\n");
		}
	}
	else
	{
		if(*turn='b')
		{
			printf("\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
			printf("@@  player WHITE is the WINNER  @@\n");
			printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");	
			printf("\n@ Because BLACK player can't place his marble anywhere.\n\n");	
		}
		else
		{
			printf("\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
			printf("@@  player BLACK is the WINNER  @@\n");
			printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");	
			printf("\n@ Because WHITE player can't place his marble anywhere.\n\n");					
		}
	}	
}

int ask_play_again()
{
	char again_or_exit='w';
	while((again_or_exit!='a')&&(again_or_exit!='e'))
	{
		printf("If you want to play again press 'a' and if you want to exit game press 'e' .");
		fflush(stdin);
		scanf("%c",&again_or_exit);
		if((again_or_exit!='a')&&(again_or_exit!='e'))
		{
			printf("!!! You can just enter 'a' or 'e' .\n");
		}
	}
	if(again_or_exit=='a')
	{
		return 1;
	}
	if(again_or_exit=='e')
	{
		system("@cls||clear");
		printf("$$  THANKS FOR PLAYING THIS GAME  $$\n\n");
		printf("%%@@  Amirmohammad Khosravi  @@%%\n\n");
		return 0;
	}
}


