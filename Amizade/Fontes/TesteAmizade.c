/***************************************************************************
*  $MCI Módulo de implementação: TAMI Teste módulo amizade
*
*  Arquivo gerado:              TesteAmizade.c
*  Letras identificadoras:      TAMI
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Amizade.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ms
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       ms   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"
#include    "CESPDIN.H"
#include    "AMIZADE.h"
#include	"PERFIL.h"
#include	"GRAFO.h"

static const char RESET_AMIZADE_CMD				[ ] = "=resetteste"
static const char CRIAR_AMIZADE_CMD       		[ ] = "=criaramizade";
static const char EXCLUIR_AMIZADE_CMD     		[ ] = "=excluiramizade";
static const char VERIFICAR_NUM_AMIGOS_CMD      [ ] = "=verificarnumamigos";
static const char ARMAZENAR_AMIZADES_CMD        [ ] = "=armazenaramizades";
static const char EXCLUIR_TODAS_AMIZADES_CMD    [ ] = "=excluirtodasamizades";
static const char VERIFICAR_AMIZADES_CMD        [ ] = "=verificaramizades";

#define TRUE  1
#define FALSE 0

#define DIM_VT_PERFIL  	10
#define DIM_VT_EMAIL  	10
#define DIM_VT_PRIMNOME 10
#define DIM_VT_CIDADE  	10
#define DIM_VT_DIA  	10
#define DIM_VT_MES  	10
#define DIM_VT_ANO  	10

PER_tpPerfil   vtPerfil[ DIM_VT_PERFIL ];

/***** Protótipos das funções encapuladas no módulo *****/

static void DestruirValor( void * pValor );
static int ValidarInxPerfil( int inxPerfil);

//static int ValidarParmIndices(int tamVetor, int *indiceEsp);

/*****  Código das funções exportadas pelo módulo  *****/
/***********************************************************************
*
*  $FC Função: TAMI &Testar amizade
*
*  $ED Descrição da função
*	  Podem ser criadas até 10 perfis, identificados pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste - anula o vetor de grafos e perfiis. Provoca vazamento de memória.
*     =criaramizade                   	inxPerfil1 	inxPerfil2 	Solicitacao   CondRetEsp
*     =excluiramizade                	inxPerfil1 	inxPerfil2 	CondRetEsp
*     =verificarnumamigos               inxPerfil 	numAmizades CondRetEsp
*     =armazenaramizades               	inxPerfil	vetPerfil	CondRetEsp 					
*		- a função armazenar amizades compara apenas 3 perfis
*     =excluirtodasamizades             inxPerfil	CondRetEsp
*     =verificaramizades                inxPerfil1 	inxPerfil2 	existeAmizade CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{

	int inxPerfil = -1 ,
		inxPerfil1 = -1 ,
		inxPerfil2 = -1 ,
		numLidos   = -1 ,
		CondRetEsp = -1  ;
	TST_tpCondRet CondRet ;

	int i ;
	AMI_tpSolitacao Solicitacao;
	int numElem = -1 ,
		numAmigos = -1;
	
	GRA_tppGrafo tpGrafo = NULL;
	GRA_tpCondRet GRA_CondRetCriarGrafo;
	PER_tpCondRet PER_CondRetCriarPerfil;
	
	char email1;
	char primNome1;
	char ultNome1;
	char cidade1;
	int dia1;
	int mes1;
	int ano1;
	
	char email2;
	char primNome2;
	char ultNome2;
	char cidade2;
	int dia2;
	int mes2;
	int ano2;
	
	char email3;
	char primNome3;
	char ultNome3;
	char cidade3;
	int dia3;
	int mes3;
	int ano3;
	
	char vtEmail 	[DIM_VT_EMAIL] = {"usuario1@gmail.com", "usuario2@gmail.com", "usuario3@gmail.com", "usuario4@gmail.com", "usuario5@gmail.com",
									  "usuario6@gmail.com", "usuario7@gmail.com", "usuario8@gmail.com", "usuario9@gmail.com", "usuario10@gmail.com"};
	char vtPrimNome [DIM_VT_PRIMNOME] = {"Usuario1", "Usuario2", "Usuario3", "Usuario4", "Usuario5", "Usuario6", "Usuario7", "Usuario8", "Usuario9", "Usuario10"};
	char vtUltNome 	[DIM_VT_ULTNOME] = {"Sobrenome1", "Sobrenome2", "Sobrenome3", "Sobrenome4", "Sobrenome5", "Sobrenome6", "Sobrenome7", "Sobrenome8", "Sobrenome9", "Sobrenome10"};
	char vtCidade 	[DIM_VT_CIDADE] = {"Cidade1", "Cidade2", "Cidade3", "Cidade4", "Cidade5", "Cidade6", "Cidade7", "Cidade8", "Cidade9", "Cidade10"};
	int  vtDia 		[DIM_VT_DIA] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int  vtMes 		[DIM_VT_MES] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int  vtAno 		[DIM_VT_ANO] = {2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010};
	
	/* Efetuar reset de teste de Amizade */

	if ( strcmp( ComandoTeste , RESET_AMIZADE_CMD ) == 0 )
	{
		if (tpGrafo == NULL){
			GRA_CondRetCriarGrafo = GRA_CriarGrafo(DestruirValor, &tpGrafo);
			if (GRA_CondRetCriarGrafo == GRA_CondRetFaltouMemoria){
				return TST_CondRetMemoria;
			}
		} else {
			GRA_DestruirGrafo(&tpGrafo);
			GRA_CondRetCriarGrafo = GRA_CriarGrafo(DestruirValor, &tpGrafo);
			if (GRA_CondRetCriarGrafo == GRA_CondRetFaltouMemoria){
				return TST_CondRetMemoria;
			}
		}
		
		
		for (i = 0; i < DIM_VT_PERFIL ; i++ ){
			PER_CondRetCriarPerfil = PER_CriarPerfil(tpGrafo, vtPerfil[i], vtEmail[i], vtPrimNome[i], vtUltNome[i],
							  vtDia[i], vtMes[i], vtAno[i], vtCidade[i]);
			if (PER_CondRetCriarPerfil == PER_CondRetFaltouMemoria){
				return TST_CondRetMemoria;
			}
		}/* for */

		return TST_CondRetOK ;

	} /* fim ativa: Efetuar reset de teste de Amizade */
	
	/* Testar Criar Amizade */

	else if ( strcmp( ComandoTeste , CRIAR_AMIZADE_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "iiii" ,&inxPerfil1, &inxPerfil2, &Solicitacao, &CondRetEsp ) ;

		if ( ( numLidos != 4 ) || ( ! ValidarInxPerfil( inxPerfil1)) || ( ! ValidarInxPerfil( inxPerfil2))){
			return TST_CondRetParm ;
		} /* if */

		CondRet = AMI_CriarAmizade(tpGrafo, inxPerfil1, inxPerfil2, Solicitacao);

		return TST_CompararInt( CondRetEsp , CondRet ,
			"Erro na condicao de retorno ao criar o Amizade"  ) ;

	} /* fim ativa: Testar Criar Amizade */


	/* Testar Excluir Amizade */

	else if ( strcmp( ComandoTeste , EXCLUIR_AMIZADE_CMD ) == 0 )
	{
		
        numLidos = LER_LerParametros("iii" , &inxPerfil1, &inxPerfil2, &CondRetEsp) ;
		if (( numLidos != 3 ) || ( ! ValidarInxPerfil( inxPerfil1)) || ( ! ValidarInxPerfil( inxPerfil2))){
			return TST_CondRetParm ;
		} /* if */

		CondRet = AMI_ExcluirAmizade(tpGrafo, inxPerfil1, inxPerfil2);
		
		return TST_CompararInt( CondRetEsp , CondRet ,
            "Condicao de retorno errada ao excluir amizade.") ;

    }  /* fim ativa: Testar Excluir Amizade */

	
	/* Testar Verificar Número de Amigos*/

	else if ( strcmp( ComandoTeste , VERIFICAR_NUM_AMIGOS_CMD ) == 0 )
	{	
		numLidos = LER_LerParametros( "iii" , &inxPerfil1, &numAmigos, &CondRetEsp ) ;
		if ( ( numLidos != 2 )|| (!ValidarInxPerfil( inxPerfil1))){
			return TST_CondRetParm ;
		} /* if */

		CondRet = AMI_VerificarNumAmigos(tpGrafo, inxPerfil1, numAmigos);

		return TST_CompararInt( CondRetEsp , CondRet ,
			"Condicao de retorno errada ao verificar número de amigos." ) ;

	} /* fim ativa: Testar Verificar Número de Amigos */

	
	/* Testar armazenar amizades */
	// Verificar essa bosta
	else if ( strcmp( ComandoTeste , ARMAZENAR_AMIZADES_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "issssiiissssiiissssiiii" ,
			&inxPerfil1, &email1, &primNome1, &ultNome1, &cidade1, &dia1, &mes1, &ano1,
						 &email2, &primNome2, &ultNome2, &cidade2, &dia2, &mes2, &ano2,
						 &email3, &primNome3, &ultNome3, &cidade3, &dia3, &mes3, &ano3, &CondRetEsp );
						 

		if (( numLidos != 23 ) || (!ValidarInxPerfil( inxPerfil1)))
		{
			return TST_CondRetParm ;
		} /* if */
		
		CondRet = AMI_ArmazenarAmizades(GRA_tppGrafo pGrafo, PER_tpPerfil Usuario, PER_tpPerfil **PerfilAmigos);

		return TST_CompararInt( CondRetEsp ,
			GRA_ExcluirVertice( vtGrafos[ inxGrafo ]) ,
			"Condição de retorno errada ao excluir vertice."   ) ;

	} /* fim ativa: Testar armazenar amizades */

	
	/* Testar excluir Todas as Amizades */
	else if ( strcmp( ComandoTeste , EXCLUIR_TODAS_AMIZADES_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii" ,
			&inxPerfil1, &CondRetEsp ) ;

		if (( numLidos != 2 )|| (!ValidarInxPerfil( inxPerfil1)))
		{
			return TST_CondRetParm ;
		} /* if */
		
		CondRet = AMI_ExcluirTodasAmizades(tpGrafo, inxPerfil1);

		return TST_CompararInt( CondRetEsp , CondRet ,
			"Condicao de retorno errada ao excluir todas as amizades." ) ;

	} /* fim ativa: Testar excluir Todas as Amizades */


	/* Testar verificar amizade */
	else if ( strcmp( ComandoTeste , EXC_ARESTA_CMD ) == 0 )
	{
		int numVert1,numVert2;

		numLidos = LER_LerParametros( "iiii" ,
			&inxPerfil1,&inxPerfil2, &existeAmizade, &CondRetEsp ) ;

		if (( numLidos != 4 ) || (!ValidarInxPerfil( inxPerfil1))|| (!ValidarInxPerfil( inxPerfil2)))
		{
			return TST_CondRetParm ;
		} /* if */

		CondRet = AMI_VerificarAmizade(tpGrafo, inxPerfil1, inxPerfil2, existeAmizade);
		
		return TST_CompararInt( CondRetEsp , CondRet ,
			"Condicao de retorno errada ao verificar amizade." ) ;

	} /* fim ativa: Testar verificar amizade */


 /* Fim função: TAMI &Testar Amizade */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TAMI -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TAMI -Destruir valor */



/***********************************************************************
*
*  $FC Função: TAMI -Validar indice de Perfil
*
***********************************************************************/

int ValidarInxPerfil( int inxPerfil)
{

	if ( ( inxPerfil <  0 )
		|| ( inxPerfil >= DIM_VT_PERFIL ))
	{
		return FALSE ;
	} /* if */

	return TRUE ;

} /* Fim função: TAMI -Validar indice de Perfil */


/********** Fim do módulo de implementação: TAMI Teste módulo Amizade **********/

