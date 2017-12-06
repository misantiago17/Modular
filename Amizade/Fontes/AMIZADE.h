#if ! defined( AMIZADE_ )
#define AMIZADE_

#include "Perfil.h"

/***************************************************************************
*  $MCD M�dulo de defini���o: AMI  M�dulo Amizade
*
*  Arquivo gerado:              AMIZADE.h
*  Letras identificadoras:      AMI
*
*  Projeto: INF 1301 / Desenvolvimento de uma rede de relacionamentos em C
*  Gestor:  DI/PUC-Rio
*  Autores: Michelle Santiago (ms)
*
*  $HA Hist�rico de evolu���o:
*   Vers�o    Autor   	 Data     	Observa���es
*     1        ms      14/11/2017 	cria���o do arquivo
*	  2		   ms	   20/11/2017	altera��o no retorno de fun��es e tipo de alguns par�metros
*     3        ms      06/12/2017   modifica��o da descri��o de retorno de par�metros de fun��es
*
*  $ED Descri���o do m�dulo
*
*    O m�dulo Amizade utiliza as fun���es do m�dulo grafo para criar amizades entre usu�rios, ou seja,
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

/* Tipo refer�ncia para uma amizade */

//typedef struct AMI_tagAmizade AMI_tpAmizade;

/***********************************************************************
*  $TC Tipo de dados: AMI Condi���es de retorno
*
*
*  $ED Descri���o do tipo
*     Condi���es de retorno das fun���es de amizade
*
***********************************************************************/

typedef enum {

	AMI_CondRetOK,
	/* Concluiu corretamente */

	AMI_NaoPossuiAmizades,
	/* O usu�rio n�o possui amizades */
	
	AMI_AmizadeJaExiste,
	/* O usu�rio n�o possui amizades */

	AMI_ArestaParaSiMesmo,
	/* Usuario tentou criar amizade com ele mesmo*/

	AMI_NaoAceitou,
	/* O usu�rio n�o aceitou a solicita���o de amizade de outro */

	AMI_AmizadeNaoExiste,
	/* N�o encontrou amizade entre dois usu�rios */

	AMI_CondRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar uma amizade */

	AMI_CondRetRetornoGraIncorreto,
	/* Condicao de retorno do m�dulo Grafo imprevista */

	AMI_UsuarioNaoExiste
	/* Usu�rio fornecido n�o existe na rede */

} AMI_tpCondRet;

/***********************************************************************
 *  $TC Tipo de dados: AMI Solicita���o
 *
 *
 *  $ED Descri���o do tipo
 *     Retorna se um usu�rio aceitou ou n�o a solicita���o de amizade de um outro usu�rio
 *
 ***********************************************************************/

typedef enum {
    
    AMI_SolicitacaoAceita,
    /* O usu�rio aceitou a solicita���o de amizade */
    
    AMI_SolicitacaoRejeitada
    /* O usu�rio rejeitou a solicita���o de amizade */
    
} AMI_tpSolitacao;


/***********************************************************************
*  $FC Fun���o: AMI  &Criar Amizade
*
*  $ED Descri���o da fun���o
*     Cria uma rela���o entre um usu�rio e outro.
*
*  $EP Par�metros
*     pGrafo    - grafo no qual se encontra a rede de usu�rios
*     Usuario1  - ponteiro para um usu�rio da rede (um v�rtice do grafo) que solicitou a amizade
*	  Usuario2 	- ponteiro para outro usu�rio da rede (outro v�rtice diferente do grafo) na 
*				  qual foi solicitada a amizade
*     Aceitacao - vari�vel booleana que cont�m a informa���o caso o segundo usu�rio aceitou 
*				  ou n�o a solicita���o de amizade
*
*  $FV Valor retornado
*     AMI_CondRetOK
*     AMI_NaoAceitou
*     AMI_UsuarioNaoExiste
*     AMI_ArestaParaSiMesmo
*     AMI_AmizadeJaExiste
*     AMI_CondRetRetornoGraIncorreto
*
***********************************************************************/

AMI_tpCondRet AMI_CriarAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil * Usuario2, AMI_tpSolitacao Aceitacao);


/***********************************************************************
*  $FC Fun���o: AMI  &Excluir Amizade
*
*  $ED Descri���o da fun���o
*     Exclui uma amizade entre dois usu�rios.
*
*  $EP Par�metros
*     pGrafo        - grafo no qual se encontra a rede de usu�rios
*	  Usuario1 		- ponteiro para o primeiro usu�rio que realizou a exclus�o da amizade.
*     Usuario2      - ponteiro para o segundo usu�rio que ter� a amizade exclu�da.
*
*  $FV Valor retornado
*      AMI_CondRetOK
*      AMI_UsuarioNaoExiste
*      AMI_AmizadeNaoExiste
*      AMI_CondRetRetornoGraIncorreto
*
***********************************************************************/

AMI_tpCondRet AMI_ExcluirAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil * Usuario2);


/***********************************************************************
*  $FC Fun���o: AMI  &Verificar N�mero de Amigos
*
*  $ED Descri���o da fun���o
*     Retorna o n�mero de amigos que um usu�rio possui.
*
*  $EP Par�metros
*     pGrafo        - grafo no qual se encontra a rede de usu�rios
*     Usuario1      - ponteiro para o usu�rio que solicitou o n�mero de amizades.
*     numAmizades   - vari�vel que ir� armazenar o n�mero de amizades encontradas,
*                   esse ponteiro j� deve estar alocado din�micamente.
*
*  $FV Valor retornado
*      AMI_CondRetOK
*      AMI_UsuarioNaoExiste
*      AMI_NaoPossuiAmizades
*      AMI_CondRetRetornoGraIncorreto
*
***********************************************************************/

AMI_tpCondRet AMI_VerificarNumAmigos(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, int* numAmizades);

/***********************************************************************
*  $FC Fun���o: AMI  &Armazenar Amizades
*
*  $ED Descri���o da fun���o
*     Exibe as informa���es do perfil de cada amigo do usu�rio.
*
*  $EP Par�metros
*     pGrafo        - grafo no qual se encontra a rede de usu�rios
*     Usuario1      - ponteiro para o usu�rio que solicitou as informa���es das amizades
*     PerfilAmigos  - lista de perfis no qual ser� armazenados os amigos do usu�rio.
*                    Esta lista j� deve estar alocada din�micamente antes da chamada da fun��o.
*
*  $FV Valor retornado
*      AMI_CondRetOK
*      AMI_NaoPossuiAmizades
*      AMI_UsuarioNaoExiste
*      AMI_CondRetFaltouMemoria
*      AMI_CondRetRetornoGraIncorreto
*
***********************************************************************/


AMI_tpCondRet AMI_ArmazenarAmizades(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil **PerfilAmigos);

/***********************************************************************
*  $FC Fun���o: AMI  &Excluir Todas as Amizades
*
*  $ED Descri���o da fun���o
*     Exclui todas as amizades de um usu�rio.
*
*  $EP Par�metros
*     pGrafo    - grafo no qual se encontra a rede de usu�rios
*     Usuario1  - ponteiro para o usu�rio que ter� suas amizades apagadas
*
*  $FV Valor retornado
*      AMI_CondRetOK
*      AMI_UsuarioNaoExiste
*      AMI_NaoPossuiAmizades
*      AMI_CondRetFaltouMemoria
*      AMI_CondRetRetornoGraIncorreto
*
***********************************************************************/

AMI_tpCondRet AMI_ExcluirTodasAmizades(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1);

/***********************************************************************
*  $FC Fun���o: AMI  &Verificar Amizade
*
*  $ED Descri���o da fun���o
*     Verifica se o Usuario1 � amigo do Usuario2
*
*  $EP Par�metros
*     pGrafo    - grafo no qual se encontra a rede de usu�rios
*     Usuario1  - ponteiro para o primeiro usu�rio que solicitou a verifica���o
*	  Usuario2  - ponteiro para o segundo usu�rio na quala  amizade ser� solicitada
*
*  $FV Valor retornado
*      AMI_CondRetOK
*      AMI_UsuarioNaoExiste
*      AMI_CondRetRetornoGraIncorreto
*      AMI_AmizadeNaoExiste
*
***********************************************************************/


AMI_tpCondRet AMI_VerificarAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil * Usuario2);


#undef AMIZADE_EXT

/********** Fim do m�dulo de defini���o: AMI  M�dulo Amizade **********/

#else
#endif
