#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "MPE_priv.h"

int cria(MP **pp, int N, int L, int tamInfo)
{
    int i, M, ret = SUCESSO;
    NoMP *aux;
	MP *desc = NULL; /* descritor alocado internamente */

    if (N > 0 && L > 0 && tamInfo > 0) {
        M = N*L;
        if( (desc = (MP*) malloc(sizeof(MP))) == NULL ) { /* cria��o do descritor geral da MpE; */
            ret = FRACASSO;
		}
        else {
            if( ( desc->vet = (NoMP*) malloc((M+N)* sizeof(NoMP)) )==NULL) {
            /* Aloca��o de mem�ria para a multipilha (vetor de unions) constituida de N*L n�s de dados (N*L = M) e os N n�s descritores das respectivas pilhas; */
                free(desc);
                desc = NULL;
                ret = FRACASSO;
            }
            else {
                desc->N = N; /* Iniciando os atributos gerais da multi-pilha; */
                desc->L = L;
                desc->tamInfo = tamInfo;
                aux = desc->vet; /* Ponteiro auxiliar aux apontando para a �rea de descritores; */
                for(i = 0; i < N ; i++) { /* Formatando a MpE: iniciando os descritores das pilhas; */
                    (aux + i)->descritor.topo = -1;
                    /* Os topos s�o iniciados com valores que n�o indexam as parti��es das respectivas pilhas,
                    indicando que a considerada pilha est� vazia. Perceba que tamb�m � poss�vel utilizar a
                    sintaxe (*pp)->vet[i].descritor ou ((*pp)->vet + i).descritor para acesso ao i-�simo
                    descritor. */
                    (aux + i)->descritor.inicioParticao = N + i*L;
                }
                aux = aux + N; /* Ponteiro auxiliar aux apontando para o in�cio da �rea de dados; */
                for(i=0; i < M ;i++) { /* Criando as �reas de dados */
                    if( ((aux+i)->dados = (void*) malloc(tamInfo)) == NULL ) {
                        for(--i; i >=0;--i) {
                            free(desc->vet[i].dados); /* Houve falha na aloca��o de pelo menos uma �rea de dados, a MpE deve ser destru�da. */
						}
                        free(desc->vet);
                        free(desc);
                        desc = NULL;
                        i = M;
                        ret = FRACASSO;
                    }
				}
            }
		}
    }
    else {
        ret = FRACASSO;
	}

	*pp = desc; /* ponteiro pra ponteiro busca o descritor e retorna ao cliente */

    return ret;
}

int insereNaPilha(MP *p, int nPilha, void* novo)
{
    if(p->vet == NULL) { /*testa existencia da pilha*/
        printf(">>Erro ao inserir, pilha inexistente\n");
        return FRACASSO;
    }
    
    if(p->N < nPilha) {
        printf(">>Erro ao inserir, pilha inexistente\n");
        return FRACASSO;
    }

    if(p->vet[nPilha-1].descritor.topo == (p->L)-1) {
        printf(">>Erro ao inserir, a pilha %d est� cheia\n", nPilha);
        return FRACASSO;
    }

    /*se a pilha existe e n�o est� cheia, inser��o pode ocorrer normalmente*/
    int inicioParticao = p->vet[nPilha-1].descritor.inicioParticao;
    p->vet[nPilha-1].descritor.topo += 1;
    int topo = p->vet[nPilha-1].descritor.topo;

    memcpy(p->vet[inicioParticao + topo].dados, novo, p->tamInfo);

    return SUCESSO;
}

int removeDaPilha(MP *p, int nPilha, void* removido)
{
    int topo = p->vet[nPilha-1].descritor.topo;
    int inicioParticao = p->vet[nPilha-1].descritor.inicioParticao;

    if(topo == -1) {
        printf("\nA pilha %d esta vazia\n", nPilha);
        return FRACASSO;
    }

    memcpy(removido, p->vet[inicioParticao + topo].dados, p->tamInfo);
    p->vet[nPilha-1].descritor.topo--;

    return SUCESSO;
}

int consultaTopo(MP *p, int nPilha, void* consultado)
{
    int topo = p->vet[nPilha-1].descritor.topo;
    int inicioParticao = p->vet[nPilha-1].descritor.inicioParticao;

    if(topo == -1) {
        printf("\nA pilha %d esta vazia\n", nPilha);
        return FRACASSO;
    }

    memcpy(consultado, p->vet[inicioParticao + topo].dados, p->tamInfo);

    return SUCESSO;
}

void destroi(MP **pp) 
{ 
    int i,j;
	int inicioParticao;

    for(i = (*pp)->N -1; i >= 0; i--) {
        inicioParticao = (*pp)->vet[i].descritor.inicioParticao;
        for(j=(*pp)->L-1;j>=0;j--) {
            free( (*pp)->vet[inicioParticao + j].dados);      
        }
    }

    free((*pp)->vet);
    free(*pp);
    *pp = NULL;
}
