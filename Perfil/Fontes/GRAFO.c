/***************************************************************************
*  $MCI M�dulo de implementa��o: GRA  Grafo generico com cabeca
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  DI/PUC-Rio
*  Autores: Gabriel Busquim (gb), Michelle Santiago (ms), Renan Moreira (rm)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor   	 Data     	Observa��es
*    18      rm/ms/gb   16/10/2017 	revisoes finais e pequenas correcoes
*    17        gb    	14/10/2017 	funcoes: GRA_NumArestas, GRA_RetornaIndiceAresta,GRA_NumVertices
*    16        ms    	13/10/2017 	alteracao GRA_IrVertice, GRA_CriarAresta, GRA_ExisteAresta, GRA_ExcluirAresta
*    15        gb    	12/10/2017 	alteracao GRA_CriarAresta, GRA_InserirAresta
*    14        gb    	11/10/2017 	alteracao GRA_InserirVertice
*    13        rm    	11/10/2017 	alteracao GRA_IrVertice, GRA_DestruirGrafo
*    12      rm/ms/gb   11/10/2017 	revisao nas structs
*    11        rm    	10/10/2017 	funcoes: GRA_IrVertice e GRA_DestruirGrafo
*    10        ms       10/10/2017 	funcao: LiberarVertice; revisao na: GRA_ExcluirVertice
*     9      gb/ms      09/10/2017 	funcoes: GRA_RetornaIdentificador
*     8        gb       08/10/2017 	funcoes: GRA_ExcluirAresta
*     7        gb       06/10/2017 	funcoes: GRA_CriarAresta, GRA_ExisteAresta
*     6     gb/rm/ms    06/10/2017 	alteracao nas funcoes: GRA_InserirVertice, GRA_ExcluirVertice
*     5        ms       05/10/2017 	alteracao nas funcoes: GRA_ObterValor, GRA_InserirVertice
*     4        ms       05/10/2017 	funcoes: GRA_ExcluirVertice, CriarSubVertice
*     3      rm/ms/gb   04/10/2017 	revisao nas structs; remocao: CriarElemento e LimparCabeca
*	  2        rm       30/09/2017  funcoes: GRA_CriarGrafo, GRA_IrVertice, GRA_ObterValor, GRA_InserirVertice, CriarElemento, LimparCabeca
*     1      rm/ms/gb   27/09/2017 	inicio desenvolvimento
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

static GRA_tpVertice *CriarVertice( void * pValor,int tam);
static void DestruirElemVertice(void *Elem);
static void DestruirElemVertices(void *Elem);

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
  *
  *  $FC Fun��o: GRA  &Destruir grafo
  *  ****/

GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo pGrafo) 
{ 
	LIS_tpCondRet CondRetLis;
	LIS_tppLista verts;
	GRA_tpVertice *vert;

	//Assertiva
	if(pGrafo==NULL)
		return GRA_CondRetParametroIncorreto;
	if(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,0)!=LIS_CondRetListaVazia)
	{
		CondRetLis=LIS_IrInicioLista(pGrafo->pVerticesGrafo);
		if(CondRetLis!=LIS_CondRetOK)
			return GRA_CondRetRetornoLisIncorreto;
		do
		{
			if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**)&verts) != LIS_CondRetOK)
				return GRA_CondRetRetornoLisIncorreto;

			if (LIS_ObterValor(verts,(void**)&vert) != LIS_CondRetOK)
				return GRA_CondRetRetornoLisIncorreto;
			if (( pGrafo->ExcluirValor != NULL ) && ( vert->pValor != NULL ))
			 {
				pGrafo->ExcluirValor(vert->pValor);
			 } 
			 free(vert->pValor);
		
		}
	    while(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,1)!=LIS_CondRetFimLista);
	}
	CondRetLis=LIS_DestruirLista(pGrafo->pVerticesGrafo);
	if(CondRetLis!=LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;
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

	//Assertiva
	if(pGrafo==NULL)
		return GRA_CondRetParametroIncorreto;

	CondRet=LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;
	if(tam==0) 
		return GRA_CondRetGrafoVazio;

	while(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, -1)!= LIS_CondRetFimLista)
	{
		contador++;
	}

	if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**) &verts) != LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;

	if(LIS_ObterValor(verts,(void**) &vert) != LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;

	while (vert->Ident != numVert) {
		if (LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, 1) == LIS_CondRetFimLista)
		{
			//nao encontrou o vertice passado como parametro->colocar corrente na posicao original
			if(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, (tam-1-contador)*-1)!=LIS_CondRetOK)
				return GRA_CondRetRetornoLisIncorreto;
			if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**) &verts) != LIS_CondRetOK)
					return GRA_CondRetRetornoLisIncorreto;
			if(LIS_ObterValor(verts,(void**) &vert) != LIS_CondRetOK)
					return GRA_CondRetRetornoLisIncorreto;
			pGrafo->pElemCorr=vert;
			return GRA_CondRetNaoAchouVertice;
		}

		if (LIS_ObterValor(pGrafo->pVerticesGrafo,(void**) &verts) != LIS_CondRetOK)
			return GRA_CondRetRetornoLisIncorreto;

		if (LIS_ObterValor(verts,(void**) &vert) != LIS_CondRetOK)
			return GRA_CondRetRetornoLisIncorreto;
	}

	if (LIS_ObterValor(verts, (void**)&vert) != LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;

	pGrafo->pElemCorr = vert;
	return GRA_CondRetOK;
	
}/* Fim fun��o: GRA  &Ir para o V�rtice*/


/***************************************************************************
 *
 *  Fun��o:  &Retorna Identificador
 *  ****/

GRA_tpCondRet GRA_RetornaIdentificador(GRA_tppGrafo pGrafo, int* numIdent) 
{
	int tam;
	LIS_tpCondRet CondRet;
	//Assertiva
	if(pGrafo==NULL)
		return GRA_CondRetParametroIncorreto;
	CondRet=LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;
	//Assertiva
	if(tam==0) 
		return GRA_CondRetGrafoVazio;
	*numIdent=pGrafo->pElemCorr->Ident;
	return GRA_CondRetOK;
	
}/* Fim fun��o: GRA  &Retorna Identificador*/


/***************************************************************************
*
*  Fun��o: GRA  &Obter refer�ncia para o valor contido no v�rtice
*  ****/

GRA_tpCondRet GRA_ObterValor(GRA_tppGrafo pGrafo, void** pValorRet)
{
	//Assertiva
	if(pGrafo == NULL)
		return GRA_CondRetParametroIncorreto;

	//Assertiva
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

GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo, void * pValor)
{
	LIS_tppLista  pLIS_Vert;
	LIS_tppLista  pLIS_Verts;
	GRA_tpVertice * pVert;
	GRA_tpVertice * pRet;
	int tam;
	LIS_tpCondRet CondRet;
	
	//Assertiva
	if(pGrafo == NULL)
		return GRA_CondRetParametroIncorreto;

	CondRet=LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;

	if (LIS_CriarLista(NULL, &(pLIS_Vert)) == LIS_CondRetFaltouMemoria) 
	{   
		return GRA_CondRetFaltouMemoria;
	}

	pVert = CriarVertice(pValor,tam);
	if (pVert == NULL)
	{
		return GRA_CondRetFaltouMemoria;
	} 
	
	//Cada elemento da lista vertices deve possuir exatamente uma referencia para um elemento da lista Vertice
	pLIS_Verts=pLIS_Vert;

	CondRet=LIS_IrFinalLista(pGrafo->pVerticesGrafo);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;

	if (LIS_InserirElementoApos(pGrafo->pVerticesGrafo,(void*)pLIS_Verts) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;

	if (LIS_InserirElementoApos(pLIS_Vert,(void*)pVert) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	
	CondRet=LIS_ObterValor(pLIS_Vert,(void**)&pRet);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;
	pGrafo->pElemCorr=pRet;
	return GRA_CondRetOK;
	
}/* Fim fun��o: GRA  &Inserir v�rtice */


 /***************************************************************************
 *
 *  Fun��o: GRA  &Excluir Vertice
 *  ****/
 
GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo)
{
	GRA_tpCondRet CondRetGra;
	GRA_tpVertice* pVert;
	GRA_tpVertice* Aresta;
	GRA_tpVertice* vertice;
	LIS_tpCondRet CondRetLis;
	LIS_tppLista vertices;
	int tam, identCorrente, i;

	//Assertiva
	if (pGrafo == NULL)
		return GRA_CondRetParametroIncorreto;

	//Assertiva
	if (pGrafo->pElemCorr == NULL)
		return GRA_CondRetGrafoVazio;

	pVert = pGrafo->pElemCorr;
	identCorrente = pVert->Ident;
	CondRetLis = LIS_ObterTamanho(pVert->pLisAresta, &tam);
	if (CondRetLis != LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;
	if (tam != 0)
	{
		//Apagando cada elemento da lista de arestas
		for (i = 0; i<tam; i++)
		{
			CondRetLis = LIS_ObterValor(pVert->pLisAresta, (void**)&Aresta);
			if (CondRetLis != LIS_CondRetOK)
				return GRA_CondRetRetornoLisIncorreto;
			GRA_ExcluirAresta(pGrafo, pVert->Ident, Aresta->Ident);
			LIS_AvancarElementoCorrente(pVert->pLisAresta, 1);
		}
		
	}
	if (( pGrafo->ExcluirValor != NULL ) && ( pVert->pValor != NULL )){
			 {
				pGrafo->ExcluirValor(pVert->pValor);
			 } 
			 free(pVert->pValor);
		
		}
	GRA_IrVertice(pGrafo,identCorrente);
	CondRetLis = LIS_ObterTamanho(pGrafo->pVerticesGrafo, &tam);
	if (CondRetLis != LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;
	//decrescendo de 1 cada identificador maior do que o identificador do vertice a ser excluido
	for (i = 0; i<tam - identCorrente; i++)
	{
		LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, 1);
		if (LIS_ObterValor(pGrafo->pVerticesGrafo, (void**)&vertices) != LIS_CondRetOK)
			return GRA_CondRetRetornoLisIncorreto;

		if (LIS_ObterValor(vertices, (void**)&vertice) != LIS_CondRetOK)
			return GRA_CondRetRetornoLisIncorreto;
		vertice->Ident = vertice->Ident - 1;
	}
	CondRetGra = GRA_IrVertice(pGrafo, identCorrente);
	if (LIS_ExcluirElemento(pGrafo->pVerticesGrafo) != LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;
	if (LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, 0) == LIS_CondRetListaVazia)
	{
		pGrafo->pElemCorr = NULL;
		return GRA_CondRetOK;
	}
	else
	{
		if (LIS_ObterValor(pGrafo->pVerticesGrafo, (void**)&vertices) != LIS_CondRetOK)
			return GRA_CondRetRetornoLisIncorreto;
		if (LIS_ObterValor(vertices, (void**)&vertice) != LIS_CondRetOK)
			return GRA_CondRetRetornoLisIncorreto;
		pGrafo->pElemCorr = vertice;
		return GRA_CondRetOK;
	}
}/*  Fim fun��o: GRA  &Excluir Vertice */


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
	IdAnterior=pGrafo->pElemCorr->Ident;
	CondRetGra=GRA_ExisteAresta(pGrafo,numVert1,numVert2);
	//ASSERTIVAS:
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
	CondRetLis=LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	if(CondRetLis!=LIS_CondRetOK)

		return GRA_CondRetRetornoLisIncorreto;

	CondRetGra=GRA_IrVertice(pGrafo,numVert1);

	if (LIS_InserirElementoApos(pGrafo->pElemCorr->pLisAresta,(void*)pVert2) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	CondRetLis=LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	if(CondRetLis!=LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;
	CondRetGra=GRA_IrVertice(pGrafo,IdAnterior);

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
	
	//ASSERTIVAS
	if(pGrafo==NULL)
		return GRA_CondRetParametroIncorreto;
	if(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,0)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
	IdAnterior=pGrafo->pElemCorr->Ident;
	CondRetGra=GRA_IrVertice(pGrafo,numVert1);
	if(CondRetGra==GRA_CondRetNaoAchouVertice)
		return GRA_CondRetNaoAchouVertice;

	CondRetGra=GRA_IrVertice(pGrafo,numVert2);
	if(CondRetGra==GRA_CondRetNaoAchouVertice)
	{
		GRA_IrVertice(pGrafo,IdAnterior);
		return GRA_CondRetNaoAchouVertice;
	}

	CondRetLIS=LIS_ObterTamanho(pGrafo->pElemCorr->pLisAresta,&tam);
	if(CondRetLIS!=LIS_CondRetOK)
		return GRA_CondRetParametroIncorreto;
	if(tam==0)
	{	
		GRA_IrVertice(pGrafo,IdAnterior);
		return GRA_CondRetNaoAchouAresta;
	}
	while(CondRetAv!=LIS_CondRetFimLista)
	{
		CondRetLIS=LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(CondRetLIS!=LIS_CondRetOK)
			return GRA_CondRetParametroIncorreto;
		if(pVerts->Ident==numVert1)
		{
			CondRetLIS=LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
			if(CondRetLIS!=LIS_CondRetOK)
				return GRA_CondRetParametroIncorreto;
			CondRetGra=GRA_IrVertice(pGrafo,IdAnterior);
			return GRA_CondRetOK;
		}
		CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);
	}
	CondRetLIS=LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	if(CondRetLIS!=LIS_CondRetOK)
		return GRA_CondRetParametroIncorreto;
	
	CondRetGra=GRA_IrVertice(pGrafo,IdAnterior);
	
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

	//Assertivas
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
			return GRA_CondRetRetornoLisIncorreto;
		if(pVerts->Ident==numVert2)
		{
			CondRetLis=LIS_ExcluirElemento(pGrafo->pElemCorr->pLisAresta);
			if(CondRetLis!=LIS_CondRetOK)
				return GRA_CondRetRetornoLisIncorreto;
			CondRetLis=LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
			if(CondRetLis!=LIS_CondRetOK)
				return GRA_CondRetRetornoLisIncorreto;
			break;
		}
		CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);

	}

	CondRetGra=GRA_IrVertice(pGrafo,numVert2);

	while(CondRetAv!=LIS_CondRetFimLista)
	{
		CondRetLis=LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(CondRetLis!=LIS_CondRetOK)
			return GRA_CondRetRetornoLisIncorreto;
		if(pVerts->Ident==numVert1)
		{
			CondRetLis=LIS_ExcluirElemento(pGrafo->pElemCorr->pLisAresta);
			if(CondRetLis!=LIS_CondRetOK)
				return GRA_CondRetRetornoLisIncorreto;
			CondRetLis=LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
			if(CondRetLis!=LIS_CondRetOK)
				return GRA_CondRetRetornoLisIncorreto;
			break;
		}
		CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);
	}
	CondRetGra=GRA_IrVertice(pGrafo,IdAnterior);
	return GRA_CondRetOK;
	
}/*  Fim fun��o: GRA  &Excluir Aresta */


 /***************************************************************************
 *
 *  Fun��o: GRA  &Retornar Numero de Arestas
 *  ****/

GRA_tpCondRet GRA_NumArestas(GRA_tppGrafo pGrafo, int *pNumArestas)
{
	//Assertivas
	if (pGrafo == NULL)
		return GRA_CondRetParametroIncorreto;
	if (pGrafo->pElemCorr == NULL)
		return GRA_CondRetGrafoVazio;
	if (LIS_ObterTamanho(pGrafo->pElemCorr->pLisAresta, pNumArestas) != LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;
	return GRA_CondRetOK;
	
}/* Fim fun��o: GRA  &Retornar Numero de Arestas*/


/***************************************************************************
*
*  Fun��o: GRA  &Retornar Numero de Vertices
*  ****/

GRA_tpCondRet GRA_NumVertices(GRA_tppGrafo pGrafo,int *pNumVerts)
{
	//Assertivas
	if(pGrafo==NULL)
		return GRA_CondRetParametroIncorreto;
	if(LIS_ObterTamanho(pGrafo->pVerticesGrafo,pNumVerts)!=LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;
	return GRA_CondRetOK;

} /* Fim fun��o: GRA  &Retornar Numero de Vertices*/


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
	//Assertivas
	if(pGrafo==NULL || pDado==NULL)
		return GRA_CondRetParametroIncorreto;
	if (pGrafo->pElemCorr == NULL)
		return GRA_CondRetGrafoVazio;
	CondRetGra=GRA_NumArestas(pGrafo,&numAr);
	if(numAr==0)
		return GRA_CondRetNumArestasZero;
	for(i=0;i<numAr;i++)
	{
		CondRetLis=LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&Aresta);
		if(CondRetLis!=LIS_CondRetOK)
			return GRA_CondRetParametroIncorreto;
		pDado[i]=Aresta->Ident;
		LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);
	}
	CondRetLis=LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	if(CondRetLis!=LIS_CondRetOK)
		return GRA_CondRetRetornoLisIncorreto;
	return GRA_CondRetOK;
	
}/* Fim fun��o: GRA  &RetornarIndicesAresta*/
		
		
/*****  C�digo das fun��es encapsuladas no m�dulo  *****/
/***********************************************************************
*
*  $FC Fun��o: GRA  -Criar o vertice da lista Vertice
*
***********************************************************************/

GRA_tpVertice *CriarVertice(void * pValor , int tam)
{
	GRA_tpVertice * pVert;

	pVert = (GRA_tpVertice *)malloc(sizeof(GRA_tpVertice));
	if (pVert == NULL)
	{
		return NULL;
	} /* if */

	pVert->Ident = tam+1;
	pVert->pValor = pValor;
	if (LIS_CriarLista(NULL, &(pVert->pLisAresta)) != LIS_CondRetOK)  
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