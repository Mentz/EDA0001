#include <stdio.h>
#include <stdlib.h>
#include "fem2.h"

int main(void)
{
    FEM *p = NULL;
    cria(&p, 10, sizeof(int));
    int *n = malloc(sizeof(int)), *c = malloc(sizeof(int)), *f = malloc(sizeof(int));
    *n = 1;
    enfileira(p, n);
    buscaNaCauda(p, c); buscaNaFrente(p, f);
    printf("E\tCauda: %d\tFrente: %d\n", *c, *f);
    *n = 2;
    enfileira(p, n);
    buscaNaCauda(p, c); buscaNaFrente(p, f);
    printf("E\tCauda: %d\tFrente: %d\n", *c, *f);
    *n = 3;
    desenfileira(p);
    buscaNaCauda(p, c); buscaNaFrente(p, f);
    printf("D\tCauda: %d\tFrente: %d\n", *c, *f);
    enfileira(p, n);
    buscaNaCauda(p, c); buscaNaFrente(p, f);
    printf("E\tCauda: %d\tFrente: %d\n", *c, *f);
    *n = 4;
    enfileira(p, n);
    buscaNaCauda(p, c); buscaNaFrente(p, f);
    printf("E\tCauda: %d\tFrente: %d\n", *c, *f);
    *n = 5;
    enfileira(p, n);
    buscaNaCauda(p, c); buscaNaFrente(p, f);
    printf("E\tCauda: %d\tFrente: %d\n", *c, *f);
    desenfileira(p);
    buscaNaCauda(p, c); buscaNaFrente(p, f);
    printf("D\tCauda: %d\tFrente: %d\n", *c, *f);
    desenfileira(p);
    buscaNaCauda(p, c); buscaNaFrente(p, f);
    printf("D\tCauda: %d\tFrente: %d\n", *c, *f);
    desenfileira(p);
    buscaNaCauda(p, c); buscaNaFrente(p, f);
    printf("D\tCauda: %d\tFrente: %d\n", *c, *f);
    desenfileira(p);
    buscaNaCauda(p, c); buscaNaFrente(p, f);
    printf("D\tCauda: %d\tFrente: %d\n", *c, *f);
    printf("Erro? %d\n", desenfileira(p));

    destroi(&p);
    return 0;
}
