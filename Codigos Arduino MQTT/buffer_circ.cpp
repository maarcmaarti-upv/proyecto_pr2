#include "buffer_circ.h"

uint32_t push(Buffer_Circ *lista, int dato)
{
    if (lleno(lista)) {
        return -1;
    }

    lista->colaCirc[lista->bufIN] = dato;
    lista->bufIN = (lista->bufIN + 1) % BUFSIZE;
    lista->contador++;

    return 0;
}

uint32_t pop(Buffer_Circ *lista, int *dato)
{
    if (vacio(lista)) {
        return -1;
    }

    *dato = lista->colaCirc[lista->bufOUT];
    lista->colaCirc[lista->bufOUT] = 0;
    lista->bufOUT = (lista->bufOUT + 1) % BUFSIZE;
    lista->contador--;

    return 0;
}

bool lleno(Buffer_Circ *lista)
{
    return (lista->contador == BUFSIZE);
}

bool vacio(Buffer_Circ *lista)
{
    return (lista->contador == 0);
}

void listar(Buffer_Circ *lista)
{
    for (uint32_t i = 0; i < lista->contador; i++) {
        Serial.printf("Elemento %u: %d\n", i, lista->colaCirc[i]);
    }
}

uint32_t getTam(Buffer_Circ *lista)
{
    return lista->contador;
}
