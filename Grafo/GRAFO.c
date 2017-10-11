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
GRA_tpNoVertices *CriarSubVertice(GRA_tpGrafo *pGrafo);

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

  /***********************************************************************
  *  $FC Função: GRA  &Destruir grafo
  *  ****/

GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo pGrafo) {
	GRA_tpNoVertices *verts;
	GRA_tpVertice *vert;

	if (LIS_IrInicioLista(pGrafo->pVerticesGrafo) != LIS_CondRetOK)
		return GRA_CondRetOK;

	do {
		if (LIS_ObterValor(pGrafo->pVerticesGrafo, &verts) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;

		if (LIS_ObterValor(verts->pLisVertice, &vert) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;

		GRA_ExcluirVertice(vert);

		LIS_DestruirLista(verts->pLisVertice);

		free(verts);

	} while (LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, 1) != LIS_CondRetFimLista);

	LIS_DestruirLista(pGrafo->pVerticesGrafo);

	free(pGrafo);

	return GRA_CondRetOK;
}/* Fim função: GRA  &Destruir grafo*/

 /***************************************************************************
 *
 *  Função: Função: GRA  &Ir para o Vértice
 *  ****/

GRA_tpCondRet GRA_IrVertice(GRA_tpGrafo *pGrafo, int numVert) {
	LIS_tppLista *verts;
	GRA_tpVertice *vert;

	if (LIS_IrInicioLista(pGrafo->pVerticesGrafo) != LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	if (LIS_ObterValor(pGrafo->pVerticesGrafo, &verts) != LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	while (vert->ident != numVert) {
		if (LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, 1) == LIS_CondRetFimLista)
			return GRA_CondRetNaoAchouVertice;

		if (LIS_ObterValor(pGrafo->pVerticesGrafo, &verts) != LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
	}

	if (LIS_IrInicioLista(verts) != LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	if (LIS_ObterValor(verts, &vert) != LIS_CondRetOK)
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
	GRA_tpVertices * pVerts;
	GRA_tpVertice * pVert;
	GRA_tpVertice*  pRet;
	int tam;
	LIS_tpCondRet CondRet;

	if(pGrafo == NULL)
		return GRA_CondRetParametroIncorreto;

	CondRet=LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;

	/* Criar elemento a inserir apos */
	pVerts = CriarSubVertice(pGrafo);
	if (pVerts == NULL)
	{
		return GRA_CondRetFaltouMemoria;
	} /* if */

	pVert = CriarVertice(pGrafo, pValor,tam);
	if (pVert == NULL)
	{
		return GRA_CondRetFaltouMemoria;
	} /* if */

	CondRet=IrFinalLista(pGrafo->pVerticesGrafo);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	if (LIS_InserirElementoApos(pGrafo->pVerticesGrafo,(void*)pVerts) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;

	if (LIS_InserirElementoApos(pVerts,(void*)pVert) == LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;

	CondRet=LIS_ObterValor(pVerts,(void**)&pRet);
	if(CondRet!=LIS_CondRetOK)
		return GRA_CondRetRetornoIncorreto;
	pGrafo->pElemCorr=pRet;
	return GRA_CondRetOK;

} /* Fim função: GRA  &Inserir vértice */

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

	int tam;
	GRA_tpVertice* pCorrenteAnterior=pGrafo->pElemCorr; 
	//GRA_tpNoVertices* pVertLisCorrenteAn;
	GRA_tpVertice* pVert1;
	GRA_tpVertice* pVert2;
	LIS_tpCondRet CondRet;
	if(pGrafo == NULL)
		return GRA_CondRetParametroIncorreto;
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
	if(pGrafo == NULL)
		return GRA_CondRetParametroIncorreto;
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
	LIS_tpCondRet CondRetLis,CondRetAv=LIS_CondRetOK;
	GRA_tpCondRet CondRetGra;  
	if(pGrafo == NULL)
		return GRA_CondRetParametroIncorreto;
	// dependendo de ir vertice,isso e denecessario
	CondRetLis=LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	if(tam==0) 
		return GRA_CondRetGrafoVazio;
	CondRetGra=GRA_ExisteAresta(pGrafo,numVert1,numVert2);
	if(CondRetGra==GRA_CondRetNaoAchouAresta)
		return GRA_CondRetNaoAchouAresta;
	//chamar funcao irvertice para o vertice 2
	while(CondRetAv!=LIS_CondRetFimLista)
	{
		CondRetLis=LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(CondRetLis!=LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
		if(pVerts->ident==numVert1)
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

	//chamar funcao irvertice para o vertice 1
	while(CondRetAv!=LIS_CondRetFimLista)
	{
		CondRetLis=LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(CondRetLis!=LIS_CondRetOK)
			return GRA_CondRetRetornoIncorreto;
		if(pVerts->ident==numVert1)
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
	pGrafo->pElemCorr=pCorrenteAnterior;
	return GRA_CondRetOK;


} /* Fim função: GRA  &Excluir Aresta */
/***************************************************************************
*
*  Função: GRA  &Excluir Vertice
*  ****/
// Pegar o valor a ser exluido passaer pelo vetor de arestas dele
GRA_tpCondRet GRA_ExcluirVertice(GRA_tpGrafo pGrafo, GRA_tpNoVertice * pVert)
{
	LIS_tpCondRet *CondRet;
	LIS_tpCondRet *CondRetExcluir;
	LIS_tpCondRet *CondRetPrimElem;
	LIS_tpCondRet *CondRetProxElem;
	LIS_tpCondRet *CondRetObterValor;
	LIS_tpCondRet *CondRetTamVert;
	GRA_tpCondRet *CondRetGraVert;
	GRA_tpCondRet *CondRetGraAres;
	GRA-tpCondRet *CondRetGraVertProx;
	int tamAres;
	int tamVert;
	CondRet = LIS_ObterTamanho(pVert->pLisAresta, &tamAres);
	if(CondRet!=LIS_CondRetOK){
		CondRetExcluir = LIS_ExcluirElemento(pVert);
		if(CondRetExcluir!=LIS_CondRetOK)
			return GRA_CondRetGrafoVazio;
		else {
			LiberarVertice(pVert, pGrafo);
			return GRA_CondRetOK;
		}
	} else {
		CondRetPrimElem = LIS_IrInicioLista(pVert->pLisAresta);
			if (CondRetPrimElem!=LIS_CondRetOK)
				return CondRetPrimElem;
			else {
				for(int i=0;i==tamAres;i+=1){	
					GRA_tpVertice *Aresta;
					CondRetObterValor = LIS_ObterValor(pVert->pLisAresta,(void**)&Aresta);
					if (CondRetObterValor!=LIS_CondRetOK){
						return CondRetObterValor;
					} else {
						CondRetGraVert = GRA_IrVertice(pGrafo,Aresta->ident); 
						if(CondRetGraVert!=GRA_CondRetOK)
							return CondRetVert
						else {
							CondRetGraAres = GRA_ExcluirAresta(pGrafo,pVert->ident,Aresta->ident);
							if (CondRetGraAres!=GRA_CondRetOK){
								return CondRetGraAres;
							} else {
								CondRetProxElem = LIS_AvancarElementoCorrente(pVert->pLisAresta,1);
								if (CondRetProxElem!=LIS_CondRetOK)
									return CondRetProxElem;
							}
						}
					}
				}
				LiberarVertice(pVert,pGrafo);
				CondRetGraVert = LIS_ObterTamanho(pGrafo->pVerticesGrafo, &tamVert);
				if (CondRetGraVert!=LIS_CondRetOK){
					return CondRetGraVert;
				} else {
					GRA_tpNoVertice * pVertProx = pVert;
					int pVertProxIdent = pVert->ident;
					for(int i=0;i==tamVert;i++){
						CondRetGraVertProx = GRA_IrVertice(pGrafo,pVertProxIdent+1);
						if (CondRetGraVertProx!=GRA_CondRetOK){
							return CondRetGraVertProx;
						} else {
							pVertProx = pGrafo->pElemCorr;
							pVertProxIdent = pVertProx->ident;
							pGrafo->pElemCorr->ident = ident - 1;
						}	
					}
				}
				
				return GRA_CondRetOK;
			}		
	}
	
	
} /* Fim função: GRA  &Excluir vértice */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: GRA  -Liberar evertice do grafo
*
***********************************************************************/

void LiberarVertice( GRA_tpNoVertice * pVert, GRA_tpGrafo * pGrafo)
   {

      if (( pGrafo->ExcluirValor != NULL ) && ( pVert->pValor != NULL)){ 
         pGrafo->ExcluirValor( pVert->pValor ) ;
      } /* if */

      free( pVert ) ;

   } /* Fim função: LIS  -Liberar elemento da lista */

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

	pVert->ident = tam+1;
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
LIS_tppLista* CriarSubVertice(GRA_tpGrafo *pGrafo, int tam){

	LIS_tppLista* pVerts;

	pVerts =(LIS_tppLista*)malloc(sizeof(LIS_tppLista));
	if (pVerts == NULL)
	{
		return NULL;
	} /* if */

	return pVerts;
}
