/*
 * PlayGame.h
 * ��2048��Ϸ
 *  Created on: 2019��2��23��
 *      Author: yanjisheng
 */

#ifndef PLAYGAME_H_
#define PLAYGAME_H_

#include "GameStep.h"

struct GameStep *startGame(char *, int);

struct GameStep *playGame(char);

#endif /* PLAYGAME_H_ */
