#ifndef FES_PRIV_H
#define FES_PRIV_H

/* no turboC para DOS use:
 #include "client~1.h"*/
#include "tda_FES.h"

struct descFES {
	void **vet;  /* ponteiro para o vetor de ponteiros */
	int cauda;   /* topo da pilha */
	int frente;
	int tamVet;  /* tamanho do vetor/tamanho m�ximo da pilha */
	int tamInfo; /* tamanho do pacote de informa��o a ser guardada  */
};

#endif
