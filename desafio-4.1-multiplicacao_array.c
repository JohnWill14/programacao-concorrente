#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

struct matrizes{
	double* matrizA;
	double* matrizB;
	int tamanho;
	double result;
};

typedef struct matrizes matrizes;

void *multiplica(void *ptr){
	matrizes *mat;

	mat = (matrizes *) ptr;

	mat->result = 0;

	for(int i=0;i<mat->tamanho;i++){
		mat->result += mat->matrizA[i]*mat->matrizB[i];
	}
}

int main(){
	int tamanhoArray;
	
	puts("insira o tamanho do array: ");
	scanf("%d", &tamanhoArray);

	double arrayA[tamanhoArray], arrayB[tamanhoArray];
	
	puts("insira os valores do primeiro Array");

	for(int i=0;i<tamanhoArray;i++){
		scanf("%lf", arrayA+i);
	}

	puts("insira os valores do segundo Array");

	for(int i=0;i<tamanhoArray;i++){
		scanf("%lf", arrayB+i);
	}

	matrizes input1;

	input1.matrizA = arrayA;
	input1.matrizB = arrayB;
	input1.tamanho = tamanhoArray;

	pthread_t thread;
	int resp = pthread_create(&thread, NULL, multiplica, (void *) &input1);
	
	pthread_join(thread, NULL);

	printf("valor da multiplicacao do array: %.2lf\n", input1.result);

	return 0;
}
