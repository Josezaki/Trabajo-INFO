#include "ArregloExplicito.h"
using namespace std;

// Crea un arreglo ordenado siguiendo la distribución lineal
int* creaArregloLineal(int largo){
    int* arr = new int[largo];
    arr[0] = rand();
    for(int i = 1; i < largo; i++){
        arr[i] = arr[i-1] + rand()%(EPSILON);
    }
    return arr;
}

// Crea un arreglo ordenado siguiendo la distribución normal
int* creaArregloNormal(int largo, double media, double desviacionEstandar){
    random_device rd;  // Generador de números aleatorios no determinista
    mt19937 gen(rd()); // Generador Mersenne Twister
    normal_distribution<double> d(media, desviacionEstandar);

    int* arr = new int[largo];

    for (int i = 0; i < largo; ++i) {
        arr[i] = d(gen);
    }

    // Ordenar el arreglo de menor a mayor
    sort(arr, arr + largo);
    return arr;
}
//                               x elemento a buscar, n es el largo 
int busquedaBinaria(int* arreglo, int x, int n) {
    int izq = 0, der = n - 1;
    while (izq <= der) {
        int medio = (izq + der) / 2;
        if (arreglo[medio] == x)
            return medio;
        if (arreglo[medio] < x)
            izq = medio + 1;
        else
            der = medio - 1;
    }
    return -1;
}

void imprimeArreglo(int* arreglo, int largo){
    for(int i = 0; i < largo; i++){
        cout << arreglo[i] << " ";
    }
    cout << endl;
}
