/*
 * HumanPlay.c
 *
 *  Created on: 2019��2��23��
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
    system("cls");/*����*/
    printf("2048\n");
    printf("W--��  A--��  S--��  D--��  0--�˳�\n");
    printf("����:%d ����:%d\n", gameStep->score, gameStep->move);
    printf("Made by Yanjisheng\n");
    printf("|-------------------|\n");/*��ʾ����ָ���*/
    for(i=0;i<=3;i++){
        for(j=0;j<=3;j++){
            if(code[i][j]==0){
                printf("|    ");/*0��ʾ�ո�*/
            }
            else{
                printf("|%4d",code[i][j]);/*��ʾ���ֺͷָ���*/
            }
        }
        printf("|\n|-------------------|\n");/*��ʾ����ָ���*/
    }
}

void humanPlayGame(char *player, int fileSaveEnabled){
	struct GameStep *gameStep = startGame(player, fileSaveEnabled);
	do{
		displayGameStep(gameStep);
		/*����free(gameStep);*/
		char c = getch();
		gameStep = playGame(c);
	}while(!isFinalGameStep(gameStep));
	displayGameStep(gameStep);
	printf("��Ϸ����\n");
	free(gameStep);
	getch();
}
