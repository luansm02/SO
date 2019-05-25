/*
	Versao com mesma Prioridade (Leitura Suja).
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h> 
#include <semaphore.h>

using namespace std;

#define nthread 10 


pthread_mutex_t mutex_cont;
pthread_mutex_t l;
pthread_mutex_t e;   
int cont = 0 ;

typedef struct stc_produto{
	int id;
	char nome[20];
	float preco;
}Produto;

Produto prod[10];

void preencheProdutos(Produto *p){
	p[0].id = 1;	strcpy(p[0].nome, "bolacha");		p[0].preco = 1.50;
	p[1].id = 2;	strcpy(p[1].nome, "sabao");			p[1].preco = 6.00;
	p[2].id = 3;	strcpy(p[2].nome, "leite");			p[2].preco = 4.50;
	p[3].id = 4;	strcpy(p[3].nome, "desodorente");	p[3].preco = 5.20;
	p[4].id = 5;	strcpy(p[4].nome, "detergente");	p[4].preco = 5.00;
	p[5].id = 6;	strcpy(p[5].nome, "talco");			p[5].preco = 3.50;
	p[6].id = 7;	strcpy(p[6].nome, "creme dental");	p[6].preco = 2.00;
	p[7].id = 8;	strcpy(p[7].nome, "feijao");		p[7].preco = 3.00;
	p[8].id = 9;	strcpy(p[8].nome, "arroz");			p[8].preco = 2.75;
	p[9].id = 10;	strcpy(p[9].nome, "suco");			p[9].preco = 1.00;
}

void * escrita(void *arg){
    int tip = *(int*) arg,index,time = rand()%4;
    float novoPreco,precoAntigo;

    printf("Thread_%d_escritor CRIADA!\n",tip);

    pthread_mutex_lock(&mutex_cont);
    cont++;
    if(cont==1)pthread_mutex_lock(&l);
    pthread_mutex_unlock(&mutex_cont);

    pthread_mutex_lock(&e);

    printf("(time:%d)Thread_%d_escritor solicitando Escrita (...)\n",time,tip);
    sleep(time);
    
    index = rand()%10;
	novoPreco = 1.0 + rand() * (10.0 - 1.0) / RAND_MAX;
	
    precoAntigo = prod[index].preco;
    prod[index].preco = novoPreco;
    printf("A Thread_%d_escritor alterou o preco do %s de %.2f para %.2f\n",tip,prod[index].nome,precoAntigo,prod[index].preco);

    pthread_mutex_unlock(&e);

    pthread_mutex_lock(&mutex_cont);
    cont--;
    if(cont==0){pthread_mutex_unlock(&l);}
    pthread_mutex_unlock(&mutex_cont);
    printf("Thread_%d_escritor TERMINADA!\n",tip);
}

void * leitura(void *arg){
        
    int tip = *(int*) arg;
    int time = rand()%4;    //tempo aleatorio 
    printf("Thread_%d_leitor CRIADA!\n",tip);

    pthread_mutex_lock(&l);
    printf("(leitura/time:%d)Thread %d emitindo nota(...)\n",time,tip);
    sleep(time);
    for(int i=0; i<10; i++){
 		printf("		(Consulta T-%d) id:%i nome:%s preco:%.2f\n",tip,prod[i].id,prod[i].nome, prod[i].preco);
        sleep(0.5);
 	}
    pthread_mutex_unlock(&l);
    printf("Thread_%d_leitor TERMINADA!\n",tip);

}

int main(){

    pthread_t thread_id[nthread];		//Vetor de Thread nThred = 10
	int retorno;						//retorno-> verifica se Create deu certo
	preencheProdutos(prod);				// Preenche o vetor de struct com valor pre-definidos

	printf("****Versao Escritor com Preferencia sobre leitor****\n\n");


    pthread_mutex_init(&mutex_cont, NULL);
    pthread_mutex_init(&l, NULL);
    pthread_mutex_init(&e, NULL);
    
    for(int j = 0; j<nthread; j++){
		if(j%2==0){
			pthread_create(&thread_id[j], NULL, escrita, (void*)&j);
		}
		else{
			pthread_create (&thread_id[j], NULL, leitura, (void*)&j);
		}
		sleep(1);
	}

    pthread_exit(NULL);
}