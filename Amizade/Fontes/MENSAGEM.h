#if ! defined( MENSAGEM_ )
#define MENSAGEM_

#include"perfil.h"

/***************************************************************************
*  $MCD M�dulo de defini��o: MEN  Lista de Mensagens de cada perfil
*
*  Arquivo gerado:              MENSAGEM.h
*  Letras identificadoras:      MEN
*
*  Projeto: INF 1301 / Desenvolvimento de uma rede de relacionamentos em C
*  Gestor:  DI/PUC-Rio
*  Autores: Gabriel Busquim (gb), Michelle Santiago (ms)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor   	 Data     	Observa��es MEN_RetornaIdentificador
*     9        ms       06/11/2017 	revis�es finais e pequenas correc�es
*     6        gb       03/11/2017  altera���es no nome de fun���es
*     5        gb       02/11/2017  altera���es da condi���o de retorno
*     4        gb       01/11/2017 	modifica���o na descri���o do retorno das fun���es
*     3        gb       27/11/2017  altera���o da descricao de fun���es
*     2        gb       20/11/2017 	inclus�o da fun���o excluir mensagem
*     1        gb       15/11/2017 	inicio desenvolvimento
*
*  $ED Descri��o do m�dulo
*
*	 O modulo Mensagem implementa funcionalidades relacionadas ao envio e manuntencao das mensagens 
*	 recebidas/enviadas por cada perfil.
*    O modulo Lista foi acoplado a ele para que sua implementacao fosse possivel.
*	 
*
***************************************************************************/

#if defined( MENSAGEM_OWN )
#define MENSAGEM_EXT
#else
#define MENSAGEM_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma mensagem */

typedef struct MEN_tagMensagem * MEN_tppMensagem;

/***********************************************************************
*  $TC Tipo de dados: MEN Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es de Mensagem
*
***********************************************************************/

typedef enum {

	MEN_CondRetOK,
	/* Concluiu corretamente */

	MEN_CondRetListaVazia,
	/* Nao foi encontrada nenhuma mensagem */

	MEN_CondRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar um elemento da lista */

	MEN_CondRetMesmoPerfil,
	/* Tentou-se escrever uma mensagem de um perfil para ele mesmo. */

	MEN_CondRetRetornoLisIncorreto,
	/* Condicao de retorno do modulo Lista imprevista */

	MEN_CondRetPerfilInvalido,
	/* Perfil passado como parametro nao existe */
	
	MEN_CondRetParametroIncorreto,
	/* Parametro passado esta diferente do especificado */

	MEN_CondRetMensagemVazia,
	/* A mensagem enviada nao possui nenhum caracter */

	MEN_CondRetMensagemExcedeuTamanho,
	/* A mensagem enviada possui mais caracteres do que o maximo permitido */

	MEN_CondRetNaoEncontrouMensagem
	/* A mensagem procurada nao foi encontrada */

} MEN_tpCondRet;

/***********************************************************************
*  $TC Tipo de dados: MEN Condi�ao de cada mensagem
*
*
*  $ED Descri��o do tipo
*     Condi�ao que cada mensagem pode possuir(enviada ou recebida)
*
***********************************************************************/
typedef enum {

	MEN_CondMsgEnviada,
	/* A mensagem foi enviada */

	MEN_CondMsgRecebida
	/* A mensagem foi recebida */

} MEN_tpCondMsg;

/***********************************************************************
*  $FC Fun��o: MEN  &Escrever Mensagem
*
*  $ED Descri��o da fun��o
*     Escreve uma mensagem de um perfil para outro. Tal mensagem � criada tanto no perfil do usuario que
*     envia a mensagem quanto no do que recebe.
*
*  $EP Par�metros
*     Remetente  	- Perfil do usuario que envia a mensagem.
*	  Destinatario 	- Perfil do usuario que recebe a mensagem.
*     MensagemEnv 	- Conteudo da mensagem
*
*  $FV Valor retornado
*     MEN_CondRetOK
*     MEN_CondRetRetornoLisIncorreto
*     MEN_CondRetMensagemExcedeuTamanho
*     MEN_CondRetMensagemVazia
*     MEN_CondRetMesmoPerfil
*     MEN_CondRetPerfilInvalido
*     MEN_CondRetFaltouMemoria
*
***********************************************************************/

MEN_tpCondRet MEN_EscreverMensagem( PER_tpPerfil * Remetente,PER_tpPerfil *Destinatario,char MensagemEnv[])  ;


/***********************************************************************
*  $FC Fun��o: MEN  &Excluir Mensagem
*
*  $ED Descri��o da fun��o
*     Exclui uma mensagem de uma lista de mensagens. A mensagem e somente apagada
*	  da lista de mensagens do perfil passado como parametro.	
*
*  $EP Par�metros
*	  Perfil  	- perfil do usu�rio o qual deseja-se apagar uma mensagem
*     flagMsg	- tipo de mensagem que deseja-se excluir(enviada ou recebida).
*	  Email 	- email do perfil relacionado a mensagem
*	  Mensagem 	- conte�do da mensagem que deseja-se apagar 
*
*  $FV Valor retornado
*     MEN_CondRetOK
*     MEN_CondRetRetornoLisIncorreto
*     MEN_CondRetListaVazia
*     MEN_CondRetNaoEncontrouMensagem
*     MEN_CondRetPerfilInvalido
*
***********************************************************************/

MEN_tpCondRet MEN_ExcluirMensagem(PER_tpPerfil * Perfil,char Email[],MEN_tpCondMsg flagMsg,char Mensagem[]);

/***********************************************************************
*  $FC Fun��o: MEN  &Excluir Mensagens de um Email
*
*  $ED Descri��o da fun��o
*	Exclui todas as mensagens de uma lista de mensagens cujo email �
*	igual ao passado como parametro.As mensagens sao somente apagadas
*	da lista de mensagens do perfil passado como parametro.	
*
*  $EP Par�metros
*	  Perfil    - perfil do usu�rio o qual deseja-se apagar as mensagens
*	  Email 	- email do perfil relacionado a mensagem  
*
*  $FV Valor retornado
*     MEN_CondRetOK
*     MEN_CondRetRetornoLisIncorreto
*     MEN_CondRetPerfilInvalido
*
***********************************************************************/

MEN_tpCondRet MEN_ExcluirMensagensEmail(PER_tpPerfil * Perfil,char Email[]);

/***********************************************************************
*  $FC Fun��o: MEN  &Modificar Email da lista de mensagens
*
*  $ED Descri��o da fun��o
*	Modifica o email todas as mensagens de uma lista de mensagens cujo email �
*	igual ao passado como parametro.O novo email sera o outro email passado
*	como parametro.	
*
*  $EP Par�metros
*	  Perfil  		- perfil do usu�rio o qual deseja-se modificar as mensagens
*	  antigoEmail 	- antigo email do perfil relacionado a mensagem
*	  novoEmail 	- novo email do perfil relacionado a mensagem
*
*  $FV Valor retornado
*     MEN_CondRetOK
*     MEN_CondRetRetornoLisIncorreto
*     MEN_CondRetPerfilInvalido
*
***********************************************************************/

MEN_tpCondRet MEN_ModificarEmailLista(PER_tpPerfil * Perfil,char antigoEmail[],char novoEmail[]);


/***********************************************************************
*  $FC Fun��o: MEN  &Obter N�mero de Mensagens
*
*  $ED Descri��o da fun��o
*     Retorna por refer�ncia o numero de mensagens enviadas ou recebidas,dependendo 
*     do valor passado como parametro
*
*  $EP Par�metros
*     Perfil  		- perfil do usu�rio o qual deseja-se saber o numero de mensagens
*     flagMsg		- tipo de Mensagem procurada.
*     numMensagens 	- ponteiro para armazenar o numero de mensagens
*
*  $FV Valor retornado
*     MEN_CondRetOK
*     MEN_CondRetParametroIncorreto
*     MEN_CondRetRetornoLisIncorreto
*     MEN_CondRetListaVazia
*     MEN_CondRetPerfilInvalido
*
***********************************************************************/

MEN_tpCondRet MEN_ObterNumMensagens(PER_tpPerfil * Perfil,MEN_tpCondMsg flagMsg, int* numMsgs)  ;


/***********************************************************************
*  $FC Fun��o: MEN  &Obter N�mero Total de Mensagens
*
*  $ED Descri��o da fun��o
*     Retorna por refer�ncia o numero de todas as mensagens referentes a um perfil
*
*  $EP Par�metros
*     Perfil  		- perfil do usu�rio o qual deseja-se saber o numero de mensagens
*     numMensagens 	- ponteiro para armazenar o numero de mensagens
*
*  $FV Valor retornado
*     MEN_CondRetOK
*     MEN_CondRetParametroIncorreto
*     MEN_CondRetRetornoLisIncorreto
*     MEN_CondRetPerfilInvalido
*
***********************************************************************/

MEN_tpCondRet MEN_ObterNumTodasMensagens(PER_tpPerfil * Perfil, int* numTotalMsgs) ;


/***********************************************************************
*  $FC Fun��o: MEN  &Obter Todas Mensagens
*
*  $ED Descri��o da fun��o
*     Armazena em 3 vetores passados como parametro as informacoes relativas a cada elemento 
*	da lista de Mensagens
*
*  $EP Par�metros
*     Perfil  		- perfil do usu�rio o qual deseja-se saber as mensagens
*	  vetTipos 		- vetor ja alocado para armazenar o tipo de cada mensagem
*	  vetEmails 	- vetor ja alocado para armazenar o email relativo a cada mensagem
*	  vetMensagens  - vetor ja alocado para armazenar as mensagens
*
*  $FV Valor retornado
*	  MEN_CondRetOK
*	  MEN_CondRetPerfilInvalido
*	  MEN_CondRetListaVazia
*	  MEN_CondRetRetornoLisIncorreto
*	  MEN_CondRetParametroIncorreto
*
***********************************************************************/

MEN_tpCondRet MEN_ObterTodasMensagens(PER_tpPerfil * Perfil, MEN_tpCondMsg vetTipos[],char* vetEmails[], char* vetMensagens[] );


/***********************************************************************
*  $FC Fun��o: MEN  &Obter Mensagens
*
*  $ED Descri��o da fun��o
*     Armazena em 2 vetores as informacoes relativas as mensagens enviadas
*	  ou recebidas por um perfil,dependendo do valor do
*	  parametro fornecido
*
*  $EP Par�metros
*     Perfil  		- perfil do usu�rio o qual deseja-se saber as mensagens
*	  vetEmails 	- vetor ja alocado para armazenar o email relativo a cada mensagem
*	  vetMensagens  - vetor ja alocado para armazenar as mensagens
*	  flagMsg		- tipo de mensagem que deseja-se armazenar(enviada ou recebida).
*
*  $FV Valor retornado
*	  MEN_CondRetOK
*	  MEN_CondRetPerfilInvalido
*	  MEN_CondRetListaVazia
*	  MEN_CondRetRetornoLisIncorreto
*	  MEN_CondRetParametroIncorreto
*
***********************************************************************/

MEN_tpCondRet MEN_ObterMensagens(PER_tpPerfil * Perfil, char* vetEmails[], char* vetMensagens[],MEN_tpCondMsg flagMsg);


/********** Fim do m�dulo de defini��o: MEN  MENfo Gen�rico com Cabe�a **********/

#else
#endif
