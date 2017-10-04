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
*     2       rm   30/09/2017 fun��es: GRA_CriarGrafo, GRA_IrVertice, GRA_ObterValor, GRA_InserirVertice, CriarElemento, LimparCabeca
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

typedef struct tagVertice {

	void * pValor;
	/* Ponteiro para o valor contido no elemento */

	LIS_tpLista* pLisAresta;
	/* Ponteiro para a lista de arestas */

	int numArestas;
	/* Numero de arestas ligadas ao vertice */

} GRA_tpVertice;

/***********************************************************************
*
*  $TC Tipo de dados: GRA No da Lista Vertices
*
*
***********************************************************************/

typedef struct tagNoVertices {

	int ident;
	/* Identificador do vertice */

	LIS_tpLista *pLisVertice;
	/* Ponteiro para lista de elementos para os quais o vertice aponta */

} GRA_tpNoVertices;



/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabe�a do grafo
*
*
***********************************************************************/

typedef struct GRA_tagGrafo {

	tpVertices* pVerticesGrafo;
	/* Ponteiro para a lista de vertices do grafo */

	tpVertice* pElemCorr;
	/* Ponteiro para o elemento corrente do grafo */

	int numVertices;
	/* N�mero de elementos do grafo */

	void(*ExcluirValor) (void * pValor);
	/* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

} GRA_tpGrafo;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

tpElemGrafo *CriarElemento(GRA_tppGrafo *pGrafo, void * pValor);
void LimparCabeca(GRA_tppGrafo *pGrafo);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: Fun��o: GRA  &Criar grafo
*  ****/

GRA_tpCondRet GRA_CriarGrafo(void(*ExcluirValor) (void * pDado), GRA_tppGrafo* GrafoRet) {

	GRA_tppGrafo *pGrafo;

	pGrafo = (GRA_tppGrafo *)malloc(sizeof(GRA_tppGrafo));
	if (pGrafo == NULL)
	{
		GrafoRet = NULL;
		return GRA_CondRetFaltouMemoria;
	} /* if */
	LIS_CriarLista(NULL, pGrafo->listaVertices);

	LimparCabeca(pGrafo);
	pGrafo->ExcluirValor = ExcluirValor;

	GrafoRet = pGrafo;
	return GRA_CondRetOK;
} /* Fim fun��o: GRA  &Criar grafo */

  /***************************************************************************
  *
  *  Fun��o: Fun��o: GRA  &Ir para o V�rtice
  *  ****/

GRA_tpCondRet GRA_IrVertice(GRA_tppGrafo *pGrafo, int numVert) {

	IrInicioLista(pGrafo->listaVertices);
	/*??????? Alguma outra condi��o de retorno pra erro aki??? */
	if (LIS_AvancarElementoCorrente(pGrafo->listaVertices, numVert) != LIS_CondRetOK)
		return GRA_CondRetNaoAchouVertice;

	pGrafo->pElemCorr = pGrafo->listaVertices;
	return GRA_CondRetOK;
}
/***************************************************************************
*
*  Fun��o: GRA  &Obter refer�ncia para o valor contido no v�rtice
*  ****/

GRA_tpCondRet GRA_ObterValor(GRA_tppGrafo *pGrafo, void** pValorRet)
{

#ifdef _DEBUG
	assert(pGrafo != NULL);
#endif

	if (pGrafo->pElemCorr == NULL)
	{
		*pValorRet = NULL;
		return GRA_CondRetGrafoVazio;
	} /* if */

	*pValorRet = pGrafo->pElemCorr->pValor;
	return GRA_CondRetOK;

} /* Fim fun��o: GRA  &Obter refer�ncia para o valor contido no v�rtice */

  /***************************************************************************
  *
  *  Fun��o: GRA  &Inserir v�rtice
  *  ****/

GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo *pGrafo, void * pValor, tpElemGrafo * elemLig)
{

	tpElemGrafo * pElem;

#ifdef _DEBUG
	assert(pGrafo != NULL);
#endif

	/* Criar elemento a inerir antes */

	pElem = CriarElemento(pGrafo, pValor);
	if (pElem == NULL)
	{
		return GRA_CondRetFaltouMemoria;
	} /* if */
	if (LIS_InserirElementoApos(elemLig->pLisElem, pElem) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	elemLig->pLisElem[elemLig->numElem] = pElem;
	elemLig->numElem++;
	if (LIS_InserirElementoApos(pElem->pLisElem, elemLig) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	pElem->pLisElem[pElem->numElem] = elemLig;
	pElem->numElem++;
} /* Fim fun��o: GRA  &Inserir v�rtice */

  /***********************************************************************
  *
  *  $FC Fun��o: GRA  -Criar o elemento
  *
  ***********************************************************************/

tpElemGrafo *CriarElemento(GRA_tppGrafo *pGrafo, void * pValor)
{

	tpElemGrafo * pElem;

	pElem = (tpElemGrafo *)malloc(sizeof(tpElemGrafo));
	if (pElem == NULL)
	{
		return NULL;
	} /* if */

	pElem->pValor = pValor;
	if (LIS_CriarLista(NULL, pElem->pLisElem) != LIS_CondRetOK)
		return NULL;
	pElem->numElem = 0;

	IrFinalLista(pGrafo->listaVertices);
	LIS_InserirElementoApos(pGrafo->listaVertices, pElem);
	pElem->numVert = pGrafo->numElem;

	pGrafo->numElem++;
	return pElem;

} /* Fim fun��o: GRA  -Criar o elemento */

  /***********************************************************************
  *
  *  $FC Fun��o: GRA  -Limpar a cabe�a do grafo
  *
  ***********************************************************************/

void LimparCabeca(GRA_tppGrafo *pGrafo)
{

	pGrafo->pOrigemGrafo = NULL;
	pGrafo->pElemCorr = NULL;
	pGrafo->numElem = 0;
} /* Fim fun��o: GRA  -Limpar a cabe�a do grafo */