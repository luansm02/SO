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

void insertionSort(int arr[], int n)  {  
    int i, key, j;  
    #pragma omp parallel for
    for (i = 1; i < n; i++) {  
        key = arr[i];  
        j = i - 1;  
        while (j >= 0 && arr[j] > key) {  
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }  
        arr[j + 1] = key;  
    }  
}  

void bubble(int vet[], int n){
    int aux;
    #pragma omp parallel sections
    {
    	#pragma omp section
	    for(int i = 0; i<n/4; i++){
	        for(int j = 0; j<n-1; j++){
	            if(vet[j] > vet[j + 1]){
	                aux = vet[j];
	                vet[j] = vet[j+1];
	                vet[j+1] = aux;
	            }
	        }
	    }

	    #pragma omp section
	    for(int i = n/4; i<((n/4)*2); i++){
	        for(int j = 0; j<n-1; j++){
	            if(vet[j] > vet[j + 1]){
	                aux = vet[j];
	                vet[j] = vet[j+1];
	                vet[j+1] = aux;
	            }
	        }
	    }

	    #pragma omp section
	    for(int i = (n/4)*2; i<((n/4)*3); i++){
	        for(int j = 0; j<n-1; j++){
	            if(vet[j] > vet[j + 1]){
	                aux = vet[j];
	                vet[j] = vet[j+1];
	                vet[j+1] = aux;
	            }
	        }
	    }
	    #pragma omp section
	    for(int i = (n/4)*3; i<n; i++){
	        for(int j = 0; j<n-1; j++){
	            if(vet[j] > vet[j + 1]){
	                aux = vet[j];
	                vet[j] = vet[j+1];
	                vet[j+1] = aux;
	            }
	        }
 		}
 	}
}

void bubble2(int vet[], int n){
    int aux;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n-1; j++){
            if(vet[j] > vet[j + 1]){
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
            }
        }
    }
}
  
void printArray(int arr[], int n){  
    int i;  
    for (i = 0; i < n; i++)  
        cout << arr[i] << " ";  
    cout << endl; 
}  

void iniciaVetor(int vet[],int tam){
    for (int i = 0; i < tam; i++){
        vet[i] = rand()%500;
    }
}
int main()  {  
    clock_t tinicio,tfim;
    int n = 50;
    int arr[n];
    iniciaVetor(arr,n);
    printArray(arr,n);
    cout<<"\n\n";
    tinicio = clock();
    bubble(arr,n);
    tfim = clock();
    //insertionSort(arr, n);  
    printArray(arr, n);
    double tempoF = ((double)(tfim-tinicio)/(((double)CLOCKS_PER_SEC)));
    cout<<"tempo: "<<tempoF<<endl;
    
  
    return 0;  
}  
  