/*
 * PlayGame.c
 *
 *  Created on: 2019��2��23��
 *      Author: yanjisheng
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>

#include "PlayGame.h"

#define GAME_STEPS_BUFFER_SIZE 1000

struct GameStep *gameSteps = NULL; /*��Ϸ��ÿһ��*/
int offset = 0;
FILE *fp = NULL; /*��Ϸ��¼�ļ�ָ��*/

/*��ʼ��Ϸ*/
struct GameStep *startGame(char *player, int fileSaveEnabled){
	time_t time_v;
	struct tm *lt;
	char fileName[50];
	char t[5];
	strcpy(fileName, "");
	gameSteps = (struct GameStep *)malloc(GAME_STEPS_BUFFER_SIZE * sizeof(struct GameStep));
	if(gameSteps == NULL){
		exit(1);
	}
	offset = 0;
	time(&time_v);
	lt = localtime(&time_v);
	sprintf(t, "%d", lt->tm_year + 1900);
	strcat(fileName, t);
	sprintf(t, "%02d", lt->tm_mon + 1);
	strcat(fileName, t);
	sprintf(t, "%02d", lt->tm_mday);
	strcat(fileName, t);
	sprintf(t, "%02d", lt->tm_hour);
	strcat(fileName, t);
	sprintf(t, "%02d", lt->tm_min);
	strcat(fileName, t);
	sprintf(t, "%02d", lt->tm_sec);
	strcat(fileName, t);
	strcat(fileName, "_");
	strcat(fileName, player);
	if(fileSaveEnabled){
		fp = fopen(fileName, "w"); /*�����ļ���¼��Ϸ����*/
	}
	struct GameStep *gameStep = getFirstGameStep(); /*��ȡ��Ϸ�ĵ�һ��*/
	copyGameStep(gameSteps, gameStep); /*������Ϸ��¼��*/
	char *gameStepStr = GameStepToString(gameStep);
	fputs(gameStepStr, fp); /*����Ϸ��¼д���ļ�*/
	free(gameStepStr);
	free(gameStep); /*�ͷŶ��ڴ�*/
	return gameSteps + offset;
}

/*��Ϸ���е�ÿһ��*/
struct GameStep *playGame(char direction){
	struct GameStep *gameStep = getNextGameStepAddNo(gameSteps + offset, direction); /*��ȡ��Ϸ����һ��*/
	if(gameStep->move > -1){ /*����Ч���裨���Ǹ���һ��һ���ģ�*/
		offset++;
		if(offset >= GAME_STEPS_BUFFER_SIZE) { /*��Ϸ��¼����Χ*/
			fflush(fp);
			offset = 0; /*���·�����ڴ�*/
		}
		copyGameStep(gameSteps + offset, gameStep); /*����һ��������Ϸ��¼*/
		char *gameStepStr = GameStepToString(gameStep);
		fputs(gameStepStr, fp);
		free(gameStepStr);
	}
	if(isFinalGameStep(gameStep)) { /*��Ϸ����*/
		fflush(fp);
		fclose(fp);
		free(gameSteps);
		return gameStep;
	}
	free(gameStep);
	return gameSteps + offset;
}
