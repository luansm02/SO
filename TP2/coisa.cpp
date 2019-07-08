#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <cstdio>

using namespace std;


int nlinha = 10;
int ncoluna = 10;
pthread_mutex_t table;
#define nthread 100


int **campoPrincipal;

void iniciaComSpace(int **campoPrincipal,int nlinha,int ncoluna);
void imprimeCampoPrincipal(int **campoPrincipal,int nlinha,int ncoluna);
void * colocaTable(void *arg);

int main(){

    pthread_t thread_id[nthread];		//Vetor de Thread nThred = 10
	int retorno;						//retorno-> verifica se Create deu certo
    pthread_mutex_init(&table, NULL);

    campoPrincipal = new int *[nlinha];
    // Cada elemento do array é um array de 10 floats 
    for(int i = 0; i < nlinha; i++)campoPrincipal[i] = new int[ncoluna];
    
    iniciaComSpace(campoPrincipal,nlinha,ncoluna);
    //imprimeCampoPrincipal(campoPrincipal,nlinha,ncoluna);
    //printf("numero thread %d",nthread);
    for(int j = 0; j<nthread; j++){
		pthread_create(&thread_id[j], NULL, &colocaTable, (void*)&j);
		usleep(rand()%100);
	}

    for(int j = 0; j<nthread; j++){
		pthread_join(thread_id[j], NULL);
		usleep(rand()%1000);
	}
    //printf("fim\n");
    usleep(1000);
    imprimeCampoPrincipal(campoPrincipal,nlinha,ncoluna);
    
}

void * colocaTable(void *arg){
 	int tip = *(int*) arg; //tip = nome da thread
	usleep(tip*2);

	int i = rand()%nlinha;
    int j = rand()%ncoluna;
    
    //pthread_mutex_lock(&table);
    printf ("Thread %d CRIADA!\n",tip);
    printf ("Thread %d escreve na linha %d e na coluna %d!\n",tip,i,j);
    campoPrincipal[i][j] = campoPrincipal[i][j] + 1;
    //imprimeCampoPrincipal(campoPrincipal,nlinha,ncoluna);
    
    
    
    //sleep(100);
    //pthread_mutex_unlock(&table);

 	printf ("Thread_%d Terminou!\n",tip);
 	
    pthread_exit(NULL);
    //return NULL;
}

void iniciaComSpace(int **campoPrincipal,int nlinha,int ncoluna){
    for(int i=0;i<nlinha;i++){
        for(int j=0;j<ncoluna;j++){
            campoPrincipal[i][j]=0;
            //cout<<campoPrincipal[i][j];
        }
    }
}
void imprimeCampoPrincipal(int **campoPrincipal,int nlinha,int ncoluna){

    cout<<"\n"<<"Tabela:"<<endl;
    int inicioLin = 0, finalLin = inicioLin+1,numLin = nlinha, numCol = ncoluna;
    char letra[ncoluna];
    cout<<"   ";
    
    if(ncoluna>26){
        for(int j=0;j<26;j++){
            letra[j]=j+'0';
            letra[j]=letra[j]+17;
            cout<<letra[j]<<"  ";
        }
        for(int j=0;j<(ncoluna-26);j++){
            letra[j]=j+'0';
            letra[j]=letra[j]+49;
            cout<<letra[j]<<"  ";
        }
    }else{
        for(int j=0;j<ncoluna;j++){
            letra[j]=j+'0';
            letra[j]=letra[j]+17;
            cout<<letra[j]<<"  ";
        }
    }
    cout<<"\n";

    while (inicioLin < numLin) {
        for (int i = inicioLin; i < finalLin; i++) {
            for (int j = 0; j < numCol; j++) {
                if (i == 0 && j == 0) {
                    cout << "  ┌──";
                }
                if (i == 0 && j >= 0 && j <= numCol - 2) {
                    cout << "┬──";
                }
                if (i == 0 && j == numCol - 1) {
                    cout << "┐";
                }
            }
        }
        cout << endl;
        for (int i = inicioLin; i < finalLin; i++) {
            if(i<=9){
                cout<<i<<" ";
            }else{
                cout<<i<<"";
            }
            for (int j = 0; j < numCol; j++) {
                if(campoPrincipal[i][j]<=9){
                    cout << "│ " << campoPrincipal[i][j];
                }else{
                    cout << "│" << campoPrincipal[i][j];
                }
                if (j == numCol - 1) {
                    if(campoPrincipal[i][j]<=9){
                        cout << "│ ";
                    }else{
                        cout << "│";
                    }
                }
            }
            
        }
        cout << endl;
        for (int i = inicioLin; i < finalLin; i++) {
            for (int j = 0; j < numCol; j++) {
               if (i >= 0&&i<=numLin-2 && j == 0) {
                    cout << "  ├─";
               }
               if (i >= 0 && i <= numLin - 2 && j >= 0 && j <= numCol - 2) {
                    cout << "─┼─";
               }
               if (i >= 0 && i <= numLin - 2 && j == numCol - 1) {
                    cout << "─┤";
               }
               if (i == (numLin - 1) && j == 0) {
                    cout << "  └──";
               }
                    if (i == (numLin - 1) && j == (numCol-1)) {
                    cout << "┘";
               }
                    if (i == (numLin - 1)&&j>=0 && j < (numCol-1)) {
                    cout << "┴──";
               }
            }
        }
        inicioLin++;
        finalLin=inicioLin+1;
    }
    cout<<"\n";
}
