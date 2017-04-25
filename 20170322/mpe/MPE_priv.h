#ifndef MPE_PRIV_H
#define MPE_PRIV_H

#include "MPE.h"

/* N� descritor da uma pilha */
typedef struct {
    short int topo;
    short int inicioParticao;
} DescPilha;

/* N� da Multi-Pilha */
typedef union {
    DescPilha descritor;
    void* dados;
} NoMP;

/* Descritor da Multi-Pilha */
typedef struct mp {
    int N; /* N = N�mero de Pilhas*/
    int L; /* L = Tamanho m�ximo da parti��o de cada Pilha*/
    int tamInfo;
    NoMP *vet;
} MP;

#endif
