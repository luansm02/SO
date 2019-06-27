#include <iostream>
#include <omp.h>
#include <math.h>
#include <time.h>
#include <cstdlib>
using namespace std;

int i, nthreads;
clock_t clock_timer;
double wall_timer;
double c[1000000]; 
  
void printMatriz(int **matriz, int tam){  
    for (int i = 0; i < tam; i++){
        for(int j = 0; j<tam;j++){
            cout<<matriz[i][j]<<" ";
        }
        cout<<endl;
    }
}  

void iniciaMatriz(int **matriz,int tam){
    for (int i = 0; i < tam; i++){
        for(int j = 0; j<tam;j++){
            matriz[i][j] = i+1;
        }
    }
}

void multiplicaMatriz(int **m1,int **m2, int **m3, int n){
    int aux = 0;
    #pragma omp parallel sections
    {
        #pragma omp section
        for(int i = 0; i<n/4; i++){
            for(int j = 0; j<n; j++){
                for (int x = 0; x < n; x++){
                    aux+=m1[i][x]*m2[x][j];
                }
                m3[i][j] = aux;
                aux = 0;
            }
        }

        #pragma omp section
        for(int i = n/4; i<((n/4)*2); i++){
            for(int j = 0; j<n; j++){
                for (int x = 0; x < n; x++){
                    aux+=m1[i][x]*m2[x][j];
                }
                m3[i][j] = aux;
                aux = 0;
            }
        }

        #pragma omp section
        for(int i = (n/4)*2; i<((n/4)*3); i++){
            for(int j = 0; j<n; j++){
                for (int x = 0; x < n; x++){
                    aux+=m1[i][x]*m2[x][j];
                }
                m3[i][j] = aux;
                aux = 0;
            }
        }
        #pragma omp section
        for(int i = (n/4)*3; i<n; i++){
            for(int j = 0; j<n; j++){
                for (int x = 0; x < n; x++){
                    aux+=m1[i][x]*m2[x][j];
                }
                m3[i][j] = aux;
                aux = 0;
            }
        }
    }
}
int main()  {  
    clock_t tinicio,tfim;
    int n = 10;
    int **matriz1;
    int **matriz2;

    matriz1 = new int *[n];
    for(int i = 0; i < n; i++)
        matriz1[i] = new int[n];

    matriz2 = new int *[n];
    for(int i = 0; i < n; i++)
        matriz2[i] = new int[n];


    iniciaMatriz(matriz1,n);
    iniciaMatriz(matriz2,n);
    int **matrizF;
    matrizF = new int *[n];
    for(int i = 0; i < n; i++)
        matrizF[i] = new int[n];
    printMatriz(matriz1, n);
    cout<<endl;
    printMatriz(matriz2,n);
    tinicio = clock();
    multiplicaMatriz(matriz1,matriz2,matrizF,n);
    tfim = clock();
    cout<<"Matriz Final: \n\n";
    printMatriz(matrizF,n);
    double tempoF = ((double)(tfim-tinicio)/(((double)CLOCKS_PER_SEC)));
    cout<<"tempo: "<<tempoF<<endl;
    
  
    return 0;  
}  
  