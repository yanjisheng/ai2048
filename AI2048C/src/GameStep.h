/*
 * GameStep.h
 * 2048游戏的每一步的数值
 *  Created on: 2019年2月23日
 *      Author: yanjisheng
 */

#ifndef GAMESTEP_H_
#define GAMESTEP_H_

/*2048游戏的每一步的数值*/
struct GameStep {
	int code[4][4]; /*游戏中的16个格子*/
	int move; /*移动次数*/
	int score; /*分数*/
	char direction; /*上一步的移动方向*/
};

/*获取游戏的第一步*/
struct GameStep *getFirstGameStep();

/*根据输入的方向获取游戏的下一步*/
struct GameStep *getNextGameStep(struct GameStep *, char, int);

struct GameStep *getNextGameStepNoAddNo(struct GameStep *, char);

struct GameStep *getNextGameStepAddNo(struct GameStep *, char);

/*判断是否是最后一步*/
int isFinalGameStep(struct GameStep *);

/*把每一步转化为字符串*/
char *GameStepToString(struct GameStep *);

void arrayCopy(int [4][4], int [4][4]);

void copyGameStep(struct GameStep *, struct GameStep *);

#endif /* GAMESTEP_H_ */
