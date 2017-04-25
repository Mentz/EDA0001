#ifndef TDA_PILHA_PRIV_H
#define TDA_PILHA_PRIV_H

/* no turboC para DOS use:
 #include "client~1.h"*/
#include "tda_pilha.h"

struct descPE {
	void **vet;			/* ponteiro para o vetor de ponteiros */
	int topo;    		/* topo da pilha */
	int tamVet;  		/*tamanho do vetor/tamanho m�ximo da pilha */
	int tamInfo; 		/* tamanho do pacote de informa��o a ser guardada  */
};

#endif
