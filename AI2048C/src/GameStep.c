/*
 * GameStep.c
 *
 *  Created on: 2019年2月23日
 *      Author: yanjisheng
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "GameStep.h"

int squashLine(int line[], int *score);
void addNumberForGameStep(struct GameStep *gameStep);
char *GameStepToString(struct GameStep *gameStep);

struct GameStep *getFirstGameStep() {
	struct GameStep *firstGameStep = (struct GameStep*) malloc(sizeof(struct GameStep)); /*给第一步分配堆内存*/
	int array[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
	arrayCopy(firstGameStep->code, array);
	firstGameStep->move = 0;
	firstGameStep->score = 0;
	firstGameStep->direction = '\0';
	//srand((unsigned)time(NULL)); /*设置随机数种子*/
	addNumberForGameStep(firstGameStep);
	return firstGameStep;
}

struct GameStep *getNextGameStepNoAddNo(struct GameStep *gameStep, char direction) {
	return getNextGameStep(gameStep, direction, 0);
}

struct GameStep *getNextGameStepAddNo(struct GameStep *gameStep, char direction) {
	return getNextGameStep(gameStep, direction, 1);
}

struct GameStep *getNextGameStep(struct GameStep *gameStep, char direction, int addNo) {
	int i,j;
	int code[4][4]; /*游戏中的16个格子（临时变量）*/
	int move = gameStep->move;
	int score = gameStep->score;
	int change = 0;
	int temp[5] = {0, 0, 0, 0, 0};
	struct GameStep *nextGameStep = (struct GameStep*) malloc(sizeof(struct GameStep)); /*给下一步分配堆内存*/
	arrayCopy(code, gameStep->code); /*从上一步给临时变量赋值*/
	switch(direction){
		case 'W':
		case 'w':/*上*/
			for(j=0;j<=3;j++){
				for(i=0;i<=3;i++){
					temp[i]=code[i][j];/*把一列数移到中间变量*/
				}
				change += squashLine(temp, &score);
				for(i=0;i<=3;i++){
					code[i][j]=temp[i];/*把处理好的中间变量移回来*/
				}
			}
			break;

		case 'A':
		case 'a':/*左*/
			for(i=0;i<=3;i++){
				for(j=0;j<=3;j++){
					temp[j]=code[i][j];/*把一行数移到中间变量*/
				}
				change += squashLine(temp, &score);
				for(j=0;j<=3;j++){
					code[i][j]=temp[j];/*把处理好的中间变量移回来*/
				}
			}
			break;

		case 'S':
		case 's':/*下*/
			for(j=0;j<=3;j++){
				for(i=0;i<=3;i++){
					temp[i]=code[3-i][j];/*把一列数移到中间变量*/
				}
				change += squashLine(temp, &score);
				for(i=0;i<=3;i++){
					code[3-i][j]=temp[i];/*把处理好的中间变量移回来*/
				}
			}
			break;

		case 'D':
		case 'd':/*右*/
			for(i=0;i<=3;i++){
				for(j=0;j<=3;j++){
					temp[j]=code[i][3-j];/*把一行数移到中间变量*/
				}
				change += squashLine(temp, &score);
				for(j=0;j<=3;j++){
					code[i][3-j]=temp[j];/*把处理好的中间变量移回来*/
				}
			}
			break;
	}
	arrayCopy(nextGameStep->code, code); /*给下一步的十六个格子赋值*/
	nextGameStep->direction = direction;
	nextGameStep->score = score;
	if(change > 0){
		nextGameStep->move = move + 1;
		if(addNo){
			addNumberForGameStep(nextGameStep);
		}
	} else {
		nextGameStep->move = -1;
	}
	return nextGameStep;
}

/*判断是否是最后一步*/
int isFinalGameStep(struct GameStep *gameStep) {
	int i, j;
	int result = 1;
	int code[4][4];
	arrayCopy(code, gameStep->code);
	for(i=0; i<=3; i++){
		for(j=0; j<=3; j++){
			if(code[i][j] == 0){
				result = 0;
				goto out;
			}
			if(i<3 && code[i][j]==code[i+1][j]){
				result = 0;
				goto out;
			}
			if(j<3 && code[i][j]==code[i][j+1]){
				result = 0;
				goto out;
			}
		}
	}
	out:
	return result;
}

/*随机选一个空格填上2或4*/
void addNumberForGameStep(struct GameStep *gameStep) {
	int i, j;
	int array[4][4];
	arrayCopy(array, gameStep->code);
	do {
		i=((unsigned) rand()) % 4;
		j=((unsigned) rand()) % 4;
	} while(array[i][j]!=0);
	if(((unsigned) rand()) % 4 == 0) {
		array[i][j]=4;
	}
	else {
		array[i][j]=2;
	}
	arrayCopy(gameStep->code, array);
}

/*对一行或一列数进行挤压操作*/
int squashLine(int line[], int *score) {
	int i;
	int t=0;
	int change = 0;/*判断数组是否有改变，0不变，1变化*/
	int scoreTemp = 0;/*本次操作中增加的得分*/
	do {
		for(i=0; i<=3 ;i++) {
			if(line[i]==0) {
				if(line[i]!=line[i+1]) {
					change=1;/*当一个0后面不是0时数组改变*/
				}
				line[i]=line[i+1];
				line[i+1]=0;
			}
		}/*去掉中间的0*/
		t++;
	} while(t<=3);/*重复多次*/
	for(i=1;i<=3;i++) {
		if(line[i]==line[i-1]){
			if(line[i]!=0){
				change=1;/*当两个非零相同的数相加时数组改变*/
				scoreTemp+=line[i];/*加分*/
			}
			line[i-1]=line[i-1]*2;
			line[i]=0;
		}
	}/*把两个相邻的相同的数加起来*/
	for(i=0;i<=3;i++) {
		if(line[i]==0) {
			line[i]=line[i+1];
			line[i+1]=0;
		}
	}/*去掉中间的0*/
	*score += scoreTemp;
	return change;
}

char *GameStepToString(struct GameStep *gameStep) {
	char *str = malloc(100 * sizeof(char));
	int array[4][4];
	int i,j;
	char t[5];
	strcpy(str, "");
	arrayCopy(array, gameStep->code);
	for(i=0; i<=3; i++) {
		for(j=0; j<=3; j++) {
			sprintf(t, "%d", array[i][j]);
			strcat(str, t);
			strcat(str, ",");
		}
	}/*游戏地图中的十六个数值转化为字符串*/
	sprintf(t, "%c", gameStep->direction);
	strcat(str, t);
	strcat(str, ",move=");
	sprintf(t, "%d", gameStep->move);
	strcat(str, t);
	strcat(str, ",score=");
	sprintf(t, "%d", gameStep->score);
	strcat(str, t);
	strcat(str, "\n");
	return str;
}

void arrayCopy(int destination[4][4], int source[4][4]){
	int i,j;
	for(i=0; i<=3; i++){
		for(j=0; j<=3; j++){
			destination[i][j] = source[i][j];
		}
	}
}

void copyGameStep(struct GameStep *destination, struct GameStep *source){
	memcpy(destination, source, sizeof(struct GameStep));
}
