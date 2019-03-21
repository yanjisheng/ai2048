/*
 * HumanPlay.c
 *
 *  Created on: 2019年2月23日
 *      Author: yanjisheng
 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "GameStep.h"
#include "PlayGame.h"

#include "HumanPlay.h"

void displayGameStep(struct GameStep *gameStep){
    int i,j;
    int code[4][4];
    arrayCopy(code, gameStep->code);
    system("cls");/*清屏*/
    printf("2048\n");
    printf("W--上  A--左  S--下  D--右  0--退出\n");
    printf("分数:%d 步数:%d\n", gameStep->score, gameStep->move);
    printf("Made by Yanjisheng\n");
    printf("|-------------------|\n");/*显示横向分隔线*/
    for(i=0;i<=3;i++){
        for(j=0;j<=3;j++){
            if(code[i][j]==0){
                printf("|    ");/*0显示空格*/
            }
            else{
                printf("|%4d",code[i][j]);/*显示数字和分隔线*/
            }
        }
        printf("|\n|-------------------|\n");/*显示横向分隔线*/
    }
}

void humanPlayGame(char *player, int fileSaveEnabled){
	struct GameStep *gameStep = startGame(player, fileSaveEnabled);
	do{
		displayGameStep(gameStep);
		/*不能free(gameStep);*/
		char c = getch();
		gameStep = playGame(c);
	}while(!isFinalGameStep(gameStep));
	displayGameStep(gameStep);
	printf("游戏结束\n");
	free(gameStep);
	getch();
}
