#ifndef BUFFER_CIRC_H
#define BUFFER_CIRC_H

#include <Arduino.h>

#define BUFSIZE 10

typedef struct {
    int colaCirc[BUFSIZE];
    uint32_t bufIN;
    uint32_t bufOUT;
    uint32_t contador;
} Buffer_Circ;

uint32_t push(Buffer_Circ *lista, int dato);
uint32_t pop(Buffer_Circ *lista, int *dato);
bool lleno(Buffer_Circ *lista);
bool vacio(Buffer_Circ *lista);
void listar(Buffer_Circ *lista);
uint32_t getTam(Buffer_Circ *lista);

#endif
