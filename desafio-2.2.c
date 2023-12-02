#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *funcaoFatorial(void *ptr);

struct tipoPack {
   char mensagem[16];
   int pos;
   unsigned long long fat;
};

typedef struct tipoPack tipoPack;

void main(void)
{
     int num_thread = 0;

     printf("Quantas threads vc quer que execute: ");
     do{
      if(num_thread<0){
      	puts("digite um valor positivo");
      }
      scanf("%d", &num_thread);
     }while(num_thread<=0);

     int  iret[num_thread];
     pthread_t thread[num_thread];

     tipoPack pack[num_thread];

     for(int i=0;i<num_thread;i++){
       char message[50];
	snprintf(message, 50, "thread %d",  i+1 );
     	strcpy(pack[i].mensagem,message);
    	
	printf("\nDigite a posicao do fatorial %d > ", i+1);
     	scanf("%d",&(pack[i].pos));
     	iret[i] = pthread_create(thread + i, NULL, funcaoFatorial, (void*) &pack[i]);
     }
     

    for(int i=0;i<num_thread;i++){
     pthread_join(thread[i], NULL);
     printf("\nThread %d fat(%d): %ld\n",i+1, pack[i].pos, pack[i].fat);
    }
     exit(0);
}

void *funcaoFatorial(void *ptr)
{    int i;

     tipoPack *pack;

     pack= (tipoPack *) ptr;

     printf("\nlog: %s: startando o calculo do fatorial\n", pack->mensagem);
     pack->fat = 1;

     if(pack->pos < 0){
     	pack->fat = 1;
     }else{
     	for (i=1; i<=(pack->pos); i++)
		(pack->fat) *= i;
     }
}
