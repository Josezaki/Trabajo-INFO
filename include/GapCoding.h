
#ifndef GapCoding_H
#define GapCoding_H

#include <iostream>
#include <cstdlib>


// Definicion de las funciones  
int* creaGC(int* arreglo, int largo);
int* creaSample(int* arreglo, int n, int m, int b);
int busquedaBinariaSample_GC(int* GC, int* Sample, int x, int n, int m, int b);
int busquedaLinealAcotadaGC(int* GC, int x, int n, int indice, int elemento_acotado);
#endif    