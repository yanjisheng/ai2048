/*
 * GameStep.h
 * 2048��Ϸ��ÿһ������ֵ
 *  Created on: 2019��2��23��
 *      Author: yanjisheng
 */

#ifndef GAMESTEP_H_
#define GAMESTEP_H_

/*2048��Ϸ��ÿһ������ֵ*/
struct GameStep {
	int code[4][4]; /*��Ϸ�е�16������*/
	int move; /*�ƶ�����*/
	int score; /*����*/
	char direction; /*��һ�����ƶ�����*/
};

/*��ȡ��Ϸ�ĵ�һ��*/
struct GameStep *getFirstGameStep();

/*��������ķ����ȡ��Ϸ����һ��*/
struct GameStep *getNextGameStep(struct GameStep *, char, int);

struct GameStep *getNextGameStepNoAddNo(struct GameStep *, char);

struct GameStep *getNextGameStepAddNo(struct GameStep *, char);

/*�ж��Ƿ������һ��*/
int isFinalGameStep(struct GameStep *);

/*��ÿһ��ת��Ϊ�ַ���*/
char *GameStepToString(struct GameStep *);

void arrayCopy(int [4][4], int [4][4]);

void copyGameStep(struct GameStep *, struct GameStep *);

#endif /* GAMESTEP_H_ */
