/***************************************************************************
*  $MCI Módulo de implementação: GRA  Grafo generico com cabeca
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
*  $TC Tipo de dados: GRA Descritor da cabeça do grafo
*
*
***********************************************************************/

typedef struct GRA_tagGrafo {

	LIS_tppLista pVerticesGrafo;
	/* Ponteiro para a lista de vertices do grafo */

	GRA_tpVertice* pElemCorr;
	/* Ponteiro para o elemento corrente do grafo */

	void(*ExcluirValor) (void * pValor);
	/* Ponteiro para a função de destruição do valor contido em um elemento */

} GRA_tpGrafo;

/***** Protótipos das funções encapuladas no módulo *****/

GRA_tpVertice *CriarVertice(GRA_tpGrafo *pGrafo, void * pValor);
GRA_tpNoVertices *CriarSubVertice(GRA_tpGrafo *pGrafo, int tam);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: Função: GRA  &Criar grafo
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
} /* Fim função: GRA  &Criar grafo */

/***************************************************************************
*
*  Função: Função: GRA  &Ir para o Vértice
*  ****/

/*GRA_tpCondRet GRA_IrVertice(GRA_tpGrafo *pGrafo, int numVert) {

IrInicioLista(pGrafo->listaVertices);
/*??????? Alguma outra condição de retorno pra erro aki??? 
if (LIS_AvancarElementoCorrente(pGrafo->listaVertices, numVert) != LIS_CondRetOK)
return GRA_CondRetNaoAchouVertice;

pGrafo->pElemCorr = pGrafo->listaVertices;
return GRA_CondRetOK;
}*/
/***************************************************************************
*
*  Função: GRA  &Obter referência para o valor contido no vértice
*  ****/

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

} /* Fim função: GRA  &Obter referência para o valor contido no vértice */

/***************************************************************************
*
*  Função: GRA  &Inserir vértice
*  ****/


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
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

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
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	if (LIS_InserirElementoApos(pGrafo->pVerticesGrafo,(void*)pVerts) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;

	if (LIS_InserirElementoApos(pVerts->pLisVertice,(void*)pVert) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;

	CondRet=LIS_ObterValor(pVerts->pLisVertice,(void**)&pRet);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	pGrafo->pElemCorr=pRet;
	return GRA_CondRetOK;

} /* Fim função: GRA  &Inserir vértice */

/***************************************************************************
*
*  Função: GRA  &Criar Aresta
*  ****/

GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2)
{
	int tam;
	GRA_tpVertice* pCorrenteAnterior=pGrafo->pElemCorr; 
	//GRA_tpNoVertices* pVertLisCorrenteAn;
	GRA_tpNoVertices* pVert1;
	GRA_tpNoVertices* pVert2;
	LIS_tpCondRet CondRet;
	// dependendo de ir vertice,isso e denecessario
	CondRet=LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	if(tam==0) 
		return GRA_CondRetGrafoVazio;
	//chamar funcao irvertice para o vertice 1
	//verificar retorno
	//LIS_ObterValor(pGrafo->pVerticesGrafo,(void**)&pVert1);
	//chamar funcao irvertice para o vertice 2
	//verificar retorno
	//LIS_ObterValor(pGrafo->pVerticesGrafo,(void**)&pVert2);
	if (LIS_InserirElementoApos(pGrafo->pElemCorr->pLisAresta,(void*)pVert1) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	CondRet=LIS_IrInicioLista(p->pElemCorr->pLisAresta);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	//chamar funcao irvertice para o vertice 1
	if (LIS_InserirElementoApos(pGrafo->pElemCorr->pLisAresta,(void*)pVert2) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	CondRet=LIS_IrInicioLista(p->pElemCorr->pLisAresta);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	pGrafo->pElemCorr=pCorrenteAnterior; 
	return GRA_CondRetOK;


} /* Fim função: GRA  &Criar Aresta */

/***************************************************************************
*
*  Função: GRA  &Existe Aresta
*  ****/

GRA_tpCondRet GRA_ExisteAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2)
{
	int tam;
	GRA_tpVertice* pCorrenteAnterior=pGrafo->pElemCorr;
	GRA_tpNoVertices* pVerts;
	LIS_tpCondRet CondRet,CondRetAv=LIS_CondRetOK;
	// dependendo de ir vertice,isso e denecessario
	CondRet=LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	if(tam==0)
		return GRA_CondRetGrafoVazio;
	//chamar funcao irvertice para o vertice 1
	//verificar retorno
	CondRet=LIS_ObterTamanho(pGrafo->pElemCorr->pLisAresta,&tam);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	if(tam==0)
		return GRA_CondRetNaoAchouAresta;
	while(CondRetAv!=LIS_CondRetFimLista)
	{
		CondRet=LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(CondRet!=LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
		if(pVerts->ident==numVert2)
		{
			CondRet=IrInicioLista(pGrafo->pElemCorr->pLisAresta);
			if(CondRet!=LIS_CondRetOK)
				return GRA_CondRetRetornoIncorreto;
			return GRA_CondRetOK;
		}
		CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);
	}
	CondRet=IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	pGrafo->pElemCorr=pCorrenteAnterior;
	return GRA_CondRetNaoAchouAresta;

} /* Fim função: GRA  &Existe Aresta */

/***************************************************************************
*
*  Função: GRA  &Excluir Aresta
*  ****/

GRA_tpCondRet GRA_ExcluirAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2)
{
	int tam;
	GRA_tpVertice* pCorrenteAnterior=pGrafo->pElemCorr;
	GRA_tpNoVertices* pVerts;
	LIS_tpCondRet CondRet,CondRetAv=LIS_CondRetOK;
	// dependendo de ir vertice,isso e denecessario
	CondRet=LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	if(tam==0) 
		return GRA_CondRetGrafoVazio;
	CondRet=GRA_ExisteAresta(pGrafo,numVert1,numVert2);
	if(CondRet==GRA_CondRetNaoAchouAresta)
		return GRA_CondRetNaoAchouAresta;
	//chamar funcao irvertice para o vertice 2
	while(CondRetAv!=LIS_CondRetFimLista)
	{
		CondRet=LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(CondRet!=LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
		if(pVerts->ident==numVert1)
		{
			CondRet=LIS_ExcluirElemento(pGrafo->pElemCorr->pLisAresta);
			if(CondRet!=LIS_CondRetOK)
				return GRA_CondRetRetornoIncorreto;
			CondRet=IrInicioLista(pGrafo->pElemCorr->pLisAresta);
			if(CondRet!=LIS_CondRetOK)
				return GRA_CondRetRetornoIncorreto;
			break;
		}
		CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);
	}
	if(CondRetAv==LIS_CondRetFimLista)
		return GRA_CondRetInconsistencia;

	//chamar funcao irvertice para o vertice 1
	while(CondRetAv!=LIS_CondRetFimLista)
	{
		CondRet=LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(CondRet!=LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
		if(pVerts->ident==numVert2)
		{
			CondRet=LIS_ExcluirElemento(pGrafo->pElemCorr->pLisAresta);
			if(CondRet!=LIS_CondRetOK)
				return GRA_CondRetRetornoIncorreto;
			CondRet=IrInicioLista(pGrafo->pElemCorr->pLisAresta);
			if(CondRet!=LIS_CondRetOK)
				return GRA_CondRetRetornoIncorreto;
			break;
		}
		CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);
	}
	pGrafo->pElemCorr=pCorrenteAnterior;
	return GRA_CondRetOK;


} /* Fim função: GRA  &Excluir Aresta */

/***************************************************************************
*
*  Função: GRA  &Excluir Vertice
*  ****/

/*GRA_tpCondRet GRA_ExcluirVertice(GRA_tpGrafo pGrafo)
{
}  Fim função: GRA  &Excluir vértice */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: GRA  -Criar o vertice da lista Vertice
*
***********************************************************************/


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

} /* Fim função: GRA  -Criar o elemento */

/***********************************************************************
*
*  $FC Função: GRA  -Criar o sub vertice,isto e,o vertice da lista Vertices
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
