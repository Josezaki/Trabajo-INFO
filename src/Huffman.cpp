#include "Huffman.h"
using namespace std;

// Encuentra todas las frecuencias de los simbolos de GapCoding
vector<simboloFrec> frecuenciaGC(int* GapCodingArreglo, int largo){
    vector<simboloFrec> frecuencia;
    int j; 
    for (int i = 1; i < largo; i++){ //iterar sobre el arreglo GapCoding
        j = 0; //iterar sobre el vector de frecuencias.
        while(j < frecuencia.size() && frecuencia[j].valor != GapCodingArreglo[i]){
            j++;
        }
        if (j == frecuencia.size()) //si j excede el limite del arreglo significa que el elemento no estaba
            frecuencia.push_back({GapCodingArreglo[i], 1, i});
        else //si no, se detuvo en el indice del elemento
            frecuencia[j].frecuencia += 1;
    }
    //ordenamos por frecuencia de mayor a menor
    sort(frecuencia.begin(), frecuencia.end(), [](simboloFrec a, simboloFrec b){
        return a.frecuencia > b.frecuencia;
    });

    return frecuencia;
}

//imprime todas las frecuencias
void imprimeFrecuencia(vector<simboloFrec> frecuencia){
    for (int i = 0; i < frecuencia.size(); i++){
        cout << "Valor: " << frecuencia[i].valor << " Frecuencia: " << frecuencia[i].frecuencia << endl;
    }
}

//Encuentra los outlier de un vector de frecuencias
unordered_map<int, int> encuentraOutliers(vector<simboloFrec> &frecuenciaGC){
    unordered_map<int, int> Outliers;
    int i = 0;
    while (i < frecuenciaGC.size()){
        if (frecuenciaGC[i].frecuencia == 1){
            Outliers[frecuenciaGC[i].indice] = frecuenciaGC[i].valor;
            frecuenciaGC.erase(frecuenciaGC.begin() + i); // se elimina el elemento con frecuencia 1 (outlier)
        }
        else
            ++i;
    }
    return Outliers;
}

// todos los procesos hasta entregar los códigos de huffman
vector<simboloCod> crearCodificacionHuffman(vector<simboloFrec> frecuenciaGC){
    // declaramos la cola de prioridad

    priority_queue <simboloFrec*, vector<simboloFrec*>, CompareSimboloFrec> huffmanQueue;

    // almacenamos todas las frecuencias a la cola de prioridad

    for (int i = 0; i < frecuenciaGC.size(); ++i){
        huffmanQueue.push(&(frecuenciaGC[i]));
    }

    // creamos el árbol de huffman y obtenemos la raíz
    simboloFrec* raiz = createHuffman(huffmanQueue);
    
    // encontramos las codificaciones dado un árbol de huffman
    vector<simboloCod> codificationNormal(frecuenciaGC.size());
    for (int i = 0; i < frecuenciaGC.size(); ++i){
        codificationNormal[i].simbolo = frecuenciaGC[i].valor;
    }

    // asignamos las codificaciones a cada simbolo desde el árbol de huffman
    vector<bool> aux;
    codificationHuffman(raiz, codificationNormal, aux);

    //retornamos los códigos con su codificacion
    return codificationNormal;
}


// crea el árbol de huffman siguiendo el algoritmo dado en clases
simboloFrec* createHuffman(priority_queue <simboloFrec*, vector<simboloFrec*>, CompareSimboloFrec> &simbols){
    simboloFrec *nuevo;
    while(simbols.size() >= 2){
        nuevo = new simboloFrec();
        nuevo->izq = simbols.top();
        simbols.pop();
        nuevo->der = simbols.top();
        simbols.pop();
        nuevo->frecuencia = nuevo->izq->frecuencia + nuevo->der->frecuencia;
        simbols.push(nuevo);
    }

    nuevo = simbols.top();
    simbols.pop();
    return nuevo;
}

// Se obtienen los códigos mediante el árbol de huffman
void codificationHuffman(simboloFrec *huffmanTree, vector<simboloCod> &codifications, vector<bool> &aux) {
    if (huffmanTree == nullptr)
        return;

    if (huffmanTree->valor != -1) { // Es una hoja del árbol
        int i = 0;
        while (i < codifications.size() && codifications[i].simbolo != huffmanTree->valor)
            i++;
        if (i < codifications.size()) // Se encontró el símbolo en el vector de codificaciones
            codifications[i].codification = aux; // Se asigna la codificación
        return;
    }

    aux.push_back(0); // se agrega un boleano 0 al arreglo auxiliar
    codificationHuffman(huffmanTree->izq, codifications, aux);
    aux.pop_back(); //una vez termina la llamada recursiva se elimina

    aux.push_back(1); // se agrega un boleano 1 al arreglo auxiliar
    codificationHuffman(huffmanTree->der, codifications, aux);
    aux.pop_back(); //una vez termina la llamada recursiva se elimina
}

// Se traducen los códigos de 0 y 1 a char
vector<simboloCodChar> traducir(vector<simboloCod> simboloCod){
    vector<simboloCodChar> simboloCodChar(simboloCod.size());
    string binario;
    char caracter;
    int decimal;
    for (int i = 0; i < simboloCod.size(); i++){ //iteramos sobre todos los simbolos
        binario = ""; // se inicializa el string binario
        for(int j = 0 ; j < simboloCod[i].codification.size(); j++){
            if (simboloCod[i].codification[j] == 1){           //iteramos sobre el vector de codificacion
                binario = "1" + binario;
            }
            else{
                binario = "0" + binario;
            }
        }
        simboloCodChar[i].simbolo = simboloCod[i].simbolo; //asignamos el simbolo
        decimal = stoi(binario,nullptr,2); // se convierte el binario a decimal
        caracter = static_cast<unsigned char>(decimal); // se convierte el decimal a char
        
        simboloCodChar[i].representacion = caracter;
    }
    return simboloCodChar;
}

// Crea un Hash con las decodificaciones 
unordered_map<unsigned char, int> CreateHash(vector<simboloCodChar> simboloCodChar){
    unordered_map<unsigned char, int> decodificar;
    for (int i = 0; i < simboloCodChar.size(); ++i){
        decodificar.insert({simboloCodChar[i].representacion, simboloCodChar[i].simbolo});
    }

    return decodificar; 
}

//Realiza una busqueda binaria sobre el sample, par asi poder acotar el intervalo de busqueda en GCHuffman.
int busquedaBinariaSample_GCHuffman(unsigned char* GCHuffman, int* Sample, int x, int n, int m, int b, unordered_map<unsigned char, int> &decodificar, unordered_map<int, int> outliers) {
    int izq = 0;
    int der = m - 1;
    int medio;
    if(x<Sample[0]) return -1;
    while (izq <= der) {
        medio = (izq + der) / 2;
        if (Sample[medio] == x)
            return medio*b;
        if (Sample[medio] < x)
            izq = medio + 1;
        else
            der = medio - 1;
    }
 
    return busquedaLinealAcotadaGCHuffman(GCHuffman, x, n, der*b, Sample[der], decodificar, outliers);
}

//Realiza una búsqueda lineal acotada similar a como se hace en el caso 2
int busquedaLinealAcotadaGCHuffman(unsigned char* GCHuffman, int x, int n, int indice, int elemento_acotado, unordered_map<unsigned char, int> &decodificar, unordered_map<int, int> outliers){ 
    int elemento_sumado = elemento_acotado; // La suma lineal se hará en la variable elemento_sumado
    for (int i = indice+1; i < n; ++i){ //se itera desde el indice hasta el final del arreglo
        if (GCHuffman[i] == 'X'){ // si el elemento es igual a la marca entonces
            if (outliers.find(i) == outliers.end()){ // si la clave no existe en el unordered map outlieres entonces se decodifica el simbolo y se suma
                elemento_sumado += decodificar[GCHuffman[i]];
            }
            else{ //si no, hay un elemento outlier y lo obtenemos desde el unordered map
                elemento_sumado += outliers[i];
            }
        }
        else{ // si el elemento no es 'X' entonces no hay marca y se suma normalmente.
            elemento_sumado += decodificar[GCHuffman[i]];
        }
        if (elemento_sumado > x)
            return -1;
        if (elemento_sumado == x)
            return i;
    }
    return -1;
}

 
//Transforma el arreglo GC a GC con codificacion de huffman
unsigned char* transformarGCaGCHuffman(int* GC, vector<simboloCodChar> &simboloCodChar, int n, unordered_map<int, int> outliers){
    unsigned char* GCHuffman = new unsigned char[n];
    int j; // j itera sobre simboloCodChar
    int k = 0; // k itera sobre las claves del unordered map "outliers"
    vector<int> claves;
    
    // Se guardan las claves de los outliers
    for (const auto& pares : outliers) {
        claves.push_back(pares.first);
    }
    
    // Se ordenan de menor a mayor
    sort(claves.begin(), claves.end());

    for (int i = 1; i < n; ++i){
        j = 0;
        if (claves.size() > 0 && claves[k] == i){ // si el indice del outlier concuerda con el indice del elemento lo marcamos con una 'X'
            GCHuffman[i] = 'X';
            k++;
        }
        else{ // si no, el elemento se encuentra codificado. Le ponemos su codificación
            while (j < simboloCodChar.size() && simboloCodChar[j].simbolo != GC[i])
                j++;
            GCHuffman[i] = simboloCodChar[j].representacion;     
        }
    }
    return GCHuffman;
}