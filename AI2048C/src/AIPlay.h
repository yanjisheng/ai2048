/*
 * AIPlay.h
 *
 *  Created on: 2019年3月2日
 *      Author: yanjisheng
 */

#ifndef AIPLAY_H_
#define AIPLAY_H_

#include "GameStep.h"

struct Weight{
	double w[4][4];
}; /*给GameStep打分的权重（系数）*/

/*根据权重给游戏步骤打分*/
double judgeTendency(struct GameStep *, struct Weight *);

/*按照给定的打分权重进行游戏，返回游戏最终成绩*/
int AIPlayGame(char *, struct Weight *);

void weightArrayCopy(double [4][4], double[4][4]);

#endif /* AIPLAY_H_ */
