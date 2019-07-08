/*
    Referencia: https://sergioprado.org/desafio-do-mes-programacao-paralela-com-o-openmp/
*/

#include <stdio.h>
#include <stdlib.h>
 
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
    int i, j, k;
    
    int **A, **B, **C, tmp;
    int Ndim, Pdim, Mdim;

    printf("Linha de A: "); scanf("%d",&Ndim);
    printf("Coluna de A e Linha de B: "); scanf("%d",&Pdim);
    printf("Coluna de B: "); scanf("%d",&Mdim);
    
    #pragma omp parallel sections
    {
        #pragma omp section
        A = alocarPreencheMatriz(Ndim,Pdim,1);
        #pragma omp section
        B = alocarPreencheMatriz(Pdim,Mdim,1);
        #pragma omp section
        C = alocarPreencheMatriz(Ndim,Mdim,0);
    }
    //imprime(Ndim,Pdim,A);
    //imprime(Pdim,Mdim,B);
    //imprime(Ndim,Mdim,C);

    #pragma omp parallel for private(tmp, i, j, k) shared(Ndim, Mdim, Pdim)         //diretiva de paralelizacao
    for (i = 0; i < Ndim; i++){                                                     //torna as variaveis tmp, i, j e k
        for (j = 0; j < Mdim; j++){                                                 //priva
            tmp = 0;
            for(k = 0;k < Pdim; k++){
                tmp += A[i][k] * B[k][j];
            }
            C[i][j] = tmp;
        }
    }
    
    //imprime(Ndim,Mdim,C);

    printf("Done!\n");
    #pragma omp parallel sections
    {
        #pragma omp section
        A = Liberar_matriz(Ndim, Pdim, A);
        #pragma omp section
        B = Liberar_matriz(Pdim, Mdim, B);
        #pragma omp section
        C = Liberar_matriz(Ndim, Mdim, C);
    }
    return 0;
}