#include "Experimentacion.h"
#include <iostream> // Para std::cout y std::endl

using namespace std;

// Constructor
Experimentacion::Experimentacion() {
    this->ini_RAM = 0.0;
    this->fin_RAM = 0.0;
}

// Toma una marca de la RAM que está utilizando el programa en un momento x
void Experimentacion::tomaMarcaIniRam() {
    getrusage(RUSAGE_SELF, &(this->resource_usage));
    this->ini_RAM = resource_usage.ru_maxrss;
}

// Toma una marca de la RAM que se está utilizando en un momento x. Resta con la inicial y imprime en MegaBytes
void Experimentacion::imprimeRamUsada() {
    getrusage(RUSAGE_SELF, &(this->resource_usage));
    this->fin_RAM = resource_usage.ru_maxrss;
    printf("Memoria utilizada por la ED: %0.3fMB\n", (fin_RAM - ini_RAM) / 1024.0);
}

// Toma una marca del tiempo en un momento x
void Experimentacion::tomaIniTiempo() {
    this->ini_tiempo = chrono::high_resolution_clock::now();
}

// Toma una marca del tiempo en un momento x. Compara con el inicial e imprime en nanosegundos
void Experimentacion::imprimeTiempo() {
    this->fin_tiempo = chrono::high_resolution_clock::now();
    auto tiempo_transcurrido = chrono::duration_cast<chrono::nanoseconds>(fin_tiempo - ini_tiempo);
    printf("Buscar en la estructura %0.d veces en promedio llevó un tiempo medio de: %0.f nanosegundos\n\n", REP, (double)tiempo_transcurrido.count() / REP);
}
