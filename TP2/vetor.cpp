#include <iostream>
#include <omp.h>
#include <time.h>
using namespace std;



void insertionSort(int arr[], int n)  {  
    int i, key, j;  
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
    //vet = new int[tam];
    for (int i = 0; i < tam; i++){
        vet[i] = rand()%500;
    }
}
  
int main()  {  
    clock_t tinicio,tfim;
    int n = 5000;
    int arr[n];
    iniciaVetor(arr,n);
    printArray(arr,n); 
    tinicio = clock();
    bubble(arr, n);  
    tfim = clock();
    printArray(arr, n);
    double tempoF = ((double)(tfim-tinicio)/(((double)CLOCKS_PER_SEC)));
    cout<<"tempo: "<<tempoF<<endl;  
  
    return 0;  
}  
  