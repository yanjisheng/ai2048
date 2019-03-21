/*
 * GameStep.c
 *
 *  Created on: 2019��2��23��
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
	struct GameStep *firstGameStep = (struct GameStep*) malloc(sizeof(struct GameStep)); /*����һ��������ڴ�*/
	int array[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
	arrayCopy(firstGameStep->code, array);
	firstGameStep->move = 0;
	firstGameStep->score = 0;
	firstGameStep->direction = '\0';
	//srand((unsigned)time(NULL)); /*�������������*/
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
	int code[4][4]; /*��Ϸ�е�16�����ӣ���ʱ������*/
	int move = gameStep->move;
	int score = gameStep->score;
	int change = 0;
	int temp[5] = {0, 0, 0, 0, 0};
	struct GameStep *nextGameStep = (struct GameStep*) malloc(sizeof(struct GameStep)); /*����һ��������ڴ�*/
	arrayCopy(code, gameStep->code); /*����һ������ʱ������ֵ*/
	switch(direction){
		case 'W':
		case 'w':/*��*/
			for(j=0;j<=3;j++){
				for(i=0;i<=3;i++){
					temp[i]=code[i][j];/*��һ�����Ƶ��м����*/
				}
				change += squashLine(temp, &score);
				for(i=0;i<=3;i++){
					code[i][j]=temp[i];/*�Ѵ���õ��м�����ƻ���*/
				}
			}
			break;

		case 'A':
		case 'a':/*��*/
			for(i=0;i<=3;i++){
				for(j=0;j<=3;j++){
					temp[j]=code[i][j];/*��һ�����Ƶ��м����*/
				}
				change += squashLine(temp, &score);
				for(j=0;j<=3;j++){
					code[i][j]=temp[j];/*�Ѵ���õ��м�����ƻ���*/
				}
			}
			break;

		case 'S':
		case 's':/*��*/
			for(j=0;j<=3;j++){
				for(i=0;i<=3;i++){
					temp[i]=code[3-i][j];/*��һ�����Ƶ��м����*/
				}
				change += squashLine(temp, &score);
				for(i=0;i<=3;i++){
					code[3-i][j]=temp[i];/*�Ѵ���õ��м�����ƻ���*/
				}
			}
			break;

		case 'D':
		case 'd':/*��*/
			for(i=0;i<=3;i++){
				for(j=0;j<=3;j++){
					temp[j]=code[i][3-j];/*��һ�����Ƶ��м����*/
				}
				change += squashLine(temp, &score);
				for(j=0;j<=3;j++){
					code[i][3-j]=temp[j];/*�Ѵ���õ��м�����ƻ���*/
				}
			}
			break;
	}
	arrayCopy(nextGameStep->code, code); /*����һ����ʮ�������Ӹ�ֵ*/
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

/*�ж��Ƿ������һ��*/
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

/*���ѡһ���ո�����2��4*/
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

/*��һ�л�һ�������м�ѹ����*/
int squashLine(int line[], int *score) {
	int i;
	int t=0;
	int change = 0;/*�ж������Ƿ��иı䣬0���䣬1�仯*/
	int scoreTemp = 0;/*���β��������ӵĵ÷�*/
	do {
		for(i=0; i<=3 ;i++) {
			if(line[i]==0) {
				if(line[i]!=line[i+1]) {
					change=1;/*��һ��0���治��0ʱ����ı�*/
				}
				line[i]=line[i+1];
				line[i+1]=0;
			}
		}/*ȥ���м��0*/
		t++;
	} while(t<=3);/*�ظ����*/
	for(i=1;i<=3;i++) {
		if(line[i]==line[i-1]){
			if(line[i]!=0){
				change=1;/*������������ͬ�������ʱ����ı�*/
				scoreTemp+=line[i];/*�ӷ�*/
			}
			line[i-1]=line[i-1]*2;
			line[i]=0;
		}
	}/*���������ڵ���ͬ����������*/
	for(i=0;i<=3;i++) {
		if(line[i]==0) {
			line[i]=line[i+1];
			line[i+1]=0;
		}
	}/*ȥ���м��0*/
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
	}/*��Ϸ��ͼ�е�ʮ������ֵת��Ϊ�ַ���*/
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
