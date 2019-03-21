/*
 * AIEvolve.h
 *
 *  Created on: 2019年3月2日
 *      Author: yanjisheng
 */

#ifndef AIEVOLVE_H_
#define AIEVOLVE_H_

#include "AIPlay.h"

/*根据两个weight获取一个新的“杂交”的weight*/
struct Weight *getHybridWeight(struct Weight *, struct Weight *);

/*获取一个随机的weight*/
struct Weight *getRandomWeight();

/*获取某个weight进行多次游戏后的平均分*/
double getWeightScore(char *, struct Weight *);

void AIEvolve(int);

#endif /* AIEVOLVE_H_ */
