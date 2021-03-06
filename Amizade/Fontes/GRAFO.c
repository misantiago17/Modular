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

		GRA_TipoEspacoVerticeGrafo

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

	#ifdef _DEBUG

		int NumVertices;
		/* Numero de vertices do grafo*/

	#endif

} GRA_tpGrafo;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static GRA_tpVertice *CriarVertice( void * pValor,int tam);
static void DestruirElemVertice(void *Elem);
static void DestruirElemVertices(void *Elem);
#if _DEBUG
	GRA_tpCondRet GRA_VerificarCabeca(void* pGrafo);
	GRA_tpCondRet GRA_VerificarElemento(GRA_tppGrafo pGrafo,void* Vert);
	GRA_tpCondRet GRA_TratarVerticeSemAresta(GRA_tppGrafo pGrafo,int identAtual,int identVizinho);
#endif


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: Fun��o: GRA  &Criar grafo
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

} /* Fim fun��o: GRA  &Criar grafo */


/***********************************************************************
*
*  $FC Fun��o: GRA  &Destruir grafo
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

}/* Fim fun��o: GRA  &Destruir grafo*/


/***************************************************************************
*
*  Fun��o: Fun��o: GRA  &Ir para o V�rtice
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

}/* Fim fun��o: GRA  &Ir para o V�rtice*/


/***************************************************************************
*
*  Fun��o:  &Retorna Identificador
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

}/* Fim fun��o: GRA  &Retorna Identificador*/


/***************************************************************************
*
*  Fun��o: GRA  &Obter refer�ncia para o valor contido no v�rtice
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

}/* Fim fun��o: GRA  &Inserir v�rtice */


/***************************************************************************
*
*  Fun��o: GRA  &Excluir Vertice
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

} /* Fim fun��o: GRA  &Criar Aresta */

/***************************************************************************
*
*  Fun��o: GRA  &Existe Aresta
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
	LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
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
	//LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	#ifdef _DEBUG
			CNT_CONTAR("GRA_ExisteAresta: Aresta nao foi encontrada" ) ;
	#endif
	GRA_IrVertice(pGrafo,IdAnterior);
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
	LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	while(CondRetAv!=LIS_CondRetFimLista)
	{
		LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
		if(pVerts->Ident==numVert2)
		{
			#ifdef _DEBUG
				CNT_CONTAR( "GRA_ExcluirAresta : Aresta foi removida da lista do primeiro vertice" ) ;
			#endif
			LIS_ExcluirElemento(pGrafo->pElemCorr->pLisAresta);
			#ifdef _DEBUG

				pVerts->NumArestas-=1;

			#endif
			break;
		}
		CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);

	}

	GRA_IrVertice(pGrafo,numVert2);
	LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
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

}/*  Fim fun��o: GRA  &Excluir Aresta */


/***************************************************************************
*
*  Fun��o: GRA  &Retornar Numero de Arestas
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

}/* Fim fun��o: GRA  &Retornar Numero de Arestas*/


/***************************************************************************
*
*  Fun��o: GRA  &Retornar Numero de Vertices
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

} /* Fim fun��o: GRA  &Retornar Numero de Vertices*/


/***************************************************************************
*
*  Fun��o: GRA  &RetornarIndicesAresta
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
	LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
	for(i=0;i<numAr;i++)
	{
		LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&Aresta);
		pDado[i]=Aresta->Ident;
		LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);
	}
	#ifdef _DEBUG
			CNT_CONTAR( "GRA_RetornaIndiceAresta: Movendo corrente da lista de arestas para posicao inicial" ) ;
	#endif
	return GRA_CondRetOK;

}/* Fim fun��o: GRA  &RetornarIndicesAresta*/

/***************************************************************************
*
*  Fun��o: GRA  &Verificar Estrutura do Grafo
*  ****/

#ifdef _DEBUG
	GRA_tpCondRet GRA_VerificarEstrutura(void* Gra)
	{
		
		int IdAnterior;
		int tam,id;
		GRA_tpCondRet retorno;
		LIS_tppLista verts;
		GRA_tpVertice* vert;
		GRA_tppGrafo pGrafo;
		GRA_tpCondRet IrVert=GRA_CondRetOK;
		CNT_CONTAR( "GRA_VerificarEstrutura" ) ;
		retorno = GRA_VerificarCabeca(Gra);
		if(retorno==GRA_CondRetErroEstrutural)
		{
			CNT_CONTAR( "GRA_VerificarEstrutura: Erro estrutural na cabeca do grafo" ) ;
			return GRA_CondRetErroEstrutural;
		}
		CED_MarcarEspacoAtivo(Gra);
		pGrafo=(GRA_tppGrafo)Gra;
		LIS_ObterTamanho(pGrafo->pVerticesGrafo,&tam);
		if(tam==0)
		{
			CNT_CONTAR( "GRA_VerificarEstrutura: Grafo nao possui vertices" ) ;
			return GRA_CondRetOK;
		}
		IdAnterior=pGrafo->pElemCorr->Ident;
		GRA_IrVertice(pGrafo,1);
		while(IrVert!=GRA_CondRetNaoAchouVertice)
		{
			LIS_ObterValor(pGrafo->pVerticesGrafo,(void**) &verts);
			LIS_ObterValor(verts,(void**) &vert);
			retorno = GRA_VerificarElemento(pGrafo,(void*)vert);
			if(retorno==GRA_CondRetErroEstrutural)
			{
				CNT_CONTAR( "GRA_VerificarEstrutura: Erro estrutural no vertice" ) ;
				GRA_IrVertice(pGrafo,IdAnterior);
				return GRA_CondRetErroEstrutural;
			}
			GRA_RetornaIdentificador(pGrafo,&id);
			IrVert=GRA_IrVertice(pGrafo,id+1);
			GRA_RetornaIdentificador(pGrafo,&id);
			
		}
		GRA_IrVertice(pGrafo,IdAnterior);
		CNT_CONTAR( "GRA_VerificarEstrutura: Estrutura do grafo esta correta" ) ;
		return GRA_CondRetOK;
	}/* Fim fun��o: GRA  &Verificar Estrutura do Grafo*/
#endif


/***************************************************************************
*
*  Fun��o: GRA  &Deturpar Estrutura do Grafo
*  ****/
#ifdef _DEBUG
	void GRA_DeturparGrafo(GRA_tppGrafo pGrafo,GRA_tpModosDeturpacao ModoDeturpar)
    {
		CNT_CONTAR( "GRA_DeturparGrafo" ) ;
      if ( pGrafo== NULL )
      {
		  CNT_CONTAR( "GRA_DeturparGrafo: Grafo e NULL" ) ;
         return ;
      } /* if */

      switch ( ModoDeturpar ) {

         case DeturpaTipoCabeca :
         {
			CNT_CONTAR( "GRA_DeturparGrafo: Deturpando tipo da cabeca do grafo" ) ;
            CED_DefinirTipoEspaco( pGrafo , CED_ID_TIPO_VALOR_NULO ) ;

            break ;

         } 

         case DeturpaElementoCorrente:
         {
			CNT_CONTAR( "GRA_DeturparGrafo: Deturpando elemento corrente do grafo" ) ;
			pGrafo->pElemCorr=NULL;
            break ;

         } 

         case DeturpaListaVertices :
         {
			CNT_CONTAR( "GRA_DeturparGrafo: Deturpando a lista de vertices do grafo" ) ;
            pGrafo->pVerticesGrafo = NULL;
            break ;

         } 
		 case DeturpaPrimeiroElementoVertice :
         {
			CNT_CONTAR( "GRA_DeturparGrafo: Deturpando o primeiro elemento da lista de vertices do grafo" ) ;
            LIS_IrInicioLista(pGrafo->pVerticesGrafo);
			LIS_ExcluirElemento(pGrafo->pVerticesGrafo);
            break ;

         }
		 default:
			 if(pGrafo->pElemCorr!=NULL)
			 {
				 switch ( ModoDeturpar ){
         case DeturpaTipoVertice :
         {
			CNT_CONTAR( "GRA_DeturparGrafo: Deturpando tipo do vertice corrente" ) ;
            CED_DefinirTipoEspaco( pGrafo->pElemCorr , CED_ID_TIPO_VALOR_NULO ) ;
            break ;

         } 
         case DeturpaListaAresta :
         {
		   CNT_CONTAR( "GRA_DeturparGrafo: Deturpando ponteiro para a lista de arestas do vertice corrente" ) ;
           pGrafo->pElemCorr->pLisAresta = NULL;

            break ;

         } 
         case DeturpaPrimeiroElementoAresta :
         {
			CNT_CONTAR( "GRA_DeturparGrafo: Deturpando primeiro elemento da lista de arestas do vertice corrente" ) ;
            LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
			LIS_ExcluirElemento(pGrafo->pElemCorr->pLisAresta);
            break ;

         } 


		 		  default:
			 break;
         } 


		 }
		}
	  CNT_CONTAR( "GRA_DeturparGrafo: Chegou ao fim da funcao" ) ;
    }
   

#endif

	/* Fim fun��o: GRA  &Deturpar Estrutura do Grafo*/



/*****  C�digo das fun��es encapsuladas no m�dulo  *****/
/***********************************************************************
*
*  $FC Fun��o: GRA  -Criar o vertice da lista Vertice
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

} /* Fim fun��o: GRA  -Criar o vertice da lista Vertice */

/***********************************************************************
*
*  $FC Fun��o: GRA  -Destruir elemento da Lista Vertices
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
*  $FC Fun��o: GRA  -Destruir elemento da Lista Vertice
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



/***********************************************************************
*
*  $FC Fun��o: GRA  -Verificar cabeca do grafo
*
***********************************************************************/
#ifdef _DEBUG
	GRA_tpCondRet GRA_VerificarCabeca(void* Gra)
	{
		int numVerts;
		GRA_tppGrafo pGrafo;
        CNT_CONTAR( "GRA_VerificarCabeca" ) ;
  
		if(Gra==NULL) {
			CNT_CONTAR( "GRA_VerificarCabeca: Cabeca do grafo e NULL" ) ;
			TST_NotificarFalha( "Tentou verificar cabe�a inexistente." ) ;
			return GRA_CondRetErroEstrutural;
		}
		if (!CED_VerificarEspaco( Gra,NULL ))
        {
			CNT_CONTAR( "GRA_VerificarCabeca: Controlador de Espaco acusou erro" ) ;
			TST_NotificarFalha( "Controle do espa�o acusou erro." ) ;
            return GRA_CondRetErroEstrutural ;
		}
		if(CED_ObterTipoEspaco(Gra)!= GRA_TipoEspacoCabecaGrafo)
		{
			CNT_CONTAR( "GRA_VerificarCabeca: Cabeca tem tipo diferente de GRA_tpGrafo" ) ;
			TST_NotificarFalha( "Tipo diferente de GRA_tpGrafo." ) ;
			return GRA_CondRetErroEstrutural;
		}
		pGrafo=(GRA_tppGrafo)Gra;
		if(pGrafo->pElemCorr==NULL && pGrafo->NumVertices!=0)
		{
			CNT_CONTAR( "GRA_VerificarCabeca: Elemento corrente e NULL,porem existem vertices alocados no grafo" ) ;
			TST_NotificarFalha( "Referencia para o corrente foi perdida" ) ;
			return GRA_CondRetErroEstrutural;
		}
		if(pGrafo->pVerticesGrafo==NULL)
		{
			CNT_CONTAR( "GRA_VerificarCabeca: Referencia para a lista de vertices foi perdida" ) ;
			TST_NotificarFalha( "Referencia para a lista de vertices foi perdida" ) ;
			return GRA_CondRetErroEstrutural;
		}
		LIS_ObterTamanho(pGrafo->pVerticesGrafo,&numVerts);
		if(numVerts !=pGrafo->NumVertices)
		{
			CNT_CONTAR( "GRA_VerificarCabeca: Numero de vertices e diferente do esperado" ) ;
			TST_NotificarFalha( "Numero de vertices e diferente do esperado" ) ;
			return GRA_CondRetErroEstrutural;
		}
		CNT_CONTAR( "GRA_VerificarCabeca: Cabeca possui estrutura correta" ) ;
		return GRA_CondRetOK;
	}
#endif


/***********************************************************************
*
*  $FC Fun��o: GRA  -Verificar vertice do grafo
*
***********************************************************************/
#ifdef _DEBUG
	GRA_tpCondRet GRA_VerificarElemento(GRA_tppGrafo pGrafo,void* Vert)
	{
		
		int numArestas,IdentViz,IdentAtual;
		GRA_tpVertice* pVertViz;
		GRA_tpVertice* pVert;
		LIS_tpCondRet CondRetAv=LIS_CondRetOK;
		CNT_CONTAR( "GRA_VerificarElemento" ) ;
		if(CED_ObterTipoEspaco(Vert)!= GRA_TipoEspacoVerticeGrafo)
		{
			CNT_CONTAR( "GRA_VerificarElemento: Tipo do vertice e diferente do esperado" ) ;
			TST_NotificarFalha( "Tipo diferente de GRA_tpVertice." ) ;
			return GRA_CondRetErroEstrutural;
		}
		pVert=(GRA_tpVertice*)Vert;
		if(pVert->pLisAresta==NULL)
		{
			CNT_CONTAR( "GRA_VerificarElemento: Referencia para a lista de arestas foi perdida" ) ;
			TST_NotificarFalha( "Referencia para a lista de arestas foi perdida." ) ;
			return GRA_CondRetErroEstrutural;
		}
		LIS_ObterTamanho(pVert->pLisAresta,&numArestas);
		if(numArestas !=pVert->NumArestas)
		{
			CNT_CONTAR( "GRA_VerificarElemento: Numero de arestas e diferente do esperado" ) ;
			TST_NotificarFalha( "Numero de arestas e diferente do esperado" ) ;
			return GRA_CondRetErroEstrutural;
		}
		if(numArestas==0)
		{	
			CNT_CONTAR( "GRA_VerificarElemento: Vertice nao possui arestas" ) ;
			return GRA_CondRetOK;
		}
		IdentAtual=pVert->Ident;
		LIS_IrInicioLista(pVert->pLisAresta);
		while(CondRetAv!=LIS_CondRetFimLista)
		{
			LIS_ObterValor(pVert->pLisAresta,(void**)&pVertViz);
			IdentViz=pVertViz->Ident;
			if(GRA_ExisteAresta(pGrafo,IdentAtual,IdentViz)!=GRA_CondRetOK)
			{
				CNT_CONTAR( "GRA_VerificarElemento: Entrou no tratador" ) ;
				GRA_TratarVerticeSemAresta(pGrafo,IdentAtual,IdentViz);
			}
			CondRetAv=LIS_AvancarElementoCorrente(pVert->pLisAresta,1);
		}
		CNT_CONTAR( "GRA_VerificarElemento: Vertice possui estrutura correta" ) ;
		return GRA_CondRetOK;
}

#endif

/***********************************************************************
*
*  $FC Fun��o: GRA  -Tratar vertice que tem aresta com outro,porem o outro nao tem aresta com o primeiro
*
***********************************************************************/
#ifdef _DEBUG
	GRA_tpCondRet GRA_TratarVerticeSemAresta(GRA_tppGrafo pGrafo,int identAtual,int identVizinho)
	{
		LIS_tpCondRet CondRetAv=LIS_CondRetOK;
		int IdAnterior;
		GRA_tpVertice* pVerts;
		CNT_CONTAR( "GRA_TratarVerticeSemAresta" ) ;
		if(pGrafo->pElemCorr==NULL)
			return GRA_CondRetOK;
		IdAnterior=pGrafo->pElemCorr->Ident;
		GRA_IrVertice(pGrafo,identAtual);
		LIS_IrInicioLista(pGrafo->pElemCorr->pLisAresta);
		while(CondRetAv!=LIS_CondRetFimLista)
		{
			LIS_ObterValor(pGrafo->pElemCorr->pLisAresta,(void**)&pVerts);
			if(pVerts->Ident==identVizinho)
			{
				CNT_CONTAR( "GRA_TratarVerticeSemAresta: Encontrou vertice" ) ;
				LIS_ExcluirElemento(pVerts->pLisAresta);
				pVerts->NumArestas-=1;
				break;
			}
			CondRetAv=LIS_AvancarElementoCorrente(pGrafo->pElemCorr->pLisAresta,1);

		}
		GRA_IrVertice(pGrafo,IdAnterior);
		CNT_CONTAR( "GRA_TratarVerticeSemAresta: Estrutura do grafo foi reparada" ) ;
		return GRA_CondRetOK;
	}
#endif



/********** Fim do m�dulo de implementa��o: GRA  Grafo generico com cabeca **********/