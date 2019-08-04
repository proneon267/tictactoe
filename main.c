/*
    TicTacToe: A simple game of tictactoe for terminals.
    Copyright (C) 2019  proneon267

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact Author:
    Email:proneon267@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include<string.h>
#define DRAW 10

#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"
#define YLLW  "\033[1;33m"
#define BLUE  "\033[1;34m"
#define MGNTA "\033[1;35m"
#define CYAN  "\033[1;36m"
#define RESET "\033[0m"

int randomValue(int min, int max)
{
    if (min > max)
    {
        int tmp = max;
        max = min;
        min = tmp;
    }

    return (rand()%(abs(max - min) + 1) + min);
}

void printBoard(char value[9])
{
    printf("\t %c ┃ %c ┃ %c \n"
           "\t━━━━━━━━━━━\n"
           "\t %c ┃ %c ┃ %c \n"
           "\t━━━━━━━━━━━\n"
           "\t %c ┃ %c ┃ %c \n\n",
           value[0],value[1],value[2],value[3],value[4],value[5],value[6],value[7],value[8]);
}
void resetArray(char* array)
{
    for(int i=0;i<9;i++){array[i]=' ';}
}
bool isAvailable(int* reservation,int input)
{
    for(int i=0;i<9;i++)
    {
        if(reservation[i]==input)   return false;
    }
    return true;
}

int compMove(int* reservation,int size)
{
    if(size==0) {return DRAW;}
    int move = randomValue(1,9);
    while(!isAvailable(reservation,move))
    {
        move=randomValue(1,9);
    }
    printf("Bot Move: %i\n",move);
    return move;
}

bool checkWin(char* value)
{
         if((value[0]==value[1]&&value[0]==value[2]&&value[0]=='X') || (value[0]==value[1]&&value[0]==value[2]&&value[0]=='O')){value[0]=value[1]=value[2]='-';return true;}
    else if((value[3]==value[4]&&value[3]==value[5]&&value[3]=='X') || (value[3]==value[4]&&value[3]==value[5]&&value[3]=='O')){value[3]=value[4]=value[5]='-';return true;}
    else if((value[6]==value[7]&&value[6]==value[8]&&value[6]=='X') || (value[6]==value[7]&&value[6]==value[8]&&value[6]=='O')){value[6]=value[7]=value[8]='-';return true;}
    else if((value[0]==value[3]&&value[0]==value[6]&&value[0]=='X') || (value[0]==value[3]&&value[0]==value[6]&&value[0]=='O')){value[0]=value[3]=value[6]='|';return true;}
    else if((value[1]==value[4]&&value[1]==value[7]&&value[1]=='X') || (value[1]==value[4]&&value[1]==value[7]&&value[1]=='O')){value[1]=value[4]=value[7]='|';return true;}
    else if((value[2]==value[5]&&value[2]==value[8]&&value[2]=='X') || (value[2]==value[5]&&value[2]==value[8]&&value[2]=='O')){value[2]=value[5]=value[8]='|';return true;}
    else if((value[0]==value[4]&&value[0]==value[8]&&value[0]=='X') || (value[0]==value[4]&&value[0]==value[8]&&value[0]=='O')){value[0]=value[4]=value[8]='\\';return true;}
    else if((value[2]==value[4]&&value[2]==value[6]&&value[2]=='X') || (value[2]==value[4]&&value[2]==value[6]&&value[2]=='O')){value[2]=value[4]=value[6]='/';return true;}
    else return false;
}

int main(int argc, char* argv[])
{
    const char* license = "tictactoe  Copyright (C) 2019  proneon267\n"
                          "This program comes with ABSOLUTELY NO WARRANTY.\n"
                          "This is free software, and you are welcome to redistribute it\n"
                          "under certain conditions.\n"
                          "For details see:<https://www.gnu.org/licenses/>\n";
    const char* help ="This is a game of "BLUE"Tic"RESET GREEN"Tac"RESET RED"Toe\n\n"RESET
                      "To win, the player has to fill three \nconsecutive boxes, vertically,horizontally or diagonally,\n"
                      "The player also needs to block the oppenet from wining.\n"
                      BLUE"The Player is X\t"RESET MGNTA"The opponent is O\n"RESET
                      GREEN"Now go win!\n"RESET;
    if(argc==2)
    {
        if(!strcmp(argv[1],"help")){puts(help);return EXIT_SUCCESS;}
        else if(!strcmp(argv[1],"license")){puts(license);return EXIT_SUCCESS;}
        else{printf("Unknown parameter\n"
                    "Run tictactoe to play the game\n");return EXIT_FAILURE;}
    }
    printf("\t\t\t"BLUE"Tic"RESET GREEN"Tac"RESET RED"Toe\n"RESET
           "Run tictactoe help -- For information on how to play the game.\n"
           "Run tictactoe license -- For information on this software's license.\n\n"
           BLUE"Player is X\t\t"RESET MGNTA"Computer is O\n"RESET
           "Board Place Values is as follows:\n");
    char value[9] = {'1','2','3','4','5','6','7','8','9'};
    int size=9;srand(time(NULL));bool error=false;
    int reservation[9];
    for(int i=0;i<9;i++){    reservation[i]=0;}
    printBoard(value);
    for(int i=0;i<9;i++){    value[i]=' ';}
    printf(CYAN"Warning:"RESET"Don't enter characters as input! Well nothing will happen!\n");
    for(int i=0;i<70;i++){printf("━");}puts("\n\t  New Game\n");
    printBoard(value);
    while (size!=0)
    {
        printf("Enter board Place number:");
        int input;char buffer[256];
        if(fgets(buffer,sizeof(buffer),stdin) == NULL){ return EXIT_FAILURE;}
        input=atoi(buffer);
        if((input>=1&&input<=9)&&isAvailable(reservation,input))
        {
            switch (input) {
                case 1:
                    value[0]='X';
                    reservation[0]=1;
                    size--;
                    error=false;
                    break;
                case 2:
                    value[1]='X';
                    reservation[1]=2;
                    size--;
                    error=false;
                    break;
                case 3:
                    value[2]='X';
                    reservation[2]=3;
                    size--;
                    error=false;
                    break;
                case 4:
                    value[3]='X';
                    reservation[3]=4;
                    size--;
                    error=false;
                    break;
                case 5:
                    value[4]='X';
                    reservation[4]=5;
                    size--;
                    error=false;
                    break;
                case 6:
                    value[5]='X';
                    reservation[5]=6;
                    size--;
                    error=false;
                    break;
                case 7:
                    value[6]='X';
                    reservation[6]=7;
                    size--;
                    error=false;
                    break;
                case 8:
                    value[7]='X';
                    reservation[7]=8;
                    size--;
                    error=false;
                    break;
                case 9:
                    value[8]='X';
                    reservation[8]=9;
                    size--;
                    error=false;
                    break;
                default:
                    printf("Enter a Valid board Place number!\n");
                    error=true;
                    break;
            }
        }
        else if((input>=1&&input<=9)&&!isAvailable(reservation,input))
        {
            printf("That place is already marked!\n");
            error=true;
        }
        else
        {
            printf("Enter valid board Place number!\n");
            error=true;
        }
        if(error){   continue;}
        if(checkWin(value)){ printf(GREEN"You Win\n"RESET); printBoard(value);  break;}
        int botMove = compMove(reservation,size);
        if(botMove==DRAW){ puts(YLLW"It's a Draw"RESET);break;}
        value[botMove-1]='O';
        reservation[botMove-1]=botMove;
        size--;
        if(checkWin(value)){ printf(RED"You Loose\n"RESET); printBoard(value);  break;}
        printBoard(value);
    }
    return EXIT_SUCCESS;
}
