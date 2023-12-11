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
	int tLinha, tColuna;
	
	puts("insira o tamanho da linha e da coluna da matriz A: ");
	scanf("%d %d", &tLinha, &tColuna);

	double **arrayA = (double **)malloc(tLinha * sizeof(double *)), **arrayB= (double **)malloc(tColuna * sizeof(double *));
	
    for (int i = 0; i < tLinha; i++) {
        arrayA[i] = (double *)malloc(tColuna * sizeof(double));
    }

    for (int i = 0; i < tColuna; i++) {
        arrayB[i] = (double *)malloc(tLinha * sizeof(double));
    }

	srand(time(NULL));	

	printf("\nmatriz A:\n");

	for(int i=0;i<tLinha;i++){
	   for(int j=0;j<tColuna;j++){
			arrayA[i][j] = rand()%11;
			printf("[%.0lf]  ", arrayA[i][j]);
	    }
	   printf("\n");
	}

	printf("\nmatriz B:\n");

	for(int i=0;i<tColuna;i++){
	   for(int j=0;j<tLinha;j++){
			arrayB[i][j] = rand()%11;
			printf("[%.0lf] ", arrayB[i][j]);
	   }
	   printf("\n");
	}

	printf("\n");

	matrizes **input = (matrizes **)malloc(tLinha * sizeof(matrizes *));
	pthread_t  **thread = (pthread_t **)malloc(tLinha * sizeof(pthread_t *));

	for(int i=0;i<tLinha;i++){
			input[i] = (matrizes *)malloc(tLinha * sizeof(matrizes));
        	thread[i] = (pthread_t *)malloc(tLinha * sizeof(pthread_t));

		for(int j=0;j<tLinha;j++){
			input[i][j].matrizA = arrayA[i];

			double *colunaMatrizB = (double *)malloc(tLinha * sizeof(double));

			for(int j2=0;j2<tColuna;j2++){
				colunaMatrizB[j2] = arrayB[j2][j]; 
			}

			input[i][j].matrizB = colunaMatrizB;
			input[i][j].tamanho = tColuna;
			int resp = pthread_create(&thread[i][j] , NULL, multiplica, (void*) &input[i][j]);

		}
	}

	puts("resultado: ");

	for(int i=0;i<tLinha;i++){
		for(int j=0;j<tLinha;j++){
			pthread_join(thread[i][j], NULL);
			printf("[%04.0lf]  ", input[i][j].result);
		}
		printf("\n");
	}

	printf("\n");

	free(input); 
    free(thread); 
    free(arrayA);
    free(arrayB);

	return 0;
}
