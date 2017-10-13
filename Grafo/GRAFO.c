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
*     2        rm    10/10/2017 Funções GRA_IrVertice e GRA_DestruirGrafo
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

	int Ident;
	/* Identficador do vertice*/

	LIS_tppLista pLisAresta;
	/* Ponteiro para a lista de arestas */
} GRA_tpVertice;


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

GRA_tpVertice *CriarVertice(GRA_tpGrafo *pGrafo, void * pValor,int tam);
void DestruirElemVertice(void *Elem);
void DestruirElemVertices(void *Elem);


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

	if (LIS_CriarLista(DestruirElemVertices, &(pGrafo->pVerticesGrafo)) == LIS_CondRetFaltouMemoria) {   
		*GrafoRet = NULL;
		return GRA_CondRetFaltouMemoria;
	}

	pGrafo->pElemCorr = NULL;

	pGrafo->ExcluirValor = ExcluirValor;

	*GrafoRet = pGrafo;
	return GRA_CondRetOK;
} /* Fim função: GRA  &Criar grafo */

  /***********************************************************************
  *  $FC Função: GRA  &Destruir grafo
  *  ****/

GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo pGrafo) 
{ 
	LIS_tpCondRet CondRetLis;
	LIS_tppLista verts;
	GRA_tpVertice *vert;

	if(pGrafo==NULL)
		GRA_CondRetParametroIncorreto;
	if(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,0)!=LIS_CondRetListaVazia)
	{
		CondRetLis=IrInicioLista(pGrafo->pVerticesGrafo);
		if(CondRetLis!=LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
		do
		{
			if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**)&verts) != LIS_CondRetOK)
				return GRA_CondRetRetornoIncorreto;

			if (LIS_ObterValor(verts,(void**)&vert) != LIS_CondRetOK)
				return GRA_CondRetRetornoIncorreto;
			if (( pGrafo->ExcluirValor != NULL ) && ( vert->pValor != NULL ))
			 {
				pGrafo->ExcluirValor(vert->pValor);
			 } /* if */
		
		}
	    while(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,1)!=LIS_CondRetFimLista);
	}
	CondRetLis=LIS_DestruirLista(pGrafo->pVerticesGrafo);
	if(CondRetLis!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	pGrafo->pElemCorr=NULL;
	pGrafo->pVerticesGrafo=NULL;
	return GRA_CondRetOK;
}/* Fim função: GRA  &Destruir grafo*/


 /***************************************************************************
 *
 *  Função: Função: GRA  &Ir para o Vértice
 *  ****/

GRA_tpCondRet GRA_IrVertice(GRA_tppGrafo pGrafo, int numVert) {
	LIS_tppLista verts;
	GRA_tpVertice* vert;
	int tam;
	LIS_tpCondRet CondRet;

	if(pGrafo==NULL)
		return GRA_CondRetParametroIncorreto;

	CondRet=LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	if(tam==0) 
		return GRA_CondRetGrafoVazio;


	if (IrInicioLista(pGrafo->pVerticesGrafo) != LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**) &verts) != LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	if(LIS_ObterValor(verts,(void**) &vert) != LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	while (vert->Ident != numVert) {
		if (LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, 1) == LIS_CondRetFimLista)
			return GRA_CondRetNaoAchouVertice;

		if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**) &verts) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;

		if (LIS_ObterValor(verts,(void**) &vert) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
	}

	if (LIS_ObterValor(verts, (void**)&vert) != LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	pGrafo->pElemCorr = vert;
	return GRA_CondRetOK;
}/* Fim função: GRA  &Ir para o Vértice*/
/***************************************************************************
*
*  Função: GRA  &Obter referência para o valor contido no vértice
*  ****/

GRA_tpCondRet GRA_ObterValor(GRA_tppGrafo pGrafo, void** pValorRet)
{


	if(pGrafo == NULL)
		return GRA_CondRetParametroIncorreto;


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
	LIS_tppLista  pLIS_Vert;
	LIS_tppLista  pLIS_Verts;
	GRA_tpVertice * pVert;
	GRA_tpVertice * pRet;
	int tam;
	LIS_tpCondRet CondRet;
		
	if(pGrafo == NULL)
		return GRA_CondRetParametroIncorreto;

	CondRet=LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	if (LIS_CriarLista(NULL, &(pLIS_Vert)) == LIS_CondRetFaltouMemoria) 
	{   
		return GRA_CondRetFaltouMemoria;
	}

	pVert = CriarVertice(pGrafo, pValor,tam);
	if (pVert == NULL)
	{
		return GRA_CondRetFaltouMemoria;
	} /* if */

	pLIS_Verts=pLIS_Vert;

	CondRet=LIS_IrFinalLista(pGrafo->pVerticesGrafo);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	if (LIS_InserirElementoApos(pGrafo->pVerticesGrafo,(void*)pLIS_Verts) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;

	if (LIS_InserirElementoApos(pLIS_Vert,(void*)pVert) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	
	CondRet=LIS_ObterValor(pLIS_Vert,(void**)&pRet);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	pGrafo->pElemCorr=pRet;
	return GRA_CondRetOK;
		}
 /* Fim função: GRA  &Inserir vértice */

/***************************************************************************
*
*  Função: GRA  &Retorna Identificador
*  ****/


GRA_tpCondRet GRA_RetornaIdentificador(GRA_tppGrafo pGrafo,
	int* pIdent)
{
	GRA_tpNoVertice* pVert;
	LIS_tpCondRet CondRet;
	if(pGrafo == NULL)
		return GRA_CondRetParametroIncorreto;
	CondRet=LIS_ObterValor(pGrafo->pVerticesGrafo,(void**)&pVert);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	pIdent=pVert->ident;
	return GRA_CondRetOK;

} /* Fim função: GRA  &Retorna Identificador */

/***************************************************************************
*
*  Função: GRA  &Criar Aresta
*  ****/

GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2)
{
	int IdAnterior;
	GRA_tpVertice* pVert1;
	GRA_tpVertice* pVert2;
	LIS_tpCondRet CondRetLis;
	GRA_tpCondRet CondRetGra;
	
	
	if(pGrafo==NULL)
		return GRA_CondRetParametroIncorreto;

	IdAnterior=pGrafo->pElemCorr->Ident;

	CondRetGra=GRA_IrVertice(pGrafo,numVert1);

	if(CondRetGra==GRA_CondRetGrafoVazio)
		return GRA_CondRetGrafoVazio;
	else if(CondRetGra==GRA_CondRetNaoAchouVertice)
		return GRA_CondRetNaoAchouVertice;

	pVert1=pGrafo->pElemCorr;
	CondRetGra=GRA_IrVertice(pGrafo,numVert2);

	if(CondRetGra==GRA_CondRetNaoAchouVertice)
	{
		CondRetGra=GRA_IrVertice(pGrafo,IdAnterior);
		return GRA_CondRetNaoAchouVertice;
	}

	pVert2=pGrafo->pElemCorr;
	if (LIS_InserirElementoApos(pGrafo->pElemCorr->pLisAresta,(void*)pVert1) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	CondRetLis=lis_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	if(CondRetLis!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	CondRetGra=GRA_IrVertice(pGrafo,numVert1);

	if (LIS_InserirElementoApos(pGrafo->pElemCorr->pLisAresta,(void*)pVert2) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	CondRetLis=LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	if(CondRetLis!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	CondRetGra=GRA_IrVertice(pGrafo,IdAnterior);
	return GRA_CondRetOK;
} /* Fim função: GRA  &Criar Aresta */


/***************************************************************************
*
*  Função: GRA  &Existe Aresta
*  ****/

GRA_tpCondRet GRA_ExisteAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2)
{
	int IdAnterior,tam;
	GRA_tpVertice* pVerts;
	LIS_tpCondRet CondRetLIS,CondRetAv=LIS_CondRetOK;
	GRA_tpCondRet CondRetGra;

	if(pGrafo==NULL)
		return GRA_CondRetParametroIncorreto;
	IdAnterior=pGrafo->pElemCorr->Ident;
	
	CondRetGra=GRA_IrVertice(pGrafo,numVert1);
	if(CondRetGra==GRA_CondRetGrafoVazio)
		return GRA_CondRetGrafoVazio;	
	if(CondRetGra==GRA_CondRetNaoAchouVertice)
		return GRA_CondRetNaoAchouVertice;

	CondRetLIS=LIS_ObterTamanho(pGrafo->pElemCorr->pLisAresta,&tam);
	if(CondRetLIS!=LIS_CondRetOK)
		return GRA_CondRetParametroIncorreto;
	if(tam==0)
	{
		return GRA_CondRetNaoAchouAresta;
	}
	while(CondRetAv!=LIS_CondRetFimLista)
	{
		CondRetLIS=LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(CondRetLIS!=LIS_CondRetOK)
			return GRA_CondRetParametroIncorreto;
		if(pVerts->Ident==numVert2)
		{
			CondRetLIS=LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
			if(CondRetLIS!=LIS_CondRetOK)
				return GRA_CondRetParametroIncorreto;
			 CondRetGra=GRA_IrVertice(pGrafo,IdAnterior);
			 if(CondRetGra!=GRA_CondRetOK)
				return GRA_CondRetInconsistencia;
			return GRA_CondRetOK;
		}
		CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);
	}
	CondRetLIS=LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	if(CondRetLIS!=LIS_CondRetOK)
		return GRA_CondRetParametroIncorreto;
	CondRetGra=GRA_IrVertice(pGrafo,IdAnterior);

	if(CondRetGra!=GRA_CondRetOK)
		return GRA_CondRetInconsistencia;
	return GRA_CondRetNaoAchouAresta;
	
}  /*Fim função: GRA  &Existe Aresta */

/***************************************************************************
*
*  Função: GRA  &Excluir Aresta
*  ****/

GRA_tpCondRet GRA_ExcluirAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2)
{
	int IdAnterior;
	GRA_tpVertice* pVerts;
	LIS_tpCondRet CondRetLis,CondRetAv=LIS_CondRetOK;
	GRA_tpCondRet CondRetGra;  

	CondRetGra=GRA_ExisteAresta(pGrafo,numVert1,numVert2);

	if(CondRetGra==GRA_CondRetParametroIncorreto)
	{
		return GRA_CondRetParametroIncorreto;
	}

	else if(CondRetGra==GRA_CondRetGrafoVazio)
	{
		return GRA_CondRetGrafoVazio;	
	}

	else if(CondRetGra==GRA_CondRetNaoAchouAresta)
	{
		return GRA_CondRetNaoAchouAresta;
	}

	else if(CondRetGra==GRA_CondRetNaoAchouVertice)
	{
		return GRA_CondRetNaoAchouVertice;	
	}

	IdAnterior=pGrafo->pElemCorr->Ident;
	CondRetGra=GRA_IrVertice(pGrafo,numVert1);



	while(CondRetAv!=LIS_CondRetFimLista)
	{
		CondRetLis=LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(CondRetLis!=LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
		if(pVerts->Ident==numVert2)
		{
			CondRetLis=LIS_ExcluirElemento(pGrafo->pElemCorr->pLisAresta);
			if(CondRetLis!=LIS_CondRetOK)
				return GRA_CondRetRetornoIncorreto;
			CondRetLis=IrInicioLista(pGrafo->pElemCorr->pLisAresta);
			if(CondRetLis!=LIS_CondRetOK)
				return GRA_CondRetRetornoIncorreto;
			break;
		}
		CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);

	}
	if(CondRetAv==LIS_CondRetFimLista)
		return GRA_CondRetInconsistencia;

	CondRetGra=GRA_IrVertice(pGrafo,numVert2);
	if(CondRetGra!=GRA_CondRetOK)
	{
		return GRA_CondRetInconsistencia;	
	}

	while(CondRetAv!=LIS_CondRetFimLista)
	{
		CondRetLis=LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(CondRetLis!=LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
		if(pVerts->Ident==numVert1)
		{
			CondRetLis=LIS_ExcluirElemento(pGrafo->pElemCorr->pLisAresta);
			if(CondRetLis!=LIS_CondRetOK)
				return GRA_CondRetRetornoIncorreto;
			CondRetLis=IrInicioLista(pGrafo->pElemCorr->pLisAresta);
			if(CondRetLis!=LIS_CondRetOK)
				return GRA_CondRetRetornoIncorreto;
			break;
		}
		CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);
	}
	CondRetGra=GRA_IrVertice(pGrafo,IdAnterior);
	if(CondRetGra!=GRA_CondRetOK)
		return GRA_CondRetInconsistencia;
	return GRA_CondRetOK;



}/*  Fim função: GRA  &Excluir Aresta */
/***************************************************************************
/***************************************************************************
*
*  Função: GRA  &Excluir Vertice
*  ****/
GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo)
{
	LIS_tpCondRet CondRetLis;
	GRA_tpCondRet CondRetGra;
	GRA_tpVertice* pVert;
	GRA_tpVertice *Aresta;
	LIS_tppLista vertices;
	GRA_tpVertice *vertice;
	int tam;
	int identCorrente;
	int i;

	if(pGrafo==NULL)
		return GRA_CondRetParametroIncorreto;

	if(pGrafo->pElemCorr==NULL)
		return GRA_CondRetGrafoVazio;

	pVert=pGrafo->pElemCorr;
	identCorrente=pVert->Ident;
	CondRetLis = LIS_ObterTamanho(pVert->pLisAresta, &tam);
	if(CondRetLis!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	if(tam!=0)
	{
		for(i=0;i<tam;i++)
		{	
			CondRetLis = LIS_ObterValor(pVert->pLisAresta,(void**)&Aresta);
			if (CondRetLis!=LIS_CondRetOK)
				return GRA_CondRetRetornoIncorreto;
			GRA_ExcluirAresta(pGrafo,pVert->Ident,Aresta->Ident);
			LIS_AvancarElementoCorrente(pVert->pLisAresta,1);
		}
	}
	GRA_IrVertice(pGrafo,identCorrente);		
	CondRetLis=LIS_ObterTamanho(pGrafo->pVerticesGrafo, &tam);
	if (CondRetLis!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	for(i=0;i<tam-identCorrente;i++)
	{
		LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,1);
		if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**)&vertices) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;

		if (LIS_ObterValor(vertices,(void**)&vertice) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
		vertice->Ident=vertice->Ident-1;
	}
	CondRetGra=GRA_IrVertice(pGrafo,identCorrente);
	if (CondRetGra!=GRA_CondRetOK)
		return GRA_CondRetInconsistencia;
	if(LIS_ExcluirElemento(pGrafo->pVerticesGrafo)!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	if(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,1)!=LIS_CondRetFimLista)
	{
		if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**)&vertices) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;

		if (LIS_ObterValor(vertices,(void**)&vertice) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
		pGrafo->pElemCorr=vertice;
		return GRA_CondRetOK;
	}
	else if(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,-1)!=LIS_CondRetFimLista)
	{
		if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**)&vertices) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;

		if (LIS_ObterValor(vertices,(void**)&vertice) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
		pGrafo->pElemCorr=vertice;
		return GRA_CondRetOK;
	}

	else
		pGrafo->pElemCorr=NULL;
	return GRA_CondRetOK;
}/*  Fim função: GRA  &Excluir Vertice */


/*****  Código das funções encapsuladas no módulo  *****/




/***********************************************************************
*
*  $FC Função: GRA  -Criar o vertice da lista Vertice
*
***********************************************************************/


GRA_tpVertice *CriarVertice(GRA_tpGrafo *pGrafo, void * pValor , int tam)
{
	GRA_tpVertice * pVert;

	pVert = (GRA_tpVertice *)malloc(sizeof(GRA_tpVertice));
	if (pVert == NULL)
	{
		return NULL;
	} /* if */

	pVert->Ident = tam+1;
	pVert->pValor = pValor;
	if (LIS_CriarLista(NULL, &(pVert->pLisAresta)) != LIS_CondRetOK)  //REVER ESSE NULL
		return NULL;

	return pVert;

} /* Fim função: GRA  -Criar o vertice da lista Vertice */

/***********************************************************************
*
*  $FC Função: GRA  -Destruir elemento da Lista Vertices
*
***********************************************************************/
void DestruirElemVertices(void *Elem)
{
	LIS_tppLista Lis=(LIS_tppLista)Elem;
	DestruirElemVertice(Lis);
}


/***********************************************************************
*
*  $FC Função: GRA  -Destruir elemento da Lista Vertice
*
***********************************************************************/

void DestruirElemVertice(void *Elem)
{
	GRA_tpVertice* vert;
	LIS_tppLista Lis=(LIS_tppLista)Elem;
	LIS_ObterValor(Lis,(void**)&vert);
	LIS_DestruirLista(vert->pLisAresta);
}
