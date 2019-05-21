#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_CLIENTES 10  //numero clientes
#define N_BARBEIROS 2  //numero de barbeiros
#define N_CADEIRAS 5    //numero de cadeiras

sem_t sem_cadeiras;   //representa as cadeiras em espera
sem_t sem_cad_barbeiro[N_BARBEIROS];  //representa as cadeiras dos barbeiros
sem_t sem_cabelo_cortado[N_BARBEIROS];  //cabelo foi cortado
sem_t sem_cliente_cadeira[N_BARBEIROS];   //não tem ninguém esperando

sem_t sem_escreve_visor, sem_le_visor;
int visor;

void* f_barbeiro(void *v) {
  int id = *(int*)v;

  while(1) {
    sem_wait(&sem_escreve_visor);   //espera ter cliente
    visor = id;   //avisa que está livre
    sem_post(&sem_le_visor);    //avisa que está acordado
    sem_wait(&sem_cliente_cadeira[id]);   //espera cliente estar na cadeira 
    //printf("Barbeiro %d cortou o cabelo de um cliente.\n", id);
    usleep(random()%1000+1);    //faz atendimento
    sem_post(&sem_cabelo_cortado[id]);    //avisa que terminou o corte    
  }
  return NULL;
}

void* f_cliente(void* v) {    //clientes
  int id = *(int*) v;
  int minha_cadeira;    //cadeira do barbeiro

  usleep(random()%700+4);
  if (sem_trywait(&sem_cadeiras) == 0) {   //tem cadeiras pra sentar
    printf("Cliente %d sentou.\n", id);   
    sem_wait(&sem_le_visor);    //espera algum barbeiro indicar que estava dormindo
    minha_cadeira = visor;    //ver qual barbeiro indicou que estava dormindo
    sem_post(&sem_escreve_visor);   //avisa que está sendo atendido
    sem_wait(&sem_cad_barbeiro[minha_cadeira]);
    printf("Cliente %d sentou na cadeira do barbeiro %d para cortar o cabelo.\n", id,minha_cadeira);
    sem_post(&sem_cliente_cadeira[minha_cadeira]);    //avisa que está na cadeira
    sem_post(&sem_cadeiras);    //deixa a cadeira
    sem_wait(&sem_cabelo_cortado[minha_cadeira]);   //espera o barbeiro fazer o corte
    sem_post(&sem_cad_barbeiro[minha_cadeira]);   //deixa a cadeira do barbeiro
    printf("Cliente %d cortou o cabelo.\n", id);
  } else
    printf("Cliente %d não tinha cadeiras para sentar.\n\n", id);
  return NULL;
}

int main() {
  pthread_t thr_clientes[N_CLIENTES], thr_barbeiros[N_BARBEIROS];
  int i, id_cl[N_CLIENTES], id_bar[N_BARBEIROS];

  printf("Cadeiras: %d\n",N_CADEIRAS);
  printf("Barbeiros: %d\n",N_BARBEIROS );
  printf("Clientes: %d\n\n", N_CLIENTES);

  sem_init(&sem_cadeiras, 0, N_CADEIRAS);   //cadeiras
  sem_init(&sem_escreve_visor, 0, 1);
  sem_init(&sem_le_visor, 0, 0);

  for (i = 0; i < N_BARBEIROS; i++) { //inicia semaforos 
    sem_init(&sem_cad_barbeiro[i], 0, 1);
    sem_init(&sem_cliente_cadeira[i], 0, 0);
    sem_init(&sem_cabelo_cortado[i], 0, 0);
  }
  
  for (i = 0; i < N_CLIENTES; i++) { //cria clientes
    id_cl[i] = i;
    pthread_create(&thr_clientes[i], NULL, f_cliente, (void*) &id_cl[i]);
  }

  for (i = 0; i < N_BARBEIROS; i++) {  //cria barbeiros
    id_bar[i] = i;
    pthread_create(&thr_barbeiros[i], NULL, f_barbeiro, (void*) &id_bar[i]);
  }
  
  for (i = 0; i < N_CLIENTES; i++) {
    pthread_join(thr_clientes[i], NULL);
  }

  printf("Acabou o expediente do barbeiro\n");

  
  
  return 0;
}