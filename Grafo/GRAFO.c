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
*     1      rm/ms/gb   05/10/2017 in�cio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "gra.h"
#include   "lis.h"

/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento do grafo
*
*
***********************************************************************/

typedef struct tagVertice {

	void * pValor;
	/* Ponteiro para o valor contido no elemento */

	LIS_tppLista pLisAresta;
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

	LIS_tppLista pLisVertice;
	/* Ponteiro para lista de elementos para os quais o vertice aponta */

} GRA_tpNoVertices;



/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabe�a do grafo
*
*
***********************************************************************/

typedef struct GRA_tagGrafo {

	LIS_tppLista pVerticesGrafo;
	/* Ponteiro para a lista de vertices do grafo */

	GRA_tpVertice* pElemCorr;
	/* Ponteiro para o elemento corrente do grafo */

	void(*ExcluirValor) (void * pValor);
	/* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

} GRA_tpGrafo;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

GRA_tpVertice *CriarVertice(GRA_tpGrafo *pGrafo, void * pValor);
GRA_tpNoVertices *CriarSubVertice(GRA_tpGrafo *pGrafo, int tam);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: Fun��o: GRA  &Criar grafo
*  ****/

GRA_tpCondRet GRA_CriarGrafo(void   ( * ExcluirValor ) ( void * pDado ), GRA_tppGrafo* GrafoRet) {

	GRA_tpGrafo *pGrafo;
	
	pGrafo = (GRA_tpGrafo *)malloc(sizeof(GRA_tpGrafo));
	if (pGrafo == NULL)
	{
		*GrafoRet = NULL;
		return GRA_CondRetFaltouMemoria;
	}

	if (LIS_CriarLista(NULL, &(pGrafo->pVerticesGrafo)) == LIS_CondRetFaltouMemoria) {   //REVISAR ESSE NULL!!!!!!!!!!!
		*GrafoRet = NULL;
		return GRA_CondRetFaltouMemoria;
	}

	pGrafo->pElemCorr = NULL;

	pGrafo->ExcluirValor = ExcluirValor;

	*GrafoRet = pGrafo;
	return GRA_CondRetOK;
} /* Fim fun��o: GRA  &Criar grafo */

  /***************************************************************************
  *
  *  Fun��o: Fun��o: GRA  &Ir para o V�rtice
  *  ****/

/*GRA_tpCondRet GRA_IrVertice(GRA_tpGrafo *pGrafo, int numVert) {

	IrInicioLista(pGrafo->listaVertices);
	/*??????? Alguma outra condi��o de retorno pra erro aki??? 
	if (LIS_AvancarElementoCorrente(pGrafo->listaVertices, numVert) != LIS_CondRetOK)
		return GRA_CondRetNaoAchouVertice;

	pGrafo->pElemCorr = pGrafo->listaVertices;
	return GRA_CondRetOK;
}*/
/***************************************************************************
*
*  Fun��o: GRA  &Obter refer�ncia para o valor contido no v�rtice
*  ****/
//Mi ----------------------------------------------------------------------------------
GRA_tpCondRet GRA_ObterValor(GRA_tppGrafo pGrafo, void** pValorRet)
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
//Mi

GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo,
	void * pValor)
{
	GRA_tpNoVertices * pVerts;
	GRA_tpVertice * pVert;
	GRA_tpVertice*  pRet;
	int tam;
	LIS_tpCondRet CondRet;


	#ifdef _DEBUG
		assert(pGrafo != NULL);
	#endif

	CondRet=LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	assert(CondRet==LIS_CondRetOK);

	/* Criar elemento a inserir apos */
	pVerts = CriarSubVertice(pGrafo,tam);
	if (pVerts == NULL)
	{
		return GRA_CondRetFaltouMemoria;
	} /* if */
	
	pVert = CriarVertice(pGrafo, pValor);
	if (pVert == NULL)
	{
		return GRA_CondRetFaltouMemoria;
	} /* if */
	
	CondRet=IrFinalLista(pGrafo->pVerticesGrafo);
	assert(CondRet==LIS_CondRetOK);
	if (LIS_InserirElementoApos(pGrafo->pVerticesGrafo,(void*)pVerts) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	//pGrafo->pVerticesGrafo[tam] = pVerts;

	if (LIS_InserirElementoApos(pVerts->pLisVertice,(void*)pVert) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;

	CondRet=LIS_ObterValor(pVerts->pLisVertice,(void**)&pRet);
	pGrafo->pElemCorr=pRet;
	return GRA_CondRetOK;
	
} /* Fim fun��o: GRA  &Inserir v�rtice */


/***************************************************************************
  *
  *  Fun��o: GRA  &Excluir Vertice
  *  ****/
  
/*GRA_tpCondRet GRA_ExcluirVertice(GRA_tpGrafo pGrafo)
{
}  Fim fun��o: GRA  &Excluir v�rtice */

  /***********************************************************************
  *
  *  $FC Fun��o: GRA  -Criar o vertice
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
	if (LIS_CriarLista(NULL, &(pVert->pLisAresta)) != LIS_CondRetOK)  //REVER ESSE NULL
		return NULL;

	return pVert;

} /* Fim fun��o: GRA  -Criar o elemento */

  /***********************************************************************
  *
  *  $FC Fun��o: GRA  -Criar o sub vertice
  *
  ***********************************************************************/
GRA_tpNoVertices *CriarSubVertice(GRA_tpGrafo *pGrafo, int tam){
	
	GRA_tpNoVertices * pVerts;
	
	pVerts = (GRA_tpNoVertices *)malloc(sizeof(GRA_tpNoVertices));
	if (pVerts == NULL)
	{
		return NULL;
	} /* if */

	pVerts->ident = tam+1;
	if (LIS_CriarLista(NULL,&(pVerts->pLisVertice)) != LIS_CondRetOK) // REVER ESSE NULL
		return NULL;

	return pVerts;
}
