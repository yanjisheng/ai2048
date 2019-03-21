/*
 * AIEvolve.c
 *
 *  Created on: 2019年3月2日
 *      Author: yanjisheng
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "AIPlay.h"

#include "AIEvolve.h"

#define AI_PLAY_TIMES 100
#define WEIGHTS_PER_GENERATION 100
#define BEST_WEIGHTS_NO 10

struct Weight *getHybridWeight(struct Weight *weight1, struct Weight *weight2){
	struct Weight *newWeight = (struct Weight *)malloc(sizeof(struct Weight));
	int i, j;
	for(i=0; i<=3; i++){
		for(j=0; j<=3; j++){
			newWeight->w[i][j] = (weight1->w[i][j] + weight2->w[i][j]) / 2;
		}
	}
	return newWeight;
}

struct Weight *getRandomWeight(){
	struct Weight *newWeight = (struct Weight *)malloc(sizeof(struct Weight));
	int i, j;
	for(i=0; i<=3; i++){
		for(j=0; j<=3; j++){
			newWeight->w[i][j] = rand() / (double) RAND_MAX * 16;
		}
	}
	return newWeight;
}

double getWeightScore(char *name, struct Weight *weight){
	int totalScore = 0;
	int i;
	for(i=0; i<AI_PLAY_TIMES; i++){
		totalScore += AIPlayGame(name, weight);
	}
	double weightScore = (double) totalScore / AI_PLAY_TIMES;
	return weightScore;
}

void AIEvolve(int generations){
	struct Weight *weights = (struct Weight *) malloc(WEIGHTS_PER_GENERATION * sizeof(struct Weight));
	struct Weight *bestWeights = (struct Weight *) malloc(BEST_WEIGHTS_NO * sizeof(struct Weight));
	double scores[WEIGHTS_PER_GENERATION];
	double temp[BEST_WEIGHTS_NO];
	int index[BEST_WEIGHTS_NO];
	int i, j, k;
	struct Weight *weight = NULL;

	//srand(time(NULL));
	for(j=0; j<generations; j++){
		/*第j代，获取每一个weight的成绩(score)*/
		for(i=0; i<WEIGHTS_PER_GENERATION; i++){
			int a=0, b=0;
			if(j==0){
				/*第0代为随机初始值*/
				switch(i){
				case 0:
					weight = (struct Weight *) malloc(sizeof(struct Weight));
					double x[4][4] = {{0,0,0,16},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
					weightArrayCopy(weight->w, x);
					break;
				case 1:
					weight = (struct Weight *) malloc(sizeof(struct Weight));
					double y[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
					weightArrayCopy(weight->w, y);
					break;
				case 2:
					weight = (struct Weight *) malloc(sizeof(struct Weight));
					double z[4][4] = {{1,2,4,8,},{1,0,0,0},{0,0,0,0},{0,0,0,0}};
					weightArrayCopy(weight->w, z);
					break;
				default:
					weight = getRandomWeight();
				}
			}else{
				/*第1代及以后为杂交值*/
				b++;
				if(b>=BEST_WEIGHTS_NO){
					a++;
					b=a+1;
					if(b>=BEST_WEIGHTS_NO){
						weight = getRandomWeight();
						goto next;
					}
				}
				weight = getHybridWeight(bestWeights + a, bestWeights + b);
				next:;
			}
			memcpy(weights + i, weight, sizeof(struct Weight));
			char str[35];
			char t[5];
			strcpy(str, "AI_Generation");
			sprintf(t, "%d", j);
			strcat(str, t);
			strcat(str, "_Item");
			sprintf(t, "%d", i);
			strcat(str, t);
			scores[i] = getWeightScore(str, weight);
			//printf("第%d代第%d个个体的得分为%lf\n", j, i, scores[i]);
			free(weight);
		}

		/*挑出成绩最好的若干个weights，存入bestWeights*/
		for(k=0; k<BEST_WEIGHTS_NO; k++){
			temp[k] = INT_MIN;
			index[k] = -1;
			for(i=0; i<WEIGHTS_PER_GENERATION; i++){
				if(temp[k] < scores[i]){
					if(k==0 || index[k-1] != i){
						temp[k] = scores[i];
						index[k] = i;
					}
				}
			}
			memcpy(bestWeights + k, weights + i, sizeof(struct Weight));
		}
	}
}



