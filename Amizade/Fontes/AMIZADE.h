#if ! defined( AMIZADE_ )
#define AMIZADE_
/***************************************************************************
*  $MCD M�dulo de defini��o: AMI  M�dulo Amizade
*
*  Arquivo gerado:              AMIZADE.h
*  Letras identificadoras:      AMI
*
*  Projeto: INF 1301 / Desenvolvimento de uma rede de relacionamentos em C
*  Gestor:  DI/PUC-Rio
*  Autores: Michelle Santiago (ms)
*
*  $HA Hist�rico de evolu��o:
*   Vers�o    Autor   	 Data     	Observa��es
*     1        ms      14/11/2017 	cria��o do arquivo
*	  2		   ms	   20/11/2017	altera��o no retorno de fun��es e tipo de alguns par�metros
*
*  $ED Descri��o do m�dulo
*
*    O m�dulo Amizade utiliza as fun��es do m�dulo grafo para criar amizades entre usu�rios, ou seja,
*    arestas entre v�rtices do grafo.
*	 
*
***************************************************************************/

#if defined( AMIZADE_OWN )
#define AMIZADE_EXT
#else
#define AMIZADE_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um perfil */

typedef struct AMI_tagAmizade AMI_tpAmizade;

/***********************************************************************
*  $TC Tipo de dados: AMI Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es de amizade
*
***********************************************************************/
// AVALIAR ISSO AQUI DEPOIS
typedef enum {

	AMI_CondRetOK,
	/* Concluiu corretamente */

	AMI_NaoPossuiAmizades,
	/* O usu�rio n�o possui amizades */

	AMI_NaoAceitou,
	/* O usu�rio n�o aceitou a solicita��o de amizade de outro */

	AMI_AmizadeNaoExiste,
	/* N�o encontrou amizade entre dois usu�rios */

	AMI_CondRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar uma amizade */

	AMI_CondRetRetornoGraIncorreto,
	/* Condicao de retorno do modulo Grafo imprevista*/
	
	AMI_CondRetRetornoPerIncorreto,
	/* Condicao de retorno do modulo Perfil imprevista*/

	//GRA_CondRetArestaJaExiste,
	/* Ja existe uma aresta entre os dois vertices passados*/

	AMI_UsuarioNaoExiste,
	/* Usu�rio fornecido n�o existe na rede*/
	
	//GRA_CondRetArestaParaSiMesmo
	/* Aresta de vertice tentando apontar para p proprio vertice*/
} AMI_tpCondRet;

/***********************************************************************
 *  $TC Tipo de dados: AMI Solicita��o
 *
 *
 *  $ED Descri��o do tipo
 *     Retorna se um us�ario aceitou ou n�o � solicita��o de amizade de um usu�rio ou n�o
 *
 ***********************************************************************/

typedef enum {
    
    AMI_SolicitacaoAceita,
    /* O usu�rio aceitou a solicita��o de amizade */
    
    AMI_SolicitacaoRejeitada,
    /* O usu�rio rejeitou a solicita��o de amizade */
    
} AMI_tpSolitacao;

/***********************************************************************
 *  $TC Tipo de dados: AMI Verifica��o
 *
 *
 *  $ED Descri��o do tipo
 *     Retorna se o usu�rio possui amizade com um segundo usu�rio ou n�o
 *
 ***********************************************************************/

 /*
typedef enum {
    
    AMI_ExisteAmizade,
    /* Foi verificado que a amizade entre dois usu�rios existe */
    
    AMI_NaoExisteAmizade,
    /* Foi verificado que a amizade entre dois usu�rios n�o existe */
    
} AMI_tpVerificacao;
*/

/***********************************************************************
*  $FC Fun��o: AMI  &Criar Amizade
*
*  $ED Descri��o da fun��o
*     Cria uma rela��o entre um usu�rio e outro.
*
*  $EP Par�metros
*     Usuario1  - ponteiro para um usu�rio da rede (um v�rtice do grafo) que solicitou a amizade
*	  Usuario2 	- ponteiro para outro usu�rio da rede (outro v�rtice diferente do grafo) na qual foi solicitada a amizade
*     Aceitacao - vari�vel booleana que cont�m a informa��o caso o segundo usu�rio aceitou ou n�o a solicita��o de amizade
*
*  $FV Valor retornado
*      AMI_CondRetOK
*      AMI_NaoAceitou
*	   AMI_UsuarioNaoExiste
*	   AMI_CondRetRetornoGraIncorreto
*	   AMI_CondRetRetornoPerIncorreto
*
***********************************************************************/

AMI_tpCondRet AMI_CriarAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil Usuario1, PER_tpPerfil Usuario2, AMI_tpSolitacao Aceitacao);


/***********************************************************************
*  $FC Fun��o: AMI  &Excluir Amizade
*
*  $ED Descri��o da fun��o
*     Exclui uma amizade entre dois usu�rios.
*
*  $EP Par�metros
*	  Usuario1 		- ponteiro para o primeiro usu�rio que realizou a exclus�o da amizade.
*     Usuario2      - ponteiro para o segundo usu�rio que ter� a amizade exclu�da.
*
*  $FV Valor retornado
*     AMI_CondRetOK
*	  AMI_UsuarioNaoExiste
*	  AMI_CondRetRetornoGraIncorreto
*	  AMI_CondRetRetornoPerIncorreto
*
***********************************************************************/

AMI_tpCondRet AMI_ExcluirAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil Usuario1, PER_tpPerfil Usuario2);


/***********************************************************************
*  $FC Fun���o: AMI  &Verificar N�mero de Amigos
*
*  $ED Descri��o da fun��o
*     Retorna o n�mero de amigos que um usu�rio possui.
*
*  $EP Par�metros
*     Usuario  - ponteiro para o usuario que solicitou o n�mero de amizades.
*     numAmizades - vari�vel que ir� armazenar o n�mero de amizades encontradas.
*
*  $FV Valor retornado
*     AMI_CondRetOK
*	  AMI_UsuarioNaoExiste
*     AMI_NaoPossuiAmizades
*	  AMI_CondRetRetornoPerIncorreto
*
***********************************************************************/

AMI_tpCondRet AMI_VerificarNumAmigos(PER_tpPerfil Usuario, int* numAmizades);

/***********************************************************************
*  $FC Fun��o: AMI  &Armazenar Amizades
*
*  $ED Descri��o da fun��o
*     Exibe as informa��es do perfil de cada amigo do usu�rio.
*
*  $EP Par�metros
*     Usuario  - ponteiro para o usu�rio que solicitou as informa��es das amizades
*
*  $FV Valor retornado
*     AMI_CondRetOK
*     AMI_NaoPossuiAmizades
*
***********************************************************************/

///////// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

AMI_tpCondRet AMI_ArmazenarAmizades(PER_tpPerfil Usuario);

/***********************************************************************
*  $FC Fun��o: AMI  &Excluir Todas as Amizades
*
*  $ED Descri��o da fun��o
*     Exclui todas as amizades de um usu�rio.
*
*  $EP Par�metros
*     Usuario - ponteiro para o usu�rio que ter� suas amizades apagadas
*
*  $FV Valor retornado
*     AMI_CondRetOK
*     AMI_NaoPossuiAmizades
*
***********************************************************************/

///////////////////// BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB

AMI_tpCondRet AMI_ExcluirTodasAmizades(PER_tpPerfil Usuario);

/***********************************************************************
*  $FC Fun��o: AMI  &Verificar Amizade
*
*  $ED Descri��o da fun��o
*     Verifica se o Usuario1 � amigo do Usuario2
*
*  $EP Par�metros
*     Usuario1 - ponteiro para o primeiro usu�rio que solicitou a verifica��o
*	  Usuario2 - ponteiro para o segundo usu�rio na quala  amizade ser� solicitada
*     ExisteAmizade - vari�vel booleana que afirma se existe amizade ou n�o entre os usu�rios
*
*  $FV Valor retornado
*     AMI_CondRetOK
*     AMI_UsuarioNaoExiste
*	  AMI_CondRetRetornoPerIncorreto
*	  AMI_CondRetRetornoGraIncorreto
*	  AMI_AmizadeNaoExiste
*
***********************************************************************/

AMI_tpCondRet AMI_VerificarAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil Usuario1, PER_tpPerfil Usuario2, AMI_tpVerificacao ExisteAmizade);


#undef AMIZADE_EXT

/********** Fim do m�dulo de defini��o: AMI  M�dulo Amizade **********/

#else
#endif