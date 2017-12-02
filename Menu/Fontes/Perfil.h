#if ! defined(PERFIL_ )
#define PERFIL_
/***************************************************************************
*  $MCD Módulo de definição: PER Gerenciamento de perfil
*
*  Arquivo gerado:              PERFIL.h
*  Letras identificadoras:      PER
*
*  Projeto: INF 1301 / Desenvolvimento de uma rede de relacionamentos em C
*  Gestor:  DI/PUC-Rio
*  Autores: Renan Moreira (rm)
*
*  $HA Histórico de evolução:
*     Versão  Autor   	 Data     	Observações
*     1      rm       27/09/2017 	inicio desenvolvimento
*
*  $ED Descrição do módulo
*
*	Modulo que armazena dados relativo ao usuario que será armazenado na rede.
*	Ele utiliza vertices de um grafo para armazenar os usuarios.
*	Não podem haver emails repetidos
*	O email é uma string de até 100 caracteres que deve ter ao menos 3 digitos seguidos por 
*	  um @, seguidos por mais dois trechos de pelo menos 1 digito cada separados por um ponto
*	O primeiro e ultimo nome da pessoa deve ser uma string de ate 50 caracteres sem numeros
*	O dia, mês e ano da data devem ser validos, considerando anos bissextos e só podem ser
*	   inseridos anos entre 1900 e 2017
*	A cidade deve ser uma string de até 50 caracteres  
*	O id está relacionado a um perfil, porém pode ser alterado após operações de exclusão de perfil
*
***************************************************************************/

#if defined( PERFIL_OWN )
#define PERFIL_EXT
#else
#define PERFIL_EXT extern
#endif

#include   "GRAFO.h"
#include   "LISTA.h"
/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um perfil */

typedef struct PER_tagPerfil PER_tpPerfil;

/***********************************************************************
*  $TC Tipo de dados: PER Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do perfil
*
***********************************************************************/

typedef enum {
	PER_CondRetOK,
	/* Concluiu corretamente */

	PER_CondRetEmailInvalido,
	/*Email inserido nao é um email valido*/

	PER_CondRetEmailJaCadastrado,
	/*Email inserido já está cadastrado*/

	PER_CondRetDataInvalida,
	/*Data inserida nao é valida*/

	PER_CondRetNomeInvalido,
	/*Nome inserido nao é valido*/

	PER_CondRetCidadeInvalida,
	/*Cidade inserida nao é valida*/

	PER_CondRetEmailInexistente,
	/*Email buscado nao existe*/

	PER_CondRetFaltouMemoria,
	/* Faltou memória ao tentar alocar espaço*/

	PER_CondRetRetornoLisIncorreto,
	/* Condicao de retorno do modulo Lista imprevista*/

	PER_CondRetRedeVazia,
	/*A rede não possui nenhum perfil criado*/

	PER_CondRetPerfilInexistente,
	/*Ponteiro para perfil passado como parametro nao existe*/

	PER_CondRetParametroGRAIncorreto,
	/*Grafo passado como parametro nao é valido*/

	PER_CondRetPerfilInvalido,
	/*Ponteiro para perfil passado como parametro nao é valido*/

	PER_CondRetRetornoGRAInesperado,
	/*Retorno do modulo grafo inesperado*/

	PER_CondRetRetornoMsgIncorreto
	/*Retorno do modulo mensagem incorreto*/
} PER_tpCondRet;

/***********************************************************************
*  $FC Função:
*
*  $ED Descrição da função
*	Cria um novo perfil na rede social
*
*  $EP Parâmetros
*     pGrafo		- Ponteiro para o grafo da rede social
*     perfil		- Ponteiro de retorno para o perfil que será criado
*     email			- Email do usuario
*     primeiroNome	- Primeiro nome do usuario
*     ultimoNome	- Ultimo nome do usuario
*     diaNasc		- Dia do nascimento do usuario
*     mesNasc		- Mês do nascimento do usuario
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
*  $FC Função: 
*
*  $ED Descrição da função
*     Exclui um perfil da rede social através do seu email
*
*  $EP Parâmetros
*	  pGrafo		- Ponteiro para o grafo da rede social
*     email			- Email do usuario que será excluido
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
*  $FC Função:
*
*  $ED Descrição da função
*	  Retorna os dados de um perfil
*
*
*  $EP Parâmetros
*     perfil		- Ponteiro para o perfil no qual se busca os dados
*     email			- Ponteiro para retorno do email do usuario
*     primeiroNome	- Ponteiro para retorno do primeiro nome do usuario
*     ultimoNome	- Ponteiro para retorno do ultimo nome do usuario
*     diaNasc		- Ponteiro para retorno do dia do nascimento do usuario
*     mesNasc		- Ponteiro para retorno do mês do nascimento do usuario
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
*  $FC Função:
*
*  $ED Descrição da função
*	  Retorna a quantidade de perfis existentes na rede social
*
*  $EP Parâmetros
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
*  $FC Função:
*
*  $ED Descrição da função
*	  Modifica o email de um usuario.
*	  Em caso de falha as informações permanecerão inalteradas
*
*  $EP Parâmetros
*     pGrafo		- Ponteiro para o grafo da rede social
*     emailAtual	- Email atual do usuario que deseja ser modificado
*     emailNovo		- Email novo do usuario após a modificação
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
*  $FC Função:
*
*  $ED Descrição da função
*	  Modifica o nome de um usuario.
*	  Em caso de falha as informações permanecerão inalteradas
*
*  $EP Parâmetros
*     pGrafo		- Ponteiro para o grafo da rede social
*     email			- Email do usuario que deseja ser modificado
*     primeiroNome	- Primeiro nome novo após a alteração
*     ultimoNome	- Ultimo nome novo após a alteração
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
*  $FC Função:
*
*  $ED Descrição da função
*	  Modifica a data de nascimento de um usuario.
*	  Em caso de falha as informações permanecerão inalteradas
*
*  $EP Parâmetros
*     pGrafo	- Ponteiro para o grafo da rede social
*     email		- Email do usuario que deseja ser modificado
*     diaNasc	- Dia do nascimento novo após a alteração
*     mesNasc	- Mes do nascimento novo após a alteração
*     anoNasc	- Ano do nascimento novo após a alteração
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
*  $FC Função:
*
*  $ED Descrição da função
*	  Modifica a cidade atual de um usuario.
*	  Em caso de falha as informações permanecerão inalteradas
*
*  $EP Parâmetros
*     pGrafo	- Ponteiro para o grafo da rede social
*     email		- Email do usuario que deseja ser modificado
*     diaNasc	- Cidade atual nova após a alteração
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
*  $FC Função:
*
*  $ED Descrição da função
*	  Busca o perfil e o id referente a um email
*
*  $EP Parâmetros
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
*  $FC Função:
*
*  $ED Descrição da função
*	Exclui todos os emails de uma rede
*
*  $EP Parâmetros
*     pGrafo	- Ponteiro para o grafo da rede social
*
*  $FV Valor retornado
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*
***********************************************************************/

PER_tpCondRet PER_ExcluirTodosPerfis(GRA_tppGrafo pGrafo);

/***********************************************************************
*  $FC Função:
*
*  $ED Descrição da função
*	  Retorna a lista de mensagens de um perfil
*
*  $EP Parâmetros
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
*  $FC Função:
*
*  $ED Descrição da função
*	 Retorna o id referente a um perfil[
*
*  $EP Parâmetros
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

/********** Fim do módulo de definição: PER  ???????????????? **********/

#else
#endif