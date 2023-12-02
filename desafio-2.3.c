#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

void *funcaoFatorial(void *ptr);

void *funcaoCalculaIntervalo(void *pts);

struct tipoPack {
   char mensagem[16];
   int pos;
   unsigned long long fat;
};

struct ponto{
	int ini;
	int fim;
	unsigned long long part;	
};

typedef struct ponto ponto;

typedef struct tipoPack tipoPack;

void main(void)
{
     pthread_t thread;

     int  iret;

     tipoPack pack;

     strcpy(pack.mensagem,"\nSou a thread 1");

     printf("\nDigite a número do fatorial 1 > ");
     scanf("%d",&(pack.pos));

     iret = pthread_create(&thread, NULL, funcaoFatorial, (void*) &pack);

     pthread_join(thread, NULL);

     printf("\nThread 1 fat(%d): %llu\n", pack.pos, pack.fat);
     exit(0);
}

void *funcaoFatorial(void *ptr)
{    int i;

     tipoPack *pack;

     pack= (tipoPack *) ptr;

     if(pack->pos < 0){
        pack->fat = 1;
        return pack;
     }

     int num_threads = ceil(log2(pack->pos));

     int tam_intervalo = num_threads >0 ? ceil(pack->pos/(num_threads*1.0)):0;

     pthread_t thread[num_threads];

     tipoPack packs[num_threads];

     ponto pts[num_threads];

     printf("numero de threads => %d  Tamanho do intervalo de cada thread => %d \n", num_threads, tam_intervalo);

     for(int i=0;i<num_threads;i++){
        pts[i].ini = (tam_intervalo*i)+1;
        pts[i].fim = pts[i].ini + tam_intervalo - 1;

        if(pts[i].fim > pack->pos){
            pts[i].fim = pack->pos;
        }

        pthread_create(thread+i, NULL, funcaoCalculaIntervalo, (void*) &pts[i]);     	
     }

     pack->fat = 1;

    for(int i=0;i<num_threads;i++){
        pthread_join(thread[i], NULL);
        printf("subthread %d calculou %d-%d: %d\n", (i+1), pts[i].ini, pts[i].fim , pts[i].part);
        pack->fat *= pts[i].part;
     }
}

void *funcaoCalculaIntervalo(void *ptr){
	ponto *pt;

	pt = (ponto *) ptr;
	
	if(pt->ini == pt->fim){
		pt->part = pt->ini;
	}else{
		pt->part = 1;
		for(int i=(pt->ini);i<=(pt->fim);i++){
			(pt->part)*=i;
		}
	}
}

