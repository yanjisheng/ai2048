/*
 * AIPlay.h
 *
 *  Created on: 2019��3��2��
 *      Author: yanjisheng
 */

#ifndef AIPLAY_H_
#define AIPLAY_H_

#include "GameStep.h"

struct Weight{
	double w[4][4];
}; /*��GameStep��ֵ�Ȩ�أ�ϵ����*/

/*����Ȩ�ظ���Ϸ������*/
double judgeTendency(struct GameStep *, struct Weight *);

/*���ո����Ĵ��Ȩ�ؽ�����Ϸ��������Ϸ���ճɼ�*/
int AIPlayGame(char *, struct Weight *);

void weightArrayCopy(double [4][4], double[4][4]);

#endif /* AIPLAY_H_ */
