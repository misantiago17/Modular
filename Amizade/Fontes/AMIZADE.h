#if ! defined( AMIZADE_ )
#define AMIZADE_

#include "Perfil.h"

/***************************************************************************
*  $MCD MÛdulo de definiçÁ„o: AMI  MÛdulo Amizade
*
*  Arquivo gerado:              AMIZADE.h
*  Letras identificadoras:      AMI
*
*  Projeto: INF 1301 / Desenvolvimento de uma rede de relacionamentos em C
*  Gestor:  DI/PUC-Rio
*  Autores: Michelle Santiago (ms)
*
*  $HA HistÛrico de evoluçÁ„o:
*   Vers„o    Autor   	 Data     	ObservaçÁıes
*     1        ms      14/11/2017 	criaçÁ„o do arquivo
*	  2		   ms	   20/11/2017	alteraÁ„o no retorno de funÁıes e tipo de alguns par‚metros
*     3        ms      06/12/2017   modificação da descrição de retorno de parâmetros de funções
*
*  $ED DescriçÁ„o do mÛdulo
*
*    O mÛdulo Amizade utiliza as funçÁıes do mÛdulo grafo para criar amizades entre usu·rios, ou seja,
*    arestas entre vÈrtices do grafo.
*	 
*
***************************************************************************/

#if defined( AMIZADE_OWN )
#define AMIZADE_EXT
#else
#define AMIZADE_EXT extern
#endif

/***** DeclaraÁıes exportadas pelo mÛdulo *****/

/* Tipo referÍncia para uma amizade */

//typedef struct AMI_tagAmizade AMI_tpAmizade;

/***********************************************************************
*  $TC Tipo de dados: AMI CondiçÁıes de retorno
*
*
*  $ED DescriçÁ„o do tipo
*     CondiçÁıes de retorno das funçÁıes de amizade
*
***********************************************************************/

typedef enum {

	AMI_CondRetOK,
	/* Concluiu corretamente */

	AMI_NaoPossuiAmizades,
	/* O usu·rio n„o possui amizades */
	
	AMI_AmizadeJaExiste,
	/* O usu·rio n„o possui amizades */

	AMI_ArestaParaSiMesmo,
	/* Usuario tentou criar amizade com ele mesmo*/

	AMI_NaoAceitou,
	/* O usu·rio n„o aceitou a solicitaçÁ„o de amizade de outro */

	AMI_AmizadeNaoExiste,
	/* N„o encontrou amizade entre dois usu·rios */

	AMI_CondRetFaltouMemoria,
	/* Faltou memÛria ao tentar criar uma amizade */

	AMI_CondRetRetornoGraIncorreto,
	/* Condicao de retorno do mÛdulo Grafo imprevista */

	AMI_UsuarioNaoExiste
	/* Usu·rio fornecido n„o existe na rede */

} AMI_tpCondRet;

/***********************************************************************
 *  $TC Tipo de dados: AMI SolicitaçÁ„o
 *
 *
 *  $ED DescriçÁ„o do tipo
 *     Retorna se um usu·rio aceitou ou n„o a solicitaçÁ„o de amizade de um outro usu·rio
 *
 ***********************************************************************/

typedef enum {
    
    AMI_SolicitacaoAceita,
    /* O usu·rio aceitou a solicitaçÁ„o de amizade */
    
    AMI_SolicitacaoRejeitada
    /* O usu·rio rejeitou a solicitaçÁ„o de amizade */
    
} AMI_tpSolitacao;


/***********************************************************************
*  $FC FunçÁ„o: AMI  &Criar Amizade
*
*  $ED DescriçÁ„o da funçÁ„o
*     Cria uma relaçÁ„o entre um usu·rio e outro.
*
*  $EP Par‚metros
*     pGrafo    - grafo no qual se encontra a rede de usuários
*     Usuario1  - ponteiro para um usu·rio da rede (um vÈrtice do grafo) que solicitou a amizade
*	  Usuario2 	- ponteiro para outro usu·rio da rede (outro vÈrtice diferente do grafo) na 
*				  qual foi solicitada a amizade
*     Aceitacao - vari·vel booleana que contÍm a informaçÁ„o caso o segundo usu·rio aceitou 
*				  ou n„o a solicitaçÁ„o de amizade
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
*  $FC FunçÁ„o: AMI  &Excluir Amizade
*
*  $ED DescriçÁ„o da funçÁ„o
*     Exclui uma amizade entre dois usu·rios.
*
*  $EP Par‚metros
*     pGrafo        - grafo no qual se encontra a rede de usuários
*	  Usuario1 		- ponteiro para o primeiro usu·rio que realizou a exclus„o da amizade.
*     Usuario2      - ponteiro para o segundo usu·rio que ter· a amizade excluÌda.
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
*  $FC FunçÁ„o: AMI  &Verificar N˙mero de Amigos
*
*  $ED DescriçÁ„o da funçÁ„o
*     Retorna o número de amigos que um usu·rio possui.
*
*  $EP Par‚metros
*     pGrafo        - grafo no qual se encontra a rede de usuários
*     Usuario1      - ponteiro para o usu·rio que solicitou o n˙mero de amizades.
*     numAmizades   - vari·vel que ir· armazenar o n˙mero de amizades encontradas,
*                   esse ponteiro já deve estar alocado dinâmicamente.
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
*  $FC FunçÁ„o: AMI  &Armazenar Amizades
*
*  $ED DescriçÁ„o da funçÁ„o
*     Exibe as informaçÁıes do perfil de cada amigo do usu·rio.
*
*  $EP Par‚metros
*     pGrafo        - grafo no qual se encontra a rede de usuários
*     Usuario1      - ponteiro para o usu·rio que solicitou as informaçÁıes das amizades
*     PerfilAmigos  - lista de perfis no qual será armazenados os amigos do usuário.
*                    Esta lista já deve estar alocada dinâmicamente antes da chamada da função.
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
*  $FC FunçÁ„o: AMI  &Excluir Todas as Amizades
*
*  $ED DescriçÁ„o da funçÁ„o
*     Exclui todas as amizades de um usu·rio.
*
*  $EP Par‚metros
*     pGrafo    - grafo no qual se encontra a rede de usuários
*     Usuario1  - ponteiro para o usuário que ter· suas amizades apagadas
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
*  $FC FunçÁ„o: AMI  &Verificar Amizade
*
*  $ED DescriçÁ„o da funçÁ„o
*     Verifica se o Usuario1 È amigo do Usuario2
*
*  $EP Par‚metros
*     pGrafo    - grafo no qual se encontra a rede de usuários
*     Usuario1  - ponteiro para o primeiro usu·rio que solicitou a verificaçÁ„o
*	  Usuario2  - ponteiro para o segundo usu·rio na quala  amizade ser· solicitada
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

/********** Fim do mÛdulo de definiçÁ„o: AMI  MÛdulo Amizade **********/

#else
#endif
