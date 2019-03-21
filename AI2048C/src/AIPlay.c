/*
 * AIPlay.c
 *
 *  Created on: 2019年3月2日
 *      Author: yanjisheng
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "PlayGame.h"

#include "AIPlay.h"

double judgeTendency(struct GameStep *gameStep, struct Weight *weight){
	double result = 0;
	int i, j;
	for(i=0; i<=3; i++){
		for(j=0; j<=3; j++){
			result += weight->w[i][j] * gameStep->code[i][j];
		}
	}
	return result;
}

int AIPlayGame(char *name, struct Weight *weight){
	static int seriesNo = 0;
	int score;
	char str[35];
	char t[5];
	int i;
	seriesNo++;
	strcpy(str, name);
	sprintf(t, "%04d", seriesNo%10000);
	strcat(str, "_");
	strcat(str, t);
	struct GameStep *gameStep = startGame(str, 0);
	do{
		char direction; /*下一步的四个可能的方向*/
		char bestDirection; /*下一步最佳的方向（tendency最高）*/
		double tendency = -1;
		for(i=1; i<=4; i++){
			switch(i){
			case 1:
				direction = 'w';
				break;
			case 2:
				direction = 'a';
				break;
			case 3:
				direction = 's';
				break;
			case 4:
				direction = 'd';
				break;
			}
			struct GameStep *nextGameStep = getNextGameStepNoAddNo(gameStep, direction);
			if(nextGameStep->move > -1){ /*下一步与当前步必须有变化*/
				double tt = judgeTendency(nextGameStep, weight);
				if(tt > tendency) {
					bestDirection = direction;
					tendency = tt;
				}
			}
			free(nextGameStep);
		}
		gameStep = playGame(bestDirection);
	}while(!isFinalGameStep(gameStep));
	score = gameStep->score;
	free(gameStep);
	return score;
}

void weightArrayCopy(double destination[4][4], double source[4][4]){
	int i, j;
	for(i=0; i<=3; i++){
			for(j=0; j<=3; j++){
				destination[i][j] = source[i][j];
			}
		}
}
