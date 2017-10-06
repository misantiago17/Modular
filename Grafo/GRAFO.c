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
*     1      rm/ms/gb   05/10/2017 início desenvolvimento
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

GRA_tpVertice *CriarVertice(GRA_tpGrafo *pGrafo, void * pValor);
GRA_tpNoVertices *CriarSubVertice(GRA_tpGrafo *pGrafo, int tam, LIS_tppLista *pLista);

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

	pGrafo->pElemCorr = NULL;

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
GRA_tpCondRet GRA_InserirVertice(GRA_tpGrafo *pGrafo, void * pValor, GRA_tpVertices * vertLig)
{
	GRA_tpNoVertices * pVerts;
	GRA_tpVertice * pVert;
	int *pTam;
	
	if (LIS_ObterTamanho(pGrafo->pVerticesGrafo,pTam) != LIS_CondRetOK)
		return GRA_CondRetGrafoVazio;

#ifdef _DEBUG
	assert(pGrafo != NULL);
#endif

	/* Criar elemento a inserir antes */
	pVerts = CriarSubVertice(pGrafo,*pTam);
	if (pVerts == NULL)
	{
		return GRA_CondRetFaltouMemoria;
	} /* if */
	
	pVert = CriarVertice(pGrafo, pValor);
	if (pVert == NULL)
	{
		return GRA_CondRetFaltouMemoria;
	} /* if */
	
	IrFinalLista(pGrafo->pVerticesGrafo);	
	if (LIS_InserirElementoApos(pGrafo->pVerticesGrafo, pVerts) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	pGrafo->pVerticesGrafo[tam] = pVerts;

	if (LIS_InserirElementoApos(pVerts->pLisVertice, pVert) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	pVerts->pLisVertice[0] = pVert;
	
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
  *  $FC Função: GRA  -Criar o vertice
  *
  ***********************************************************************/

  // -------------------------------------------------------------------------------------
  
GRA_tpVertice *CriarVertice(GRA_tpGrafo *pGrafo, void * pValor)
{
	GRA_tpVertice * pVert;

	pVert = (GRA_tpVertice *)malloc(sizeof(GRA_tpVertice));
	if (pVert == NULL)
	{
		return NULL;
	} /* if */

	pVert->pValor = pValor;
	if (LIS_CriarLista(NULL, pVert->pLisAresta) != LIS_CondRetOK)
		return NULL;

	return pVert;

} /* Fim função: GRA  -Criar o elemento */

  /***********************************************************************
  *
  *  $FC Função: GRA  -Criar o sub vertice
  *
  ***********************************************************************/
GRA_tpNoVertices *CriarSubVertice(GRA_tpGrafo *pGrafo, int tam){
	
	GRA_tpVertices * pVerts;
	
	pVerts = (GRA_tpVertices *)malloc(sizeof(GRA_tpVertices));
	if (pVerts == NULL)
	{
		return NULL;
	} /* if */

	pVerts->ident = tam;
	if (LIS_CriarLista(NULL, pVerts->pLisVertice) != LIS_CondRetOK)
		return NULL;

	return pVerts;
}
