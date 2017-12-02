/***************************************************************************
*  $MCI Módulo de implementação: GRA  Grafo generico com cabeca
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  DI/PUC-Rio
*  Autores: Gabriel Busquim (gb), Michelle Santiago (ms), Renan Moreira (rm)
*
*  $HA Histórico de evolução:
*     Versão  Autor   	 Data     	Observações
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
#include   <malloc.h>
#include   "GRAFO.h"
#include   "LISTA.h"

#ifdef _DEBUG
	#include   "GENERICO.h"
	#include   "CONTA.h"
	#include   "CESPDIN.H"
#endif

/***** Definicao de tipos de dados *****/
#ifdef _DEBUG
	typedef enum
	{
		CED_ID_TIPO_VALOR_NULO ,

		GRA_TipoEspacoCabecaGrafo,

		GRA_TipoEspacoVerticeGrafo,

		CED_ID_TIPO_ILEGAL = 999 
	} CED_tpIdTipoEspaco ;
#endif


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

	#ifdef _DEBUG

		int NumArestas;
		/* Numero de arestas que o vertice possui*/

	#endif

} GRA_tpVertice;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça do grafo
*
***********************************************************************/

typedef struct GRA_tagGrafo {

	LIS_tppLista pVerticesGrafo;
	/* Ponteiro para a lista de vertices do grafo */

	GRA_tpVertice* pElemCorr;
	/* Ponteiro para o elemento corrente do grafo */

	void(*ExcluirValor) (void * pValor);
	/* Ponteiro para a função de destruição do valor contido em um elemento */

	#ifdef _DEBUG

		int NumVertices;
		/* Numero de vertices do grafo*/

	#endif

} GRA_tpGrafo;

/***** Protótipos das funções encapuladas no módulo *****/

static GRA_tpVertice *CriarVertice( void * pValor,int tam);
static void DestruirElemVertice(void *Elem);
static void DestruirElemVertices(void *Elem);
#if _DEBUG
	GRA_tpCondRet GRA_VerificarCabeça(GRA_tppGrafo pGrafo);
	GRA_tpCondRet GRA_VerificarElemento(GRA_tpVertice* pVert);
#endif


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: Função: GRA  &Criar grafo
*  ****/
GRA_tpCondRet GRA_CriarGrafo(void   ( * ExcluirValor ) ( void * pDado ), GRA_tppGrafo* GrafoRet) {
	
	GRA_tpGrafo *pGrafo;
	 #ifdef _DEBUG
        CNT_CONTAR("GRA_CriarGrafo");	 
     #endif
	pGrafo = (GRA_tpGrafo *)malloc(sizeof(GRA_tpGrafo));
	if (pGrafo == NULL)
	{
		*GrafoRet = NULL;
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_CriarGrafo: Faltou memoria para criar a cabeca do grafo" ) ;
		#endif
		return GRA_CondRetFaltouMemoria;
	}
	if (LIS_CriarLista(DestruirElemVertices, &(pGrafo->pVerticesGrafo)) == LIS_CondRetFaltouMemoria) {   
		*GrafoRet = NULL;
		free(pGrafo);
		return GRA_CondRetFaltouMemoria;
	}

	pGrafo->pElemCorr = NULL;

	pGrafo->ExcluirValor = ExcluirValor;

	*GrafoRet = pGrafo;

	#ifdef _DEBUG

         CED_DefinirTipoEspaco( pGrafo , GRA_TipoEspacoCabecaGrafo ) ;
		 pGrafo->NumVertices=0;
		 CNT_CONTAR("GRA_CriarGrafo: O grafo foi criado" ) ;

	#endif


	return GRA_CondRetOK;

} /* Fim função: GRA  &Criar grafo */


/***********************************************************************
*
*  $FC Função: GRA  &Destruir grafo
*  ****/

GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo pGrafo) 
{ 
	
	LIS_tppLista verts;
	GRA_tpVertice *vert;
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_DestruirGrafo" ) ;
    #endif
	//Assertiva
	if(pGrafo==NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_DestruirGrafo: Grafo e NULL" ) ;
		#endif
		return GRA_CondRetParametroIncorreto;
	}
	if(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,0)!=LIS_CondRetListaVazia)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_DestruirGrafo: Chamando funcao de exclusao para cada vertice" ) ;
		#endif
		LIS_IrInicioLista(pGrafo->pVerticesGrafo);
		do
		{
			LIS_ObterValor(pGrafo->pVerticesGrafo,(void**)&verts);

			LIS_ObterValor(verts,(void**)&vert);
			if (( pGrafo->ExcluirValor != NULL ))
			{
				pGrafo->ExcluirValor(vert->pValor);
			} 

		}
		while(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,1)!=LIS_CondRetFimLista);
	}
    LIS_DestruirLista(pGrafo->pVerticesGrafo);
	pGrafo->pElemCorr=NULL;
	pGrafo->pVerticesGrafo=NULL;
	free(pGrafo);
	#ifdef _DEBUG
			CNT_CONTAR( "GRA_DestruirGrafo: Grafo foi destruido" ) ;
	#endif
	return GRA_CondRetOK;

}/* Fim função: GRA  &Destruir grafo*/


/***************************************************************************
*
*  Função: Função: GRA  &Ir para o Vértice
*  ****/

GRA_tpCondRet GRA_IrVertice(GRA_tppGrafo pGrafo, int numVert) {

	LIS_tppLista verts;
	GRA_tpVertice* vert;
	int tam,contador=0;
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_IrVertice" ) ;
    #endif
	//Assertiva
	if(pGrafo==NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_IrVertice: Grafo e NULL" ) ;
		#endif
		return GRA_CondRetParametroIncorreto;
	}
	LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	if(tam==0)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_IrVertice: Grafo esta vazio" ) ;
		#endif
		return GRA_CondRetGrafoVazio;
	}
	while(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, -1)!= LIS_CondRetFimLista)
	{
		contador++;
	}

	LIS_ObterValor(pGrafo->pVerticesGrafo,(void**) &verts);

	LIS_ObterValor(verts,(void**) &vert);

	while (vert->Ident != numVert) {
		if (LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, 1) == LIS_CondRetFimLista)
		{
			//nao encontrou o vertice passado como parametro->colocar corrente na posicao original
			#ifdef _DEBUG
				CNT_CONTAR( "GRA_IrVertice: Vertice nao foi encontrado" ) ;
			#endif
			LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, (tam-1-contador)*-1);
			LIS_ObterValor(pGrafo->pVerticesGrafo,(void**) &verts);
			LIS_ObterValor(verts,(void**) &vert);
			pGrafo->pElemCorr=vert;
			return GRA_CondRetNaoAchouVertice;
		}

		LIS_ObterValor(pGrafo->pVerticesGrafo,(void**) &verts);
		LIS_ObterValor(verts,(void**) &vert);
	}

	LIS_ObterValor(verts, (void**)&vert);

	#ifdef _DEBUG
			CNT_CONTAR( "GRA_IrVertice: Colocando vertice como corrente" ) ;
	#endif
	pGrafo->pElemCorr = vert;
	return GRA_CondRetOK;

}/* Fim função: GRA  &Ir para o Vértice*/


/***************************************************************************
*
*  Função:  &Retorna Identificador
*  ****/

GRA_tpCondRet GRA_RetornaIdentificador(GRA_tppGrafo pGrafo, int* numIdent) 
{
	int tam;
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_RetornaIdentificador" ) ;
    #endif
	//Assertiva
	if(pGrafo==NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_RetornaIdentificador: Grafo e NULL" ) ;
		#endif
		return GRA_CondRetParametroIncorreto;
	}
	LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
	//Assertiva
	if(tam==0)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_RetornaIdentificador: Grafo esta vazio" ) ;
		#endif
		return GRA_CondRetGrafoVazio;
	}
	#ifdef _DEBUG
		CNT_CONTAR( "GRA_RetornaIdentificador: Obtendo identificador" ) ;
	#endif
	*numIdent=pGrafo->pElemCorr->Ident;
	return GRA_CondRetOK;

}/* Fim função: GRA  &Retorna Identificador*/


/***************************************************************************
*
*  Função: GRA  &Obter referência para o valor contido no vértice
*  ****/

GRA_tpCondRet GRA_ObterValor(GRA_tppGrafo pGrafo, void** pValorRet)
{
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_ObterValor" ) ;
    #endif
	//Assertiva
	if(pGrafo == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_ObterValor: Grafo e NULL" ) ;
		#endif
		return GRA_CondRetParametroIncorreto;
	}
	//Assertiva
	if (pGrafo->pElemCorr == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_ObterValor: Grafo esta vazio" ) ;
		#endif
		*pValorRet = NULL;
		return GRA_CondRetGrafoVazio;
	} /* if */
	#ifdef _DEBUG
		CNT_CONTAR( "GRA_ObterValor: Obtendo valor do elemento" ) ;
	#endif
	*pValorRet = pGrafo->pElemCorr->pValor;
	return GRA_CondRetOK;

} /* Fim função: GRA  &Obter referência para o valor contido no vértice */


/***************************************************************************
*
*  Função: GRA  &Inserir vértice
*  ****/

GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo, void * pValor)
{
	LIS_tppLista  pLIS_Vert;
	LIS_tppLista  pLIS_Verts;
	GRA_tpVertice * pVert;
	GRA_tpVertice * pRet;
	int tam;

	#ifdef _DEBUG
         CNT_CONTAR( "GRA_InserirVertice" ) ;
    #endif
	//Assertiva
	if(pGrafo == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_InserirVertice: Grafo e NULL" ) ;
		#endif
		return GRA_CondRetParametroIncorreto;
	}
	LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);


	if (LIS_CriarLista(NULL, &(pLIS_Vert)) == LIS_CondRetFaltouMemoria) 
	{
		return GRA_CondRetFaltouMemoria;
	}

	pVert = CriarVertice(pValor,tam);
	if (pVert == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_InserirVertice: Faltou memoria ao criar vertice" ) ;
		#endif
		return GRA_CondRetFaltouMemoria;
	} 

	//Cada elemento da lista vertices deve possuir exatamente uma referencia para um elemento da lista Vertice
	pLIS_Verts=pLIS_Vert;

	LIS_IrFinalLista(pGrafo->pVerticesGrafo);

	if (LIS_InserirElementoApos(pGrafo->pVerticesGrafo,(void*)pLIS_Verts) == LIS_CondRetFaltouMemoria)
	{
		return GRA_CondRetFaltouMemoria;
	}
	if (LIS_InserirElementoApos(pLIS_Vert,(void*)pVert) == LIS_CondRetFaltouMemoria)
	{
		return GRA_CondRetFaltouMemoria;
	}

	LIS_ObterValor(pLIS_Vert,(void**)&pRet);

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_InserirVertice: Atualizando elemento corrente" ) ;
	#endif
	pGrafo->pElemCorr=pRet;
	#ifdef _DEBUG

		pGrafo->NumVertices+=1;

	#endif

	return GRA_CondRetOK;

}/* Fim função: GRA  &Inserir vértice */


/***************************************************************************
*
*  Função: GRA  &Excluir Vertice
*  ****/

GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo)
{
	
	GRA_tpVertice* pVert;
	GRA_tpVertice* Aresta;
	GRA_tpVertice* vertice;
	LIS_tppLista vertices;
	int tam, identCorrente, i;
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_ExcluirVertice" ) ;
    #endif
	//Assertiva
	if (pGrafo == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluirVertice: Grafo e NULL" ) ;
		#endif
		return GRA_CondRetParametroIncorreto;
	}

	//Assertiva
	if (pGrafo->pElemCorr == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluirVertice: Grafo e vazio" ) ;
		#endif
		return GRA_CondRetGrafoVazio;
	}
	pVert = pGrafo->pElemCorr;
	identCorrente = pVert->Ident;
	LIS_ObterTamanho(pVert->pLisAresta, &tam);

	if (tam != 0)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluirVertice: Apagando elementos da lista de Arestas" ) ;
		#endif
		//Apagando cada elemento da lista de arestas
		for (i = 0; i<tam; i++)
		{
			LIS_ObterValor(pVert->pLisAresta, (void**)&Aresta);
			GRA_ExcluirAresta(pGrafo, pVert->Ident, Aresta->Ident);
			LIS_AvancarElementoCorrente(pVert->pLisAresta, 1);
		}

	}
	if (( pGrafo->ExcluirValor != NULL ))
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluirVertice: Chamando funcao de exclusao para o vertice" ) ;
		#endif
		pGrafo->ExcluirValor(pVert->pValor);
	}

	GRA_IrVertice(pGrafo,identCorrente);

	//decrescendo de 1 cada identificador maior do que o identificador do vertice a ser excluido
    LIS_ObterTamanho(pGrafo->pVerticesGrafo, &tam);
	for (i = 0; i<tam - identCorrente; i++)
	{

		LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, 1);
		LIS_ObterValor(pGrafo->pVerticesGrafo, (void**)&vertices);
			
		LIS_ObterValor(vertices, (void**)&vertice);
		vertice->Ident = vertice->Ident - 1;
	}
	GRA_IrVertice(pGrafo, identCorrente);

	LIS_ExcluirElemento(pGrafo->pVerticesGrafo);


	#ifdef _DEBUG
		pGrafo->NumVertices-=1;
	#endif

	if (LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo, 0) == LIS_CondRetListaVazia)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluirVertice: Grafo e vazio apos a exclusao" ) ;
		#endif
		pGrafo->pElemCorr = NULL;
		return GRA_CondRetOK;
	}
	else
	{
		LIS_ObterValor(pGrafo->pVerticesGrafo, (void**)&vertices);
		LIS_ObterValor(vertices, (void**)&vertice);
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluirVertice: Atualizando elemento corrente" ) ;
		#endif
		pGrafo->pElemCorr = vertice;
		return GRA_CondRetOK;
	}
}/*  Fim função: GRA  &Excluir Vertice */


/***************************************************************************
*
*  Função: GRA  &Criar Aresta
*  ****/

GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2)
{
	int IdAnterior;
	GRA_tpVertice* pVert1;
	GRA_tpVertice* pVert2;
	GRA_tpCondRet CondRetGra;
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_CriarAresta" ) ;
    #endif
	if(numVert1==numVert2)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_CriarAresta: Falha ao criar aresta de um vertice para ele mesmo" ) ;
		#endif
		return GRA_CondRetArestaParaSiMesmo;
	}
	
	CondRetGra=GRA_ExisteAresta(pGrafo,numVert1,numVert2);
	//ASSERTIVAS:
	if(CondRetGra==GRA_CondRetParametroIncorreto)
	{
		#ifdef _DEBUG
			CNT_CONTAR("GRA_CriarAresta: Grafo e NULL" ) ;
		#endif
		return GRA_CondRetParametroIncorreto;
	}

	else if(CondRetGra==GRA_CondRetGrafoVazio)
	{
		#ifdef _DEBUG
			CNT_CONTAR("GRA_CriarAresta: Grafo e vazio" ) ;
		#endif
		return GRA_CondRetGrafoVazio;	
	}


	else if(CondRetGra==GRA_CondRetNaoAchouVertice)
	{
		#ifdef _DEBUG
			CNT_CONTAR("GRA_CriarAresta: Vertice nao foi encontrado" ) ;
		#endif
		return GRA_CondRetNaoAchouVertice;	
	}
	else if(CondRetGra==GRA_CondRetOK)
	{
		#ifdef _DEBUG
			CNT_CONTAR("GRA_CriarAresta: Aresta ja existe" ) ;
		#endif
		return GRA_CondRetArestaJaExiste;
	}

	IdAnterior=pGrafo->pElemCorr->Ident;
	GRA_IrVertice(pGrafo,numVert1);


	pVert1=pGrafo->pElemCorr;
	GRA_IrVertice(pGrafo,numVert2);


	pVert2=pGrafo->pElemCorr;
	if (LIS_InserirElementoApos(pGrafo->pElemCorr->pLisAresta,(void*)pVert1) == LIS_CondRetFaltouMemoria)
	{
		return GRA_CondRetFaltouMemoria;
	}

	#ifdef _DEBUG

		pVert2->NumArestas+=1;

	#endif

	LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);

	GRA_IrVertice(pGrafo,numVert1);

	if (LIS_InserirElementoApos(pGrafo->pElemCorr->pLisAresta,(void*)pVert2) == LIS_CondRetFaltouMemoria)
	{
		return GRA_CondRetFaltouMemoria;
	}

	#ifdef _DEBUG

		pVert1->NumArestas+=1;

	#endif

	LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);

	#ifdef _DEBUG
		CNT_CONTAR("GRA_CriarAresta:Restaurando corrente anterior" ) ;
	#endif
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
	LIS_tpCondRet CondRetAv=LIS_CondRetOK;
	GRA_tpCondRet CondRetGra;
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_ExisteAresta" ) ;
    #endif
	//ASSERTIVAS

	if(pGrafo==NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR("GRA_ExisteAresta: Grafo e NULL" ) ;
		#endif
		return GRA_CondRetParametroIncorreto;
	}
	if(LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,0)==LIS_CondRetListaVazia)
	{
		#ifdef _DEBUG
			CNT_CONTAR("GRA_ExisteAresta: Grafo e vazio" ) ;
		#endif
		return GRA_CondRetGrafoVazio;
	}
	IdAnterior=pGrafo->pElemCorr->Ident;
	CondRetGra=GRA_IrVertice(pGrafo,numVert1);
	if(CondRetGra==GRA_CondRetNaoAchouVertice)
	{
		#ifdef _DEBUG
			CNT_CONTAR("GRA_ExisteAresta: Nao achou o primeiro vertice" ) ;
		#endif
		return GRA_CondRetNaoAchouVertice;
	}
	CondRetGra=GRA_IrVertice(pGrafo,numVert2);
	if(CondRetGra==GRA_CondRetNaoAchouVertice)
	{
		#ifdef _DEBUG
			CNT_CONTAR("GRA_ExisteAresta: Nao achou o segundo vertice" ) ;
		#endif
		GRA_IrVertice(pGrafo,IdAnterior);
		return GRA_CondRetNaoAchouVertice;
	}

	LIS_ObterTamanho(pGrafo->pElemCorr->pLisAresta,&tam);

	if(tam==0)
	{
		#ifdef _DEBUG
			CNT_CONTAR("GRA_ExisteAresta: Vertice nao possui aresta" ) ;
		#endif
		GRA_IrVertice(pGrafo,IdAnterior);
		return GRA_CondRetNaoAchouAresta;
	}
	while(CondRetAv!=LIS_CondRetFimLista)
	{
		LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(pVerts->Ident==numVert1)
		{
			#ifdef _DEBUG
				CNT_CONTAR("GRA_ExisteAresta: Aresta foi encontrada" ) ;
			#endif
			LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
			GRA_IrVertice(pGrafo,IdAnterior);
			return GRA_CondRetOK;
		}
		CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);
	}
	LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	#ifdef _DEBUG
			CNT_CONTAR("GRA_ExisteAresta: Aresta nao foi encontrada" ) ;
	#endif
	GRA_IrVertice(pGrafo,IdAnterior);

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
	LIS_tpCondRet CondRetAv=LIS_CondRetOK;
	GRA_tpCondRet CondRetGra;  
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_ExcluirAresta" ) ;
    #endif
	CondRetGra=GRA_ExisteAresta(pGrafo,numVert1,numVert2);

	//Assertivas
	if(CondRetGra==GRA_CondRetParametroIncorreto)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluirAresta : Grafo e NULL" ) ;
		#endif
		return GRA_CondRetParametroIncorreto;
	}

	else if(CondRetGra==GRA_CondRetGrafoVazio)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluirAresta : Grafo e vazio" ) ;
		#endif
		return GRA_CondRetGrafoVazio;	
	}

	else if(CondRetGra==GRA_CondRetNaoAchouVertice)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluirAresta : Vertice nao foi encontrado" ) ;
		#endif
		return GRA_CondRetNaoAchouVertice;	
	}
		else if(CondRetGra==GRA_CondRetNaoAchouAresta)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluirAresta : Aresta nao foi encontrada" ) ;
		#endif
		return GRA_CondRetNaoAchouAresta;
	}

	IdAnterior=pGrafo->pElemCorr->Ident;
	GRA_IrVertice(pGrafo,numVert1);

	while(CondRetAv!=LIS_CondRetFimLista)
	{
		LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(pVerts->Ident==numVert2)
		{
			#ifdef _DEBUG
				CNT_CONTAR( "GRA_ExcluirAresta : Aresta foi removida da lista do primeiro vertice" ) ;
			#endif
			LIS_ExcluirElemento(pGrafo->pElemCorr->pLisAresta);
			LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
			#ifdef _DEBUG

				pVerts->NumArestas-=1;

			#endif
			break;
		}
		CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);

	}

	GRA_IrVertice(pGrafo,numVert2);

	while(CondRetAv!=LIS_CondRetFimLista)
	{
		LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(pVerts->Ident==numVert1)
		{
			#ifdef _DEBUG
				CNT_CONTAR( "GRA_ExcluirAresta : Aresta foi removida da lista do segundo vertice" ) ;
			#endif
			LIS_ExcluirElemento(pGrafo->pElemCorr->pLisAresta);
			LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);

			#ifdef _DEBUG

				pVerts->NumArestas-=1;

			#endif
			break;
		}
		CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);
	}
	#ifdef _DEBUG
		CNT_CONTAR("GRA_ExcluirAresta:Restaurando corrente anterior" ) ;
	#endif
	GRA_IrVertice(pGrafo,IdAnterior);
	return GRA_CondRetOK;

}/*  Fim função: GRA  &Excluir Aresta */


/***************************************************************************
*
*  Função: GRA  &Retornar Numero de Arestas
*  ****/

GRA_tpCondRet GRA_NumArestas(GRA_tppGrafo pGrafo, int *pNumArestas)
{
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_NumArestas" ) ;
    #endif
	//Assertivas
	if (pGrafo == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_NumArestas: Grafo e NULL" ) ;
		#endif
		return GRA_CondRetParametroIncorreto;
	}
	if (pGrafo->pElemCorr == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_NumArestas: Grafo e vazio" ) ;
		#endif
		return GRA_CondRetGrafoVazio;
	}
	#ifdef _DEBUG
		CNT_CONTAR( "GRA_NumArestas: Obtendo numero de arestas" ) ;
	#endif
	LIS_ObterTamanho(pGrafo->pElemCorr->pLisAresta, pNumArestas);

	return GRA_CondRetOK;

}/* Fim função: GRA  &Retornar Numero de Arestas*/


/***************************************************************************
*
*  Função: GRA  &Retornar Numero de Vertices
*  ****/

GRA_tpCondRet GRA_NumVertices(GRA_tppGrafo pGrafo,int *pNumVerts)
{
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_NumVertices" ) ;
    #endif
	//Assertivas
	if(pGrafo==NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_NumVertices: Grafo e NULL" ) ;
		#endif
		return GRA_CondRetParametroIncorreto;
	}
	#ifdef _DEBUG
		CNT_CONTAR( "GRA_NumVertices: Obtendo numero de vertices" ) ;
	#endif
	LIS_ObterTamanho(pGrafo->pVerticesGrafo,pNumVerts);
	return GRA_CondRetOK;

} /* Fim função: GRA  &Retornar Numero de Vertices*/


/***************************************************************************
*
*  Função: GRA  &RetornarIndicesAresta
*  ****/

GRA_tpCondRet GRA_RetornaIndiceAresta(GRA_tppGrafo pGrafo,int* pDado)
{
	GRA_tpVertice* Aresta; 
	GRA_tpCondRet CondRetGra;
	int numAr,i;
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_RetornaIndiceAresta" ) ;
    #endif
	//Assertivas
	if(pGrafo==NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_RetornaIndiceAresta: Grafo e NULL" ) ;
		#endif
		return GRA_CondRetParametroIncorreto;
	}
	if (pGrafo->pElemCorr == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_RetornaIndiceAresta: Grafo e vazio" ) ;
		#endif
		return GRA_CondRetGrafoVazio;
	}
	CondRetGra=GRA_NumArestas(pGrafo,&numAr);
	if(numAr==0)
	{
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_RetornaIndiceAresta: Vertice nao possui aresta" ) ;
		#endif
		return GRA_CondRetNumArestasZero;
	}
	for(i=0;i<numAr;i++)
	{
		LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&Aresta);
		pDado[i]=Aresta->Ident;
		LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);
	}
	#ifdef _DEBUG
			CNT_CONTAR( "GRA_RetornaIndiceAresta: Movendo corrente da lista de arestas para posicao inicial" ) ;
	#endif
	LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	return GRA_CondRetOK;

}/* Fim função: GRA  &RetornarIndicesAresta*/


/*****  Código das funções encapsuladas no módulo  *****/
/***********************************************************************
*
*  $FC Função: GRA  -Criar o vertice da lista Vertice
*
***********************************************************************/

GRA_tpVertice *CriarVertice(void * pValor , int tam)
{
	GRA_tpVertice * pVert;
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_CriarVertice" ) ;
    #endif
	pVert = (GRA_tpVertice *)malloc(sizeof(GRA_tpVertice));
	if (pVert == NULL)
	{
		#ifdef _DEBUG
			 CNT_CONTAR( "GRA_CriarVertice: Faltou memoria ao criar o vertice" ) ;
		#endif
		return NULL;
	} /* if */

	pVert->Ident = tam+1;
	pVert->pValor = pValor;
	if (LIS_CriarLista(NULL, &(pVert->pLisAresta)) != LIS_CondRetOK)
	{
		free(pVert);
		return NULL;
	}

	#ifdef _DEBUG
		 CNT_CONTAR( "GRA_CriarVertice: Vertice criado com sucesso" ) ;
		 pVert->NumArestas=0;
         CED_DefinirTipoEspaco( pVert , GRA_TipoEspacoVerticeGrafo ) ;
       
	#endif

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
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_DestruirElemVertices" ) ;
    #endif
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
	#ifdef _DEBUG
         CNT_CONTAR( "GRA_DestruirElemVertice" ) ;
    #endif
	LIS_ObterValor(Lis,(void**)&vert);
	LIS_DestruirLista(vert->pLisAresta);
	free(vert);
	LIS_DestruirLista(Lis);
}

#ifdef _DEBUG
	/*GRA_tpCondRet GRA_VerificarEstrutura(GRA_tppGrafo pGrafo)
	{
		int IdAnterior;
		int tam;
		GRA_tpCondRet retorno;
		LIS_tppLista verts;
		GRA_tpVertice* vert;
		LIS_tpCondRet CondRetAv=LIS_CondRetOK;
		IdAnterior=pGrafo->pElemCorr->Ident;
		retorno = GRA_VerificarCabeça(pGrafo);
		if(retorno==GRA_CondRetParametroIncorreto)
			return GRA_CondRetParametroIncorreto;
		else if(retorno==GRA_CondRetErroEstrutural)
			return GRA_CondRetErroEstrutural;
		LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
		if(tam==0)
		{
			return GRA_CondRetOK;
		}
		LIS_IrInicioLista(pGrafo->pVerticesGrafo);
		while(CondRetAv!=LIS_CondRetFimLista)
		{
			LIS_ObterValor(pGrafo->pVerticesGrafo,(void**) &verts);
			LIS_ObterValor(verts,(void**) &vert);
			if(vert==NULL)
			{
				GRA_IrVertice(pGrafo,IdAnterior);
				return GRA_CondRetErroEstrutural;
			}
			retorno = GRA_VerificarElemento(vert);
			else if(retorno==GRA_CondRetErroEstrutural)
			{
				GRA_IrVertice(pGrafo,IdAnterior);
				return GRA_CondRetErroEstrutural;
			}
			CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,1);	
		}
		GRA_IrVertice(pGrafo,IdAnterior);
		return GRA_CondRetOK;
	}
#endif

#ifdef _DEBUG
	GRA_tpCondRet GRA_VerificarCabeça(GRA_tppGrafo pGrafo)
	{
		int numVerts;
		if(pGrafo==NULL) 
			return GRA_CondRetParametroIncorreto;
		if(pGrafo->pElemCorr==NULL && pGrafo->NumVertices!=0)
			return GRA_CondRetErroEstrutural;
		if(pGrafo->pVerticesGrafo==NULL)
			return GRA_CondRetErroEstrutural;
		LIS_ObterTamanho(pGrafo->pVerticesGrafo,&numVerts);
		if(numVerts !=pGrafo->NumVertices)
			return GRA_CondRetErroEstrutural;
		if(CED_ObterTipo(pGrafo)!= GRA_TipoEspacoCabecaGrafo)
			return GRA_CondRetErroEstrutural;
		return GRA_CondRetOK;
	}
#endif



#ifdef _DEBUG
	GRA_tpCondRet GRA_VerificarElemento(GRA_tpVertice* pVert)
	{
		int numArestas,IdentViz,IdentAtual;
		GRA_tpVertice* pVertViz;
		LIS_tpCondRet CondRetAv=LIS_CondRetOK;
		if(CED_ObterTipo(pVert)!= GRA_TipoEspacoVerticeGrafo)
			return CondRet_ErroEstrutural;
		if(pVert->pLisAresta==NULL) 
			return CondRet_ErroEstrutural;
		LIS_ObterTamanho(pGrafo->pLisAresta,&numArestas);
		if(numVerts !=pGrafo->NumArestas)
			return GRA_CondRetErroEstrutural;
		if(numArestas==0)
			return GRA_CondRetOK;
		IdentAtual=pVert->Ident;
		LIS_IrInicioLista(pGrafo->pLisAresta);
		while(CondRetAv!=LIS_CondRetFimLista)
		{
			LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVertViz);
			if(CED_ObterTipo(pVertViz)!= GRA_TipoEspacoVerticeGrafo)
				return CondRet_ErroEstrutural;
			IdentViz=pVertViz->Ident;
			if(GRA_ExisteAresta(pGrafo,IdentAtual,IdentViz)!=GRA_CondRetOK)
				return CondRet_ErroEstrutural
			CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pVerticesGrafo,1);
		}
		return GRA_CondRetOK;
}
*/
#endif