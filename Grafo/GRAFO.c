/***************************************************************************
*  $MCI M�dulo de implementa��o: GRA  Grafo generico
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: ????????????????
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  DI/PUC-Rio
*  Autores: Gabriel Busquim (gb), Michelle Santiago (ms), Renan Moreira (rm)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     2       rm   30/09/2017 fun��es
*     1       rm   27/09/2017 in�cio desenvolvimento
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
*  $TC Tipo de dados: GRA Descritor da cabe�a do grafo
*
*
***********************************************************************/

typedef struct GRA_tagGrafo {

	tpElemGrafo * pOrigemGrafo;
	/* Ponteiro para a origem do grafo */

	tpElemGrafo * pElemCorr;
	/* Ponteiro para o elemento corrente do grafo */

	int numElem;
	/* N�mero de elementos do grafo */

	void(*ExcluirValor) (void * pValor);
	/* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

} GRA_tpGrafo;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

void LimparCabeca(GRA_tppGrafo pGrafo);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: Fun��o: GRA  &Criar grafo
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
} /* Fim fun��o: GRA  &Criar grafo */

/***************************************************************************
*
*  Fun��o: GRA  &Obter refer�ncia para o valor contido no v�rtice
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

} /* Fim fun��o: GRA  &Obter refer�ncia para o valor contido no v�rtice */


/***********************************************************************
*
*  $FC Fun��o: GRA  -Limpar a cabe�a do grafo
*
***********************************************************************/

void LimparCabeca(GRA_tppGrafo pGrafo)
{

	pGrafo->pOrigemGrafo = NULL;
	pGrafo->pElemCorr = NULL;
	pGrafo->numElem = 0;

} /* Fim fun��o: GRA  -Limpar a cabe�a do grafo */