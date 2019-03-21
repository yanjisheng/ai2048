/*
 * AIEvolve.h
 *
 *  Created on: 2019��3��2��
 *      Author: yanjisheng
 */

#ifndef AIEVOLVE_H_
#define AIEVOLVE_H_

#include "AIPlay.h"

/*��������weight��ȡһ���µġ��ӽ�����weight*/
struct Weight *getHybridWeight(struct Weight *, struct Weight *);

/*��ȡһ�������weight*/
struct Weight *getRandomWeight();

/*��ȡĳ��weight���ж����Ϸ���ƽ����*/
double getWeightScore(char *, struct Weight *);

void AIEvolve(int);

#endif /* AIEVOLVE_H_ */
