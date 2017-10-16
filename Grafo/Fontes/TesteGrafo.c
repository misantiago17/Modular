/***************************************************************************
*  $MCI Módulo de implementação: TGRA Teste grafo com cabeça
*
*  Arquivo gerado:              TesteGrafo.c
*  Letras identificadoras:      TGRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Grafo.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gab
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     6       gab   01/out/2017 implementacao dos testes da funcao ObterTamanho e utilizando uma estrutura que guarde Nome, Data, Cidade e Email.
*     5       gab   01/out/2017 modificacao no módulo de teste para que as funções do módulo Grafo retornem uma condição de retorno
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Grafo.h"



static const char RESET_GRAFO_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_GRAFO_CMD         [ ] = "=criargrafo"     ;
static const char DESTRUIR_GRAFO_CMD      [ ] = "=destruirgrafo"  ;
static const char IR_VERT_CMD             [ ] = "=irvertice"  ;
static const char INS_VERT_CMD            [ ] = "=inserirvertice"   ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorvert" ;
static const char CRIAR_ARESTA_CMD        [ ] = "=criararesta"     ;
static const char EXISTE_ARESTA_CMD       [ ] = "=existearesta"     ;
static const char EXC_VERT_CMD            [ ] = "=excluirvertice"    ;
static const char EXC_ARESTA_CMD          [ ] = "=excluiraresta"     ;
static const char NUM_VERTS_CMD           [ ] = "=obternumverts" ;
static const char NUM_ARESTAS_CMD         [ ] = "=obternumarestas" ;
static const char INDICES_ARESTAS_CMD     [ ] = "=indicesarestas" ;
static const char RET_IDENT_CMD           [ ] = "=retornaident" ;


struct infs{
	char Nome[100];
	char Cidade[50];
	char Email[100];
	char Data[12];

};
typedef struct infs Teste_Infs;

#define TRUE  1
#define FALSE 0

#define DIM_VT_GRAFO   10




GRA_tppGrafo   vtGrafos[ DIM_VT_GRAFO ] ;

/***** Protótipos das funções encapuladas no módulo *****/


static int ValidarInxGrafo( int inxGrafo) ;
static int ValidarParmIndices(int tamVetor, int *indiceEsp);
/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRA &Testar grafo
*
*  $ED Descrição da função
*     Podem ser criadas até 10 grafos, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de grafos. Provoca vazamento de memória
*     =criargrafo                   inxGrafo CondRetEsp
*     =destruirgrafo                inxGrafo CondRetEsp
*     =irvertice                    inxGrafo numVert CondRetEsp
*     =inserirvertice                   inxGrafo  Nome Data Cidade Email CondRetEsp
*     =obtervalorvert               inxGrafo  Nome Data Cidade Email CondRetEsp
*     =criararesta                  inxGrafo  numVert1 numVert2 CondRetEsp
*     =excluirvertice               inxGrafo  CondRetEsp
*     =excluiraresta                inxGrafo  numVert1 numVert2 CondRetEsp
*	  =existearesta					inxGrafo  numVert1 numVert2 CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{

	int inxGrafo  = -1 ,
		numLidos   = -1 ,
		CondRetEsp = -1  ;
	Teste_Infs* pDado;
	TST_tpCondRet CondRet ;

	char NomeRet[100];
	char CidadeRet[50];
	char EmailRet[100];
	char DataRet[12];

	char NomeEsp[100];
	char CidadeEsp[50];
	char EmailEsp[100];
	char DataEsp[12];



	int i ;

	int numElem = -1 ;



	/* Efetuar reset de teste de GRAFO */

	if ( strcmp( ComandoTeste , RESET_GRAFO_CMD ) == 0 )
	{

		for( i = 0 ; i < DIM_VT_GRAFO ; i++ )
		{
			vtGrafos[ i ] = NULL ;
		} /* for */

		return TST_CondRetOK ;

	} /* fim ativa: Efetuar reset de teste de Grafo */

	/* Testar Criar Grafo */

	else if ( strcmp( ComandoTeste , CRIAR_GRAFO_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "ii" ,
			&inxGrafo, &CondRetEsp ) ;

		if ( ( numLidos != 2 )
			|| ( ! ValidarInxGrafo( inxGrafo)))
		{
			return TST_CondRetParm ;
		} /* if */

		CondRet=GRA_CriarGrafo( NULL,&vtGrafos[inxGrafo]) ;

		return TST_CompararInt( CondRetEsp , CondRet ,
			"Erro na condicao de retorno ao criar o Grafo"  ) ;

	} /* fim ativa: Testar CriarGrafo */


	/* Testar Destruir Grafo */

	else if ( strcmp( ComandoTeste , DESTRUIR_GRAFO_CMD ) == 0 )
	{

		GRA_tpCondRet debug;
            numLidos = LER_LerParametros( "ii" ,
                               &inxGrafo,&CondRetEsp ) ;
            if ( ( numLidos != 2 )
              || ( ! ValidarInxGrafo( inxGrafo)))
            {
               return TST_CondRetParm ;
            } /* if */


            debug=GRA_DestruirGrafo( vtGrafos[ inxGrafo ] ) ;
			CondRet= TST_CompararInt( CondRetEsp , debug ,
                     "Condicao de retorno errada ao destruir o grafo.") ;
			if(CondRet!=TST_CondRetOK)
					return CondRet;

			if(debug==GRA_CondRetOK)
				vtGrafos[ inxGrafo ] = NULL ;

			 return TST_CondRetOK ;
           

         }  /* fim ativa: Testar Destruir Grafo */

	/* Testar inserir vertice*/

	else if ( strcmp( ComandoTeste , INS_VERT_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "issssi" ,
			&inxGrafo  ,NomeRet,DataRet,CidadeRet,EmailRet,&CondRetEsp ) ;

		if ( ( numLidos != 6 )
			|| ( ! ValidarInxGrafo( inxGrafo)) )
		{
			return TST_CondRetParm ;
		} /* if */

		pDado = ( Teste_Infs * ) malloc( sizeof(Teste_Infs )) ;
		if ( pDado == NULL )
		{
			return TST_CondRetMemoria ;
		} /* if */

		strcpy(pDado->Nome,NomeRet);
		strcpy(pDado->Cidade,CidadeRet);
		strcpy(pDado->Data,DataRet);
		strcpy(pDado->Email,EmailRet);

		CondRet = GRA_InserirVertice( vtGrafos[ inxGrafo ] , pDado ) ;

		if ( CondRet != GRA_CondRetOK )
		{
			free( pDado ) ;
		} /* if */

		return TST_CompararInt( CondRetEsp , CondRet ,
			"Condicao de retorno errada ao inserir vertice." ) ;

	} /* fim ativa: Testar inserir vertice */


	/* Testar excluir vertice */

	else if ( strcmp( ComandoTeste , EXC_VERT_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "ii" ,
			&inxGrafo , &CondRetEsp ) ;

		if ( ( numLidos != 2 )
			|| ( ! ValidarInxGrafo( inxGrafo)) )
		{
			return TST_CondRetParm ;
		} /* if */

		return TST_CompararInt( CondRetEsp ,
			GRA_ExcluirVertice( vtGrafos[ inxGrafo ]) ,
			"Condição de retorno errada ao excluir vertice."   ) ;

	} /* fim ativa: Testar excluir vertice */

	/* Testar Criar Aresta */

	else if ( strcmp( ComandoTeste , CRIAR_ARESTA_CMD ) == 0 )
	{
		int numVert1,numVert2;

		numLidos = LER_LerParametros( "iiii" ,
			&inxGrafo ,&numVert1,&numVert2, &CondRetEsp ) ;

		if ( ( numLidos != 4 )
			|| ( ! ValidarInxGrafo( inxGrafo)) )
		{
			return TST_CondRetParm ;
		} /* if */

		return TST_CompararInt( CondRetEsp ,
			GRA_CriarAresta( vtGrafos[ inxGrafo ],numVert1,numVert2) ,
			"Condição de retorno errada ao excluir aresta."   ) ;

	} /* fim ativa: Testar criar aresta */


	/* Testar excluir aresta */

	else if ( strcmp( ComandoTeste , EXC_ARESTA_CMD ) == 0 )
	{
		int numVert1,numVert2;

		numLidos = LER_LerParametros( "iiii" ,
			&inxGrafo ,&numVert1,&numVert2, &CondRetEsp ) ;

		if ( ( numLidos != 4 )
			|| ( ! ValidarInxGrafo( inxGrafo)) )
		{
			return TST_CondRetParm ;
		} /* if */

		return TST_CompararInt( CondRetEsp ,
			GRA_ExcluirAresta( vtGrafos[ inxGrafo ],numVert1,numVert2) ,
			"Condição de retorno errada ao excluir aresta."   ) ;

	} /* fim ativa: Testar excluir aresta */

		/* Testar existe aresta */

	else if ( strcmp( ComandoTeste , EXISTE_ARESTA_CMD ) == 0 )
	{
		int numVert1,numVert2;

		numLidos = LER_LerParametros( "iiii" ,
			&inxGrafo ,&numVert1,&numVert2, &CondRetEsp ) ;

		if ( ( numLidos != 4 )
			|| ( ! ValidarInxGrafo( inxGrafo)) )
		{
			return TST_CondRetParm ;
		} /* if */

		return TST_CompararInt( CondRetEsp ,
			GRA_ExisteAresta( vtGrafos[ inxGrafo ],numVert1,numVert2) ,
			"Condição de retorno errada ao verificar existencia da aresta."   ) ;

	} /* fim ativa: Testar existe aresta */

	/* Testar obter valor do elemento corrente */

	else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
	{
		Teste_Infs* Ret;
		TST_tpCondRet debug;
		numLidos = LER_LerParametros( "issssi" ,
			&inxGrafo  ,NomeEsp,DataEsp,CidadeEsp,EmailEsp,&CondRetEsp ) ;

		if ( ( numLidos != 6 )
			|| ( ! ValidarInxGrafo( inxGrafo)) )
		{
			return TST_CondRetParm ;
		} /* if */

		CondRet=GRA_ObterValor( vtGrafos[ inxGrafo ],(void**)&Ret) ;


		debug=TST_CompararInt(CondRet , CondRetEsp ,
			"Retorno de obter valor diferente do esperado" ) ;

		if(debug!=TST_CondRetOK)
			return debug;

		if(CondRet==GRA_CondRetGrafoVazio)
			return TST_CondRetOK;

		debug=TST_CompararPonteiroNulo( 1 , Ret ,
			"Dado deveria existir." );

		if(debug!=TST_CondRetOK)
			return debug;

		debug=TST_CompararString( NomeEsp , Ret->Nome ,
			"Campo Nome nao e igual ao esperado");
		if(debug!=TST_CondRetOK)
			return debug; 

		debug=TST_CompararString( CidadeEsp , Ret->Cidade ,
			"Campo Cidade nao e igual ao esperado" );
		if(debug!=TST_CondRetOK)
			return debug; 

		debug=TST_CompararString( EmailEsp ,Ret->Email,
			"Campo Email nao e igual ao esperado" );
		if(debug!=TST_CondRetOK)
			return debug; 

		return TST_CompararString(DataEsp ,  Ret->Data,
			"Campo Data nao e igual ao esperado" );


	} /* fim ativa: Testar obter valor do elemento corrente */

	/* Testar ir Vertice */

	else if ( strcmp( ComandoTeste , IR_VERT_CMD ) == 0 )
	{
		int numVert;


			numLidos = LER_LerParametros( "iii" , &inxGrafo,&numVert,&CondRetEsp ) ;

		if ( ( numLidos != 3 )
			|| ( ! ValidarInxGrafo( inxGrafo)) )
		{
			return TST_CondRetParm ;
		} /* if */

		return TST_CompararInt( CondRetEsp ,GRA_IrVertice( vtGrafos[ inxGrafo ],numVert ) ,
			"Condição de retorno errada ao ir para o vertice."   ) ;


	} /* fim ativa: Testar ir Vertice  */


		/* Testar Retornar Identificador */

	else if ( strcmp( ComandoTeste , RET_IDENT_CMD ) == 0 )
	{
		GRA_tpCondRet debugGRA;
		int numIdent;
		int numIdentEsp;

		numLidos = LER_LerParametros( "iii" , &inxGrafo,&numIdentEsp,&CondRetEsp ) ;

		if ( ( numLidos != 3 )
			|| ( ! ValidarInxGrafo( inxGrafo)) )
		{
			return TST_CondRetParm ;
		} /* if */

		debugGRA=GRA_RetornaIdentificador(vtGrafos[ inxGrafo ],&numIdent);
		CondRet= TST_CompararInt( CondRetEsp , debugGRA,"Condicao de retorno errada ao retornar identificador do vertice corrente" ) ;
		if (CondRet != TST_CondRetOK) {
				return CondRet;
		}

		return TST_CompararInt( numIdentEsp , numIdent
                       , "Identificador retornado inesperado" ) ;


	} /* fim ativa: Retornar Identificador  */

	/* Testar Retornar numVertices */

	else if ( strcmp( ComandoTeste , NUM_VERTS_CMD ) == 0 )
	{

			 GRA_tpCondRet debugGRA;
			 int numRet;

            numLidos = LER_LerParametros( "iii" , &inxGrafo , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxGrafo( inxGrafo )) )
            {
               return TST_CondRetParm ;
            } /* if */

			debugGRA=GRA_NumVertices(vtGrafos[ inxGrafo ], &numRet);
			CondRet= TST_CompararInt( CondRetEsp , debugGRA,
            "Condicao de retorno errada ao obter numero de vertices" ) ;

			if (CondRet != TST_CondRetOK) {
				return CondRet;
			}

			return TST_CompararInt( numElem , numRet
                       , "Numero de elementos retornado inesperado" ) ;


	} /* fim ativa: Testar Retornar numVertices  */

	/* Testar Retornar numArestas */

	else if ( strcmp( ComandoTeste , NUM_ARESTAS_CMD ) == 0 )
	{
			 GRA_tpCondRet debugGRA;
			 int numRet;

            numLidos = LER_LerParametros( "iii" , &inxGrafo , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxGrafo( inxGrafo )) )
            {
               return TST_CondRetParm ;
            } /* if */

			debugGRA=GRA_NumArestas(vtGrafos[ inxGrafo ], &numRet);
			CondRet= TST_CompararInt( CondRetEsp , debugGRA,
            "Condicao de retorno errada ao obter numero de arestas" ) ;

			if (CondRet != TST_CondRetOK) {
				return CondRet;
			}

			return TST_CompararInt( numRet , numElem
                       , "Numero de elementos retornado inesperado" ) ;

	} /* fim ativa: Testar Retornar numArestas */

	/* Testar Retornar indice das arestas */

	else if ( strcmp( ComandoTeste , INDICES_ARESTAS_CMD  ) == 0 )
	{
		int tamVetor,i;
		int indiceEsp[5];
		int* indice;
		GRA_tpCondRet debugGRA;

		numLidos = LER_LerParametros( "iiiiiiii" , &inxGrafo,&tamVetor,&indiceEsp[0],&indiceEsp[1],&indiceEsp[2],&indiceEsp[3],
			&indiceEsp[4],&CondRetEsp) ;

		if ( ( numLidos != 8 )
			|| ( ! ValidarInxGrafo( inxGrafo )) || (!ValidarParmIndices(tamVetor,indiceEsp) ))
		{
			return TST_CondRetParm ;
		} /* if */
		indice=(int*)malloc(tamVetor*sizeof(int));
		if ( indice == NULL )
		{
			return TST_CondRetMemoria ;
		} /* if */

		debugGRA=GRA_RetornaIndiceAresta(vtGrafos[ inxGrafo ],indice);

		CondRet=TST_CompararInt( CondRetEsp ,debugGRA  ,
			"Condição de retorno errada ao retornar indices das arestas."   ) ;

		if (CondRet != TST_CondRetOK) {
				return CondRet;
			}
		if(tamVetor==0 && debugGRA==GRA_CondRetNumArestasZero)
			return TST_CondRetOK;


		for(i=0;i<tamVetor;i++)
		{
			CondRet=TST_CompararInt( indiceEsp[i] ,indice[i]  ,
			"Aresta do vetor nao e igual  a esperada" ) ;
			if (CondRet != TST_CondRetOK) {
				return CondRet;
			}
		}

		return TST_CondRetOK;

	} /* fim ativa: Retornar indice das arestas  */
	
	return TST_CondRetNaoConhec;
}

 /* Fim função: TGRA &Testar Grafo */


/*****  Código das funções encapsuladas no módulo  *****/





/***********************************************************************
*
*  $FC Função: TGRA -Validar indice de Grafo
*
***********************************************************************/

int ValidarInxGrafo( int inxGrafo)
{

	if ( ( inxGrafo <  0 )
		|| ( inxGrafo >= DIM_VT_GRAFO ))
	{
		return FALSE ;
	} /* if */

	return TRUE ;

} /* Fim função: TGRA -Validar indice de Grafo */

/***********************************************************************
*
*  $FC Função: TGRA -Validar parametros do teste de Retornar Indices de Aresta
*
***********************************************************************/

int ValidarParmIndices( int tamVetor , int *indiceEsp )
{
	switch(tamVetor)
	{
	case 0:
		if (indiceEsp[0] == 0 && indiceEsp[1] == 0 && indiceEsp[2] == 0 && indiceEsp[3] == 0 && indiceEsp[4] == 0) {
			return TRUE;
			break;
		}
		else {
			return FALSE;
			break;
		}

	case 1:
		if (indiceEsp[0] != 0 && indiceEsp[1] == 0 && indiceEsp[2] == 0 && indiceEsp[3] == 0 && indiceEsp[4] == 0) {
			return TRUE;
			break;
		}
		else {
			return FALSE;
			break;
		}

	case 2:
		if (indiceEsp[0] != 0 && indiceEsp[1] != 0 && indiceEsp[2] == 0 && indiceEsp[3] == 0 && indiceEsp[4] == 0) {
			return TRUE;
			break;
		}
		else {
			return FALSE;
			break;
		}

	case 3:
		if (indiceEsp[0] != 0 && indiceEsp[1] != 0 && indiceEsp[2] != 0 && indiceEsp[3] == 0 && indiceEsp[4] == 0) {
			return TRUE;
			break;
		}
		else {
			return FALSE;
			break;
		}

	case 4:
		if (indiceEsp[0] != 0 && indiceEsp[1] != 0 && indiceEsp[2] != 0 && indiceEsp[3] != 0 && indiceEsp[4] == 0) {
			return TRUE;
			break;
		}
		else {
			return FALSE;
			break;
		}
	case 5:
		if (indiceEsp[0] != 0 && indiceEsp[1] != 0 && indiceEsp[2] != 0 && indiceEsp[3] != 0 && indiceEsp[4] != 0) {
			return TRUE;
			break;
		}
		else {
			return FALSE;
			break;
		}
	default:
			return FALSE;

	}
} /* Fim função: TGRA -Validar indice de Grafo */




/********** Fim do módulo de implementação: TGRA Teste Grafo com cabeca **********/

