#include "GapCoding.h"

using namespace std;

int* creaGC(int* arreglo, int largo){

    int* GC = new int[largo];
    GC[0] = arreglo[0]; //Inicializa el primer elemento

    for (int i = 1; i < largo; i++){
        //Resta el actual con el anterior :3 
        GC[i]= arreglo[i] - arreglo[i-1];

    }
    return GC;
}

int* creaSample(int* arreglo, int n, int m, int b){
    // creamos el arreglo sample
    int* sample = new int[m];
    for (int i = 0; i < m; i++){
        sample[i] = arreglo[i*b];
    }
    return sample;
}

int busquedaBinariaSample_GC(int* GC, int* Sample, int x, int n, int m, int b) {
    int izq = 0, der = m - 1;
    if(x<Sample[0]) return -1;
    while (izq <= der) {
        int medio = (izq + der) / 2;
        if (Sample[medio] == x)
            return medio*b;
        if (Sample[medio] < x)
            izq = medio + 1;
        else
            der = medio - 1;
    }
    
    return busquedaLinealAcotadaGC(GC, x, n, der*b, Sample[der]);
}

int busquedaLinealAcotadaGC(int* GC, int x, int n, int indice, int elemento_acotado){ 
    int elemento_sumado = elemento_acotado;
    for (int i = indice+1; i < n; ++i){
        elemento_sumado += GC[i];
        if (elemento_sumado > x)
            return -1;
        if (elemento_sumado == x)
            return i;
    }
    return -1;
}