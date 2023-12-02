#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *funcaoFatorial(void *ptr);

struct tipoPack {
   char mensagem[16];
   int pos, fat;
};

typedef struct tipoPack tipoPack;

void main(void)
{
     pthread_t thread1, thread2;

     int  iret1, iret2;

     tipoPack pack1, pack2;

     strcpy(pack1.mensagem,"\nSou a thread 1");

     strcpy(pack2.mensagem,"\nSou a thread 2");

     printf("\nDigite a posicao do fatorial 1 > ");
     scanf("%d",&(pack1.pos));

     printf("\nDigite a posicao do fatorial 2 > ");
     scanf("%d",&(pack2.pos));

     iret1 = pthread_create(&thread1, NULL, funcaoFatorial, (void*) &pack1);

     iret2 = pthread_create(&thread2, NULL, funcaoFatorial, (void*) &pack2);

     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL);

     printf("\nThread 1 fat(%d): %d\n", pack1.pos, pack1.fat);
     printf("\nThread 2 fat(%d): %d\n", pack2.pos, pack2.fat);
     exit(0);
}

void *funcaoFatorial(void *ptr)
{    int i;

     tipoPack *pack;

     pack= (tipoPack *) ptr;

     printf("%s: vou realizar o calculo do fatorial", pack->mensagem);
     pack->fat = 1;
     for (i=1; i<=(pack->pos); i++)
	(pack->fat) *= i;

}
