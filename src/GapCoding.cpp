#include "GapCoding.h"

using namespace std;

//Crea arreglo GAP CODING igual al largo del arreglo original.
int* creaGC(int* arreglo, int largo){
    int* GC = new int[largo];
    GC[0] = arreglo[0]; //Inicializa el primer elemento
    for (int i = 1; i < largo; i++){
        GC[i]= arreglo[i] - arreglo[i-1]; //Resta el actual con el anterior 
    }
    return GC;
}


//Creamos el arreglo SAMPLE de tamaño m. Cada salto sera de tamaño b. 
int* creaSample(int* arreglo, int n, int m, int b){
    int* sample = new int[m]; // creamos el arreglo sample
    for (int i = 0; i < m; i++){
        sample[i] = arreglo[i*b]; //En el indice i del SAMPLE, colocaremos lo que hay en el arreglo original, en la posicion i*b
    }
    return sample;
}


///Realiza una busqueda binaria sobre el sample, par asi poder acotar el intervalo de busqueda en GC.
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
    
    //Si no se encuentra el elemento x en el sample, entonces procedemos a buscarlo linealmente en el
    //arreglo GC pero gracias a la busqueda binaria, la busqueda lineal sera en un intervalo acotado
    return busquedaLinealAcotadaGC(GC, x, n, der*b, Sample[der]);
}
//Se realizara una busqueda lineal en un intervao acotado en el arreglo GC.
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