/*
 * PlayGame.c
 *
 *  Created on: 2019年2月23日
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

struct GameStep *gameSteps = NULL; /*游戏的每一步*/
int offset = 0;
FILE *fp = NULL; /*游戏记录文件指针*/

/*开始游戏*/
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
		fp = fopen(fileName, "w"); /*创建文件记录游戏过程*/
	}
	struct GameStep *gameStep = getFirstGameStep(); /*获取游戏的第一步*/
	copyGameStep(gameSteps, gameStep); /*存入游戏记录中*/
	char *gameStepStr = GameStepToString(gameStep);
	fputs(gameStepStr, fp); /*把游戏记录写入文件*/
	free(gameStepStr);
	free(gameStep); /*释放堆内存*/
	return gameSteps + offset;
}

/*游戏进行的每一步*/
struct GameStep *playGame(char direction){
	struct GameStep *gameStep = getNextGameStepAddNo(gameSteps + offset, direction); /*获取游戏的下一步*/
	if(gameStep->move > -1){ /*是有效步骤（不是跟上一步一样的）*/
		offset++;
		if(offset >= GAME_STEPS_BUFFER_SIZE) { /*游戏记录超范围*/
			fflush(fp);
			offset = 0; /*重新分配堆内存*/
		}
		copyGameStep(gameSteps + offset, gameStep); /*把下一步存入游戏记录*/
		char *gameStepStr = GameStepToString(gameStep);
		fputs(gameStepStr, fp);
		free(gameStepStr);
	}
	if(isFinalGameStep(gameStep)) { /*游戏结束*/
		fflush(fp);
		fclose(fp);
		free(gameSteps);
		return gameStep;
	}
	free(gameStep);
	return gameSteps + offset;
}
