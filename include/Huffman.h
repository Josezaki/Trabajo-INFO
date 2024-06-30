#ifndef Huffman_H
#define Huffman_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <queue>
#include <unordered_map>

// SimboloFrec es una estructura que contiene un simbolo y su frecuencia
struct simboloFrec{
    int valor = -1;
    float frecuencia;
    simboloFrec* izq;
    simboloFrec* der;
};

// SimboloCod es una estructura que contiene un simbolo y su codificación
struct simboloCod{
    int simbolo;
    std::vector<bool> codification;
};

struct simboloCodChar{
    int simbolo;
    unsigned char representacion;
};

struct CompareSimboloFrec{
    bool operator()(simboloFrec* const& n1, simboloFrec* const& n2){
        return n1->frecuencia >= n2->frecuencia;
    }
};

// Definicion de las funciones
std::vector<simboloFrec> frecuenciaGC(int* GapCodingArreglo, int largo);
void imprimeFrecuencia(std::vector<simboloFrec> frecuencia);

std::vector<simboloCod> crearCodificacionHuffman(std::vector<simboloFrec> frecuenciaGC);
simboloFrec* createHuffman(std::priority_queue <simboloFrec*, std::vector<simboloFrec*>, CompareSimboloFrec> &simbols);

void codificationHuffman(simboloFrec *huffmanTree, std::vector<simboloCod> &codifications, std::vector<bool> &aux);

std::vector<simboloCodChar> traducir(std::vector<simboloCod> simboloCod);
std::unordered_map<unsigned char, int> CreateHash(std::vector<simboloCodChar> simboloCodChar);

unsigned char* transformarGCaGCHuffman(int* GC, std::vector<simboloCodChar> &simboloCodChar, int n);
int busquedaBinariaSample_GCHuffman(unsigned char* GCHuffman, int* Sample, int x, int n, int m, int b, std::unordered_map<unsigned char, int> &decodificar);
int busquedaLinealAcotadaGCHuffman(unsigned char* GCHuffman, int x, int n, int indice, int elemento_acotado, std::unordered_map<unsigned char, int> &decodificar);

#endif