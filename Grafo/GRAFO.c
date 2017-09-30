/***************************************************************************
*  $MCI Módulo de implementação: GRA  Grafo generico
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: ????????????????
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  DI/PUC-Rio
*  Autores: Gabriel Busquim (gb), Michelle Santiago (ms), Renan Moreira (rm)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     2       rm   30/09/2017 funções
*     1       rm   27/09/2017 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "GRAFO.h"
#include   "LISTA.h"

/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento do grafo
*
*
***********************************************************************/

typedef struct tagElemGrafo {

	void * pValor;
	/* Ponteiro para o valor contido no elemento */

	struct tpElemGrafo **pLisElem;
	/* Ponteiro para lista de elementos para os quais o vertice aponta */

} tpElemGrafo;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça do grafo
*
*
***********************************************************************/

typedef struct GRA_tagGrafo {

	tpElemGrafo * pOrigemGrafo;
	/* Ponteiro para a origem do grafo */

	tpElemGrafo * pElemCorr;
	/* Ponteiro para o elemento corrente do grafo */

	int numElem;
	/* Número de elementos do grafo */

	void(*ExcluirValor) (void * pValor);
	/* Ponteiro para a função de destruição do valor contido em um elemento */

} GRA_tpGrafo;

/***** Protótipos das funções encapuladas no módulo *****/

void LimparCabeca(GRA_tppGrafo pGrafo);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: Função: GRA  &Criar grafo
*  ****/

GRA_tpCondRet GRA_CriarGrafo(
	void(*ExcluirValor) (void * pDado), GRA_tppGrafo* GrafoRet) {

	GRA_tpGrafo *pGrafo;

	pGrafo = (GRA_tpGrafo *)malloc(sizeof(GRA_tpGrafo));
	if (pGrafo == NULL)
	{
		*GrafoRet = NULL;
		return GRA_CondRetFaltouMemoria;
	} /* if */
	
	LimparCabeca(pGrafo);
	*GrafoRet = pGrafo;

	pGrafo->ExcluirValor = ExcluirValor;


	return GRA_CondRetOK;
} /* Fim função: GRA  &Criar grafo */

/***************************************************************************
*
*  Função: GRA  &Obter referência para o valor contido no vértice
*  ****/

LIS_tpCondRet LIS_ObterValor(LIS_tppLista pLista, void** pValorRet);
{

#ifdef _DEBUG
	assert(pLista != NULL);
#endif

	if (pLista->pElemCorr == NULL)
	{
		*pValorRet = NULL;
		return LIS_CondRetListaVazia;
	} /* if */

	*pValorRet = pLista->pElemCorr->pValor;
	return LIS_CondRetOK;

} /* Fim função: GRA  &Obter referência para o valor contido no vértice */


/***********************************************************************
*
*  $FC Função: GRA  -Limpar a cabeça do grafo
*
***********************************************************************/

void LimparCabeca(GRA_tppGrafo pGrafo)
{

	pGrafo->pOrigemGrafo = NULL;
	pGrafo->pElemCorr = NULL;
	pGrafo->numElem = 0;

} /* Fim função: GRA  -Limpar a cabeça do grafo */