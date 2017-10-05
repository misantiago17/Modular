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
*     2       rm   30/09/2017 funções: GRA_CriarGrafo, GRA_IrVertice, GRA_ObterValor, GRA_InserirVertice, CriarElemento, LimparCabeca
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

typedef struct tagVertice {

	void * pValor;
	/* Ponteiro para o valor contido no elemento */

	LIS_tpLista* pLisAresta;
	/* Ponteiro para a lista de arestas */

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
*  $TC Tipo de dados: GRA Descritor da cabeça do grafo
*
*
***********************************************************************/

typedef struct GRA_tagGrafo {

	LIS_tpLista* pVerticesGrafo;
	/* Ponteiro para a lista de vertices do grafo */

	GRA_tpVertice* pElemCorr;
	/* Ponteiro para o elemento corrente do grafo */

	void(*ExcluirValor) (void * pValor);
	/* Ponteiro para a função de destruição do valor contido em um elemento */

} GRA_tpGrafo;

/***** Protótipos das funções encapuladas no módulo *****/

tpElemGrafo *CriarElemento(GRA_tpGrafo *pGrafo, void * pValor);
void LimparCabeca(GRA_tpGrafo *pGrafo);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: Função: GRA  &Criar grafo
*  ****/

GRA_tpCondRet GRA_CriarGrafo(void(*ExcluirValor) (void * pDado), GRA_tpGrafo* GrafoRet) {

	GRA_tpGrafo *pGrafo;
	
	pGrafo = (GRA_tpGrafo *)malloc(sizeof(GRA_tpGrafo));
	if (pGrafo == NULL)
	{
		GrafoRet = NULL;
		return GRA_CondRetFaltouMemoria;
	}

	if (LIS_CriarLista(NULL, pGrafo->pVerticesGrafo) == LIS_CondRetFaltouMemoria) {
		GrafoRet = NULL;
		return GRA_CondRetFaltouMemoria;
	}

	LimparCabeca(pGrafo);

	pGrafo->ExcluirValor = ExcluirValor;

	GrafoRet = pGrafo;
	return GRA_CondRetOK;
} /* Fim função: GRA  &Criar grafo */

  /***************************************************************************
  *
  *  Função: Função: GRA  &Ir para o Vértice
  *  ****/

GRA_tpCondRet GRA_IrVertice(GRA_tpGrafo *pGrafo, int numVert) {

	IrInicioLista(pGrafo->listaVertices);
	/*??????? Alguma outra condição de retorno pra erro aki??? */
	if (LIS_AvancarElementoCorrente(pGrafo->listaVertices, numVert) != LIS_CondRetOK)
		return GRA_CondRetNaoAchouVertice;

	pGrafo->pElemCorr = pGrafo->listaVertices;
	return GRA_CondRetOK;
}
/***************************************************************************
*
*  Função: GRA  &Obter referência para o valor contido no vértice
*  ****/
//Mi ----------------------------------------------------------------------------------
GRA_tpCondRet GRA_ObterValor(GRA_tpGrafo *pGrafo, void** pValorRet)
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

} /* Fim função: GRA  &Obter referência para o valor contido no vértice */

  /***************************************************************************
  *
  *  Função: GRA  &Inserir vértice
  *  ****/
//Mi
GRA_tpCondRet GRA_InserirVertice(GRA_tpGrafo *pGrafo, void * pValor, tpElemGrafo * elemLig)
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
} /* Fim função: GRA  &Inserir vértice */


/***************************************************************************
  *
  *  Função: GRA  &Excluir Vertice
  *  ****/
  
GRA_tpCondRet GRA_ExcluirVertice(GRA_tpGrafo pGrafo);
{
} /* Fim função: GRA  &Excluir vértice */

  /***********************************************************************
  *
  *  $FC Função: GRA  -Criar o elemento
  *
  ***********************************************************************/

  // -------------------------------------------------------------------------------------
  
tpElemGrafo *CriarElemento(GRA_tpGrafo *pGrafo, void * pValor)
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

} /* Fim função: GRA  -Criar o elemento */

  /***********************************************************************
  *
  *  $FC Função: GRA  -Limpar a cabeça do grafo
  *
  ***********************************************************************/

void LimparCabeca(GRA_tpGrafo *pGrafo)
{

	pGrafo->pElemCorr = NULL;
	pGrafo->numVertices = 0;
} /* Fim função: GRA  -Limpar a cabeça do grafo */