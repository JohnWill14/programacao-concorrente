#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

typedef int tipoVetor[1000];

int X, nElem, num_thread;

tipoVetor V;

struct intervalo{
	int ini;
	int fim;
	int qtd;	
	int busc;
};

typedef struct intervalo intervalo;

void geraVetor(void){   
    int i;
    
    srand(time(NULL));
    
    printf("\nVetor Gerado: ");

    for (i=0;i<nElem;i++) {
        V[i]=rand()%10;
        printf("%d, ",V[i]);
    }
}

void *busca(void *inter){
	intervalo *it;

	it = (intervalo *) inter;
	for(int i = it->ini;i<=it->fim;i++){
		if(V[i] == X){
			V[i] = -1;
			it ->qtd +=1;
		}
	}
}

int buscaXNoVetor(void){   
    int i;
    pthread_t thread[num_thread];
    int resp[num_thread];
    intervalo	inter[num_thread];
    int tamanho_inter = ceil(nElem/(num_thread*1.0));
    int limit = num_thread;
    
    time_t tempoSeg;
    struct tm *tempoLocal;


    time(&tempoSeg);
    tempoLocal = localtime(&tempoSeg);
    printf("\nHorario Inicial: %s \n", asctime(tempoLocal));
    
    for(int i=0;i<num_thread;i++){
    	inter[i].ini = (tamanho_inter*i);
	inter[i].fim = inter[i].ini+tamanho_inter-1;
	inter[i].qtd = 0;
	inter[i].busc = X;

	if(inter[i].ini>=nElem){
		limit = i;
		break;
	}

	if(inter[i].fim >= nElem){
	    inter[i].fim = nElem - 1;
	}

    	resp[i] = pthread_create(thread+i, NULL, busca, (void*) (inter+i));
    }

    
    int qtd = 0;

    for (i=0; i<limit; i++){

        pthread_join(thread[i], NULL);
	printf("thread %d - busca inicio: %d fim: %d encontrou %d ocorrencia(s)\n", i+1, inter[i].ini, inter[i].fim, inter[i].qtd);
	
	qtd += inter[i].qtd;
    }

     time(&tempoSeg);
     tempoLocal = localtime(&tempoSeg);
     printf("\nHorario Final: %s \n", asctime(tempoLocal));

    return qtd;

}

void main()
{   int quant;
 
    printf("Insira o número de threads => ");
    scanf("%d", &num_thread);

    printf("\nQual o tamanho do vetor => ");
    scanf("%d",&nElem);
    

    geraVetor();

    printf("\nQual o valor de X a ser procurado => ");
    scanf("%d",&X);

    quant=buscaXNoVetor();
    
    for(int i=0;i<nElem;i++){
	if(V[i]==-1)
    		printf("%d encontrado na posicao %d do vetor\n", X, i);
    }

    printf("\nNumero de Elementos Encontrados => %d\n", quant);
}
