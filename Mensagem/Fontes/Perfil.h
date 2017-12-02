#if ! defined(PERFIL_ )
#define PERFIL_
/***************************************************************************
*  $MCD M�dulo de defini��o: PER Gerenciamento de perfil
*
*  Arquivo gerado:              PERFIL.h
*  Letras identificadoras:      PER
*
*  Projeto: INF 1301 / Desenvolvimento de uma rede de relacionamentos em C
*  Gestor:  DI/PUC-Rio
*  Autores: Renan Moreira (rm)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor   	 Data     	Observa��es
*     1      rm       27/09/2017 	inicio desenvolvimento
*
*  $ED Descri��o do m�dulo
*
*	Modulo que armazena dados relativo ao usuario que ser� armazenado na rede.
*	Ele utiliza vertices de um grafo para armazenar os usuarios.
*	N�o podem haver emails repetidos
*	O email � uma string de at� 100 caracteres que deve ter ao menos 3 digitos seguidos por 
*	  um @, seguidos por mais dois trechos de pelo menos 1 digito cada separados por um ponto
*	O primeiro e ultimo nome da pessoa deve ser uma string de ate 50 caracteres sem numeros
*	O dia, m�s e ano da data devem ser validos, considerando anos bissextos e s� podem ser
*	   inseridos anos entre 1900 e 2017
*	A cidade deve ser uma string de at� 50 caracteres  
*	O id est� relacionado a um perfil, por�m pode ser alterado ap�s opera��es de exclus�o de perfil
*
***************************************************************************/

#if defined( PERFIL_OWN )
#define PERFIL_EXT
#else
#define PERFIL_EXT extern
#endif

#include   "GRAFO.h"
#include   "LISTA.h"
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
	/* Concluiu corretamente */

	PER_CondRetEmailInvalido,
	/*Email inserido nao � um email valido*/

	PER_CondRetEmailJaCadastrado,
	/*Email inserido j� est� cadastrado*/

	PER_CondRetDataInvalida,
	/*Data inserida nao � valida*/

	PER_CondRetNomeInvalido,
	/*Nome inserido nao � valido*/

	PER_CondRetCidadeInvalida,
	/*Cidade inserida nao � valida*/

	PER_CondRetEmailInexistente,
	/*Email buscado nao existe*/

	PER_CondRetFaltouMemoria,
	/* Faltou mem�ria ao tentar alocar espa�o*/

	PER_CondRetRetornoLisIncorreto,
	/* Condicao de retorno do modulo Lista imprevista*/

	PER_CondRetRedeVazia,
	/*A rede n�o possui nenhum perfil criado*/

	PER_CondRetPerfilInexistente,
	/*Ponteiro para perfil passado como parametro nao existe*/

	PER_CondRetParametroGRAIncorreto,
	/*Grafo passado como parametro nao � valido*/

	PER_CondRetPerfilInvalido,
	/*Ponteiro para perfil passado como parametro nao � valido*/

	PER_CondRetRetornoGRAInesperado,
	/*Retorno do modulo grafo inesperado*/

	PER_CondRetRetornoMsgIncorreto
	/*Retorno do modulo mensagem incorreto*/
} PER_tpCondRet;

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*	Cria um novo perfil na rede social
*
*  $EP Par�metros
*     pGrafo		- Ponteiro para o grafo da rede social
*     perfil		- Ponteiro de retorno para o perfil que ser� criado
*     email			- Email do usuario
*     primeiroNome	- Primeiro nome do usuario
*     ultimoNome	- Ultimo nome do usuario
*     diaNasc		- Dia do nascimento do usuario
*     mesNasc		- M�s do nascimento do usuario
*     anoNasc		- Ano do nascimento do usuario
*     cidade		- Cidade na qual o usuario vive
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetEmailJaCadastrado
*     PER_CondRetEmailInvalido
*     PER_CondRetNomeInvalido
*     PER_CondRetDataInvalida
*     PER_CondRetCidadeInvalida
*     PER_CondRetFaltouMemoria
*
***********************************************************************/

PER_tpCondRet PER_CriarPerfil(GRA_tppGrafo pGrafo, PER_tpPerfil **perfil, char *email, char *primeiroNome, char *ultimoNome,
							  int diaNasc, int mesNasc, int anoNasc, char *cidade);

/***********************************************************************
*  $FC Fun��o: 
*
*  $ED Descri��o da fun��o
*     Exclui um perfil da rede social atrav�s do seu email
*
*  $EP Par�metros
*	  pGrafo		- Ponteiro para o grafo da rede social
*     email			- Email do usuario que ser� excluido
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetEmailInexistente
*     PER_CondRetRetornoLisIncorreto
*	  PER_CondRetRetornoMsgIncorreto
*
***********************************************************************/

PER_tpCondRet PER_ExcluirPerfil(GRA_tppGrafo pGrafo, char *email);


/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*	  Retorna os dados de um perfil
*
*
*  $EP Par�metros
*     perfil		- Ponteiro para o perfil no qual se busca os dados
*     email			- Ponteiro para retorno do email do usuario
*     primeiroNome	- Ponteiro para retorno do primeiro nome do usuario
*     ultimoNome	- Ponteiro para retorno do ultimo nome do usuario
*     diaNasc		- Ponteiro para retorno do dia do nascimento do usuario
*     mesNasc		- Ponteiro para retorno do m�s do nascimento do usuario
*     anoNasc		- Ponteiro para retorno do ano do nascimento do usuario
*     cidade		- Ponteiro para retorno da cidade na qual o usuario vive
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetPerfilInvalido
*
***********************************************************************/

PER_tpCondRet PER_ObterPerfil(PER_tpPerfil *perfil, char *email, char *primeiroNome, char *ultimoNome,
							  int *diaNasc, int *mesNasc, int *anoNasc, char *cidade);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*	  Retorna a quantidade de perfis existentes na rede social
*
*  $EP Par�metros
*     pGrafo	- Ponteiro para o grafo da rede social
*     qtd		- Ponteiro para retorno da quantidade de usuarios
*
*  $FV Valor retornado
*     PER_CondRetOK
*	  PER_CondRetParametroGRAIncorreto
*
***********************************************************************/

PER_tpCondRet PER_NumeroPerfis(GRA_tppGrafo pGrafo, int *qtd);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*	  Modifica o email de um usuario.
*	  Em caso de falha as informa��es permanecer�o inalteradas
*
*  $EP Par�metros
*     pGrafo		- Ponteiro para o grafo da rede social
*     emailAtual	- Email atual do usuario que deseja ser modificado
*     emailNovo		- Email novo do usuario ap�s a modifica��o
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetEmailJaCadastrado
*     PER_CondRetEmailInvalido
*     PER_CondRetEmailInexistente
*	  PER_CondRetRetornoMsgIncorreto
*
***********************************************************************/

PER_tpCondRet PER_ModificaEmail(GRA_tppGrafo pGrafo, char *emailAtual, char *emailNovo);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*	  Modifica o nome de um usuario.
*	  Em caso de falha as informa��es permanecer�o inalteradas
*
*  $EP Par�metros
*     pGrafo		- Ponteiro para o grafo da rede social
*     email			- Email do usuario que deseja ser modificado
*     primeiroNome	- Primeiro nome novo ap�s a altera��o
*     ultimoNome	- Ultimo nome novo ap�s a altera��o
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetNomeInvalido
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetEmailInexistente
*
***********************************************************************/

PER_tpCondRet PER_ModificaNome(GRA_tppGrafo pGrafo, char *email, char *primeiroNome, char *ultimoNome);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*	  Modifica a data de nascimento de um usuario.
*	  Em caso de falha as informa��es permanecer�o inalteradas
*
*  $EP Par�metros
*     pGrafo	- Ponteiro para o grafo da rede social
*     email		- Email do usuario que deseja ser modificado
*     diaNasc	- Dia do nascimento novo ap�s a altera��o
*     mesNasc	- Mes do nascimento novo ap�s a altera��o
*     anoNasc	- Ano do nascimento novo ap�s a altera��o
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetDataInvalida
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetEmailInexistente
*
***********************************************************************/

PER_tpCondRet PER_ModificaDataNasc(GRA_tppGrafo pGrafo, char *email, int diaNasc, int mesNasc, int anoNasc);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*	  Modifica a cidade atual de um usuario.
*	  Em caso de falha as informa��es permanecer�o inalteradas
*
*  $EP Par�metros
*     pGrafo	- Ponteiro para o grafo da rede social
*     email		- Email do usuario que deseja ser modificado
*     diaNasc	- Cidade atual nova ap�s a altera��o
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetCidadeInvalida
*     PER_CondRetEmailInexistente
*     PER_CondRetParametroGRAIncorreto
*
***********************************************************************/

PER_tpCondRet PER_ModificaCidade(GRA_tppGrafo pGrafo, char *email, char *cidade);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*	  Busca o perfil e o id referente a um email
*
*  $EP Par�metros
*     pGrafo	- Ponteiro para o grafo da rede social
*     email		- Email do usuario que deseja ser buscado
*     perfil	- Ponteiro de retorno para o perfil buscado
*     id		- Ponteiro de retorno para a Id referente ao email
*
*  $FV Valor retornado
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRedeVazia
*     PER_CondRetEmailJaCadastrado
*     PER_CondRetEmailInexistente
*
***********************************************************************/

PER_tpCondRet PER_BuscaEmail(GRA_tppGrafo pGrafo, char *email, PER_tpPerfil **perfil, int *id);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*	Exclui todos os emails de uma rede
*
*  $EP Par�metros
*     pGrafo	- Ponteiro para o grafo da rede social
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*
***********************************************************************/

PER_tpCondRet PER_ExcluirTodosPerfis(GRA_tppGrafo pGrafo);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*	  Retorna a lista de mensagens de um perfil
*
*  $EP Par�metros
*     perfil	- Ponteiro para o perfil desejado
*     mensagens	- Ponteiro de retorno para a lista de mensagens desse perfil
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetPerfilInexistente
*
***********************************************************************/

PER_tpCondRet PER_retornaLisMensagens(PER_tpPerfil *perfil, LIS_tppLista *mensagens);

/***********************************************************************
*  $FC Fun��o:
*
*  $ED Descri��o da fun��o
*	 Retorna o id referente a um perfil[
*
*  $EP Par�metros
*     pGrafo	- Ponteiro para o grafo da rede social
*     perfil	- Ponteiro para o perfil desejado
*     id		- Ponteiro de retorno para a Id referente ao perfil
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetPerfilInexistente
*
***********************************************************************/
PER_tpCondRet PER_retornaIdPerfil(GRA_tppGrafo pGrafo, PER_tpPerfil *perfil, int *id);

#undef PERFIL_EXT

/********** Fim do m�dulo de defini��o: PER  ???????????????? **********/

#else
#endif