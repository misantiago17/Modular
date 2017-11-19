#if ! defined(PERFIL_ )
#define PERFIL_
/***************************************************************************
*  $MCD M�dulo de defini��o: GRA  Grafo Generico com Cabe�a
*
*  Arquivo gerado:              PERFIL.h
*  Letras identificadoras:      PER
*
*  Projeto: INF 1301 / Desenvolvimento de uma rede de relacionamentos em C
*  Gestor:  DI/PUC-Rio
*  Autores: Renan Moreira (rm)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor   	 Data     	Observa��es GRA_RetornaIdentificador
*     1      rm       27/09/2017 	inicio desenvolvimento
*
*  $ED Descri��o do m�dulo
*
*	 
*	 
*
***************************************************************************/

#if defined( PERFIL_OWN )
#define PERFIL_EXT
#else
#define PERFIL_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um perfil */

typedef struct PER_tagPerfil PER_tpPerfil;

/***********************************************************************
*  $TC Tipo de dados: PER Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do perfil
*
***********************************************************************/

typedef enum {
	PER_CondRetOK,

	PER_CondRetPonteiroParaRetornoInvalido,

	PER_CondRetEmailInvalido,

	PER_CondRetEmailJaCadastrado,

	PER_CondRetDataInvalida,

	PER_CondRetParametroNulo,

	PER_CondRetNomeInvalido,

	PER_CondRetCidadeInvalida,

	PER_CondRetEmailInexistente,

	PER_CondRetFaltouMemoria,

	PER_CondRetRetornoLisIncorreto,

	PER_CondRetRedeVazia,

	PER_CondRetPerfilInexistente,

	PER_CondRetNaoHaAmizade,

	PER_CondRetParametroIncorreto,

	PER_CondRetAmizadeJaCriada,

	PER_CondRetGrafoInvalido,

	PER_CondRetParametroGRAIncorreto

} PER_tpCondRet;


/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*
*
*
*  $EP Par�metros
*
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetEmailJaCadastrado
*     PER_CondRetEmailInvalido
*     PER_CondRetNomeInvalido
*     PER_CondRetDataInvalida
*     PER_CondRetCidadeInvalida
*     PER_CondRetFaltouMemoria
*
***********************************************************************/

PER_tpCondRet PER_CriarPerfil(GRA_tppGrafo pGrafo, PER_tpPerfil *perfil, char *email, char *primeiroNome, char *ultimoNome,
							  int diaNasc, int mesNasc, int anoNasc, char *cidade);

/***********************************************************************
*  $FC Fun��o: 
*
*  $ED Descri��o da fun��o
*     
*		
*
*  $EP Par�metros
*	  
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetEmailInexistente
*
***********************************************************************/

PER_tpCondRet PER_ExcluirPerfil(GRA_tppGrafo pGrafo, char *email);


/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*
*
*
*  $EP Par�metros
*
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetEmailInexistente
*     PER_CondRetFaltouMemoria
*
***********************************************************************/

PER_tpCondRet PER_ObterPerfil(GRA_tppGrafo pGrafo, char *email, char **primeiroNome, char **ultimoNome,
							  int *diaNasc, int *mesNasc, int *anoNasc, char **cidade);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*
*
*
*  $EP Par�metros
*
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetRedeVazia
*
***********************************************************************/

PER_tpCondRet PER_NumeroPerfis(GRA_tppGrafo pGrafo, int *qtd);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*
*
*
*  $EP Par�metros
*
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetEmailJaCadastrado
*     PER_CondRetEmailInvalido
*     PER_CondRetEmailInexistente
*     PER_CondRetFaltouMemoria
*
***********************************************************************/

PER_tpCondRet PER_ModificaEmail(GRA_tppGrafo pGrafo, char *emailAtual, char *emailNovo);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*
*
*
*  $EP Par�metros
*
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetNomeInvalido
*     PER_CondRetEmailInexistente
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetFaltouMemoria
*
***********************************************************************/

PER_tpCondRet PER_ModificaNome(GRA_tppGrafo pGrafo, char *email, char *primeiroNome, char *ultimoNome);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*
*
*
*  $EP Par�metros
*
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetDataInvalida
*     PER_CondRetEmailInexistente
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*
***********************************************************************/

PER_tpCondRet PER_ModificaDataNasc(GRA_tppGrafo pGrafo, char *email, int diaNasc, int mesNasc, int anoNasc);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*
*
*
*  $EP Par�metros
*
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetCidadeInvalida
*     PER_CondRetEmailInexistente
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetFaltouMemoria
*
***********************************************************************/

PER_tpCondRet PER_ModificaCidade(GRA_tppGrafo pGrafo, char *email, char *cidade);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*
*
*
*  $EP Par�metros
*
*
*  $FV Valor retornado
*
*
***********************************************************************/

PER_tpCondRet PER_ExcluirTodosPerfis(GRA_tppGrafo pGrafo);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*
*
*
*  $EP Par�metros
*
*
*  $FV Valor retornado
*
*
***********************************************************************/

PER_tpCondRet PER_adicionaMensagem(GRA_tppGrafo pGrafo, char *email);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*
*
*
*  $EP Par�metros
*
*
*  $FV Valor retornado
*
*
***********************************************************************/

PER_tpCondRet PER_RetornaMensagens(GRA_tppGrafo pGrafo);

#undef PERFIL_EXT

/********** Fim do m�dulo de defini��o: PER  ???????????????? **********/

#else
#endif