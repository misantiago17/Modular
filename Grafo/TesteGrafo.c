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
static const char INS_VERT_CMD            [ ] = "=insvertice"   ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char CRIAR_ARESTA_CMD        [ ] = "=criararesta"     ;
static const char EXISTE_ARESTA_CMD        [ ] = "=existearesta"     ;
static const char EXC_VERT_CMD            [ ] = "=excluirvertice"    ;
static const char EXC_ARESTA_CMD          [ ] = "=excluiraresta"     ;


struct infs{
	char Nome[100];
	char Cidade[50];
	char Email[100];
	char Data[12];

};
typedef struct infs Teste_Infs;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_GRAFO   10
#define DIM_VALOR     100



Gra_tppGrafo   vtGrafos[ DIM_VT_Grafo ] ;

/***** Protótipos das funções encapuladas no módulo *****/


static int ValidarInxGrafo( int inxGrafo , int Modo ) ;

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
*     =insvertice                   inxGrafo  Nome Data Cidade Email CondRetEsp
*     =obtervalorelem               inxGrafo  Nome Data Cidade Email CondRetEsp
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
			&inxGrafo, &CondRet ) ;

		if ( ( numLidos != 2 )
			|| ( ! ValidarInxGrafo( inxGrafo , VAZIO )))
		{
			return TST_CondRetParm ;
		} /* if */

		CondRetEsp=GRA_CriarGrafo( NULL,&vtGrafos[inxGrafo]) ;

		return TST_CompararInt( CondRetEsp , CondRet ,
			"Erro na condicao de retorno ao criar o Grafo"  ) ;

	} /* fim ativa: Testar CriarGrafo */


	/* Testar Destruir Grafo */

	else if ( strcmp( ComandoTeste , DESTRUIR_GRAFO_CMD ) == 0 )
	{

            numLidos = LER_LerParametros( "ii" ,
                               &inxGrafo,&CondRetEsp ) ;
            if ( ( numLidos != 2 )
              || ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */


            CondRet=LIS_DestruirGrafo( vtGrafos[ inxGrafo ] ) ;
			debug= TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao destruir o grafo.") ;
			if(debug!=TST_CondRetOK)
					return debug;

			if(CondRet==LIS_CondRetOK)
				vtGrafos[ inxGrafo ] = NULL ;

			 return TST_CondRetOK ;
           

         }  /* fim ativa: Testar Destruir Grafo */

	/* Testar inserir vertice*/

	else if ( strcmp( ComandoTeste , INS_VERT_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "issssi" ,
			&inxGrafo  ,NomeRet,DataRet,CidadeRet,EmailRet,&CondRetEsp ) ;

		if ( ( numLidos != 6 )
			|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
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

	} /* fim ativa: Testar inserir elemento antes */


	/* Testar excluir vertice */

	else if ( strcmp( ComandoTeste , EXC_VERT_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "ii" ,
			&inxGrafo , &CondRetEsp ) ;

		if ( ( numLidos != 3 )
			|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
		{
			return TST_CondRetParm ;
		} /* if */

		return TST_CompararInt( CondRetEsp ,
			GRA_ExcluirVertice( vtGrafos[ inxGrafo ]) ,
			"Condição de retorno errada ao excluir vertice."   ) ;

	} /* fim ativa: Testar excluir vertice */


	/* Testar excluir aresta */

	else if ( strcmp( ComandoTeste , EXISTE_ARESTA_CMD ) == 0 )
	{
		int numVert1,numVert2;

		numLidos = LER_LerParametros( "iiii" ,
			&inxGrafo ,&numVert1,&numVert2, &CondRetEsp ) ;

		if ( ( numLidos != 4 )
			|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
		{
			return TST_CondRetParm ;
		} /* if */

		return TST_CompararInt( CondRetEsp ,
			GRA_ExcluirAresta( vtGrafos[ inxGrafo ],numVert1,numVert2) ,
			"Condição de retorno errada ao excluir aresta."   ) ;

	} /* fim ativa: Testar excluir aresta */

		/* Testar existe aresta */

	else if ( strcmp( ComandoTeste , EXC_ARESTA_CMD ) == 0 )
	{
		int numVert1,numVert2;

		numLidos = LER_LerParametros( "iiii" ,
			&inxGrafo ,&numVert1,&numVert2, &CondRetEsp ) ;

		if ( ( numLidos != 4 )
			|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
		{
			return TST_CondRetParm ;
		} /* if */

		return TST_CompararInt( CondRetEsp ,
			GRA_ExisteAresta( vtGrafos[ inxGrafo ],numVert1,numVert2) ,
			"Condição de retorno errada ao excluir aresta."   ) ;

	} /* fim ativa: Testar excluir aresta */

	/* Testar obter valor do elemento corrente */

	else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
	{
		Teste_Infs* Ret;
		TST_tpCondRet debug;
		numLidos = LER_LerParametros( "issssi" ,
			&inxGrafo  ,NomeEsp,DataEsp,CidadeEsp,EmailEsp,&CondRetEsp ) ;

		if ( ( numLidos != 6 )
			|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
		{
			return TST_CondRetParm ;
		} /* if */

		CondRet=GRA_ObterValor( vtGrafos[ inxGrafo ],(void**)&Ret) ;


		debug=TST_CompararInt(CondRet , CondRetEsp ,
			"Retorno de obter valor diferente do esperado" ) ;

		if(debug!=TST_CondRetOK)
			return debug;

		if(CondRet==GRA_CondRetGrafoVazia)
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
		GRA_tpCondRet CondRet

			numLidos = LER_LerParametros( "ii" , &inxGrafo,&numVert ) ;

		if ( ( numLidos != 2 )
			|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
		{
			return TST_CondRetParm ;
		} /* if */

		return TST_CompararInt( CondRetEsp ,GRA_IrVertice( vtGrafos[ inxGrafo ],numVert ) ,
			"Condição de retorno errada ao ir para o vertice."   ) ;


	} /* fim ativa: Testar ir Vertice  */
	return TST_CondRetNaoConhec;
}

 /* Fim função: TGRA &Testar Grafo */


/*****  Código das funções encapsuladas no módulo  *****/





/***********************************************************************
*
*  $FC Função: TGRA -Validar indice de Grafo
*
***********************************************************************/

int ValidarInxGrafo( int inxGrafo , int Modo )
{

	if ( ( inxGrafo <  0 )
		|| ( inxGrafo >= DIM_VT_GRAFO ))
	{
		return FALSE ;
	} /* if */

	if ( Modo == VAZIO )
	{
		if ( vtGrafos[ inxGrafo ] != 0 )
		{
			return FALSE ;
		} /* if */
	} else
	{
		if ( vtGrafos[ inxGrafo ] == 0 )
		{
			return FALSE ;
		} /* if */
	} /* if */

	return TRUE ;

} /* Fim função: TGRA -Validar indice de Grafo */




/********** Fim do módulo de implementação: TGRA Teste Grafo com cabeca **********/

