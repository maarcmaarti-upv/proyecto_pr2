#include "buffer_circ.h"

uint32_t push(Buffer_Circ* lista, int dato)  // Inserta un dato en el buffer circular
{
    if (lleno(lista)) {                      // Si el buffer está lleno no se inserta
        return -1;
    }

    lista->colaCirc[lista->bufIN] = dato;    // Escribe el dato en la posición bufIN
    lista->bufIN = (lista->bufIN + 1) % BUFSIZE; // Avanza el índice de entrada de forma circular
    lista->contador++;                       // Aumenta el número de elementos almacenados

    return 0;
}

uint32_t pop(Buffer_Circ* lista, int* dato)  // Extrae un dato del buffer circular
{
    if (vacio(lista)) {                      // Si el buffer está vacío, no se puede extraer
        return -1;
    }

    *dato = lista->colaCirc[lista->bufOUT];  // Obtiene el dato de la posición bufOUT
    lista->colaCirc[lista->bufOUT] = 0;      // Limpia la posición (opcional, solo por estética)
    lista->bufOUT = (lista->bufOUT + 1) % BUFSIZE; // Avanza el índice de salida circularmente
    lista->contador--;                       // Reduce el número de elementos almacenados

    return 0;                                // Extracción correcta
}

bool lleno(Buffer_Circ* lista)               // Indica si el buffer está lleno
{
    return (lista->contador == BUFSIZE);
}

bool vacio(Buffer_Circ* lista)               // Indica si el buffer está vacío
{
    return (lista->contador == 0);
}

void listar(Buffer_Circ* lista)              // Imprime por Serial todos los elementos del buffer
{
    for (uint32_t i = 0; i < lista->contador; i++) {
        Serial.printf("Elemento %u: %d\n", i, lista->colaCirc[i]); // Muestra índice y valor
    }
}

uint32_t getTam(Buffer_Circ* lista)          // Devuelve cuántos elementos que hay en el buffer
{
    return lista->contador;
}
