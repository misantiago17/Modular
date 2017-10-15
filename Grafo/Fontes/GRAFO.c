/***************************************************************************
*  $MCI M�dulo de implementa��o: GRA  Grafo generico com cabeca
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
*     2        rm    10/10/2017 Fun��es GRA_IrVertice e GRA_DestruirGrafo
*     1      rm/ms/gb   05/10/2017 in�cio desenvolvimento
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

GRA_tpVertice *CriarVertice(GRA_tpGrafo *pGrafo, void * pValor,int tam);
void DestruirElemVertice(void *Elem);
void DestruirElemVertices(void *Elem);


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

	if (LIS_CriarLista(DestruirElemVertices, &(pGrafo->pVerticesGrafo)) == LIS_CondRetFaltouMemoria) {   
		*GrafoRet = NULL;
		return GRA_CondRetFaltouMemoria;
	}

	pGrafo->pElemCorr = NULL;

	pGrafo->ExcluirValor = ExcluirValor;

	*GrafoRet = pGrafo;
	return GRA_CondRetOK;
} /* Fim fun��o: GRA  &Criar grafo */

  /***********************************************************************
  *  $FC Fun��o: GRA  &Destruir grafo
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
		CondRetLis=LIS_IrInicioLista(pGrafo->pVerticesGrafo);
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
}/* Fim fun��o: GRA  &Destruir grafo*/


 /***************************************************************************
 *
 *  Fun��o: Fun��o: GRA  &Ir para o V�rtice
 *  ****/

GRA_tpCondRet GRA_IrVertice(GRA_tppGrafo pGrafo, int numVert) {
	LIS_tppLista verts;
	GRA_tpVertice* vert;
	int tam,contador=0;
	LIS_tpCondRet CondRet;

	if(pGrafo==NULL)
		return GRA_CondRetParametroIncorreto;

	CondRet=LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	if(tam==0) 
		return GRA_CondRetGrafoVazio;

	while(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, -1)!= LIS_CondRetFimLista)
	{
		contador++;
	}

	if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**) &verts) != LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	if(LIS_ObterValor(verts,(void**) &vert) != LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	while (vert->Ident != numVert) {
		if (LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, 1) == LIS_CondRetFimLista)
		{
			
			if(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, (tam-1-contador)*-1)!=LIS_CondRetOK)
				return GRA_CondRetRetornoIncorreto;
			if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**) &verts) != LIS_CondRetOK)
					return GRA_CondRetRetornoIncorreto;
			if(LIS_ObterValor(verts,(void**) &vert) != LIS_CondRetOK)
					return GRA_CondRetRetornoIncorreto;
			pGrafo->pElemCorr=vert;
			return GRA_CondRetNaoAchouVertice;
		}

		if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**) &verts) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;

		if (LIS_ObterValor(verts,(void**) &vert) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
	}

	if (LIS_ObterValor(verts, (void**)&vert) != LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	pGrafo->pElemCorr = vert;
	return GRA_CondRetOK;
}/* Fim fun��o: GRA  &Ir para o V�rtice*/
/***************************************************************************
*
*  Fun��o: GRA  &Obter refer�ncia para o valor contido no v�rtice
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

} /* Fim fun��o: GRA  &Obter refer�ncia para o valor contido no v�rtice */

/***************************************************************************
*
*  Fun��o: GRA  &Inserir v�rtice
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
 /* Fim fun��o: GRA  &Inserir v�rtice */


/***************************************************************************
*
*  Fun��o: GRA  &Criar Aresta
*  ****/

GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2)
{
	int IdAnterior;
	GRA_tpVertice* pVert1;
	GRA_tpVertice* pVert2;
	LIS_tpCondRet CondRetLis;
	GRA_tpCondRet CondRetGra;

	if(numVert1==numVert2)
		return GRA_CondRetArestaParaSiMesmo;
	
	CondRetGra=GRA_ExisteAresta(pGrafo,numVert1,numVert2);

	if(CondRetGra==GRA_CondRetParametroIncorreto)
	{
		return GRA_CondRetParametroIncorreto;
	}

	else if(CondRetGra==GRA_CondRetGrafoVazio)
	{
		return GRA_CondRetGrafoVazio;	
	}


	else if(CondRetGra==GRA_CondRetNaoAchouVertice)
	{
		return GRA_CondRetNaoAchouVertice;	
	}

		else if(CondRetGra==GRA_CondRetOK)
	{
		return GRA_CondRetArestaJaExiste;
	}

	IdAnterior=pGrafo->pElemCorr->Ident;

	CondRetGra=GRA_IrVertice(pGrafo,numVert1);


	if(CondRetGra==GRA_CondRetNaoAchouVertice)
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
	CondRetLis=IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	if(CondRetLis!=LIS_CondRetOK)

		return GRA_CondRetRetornoIncorreto;

	CondRetGra=GRA_IrVertice(pGrafo,numVert1);
	if(CondRetGra!=GRA_CondRetOK)
		return GRA_CondRetInconsistencia;

	if (LIS_InserirElementoApos(pGrafo->pElemCorr->pLisAresta,(void*)pVert2) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	CondRetLis=IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	if(CondRetLis!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	CondRetGra=GRA_IrVertice(pGrafo,IdAnterior);
	if(CondRetGra!=GRA_CondRetOK)
		return GRA_CondRetInconsistencia;
	return GRA_CondRetOK;


} /* Fim fun��o: GRA  &Criar Aresta */


/***************************************************************************
*
*  Fun��o: GRA  &Existe Aresta
*  ****/

GRA_tpCondRet GRA_ExisteAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2)
{
	int IdAnterior,tam;
	GRA_tpVertice* pVerts;
	LIS_tpCondRet CondRetLIS,CondRetAv=LIS_CondRetOK;
	GRA_tpCondRet CondRetGra;

	if(pGrafo==NULL)
		return GRA_CondRetParametroIncorreto;
	if(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,0)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
	IdAnterior=pGrafo->pElemCorr->Ident;

	CondRetGra=GRA_IrVertice(pGrafo,numVert1);
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

}  /*Fim fun��o: GRA  &Existe Aresta */

/***************************************************************************
*
*  Fun��o: GRA  &Excluir Aresta
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
			CondRetLis=LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
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
			CondRetLis=LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
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



}/*  Fim fun��o: GRA  &Excluir Aresta */
/***************************************************************************
*
*  Fun��o: GRA  &Excluir Vertice
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
	if(LIS_ExcluirElemento(pGrafo->pVerticesGrafo)!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	if(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,0)==LIS_CondRetListaVazia)
	{
		pGrafo->pElemCorr=NULL;
		return GRA_CondRetOK;
	}
	else
	{
		if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**)&vertices) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;

		if (LIS_ObterValor(vertices,(void**)&vertice) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
		pGrafo->pElemCorr=vertice;
		return GRA_CondRetOK;
	}

	return GRA_CondRetOK;
}/*  Fim fun��o: GRA  &Excluir Vertice */

/***************************************************************************
*
*  Fun��o: GRA  &Retornar Numero de Vertices
*  ****/

GRA_tpCondRet GRA_NumVertices(GRA_tppGrafo pGrafo,int *pNumVerts)
{
	if(pGrafo==NULL)
		return GRA_CondRetParametroIncorreto;
	if(LIS_ObterTamanho(pGrafo->pVerticesGrafo,pNumVerts)!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	return GRA_CondRetOK;


} /* Fim fun��o: GRA  &Retornar Numero de Vertices*/

/***************************************************************************
*
*  Fun��o: GRA  &Retornar Numero de Arestas
*  ****/

GRA_tpCondRet GRA_NumArestas(GRA_tppGrafo pGrafo,int *pNumArestas)
{

	if(pGrafo==NULL)
		return GRA_CondRetParametroIncorreto;
	if(pGrafo->pElemCorr==NULL)
		return GRA_CondRetGrafoVazio;
	if(LIS_ObterTamanho(pGrafo->pElemCorr->pLisAresta,pNumArestas)!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	return GRA_CondRetOK;

}/* Fim fun��o: GRA  &Retornar Numero de Arestas*/


/***************************************************************************
*
*  Fun��o: GRA  &RetornarIndicesAresta
*  ****/

GRA_tpCondRet GRA_RetornaIndiceAresta(GRA_tppGrafo pGrafo,int* pDado)
{
	GRA_tpVertice* Aresta; 
	GRA_tpCondRet CondRetGra;
	LIS_tpCondRet CondRetLis;
	int numAr,i;
	CondRetGra=GRA_NumArestas(pGrafo,&numAr);
	if(numAr==0)
		return GRA_CondRetNumArestasZero;
	for(i=0;i<numAr;i++)
	{
		CondRetLis=LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&Aresta);
		if(CondRetLis!=LIS_CondRetOK)
			return GRA_CondRetParametroIncorreto;
		pDado[i]=Aresta->Ident;
	}
	CondRetLis=IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	if(CondRetLis!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	return GRA_CondRetOK;



}/* Fim fun��o: GRA  &RetornarIndicesAresta*/
		



/*****  C�digo das fun��es encapsuladas no m�dulo  *****/




/***********************************************************************
*
*  $FC Fun��o: GRA  -Criar o vertice da lista Vertice
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

} /* Fim fun��o: GRA  -Criar o vertice da lista Vertice */

/***********************************************************************
*
*  $FC Fun��o: GRA  -Destruir elemento da Lista Vertices
*
***********************************************************************/
void DestruirElemVertices(void *Elem)
{
	LIS_tppLista Lis=(LIS_tppLista)Elem;
	DestruirElemVertice(Lis);
}


/***********************************************************************
*
*  $FC Fun��o: GRA  -Destruir elemento da Lista Vertice
*
***********************************************************************/

void DestruirElemVertice(void *Elem)
{
	GRA_tpVertice* vert;
	LIS_tppLista Lis=(LIS_tppLista)Elem;
	LIS_ObterValor(Lis,(void**)&vert);
	LIS_DestruirLista(vert->pLisAresta);
	LIS_DestruirLista(Lis);
}
