#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>

#define CLIENTES 15                /* número de cadeiras para os clientes à espera */
#define CADEIRAS 3

sem_t semCadeira;	// semaforo para cadeiras livres
sem_t semCadeiraAtendimento; //semaforo cadeira do barbeiro
sem_t semCabeloCortado; //semaforo cabelo cortado ou nao

pthread_t barbeiro;		//threads barbeiro
pthread_t cliente[CLIENTES];	//threads clientes
int id[CLIENTES];

void * vidaCliente(void * arg){
	int id = *(int*) arg;
	usleep(id*2);
	if(sem_trywait(&semCadeira) == 0){
		printf("Tem cadeiras para o Cliente %d \n",id);;
		sem_wait(&semCadeiraAtendimento);	//aguarda o barbeiro
		sem_post(&semCadeira);	//é atendido
		sem_wait(&semCabeloCortado);	//espera cortar o cabelo
		printf("O cliente %d cortou o cabelo\n\n", id);
		sem_post(&semCadeira);	//libera cadeira
		sem_post(&semCadeiraAtendimento);	//libera barbeiro
	}else{
		printf("Não havia cadeiras para o cliente %d \n\n",id);
	}
	pthread_exit(NULL);

} 

void * vidaBarbeiro(void * arg){
	usleep(10);
	while(1){
		sem_wait(&semCadeira); //espera ter cliente e dorme enquanto isso
		printf("Barbeiro atendendo cliente\n");
		usleep(500);	//realizando atendimento
		sem_post(&semCabeloCortado);	//terminou de atender
	}
	pthread_exit(NULL);
}

int main(){
	sem_init(&semCadeira, 0, CADEIRAS);	//inicia semaforo
	sem_init(&semCadeiraAtendimento, 0, 1);	//inicia semaforo
	sem_init(&semCabeloCortado, 0, 0);	//inicia semaforo

	int j = 0;
	pthread_create(&barbeiro, NULL, &vidaBarbeiro, (void*)&id[j]);

	for(j = 0; j<CLIENTES; j++){
		id[j] = j;
		pthread_create(&cliente[j], NULL, &vidaCliente, (void*)&id[j]); //cria threads
		usleep(rand()%100);	//tempo para ver outro cliente
	}

	for(int i = 0; i<CLIENTES; i++){
		pthread_join(cliente[i], NULL);	//saida das threads do clientes
	}

	printf("Acabou o espediente e o barbeiro foi pra casa dormir \n");

	return 0;
}