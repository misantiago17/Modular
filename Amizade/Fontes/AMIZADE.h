#if ! defined( AMIZADE_ )
#define AMIZADE_
/***************************************************************************
*  $MCD Módulo de definição: AMI  Módulo Amizade
*
*  Arquivo gerado:              AMIZADE.h
*  Letras identificadoras:      AMI
*
*  Projeto: INF 1301 / Desenvolvimento de uma rede de relacionamentos em C
*  Gestor:  DI/PUC-Rio
*  Autores: Michelle Santiago (ms)
*
*  $HA Histórico de evolução:
*   Versão    Autor   	 Data     	Observações
*     1        ms      14/11/2017 	criação do arquivo
*
*
*  $ED Descrição do módulo
*
*    O módulo Amizade utiliza as funções do módulo grafo para criar amizades entre usuários, ou seja,
*    arestas entre vértices do grafo.
*	 
*
***************************************************************************/

#if defined( AMIZADE_OWN )
#define AMIZADE_EXT
#else
#define AMIZADE_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para amizade */
// ???
//typedef struct GRA_tagGrafo * GRA_tppGrafo;

/***********************************************************************
*  $TC Tipo de dados: AMI Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de amizade
*
***********************************************************************/
// AVALIAR ISSO AQUI DEPOIS
typedef enum {

	AMI_CondRetOK,
	/* Concluiu corretamente */

	AMI_NaoPossuiAmizades,
	/* O usuário não possui amizades */

	AMI_NaoAceitou,
	/* O usuário não aceitou a solicitação de amizade de outro */

	//GRA_CondRetNaoAchouAresta,
	/* N„o encontrou a aresta procurada */

	AMI_CondRetFaltouMemoria,
	/* Faltou memória ao tentar criar uma amizade */

	//GRA_CondRetRetornoLisIncorreto,
	/* Condicao de retorno do modulo Lista imprevista*/
	
	//GRA_CondRetParametroIncorreto,
	/* Parametro passado esta diferente do especificado*/

	//GRA_CondRetArestaJaExiste,
	/* Ja existe uma aresta entre os dois vertices passados*/

	AMI_UsuarioNaoExiste,
	/* Usuário fornecido não existe na rede*/
	
	//GRA_CondRetArestaParaSiMesmo
	/* Aresta de vertice tentando apontar para p proprio vertice*/
} AMI_tpCondRet;

/***********************************************************************
 *  $TC Tipo de dados: AMI Solicitação
 *
 *
 *  $ED Descrição do tipo
 *     Retorna se um usúario aceitou ou não à solicitação de amizade de um usuário ou não
 *
 ***********************************************************************/

typedef enum {
    
    AMI_SolicitacaoAceita,
    /* O usuário aceitou a solicitação de amizade */
    
    AMI_SolicitacaoRejeitada,
    /* O usuário rejeitou a solicitação de amizade */
    
} AMI_tpSolitacao;

/***********************************************************************
 *  $TC Tipo de dados: AMI Verificação
 *
 *
 *  $ED Descrição do tipo
 *     Retorna se o usuário possui amizade com um segundo usuário ou não
 *
 ***********************************************************************/

typedef enum {
    
    AMI_ExisteAmizade,
    /* Foi verificado que a amizade entre dois usuários existe */
    
    AMI_NaoExisteAmizade,
    /* Foi verificado que a amizade entre dois usuários não existe */
    
} AMI_tpVerificacao;


/***********************************************************************
*  $FC Função: AMI  &Criar Amizade
*
*  $ED Descrição da função
*     Cria uma relação entre um usuário e outro.
*
*  $EP Parâmetros
*     Usuario1  - ponteiro para um usuário da rede (um vértice do grafo) que solicitou a amizade
*	  Usuario2 	- ponteiro para outro usuário da rede (outro vértice diferente do grafo) na qual foi solicitada a amizade
*     Aceitacao - variável booleana que contém a informação caso o segundo usuário aceitou ou não a solicitação de amizade
*
*  $FV Valor retornado
*      AMI_CondRetOK
*      AMI_NaoAceitou
*	   AMI_CondRetFaltouMemoria
*
***********************************************************************/

AMI_tpCondRet AMI_CriarAmizade(Perfil Usuario1, Perfil Usuario2, AMI_tpSolitacao Aceitacao);


/***********************************************************************
*  $FC Função: AMI  &Excluir Amizade
*
*  $ED Descrição da função
*     Exclui uma amizade entre dois usuários.
*
*  $EP Parâmetros
*	  Usuario1 		- ponteiro para o primeiro usuário que realizou a exclusão da amizade.
*     Usuario2      - ponteiro para o segundo usuário que terá a amizade excluída.
*
*  $FV Valor retornado
*     AMI_CondRetOK
*
***********************************************************************/

AMI_tpCondRet AMI_ExcluirAmizade(Perfil Usuario1, Perfil Usuario2);


/***********************************************************************
*  $FC Função: AMI  &Verificar Número de Amigos
*
*  $ED Descrição da função
*     Retorna o número de amigos que um usuário possui.
*
*  $EP Parâmetros
*     Usuario  - ponteiro para o usuario que solicitou o número de amizades.
*     numAmizades - variável que irá armazenar o número de amizades encontradas.
*
*  $FV Valor retornado
*     AMI_CondRetOK
*     AMI_NaoPossuiAmizades
*
***********************************************************************/

AMI_tpCondRet AMI_VerificarNumAmigos(Perfil Usuario, int numAmizades);

/***********************************************************************
*  $FC Função: AMI  &Exibir Amizades
*
*  $ED Descrição da função
*     Exibe as informações do perfil de cada amigo do usuário.
*
*  $EP Parâmetros
*     Usuario  - ponteiro para o usuário que solicitou as informações das amizades
*
*  $FV Valor retornado
*     AMI_CondRetOK
*     AMI_NaoPossuiAmizades
*
***********************************************************************/

AMI_tpCondRet AMI_ExibirAmizades(Perfil Usuario);

/***********************************************************************
*  $FC Função: AMI  &Excluir Todas as Amizades
*
*  $ED Descrição da função
*     Exclui todas as amizades de um usuário.
*
*  $EP Parâmetros
*     Usuario - ponteiro para o usuário que terá suas amizades apagadas
*
*  $FV Valor retornado
*     AMI_CondRetOK
*     AMI_NaoPossuiAmizades
*
***********************************************************************/

AMI_tpCondRet AMI_ExcluirTodasAmizades(Perfil Usuario);

/***********************************************************************
*  $FC Função: AMI  &Verificar Amizade
*
*  $ED Descrição da função
*     Verifica se o Usuario1 é amigo do Usuario2
*
*  $EP Parâmetros
*     Usuario1 - ponteiro para o primeiro usuário que solicitou a verificação
*	  Usuario2 - ponteiro para o segundo usuário na quala  amizade será solicitada
*     ExisteAmizade - variável booleana que afirma se existe amizade ou não entre os usuários
*
*  $FV Valor retornado
*     AMI_CondRetOK
*     AMI_UsuarioNaoExiste
*
***********************************************************************/

AMI_tpCondRet AMI_VerificarAmizade(Perfil Usuario1, Perfil Usuario2, AMI_tpVerificacao ExisteAmizade) ;


#undef AMIZADE_EXT

/********** Fim do módulo de definição: AMI  Módulo Amizade **********/

#else
#endif
