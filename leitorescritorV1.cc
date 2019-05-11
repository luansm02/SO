/*
	Versao sem controle de concorrencia	- V1
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include<unistd.h> 

using namespace std;

#define nthread 10 // considerando que o id de thread comeca de 0 ate 9


typedef struct stc_produto{
	int id;
	char nome[20];
	float preco;
}Produto;


//Alimenta o vetor de Struct do Tipo Produto
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

Produto prod[10];

void * escrita(void *arg){
 	char *tip = (char *)arg;	//tip = nome da Thread
	printf ("O - Thread %s CRIADA!\n",tip);

	int index = rand()%10;
	float novoPreco = 1.0 + rand() * (10.0 - 1.0) / RAND_MAX;
 	int time = rand()%4;	//tempo aleatorio entre 0 e 3
 	printf("(escrita/Time:%d) - Thread %s atualizando preco do item id:%i de %.2f para %.2f(...)\n",time,tip, prod[index].id, prod[index].preco, novoPreco);
 	sleep(time);
 	prod[index].preco = novoPreco;	//Atribuicao do novo preco(sessao critica)
 	printf("Atualizado com sucesso (Thread %s): id:%i nome:%s preco:%.2f\n",tip, prod[index].id, prod[index].nome, prod[index].preco);
 
 	printf ("X - Thread %s Terminou!\n",tip);
	
	
 	pthread_exit(NULL);
}

void * leitura(void *arg){
	char *tip = (char*)arg;		//tip = nome da Thread
	
	printf ("O - Thread %s CRIADA!\n",tip);	
	int time = rand()%4;
	printf("(leitura/Time:%d) - A thread %s emitindo nota(...)\n", time,tip);
	sleep(time);
	//Imprime a Consulta Completa
	for(int i=0; i<10; i++){
 		printf("		(Consulta %s) id:%i nome:%s preco:%.2f\n",tip,prod[i].id,prod[i].nome, prod[i].preco);
 	}
	printf ("X - Thread %s Terminou!\n",tip);
	
	pthread_exit(NULL);
}


int main (int argc, char *argv[]){

	pthread_t thread_id[nthread];		//Vetor de Thread nThred = 10
	int retorno;						//retorno-> verifica se Create deu certo
	preencheProdutos(prod);				// Preenche o vetor de struct com valor pre-definidos
	
	printf("****Versao sem controle de Concorrencia****\n");
	printf("OBS: O - criacao / X - Exclusao\n\n");

	//Cria Threads e verifica se deu certo

	retorno = pthread_create (&thread_id[0], NULL, escrita, (void*)"T0-escritor");if(retorno!=0)printf("Erro na criacao da Thread 0!");
	retorno = pthread_create (&thread_id[1], NULL, leitura, (void*)"T1-leitor");if(retorno!=0)printf("Erro na criacao da Thread 1!");
	retorno = pthread_create (&thread_id[2], NULL, escrita, (void*)"T2-escritor");if(retorno!=0)printf("Erro na criacao da Thread 2!");
	retorno = pthread_create (&thread_id[3], NULL, leitura, (void*)"T3-leitor");if(retorno!=0)printf("Erro na criacao da Thread 3!");
	retorno = pthread_create (&thread_id[4], NULL, escrita, (void*)"T4-escritor");if(retorno!=0)printf("Erro na criacao da Thread 4!");
	retorno = pthread_create (&thread_id[5], NULL, leitura, (void*)"T5-leitor");if(retorno!=0)printf("Erro na criacao da Thread 5!");
	retorno = pthread_create (&thread_id[6], NULL, escrita, (void*)"T6-escritor");if(retorno!=0)printf("Erro na criacao da Thread 6!");
	retorno = pthread_create (&thread_id[7], NULL, leitura, (void*)"T7-leitor");if(retorno!=0)printf("Erro na criacao da Thread 7!");
	retorno = pthread_create (&thread_id[8], NULL, escrita, (void*)"T8-escritor");if(retorno!=0)printf("Erro na criacao da Thread 8!");
	retorno = pthread_create (&thread_id[9], NULL, leitura, (void*)"T9-leitor");if(retorno!=0)printf("Erro na criacao da Thread 9!");
	
	pthread_exit(NULL);
	
 	return 0;
}