/*
 * PlayGame.h
 * 玩2048游戏
 *  Created on: 2019年2月23日
 *      Author: yanjisheng
 */

#ifndef PLAYGAME_H_
#define PLAYGAME_H_

#include "GameStep.h"

struct GameStep *startGame(char *, int);

struct GameStep *playGame(char);

#endif /* PLAYGAME_H_ */
