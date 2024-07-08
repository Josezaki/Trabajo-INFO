#ifndef EXPERIMENTACION_H
#define EXPERIMENTACION_H

#include <chrono>           // Utilizado para medir el tiempo que se demora en realizar las búsquedas
#include <sys/resource.h>   // Utilizado para medir la memoria RAM utilizada en ejecución
#include <cstdio>

#define PRINT 0
#define REP 10000
#define EXP 1

// Definición de la clase1

class Experimentacion {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> ini_tiempo;
    std::chrono::time_point<std::chrono::high_resolution_clock> fin_tiempo;
    float ini_RAM;
    float fin_RAM;
    struct rusage resource_usage;

public:
    Experimentacion();

    // Métodos
    void tomaMarcaIniRam(); // Toma una marca de la RAM que está utilizando el programa en un momento x
    void imprimeRamUsada(); // Toma una marca de la RAM que se está utilizando en un momento x. Resta con la inicial y imprime en MegaBytes
    void tomaIniTiempo();   // Toma una marca del tiempo en un momento x
    void imprimeTiempo();   // Toma una marca del tiempo en un momento x. Compara con el inicial e imprime en nanosegundos
};

#endif // EXPERIMENTACION_H
