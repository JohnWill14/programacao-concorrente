#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *funcaoImprimeMensagem( void *ptr );

int vetor[3000];

void main(void)
{
    pthread_t thread1, thread2, thread3;
    
    int um = 1;
    int dois = 2;
    int tres = 3;
    
    int  iret1, iret2, iret3;


    iret1 = pthread_create(&thread1, NULL, funcaoImprimeMensagem, (void*) &um);

    iret2 = pthread_create(&thread2, NULL, funcaoImprimeMensagem, (void*) &dois);

    iret3 = pthread_create(&thread3, NULL, funcaoImprimeMensagem, (void*) &tres);

    printf("\nCriacao da thread 1 retornou: %d\n",iret1);
    printf("\nCriacao da thread 2 retornou: %d\n",iret2);
    printf("\nCriacao da thread 3 retornou: %d", iret3),
    /* Espera as threads completarem para entao continuar, para nao
       correr o risco de terminar o programa principal antes das
       threads terminarem. O termino do processo causa forcadamente
       o termino de suas tarefas */

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("\nthreads 1, 2 e 3 finalizaram :( ...\n");
   
    for(int i=0;i<3000;i++){
    	printf("[%d] => %d\n", i, vetor[i]);
    }


    exit(0);
}

void *funcaoImprimeMensagem( void *ptr )
{
     int *numero_thread;
     numero_thread = (int*) ptr;
     
     int valor = *numero_thread;

     for(int i = 0; i<1000; i++){
     	printf("thread %d %d\n", valor, i+1);
	vetor[i+((valor-1)*1000)] = valor;
     }
}

/*
     para o item 4 foi modificado a funcao funcaoImprimeMensagem pra receber um endereco do tipo int
     nessa funcao foi configurado pra q a thread1 popule a primeira parte do vetor, a thread2 popule a segunda
     e assim por diante.

     A msg he configurada com base na thread e no valor passado na funcao
*/
