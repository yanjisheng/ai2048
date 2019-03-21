/*
 * main.c
 *
 *  Created on: 2019年2月23日
 *      Author: yanjisheng
 */

#include "GameStep.h"
#include "PlayGame.h"
#include "HumanPlay.h"
#include "AIPlay.h"
#include "AIEvolve.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	srand((unsigned)time(NULL));
	int times = 0;
	char player[15];
	int fileSaveEnabled = 0;
	if(argc == 1){
		puts("请选择：1. 人玩(-h); 2. 机器玩(-a)\n");
		char i = getche();
		if(i == '1' || i == 'h'){
			puts("\n请输入玩家姓名\n");
			scanf("%s", player);
			humanPlayGame(player, fileSaveEnabled);
		}else if(i == '2' || i == 'a'){
			puts("\n请输入迭代次数\n");
			scanf("%d", &times);
			if(times > 1){
				AIEvolve(times);
			}
		}
	}else if(strcmp(strlwr(argv[1]), "-h") == 0 && argc >= 3 && strcmp(strlwr(argv[2]), "-f") != 0){
		strcpy(player, argv[2]);
		if(strcmp(strlwr(argv[3]), "-f") == 0){
			fileSaveEnabled = 1;
		}
		humanPlayGame(player, fileSaveEnabled);
	}else if(strcmp(strlwr(argv[1]), "-a") == 0 && argc >= 3 && atoi(argv[2]) > 0){
		times = atoi(argv[2]);
		AIEvolve(times);
	}else{
		printf("参数错误\n");
	}

	return 0;
}
