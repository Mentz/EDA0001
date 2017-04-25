#include <stdlib.h>
#include <string.h> 
#include "tdaPilhaPriv.h"


int cria(PE **pp, int capMax, int tamInfo) 
{
	int i=0, ret = SUCESSO;
	PE *desc = NULL; /* descritor � alocado dentro do TDA */

	desc = (PE*) malloc( sizeof(PE) );

	if( desc != NULL ) {
		desc->topo = -1;
		desc->tamVet = capMax;
		desc->tamInfo = tamInfo;
		desc->vet = (void**) malloc( capMax * sizeof(void*) );

		if( desc->vet != NULL ) {
			for(i=0; i < capMax; i++) {
				desc->vet[i] = (void*) malloc( tamInfo );

				if( desc->vet[i] == NULL ) {
					for(i=i-1; i >= 0; i--) {
						free(desc->vet[i]);
					}

					free(desc->vet);
					free(desc);
					desc = NULL;
					ret = FRACASSO;
					break;
				}
			}
		}
		else {
			free(desc);
			desc = NULL;
			ret = FRACASSO;
		}
	}
	else {
		ret = FRACASSO;
	}

	*pp = desc; /* ap�s aloca��o, descritor criado � recebido por ref�rencia e retornado ao cliente */

	return ret;
}

void destroi(PE **pp)
{ 
	int i;

	for(i = 0; i< (*pp)->tamVet; i++)  /*libera mem�ria que inicializa os ponteiros void*/
		free( (*pp)->vet[i]);   /* equivalente a: *(p->vet + i));*/
	free((*pp)->vet);
	free(*pp);
	*pp = NULL;
}

void purga(PE *p) 
{
	p->topo = -1;
}

int buscaNoTopo(PE *p, void *pReg) 
{
	int ret;

	if (p->topo == VAZIA) { /* acesso direto ao topo */
		ret = FRACASSO;
	}
	else {
		memcpy(pReg, (p->vet[p->topo]), p->tamInfo);
		ret = SUCESSO;
	}

	return ret;
}

/*------------ATEN��O: pelo conceito de transa��o at�mica
  desempilha  #apenas# decrementaria o topo ---------------------*/

int desempilha(PE *p)
{ 
	int ret;

	if (p->topo == VAZIA) {
		ret = FRACASSO;
	}
	else {
		p->topo--;
		ret = SUCESSO;
	}

	return ret;
}

int empilha(PE *p, void * novo)
{ 
	int ret;

	if (p->topo < p->tamVet-1) { 
		p->topo++;

		/*c�pia um bloco de tamanho definido deste o endere�o novo at� o endere�o 
		  definido por *(p->vet+p->topo) */
		memcpy(*(p->vet+p->topo), novo, p->tamInfo);

		ret = SUCESSO;
	}

	else { /* caso pilha cheia*/
		ret = FRACASSO;
	}

	return ret;
}

int testaVazia(PE *p) 
{
	int ret;

	if (p->topo == VAZIA) /* acesso direto ao topo */
		ret = SIM;
	else
		ret = NAO;

	return ret;
}

int testaCheia(PE *p) 
{
	int ret;

	if (p->topo >= p->tamVet-1) /* acesso direto ao topo */
		ret = SIM;
	else
		ret = NAO;

	return ret;
}
