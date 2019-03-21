/*
 * main.c
 *
 *  Created on: 2019��2��23��
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
		puts("��ѡ��1. ����(-h); 2. ������(-a)\n");
		char i = getche();
		if(i == '1' || i == 'h'){
			puts("\n�������������\n");
			scanf("%s", player);
			humanPlayGame(player, fileSaveEnabled);
		}else if(i == '2' || i == 'a'){
			puts("\n�������������\n");
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
		printf("��������\n");
	}

	return 0;
}
