/*
    Referencia: https://sergioprado.org/desafio-do-mes-programacao-paralela-com-o-openmp/
*/

#include <stdio.h>
#include <stdlib.h>
 
#define ORDER 8 //1024
#define AVAL 3.0
#define BVAL 5.0
#define TOL  0.001
 

void imprime(int linha,int coluna,int **mt){
    for(int i=0;i<linha;i++){
        for(int j=0;j<coluna;j++){
            printf("%d ",mt[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int** alocarPreencheMatriz(int Linhas,int Colunas,char tipo){
 
    int **m = (int**)malloc(Linhas * sizeof(int*));
 
    for (int i = 0; i < Linhas; i++){
        m[i] = (int*) malloc(Colunas * sizeof(int));
        for (int j = 0; j < Colunas; j++){
            if(tipo==0)m[i][j] = 0;
            else m[i][j] = rand()%10;
        }
    }
    return m;
}

int **Liberar_matriz (int linha, int coluna, int **mt)      //Ref: http://mtm.ufsc.br/~azeredo/cursoC/aulas/ca70.html
{
  int  i;  /* variavel auxiliar */
    if (mt == NULL) return (NULL);
    if (linha < 1 || coluna < 1) {  /* verifica parametros recebidos */
    printf ("** Erro: Parametro invalido **\n");
        return (mt);
    }
    for (i=0; i<linha; i++)free(mt[i]); /* libera as linhas da matriz */
    free(mt);      /* libera a matriz */
    return (NULL); /* retorna um ponteiro nulo */
}

int main(int argc, char **argv)
{
    int ** A, **B, **C,tmp;
    int Ndim,Pdim,Mdim;
    int i, j, k;
    
    printf("Linha de A: "); scanf("%d",&Ndim);
    printf("Coluna de A e Linha de B: "); scanf("%d",&Pdim);
    printf("Coluna de B: "); scanf("%d",&Mdim);
    
    A = alocarPreencheMatriz(Ndim,Pdim,1);
    B = alocarPreencheMatriz(Pdim,Mdim,1);
    C = alocarPreencheMatriz(Ndim,Mdim,0);

    //imprime(Ndim,Pdim,A);
    //imprime(Pdim,Mdim,B);
    //imprime(Ndim,Mdim,C);

    for (i = 0; i < Ndim; i++){
        for (j = 0; j < Mdim; j++){
            tmp = 0;
            for(k = 0; k < Pdim; k++){
                tmp += A[i][k] * B[k][j]; 
            }
            C[i][j] = tmp;
        }
    }
    
    //imprime(Ndim,Mdim,C);

    printf("Done!\n");
    A = Liberar_matriz(Ndim, Pdim, A);
    B = Liberar_matriz(Pdim, Mdim, B);
    C = Liberar_matriz(Ndim, Mdim, C);
    return 0;
}