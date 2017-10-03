#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*  $MCD M�dulo de defini��o: GRA  Grafo Generico com Cabe�a
*
*  Arquivo gerado:              GRAFO.h
*  Letras identificadoras:      GRA
*
*  Projeto: INF 1301 / Desenvolvimento de uma rede de relacionamentos em C
*  Gestor:  DI/PUC-Rio
*  Autores: Gabriel Busquim (gb), Michelle Santiago (ms), Renan Moreira (rm)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       ms   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*
*	  Implementa um grafo gen�rico.
*	  Apenas um grafo ir� existir e ele ir� aglomerar todas as listas presentes.
*	  O Grafo possu� uma cabe�a que acopla o m�dulo Lista com o m�dulo Grafo.
*
*****************************************************************************
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/

#if defined( GRAFO_OWN )
#define GRAFO_EXT
#else
#define GRAFO_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um grafo */

typedef struct GRA_tagGrafo * GRA_tppGrafo;

/***********************************************************************
*  $TC Tipo de dados: GRA Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da grafo
*
***********************************************************************/

typedef enum {

	GRA_CondRetOK,
	/* Concluiu corretamente */

	GRA_CondRetGrafoVazio,
	/* O grafo n�o cont�m v�rtices */

	GRA_CondRetFimGrafo,
	/* Foi percorrido todo o grafo */

	GRA_CondRetNaoAchouVertice,
	/* N�o encontrou o vertice procurado */

	GRA_CondRetNaoAchouAresta,
	/* N�o encontrou a aresta procurada */

	GRA_CondRetFaltouMemoria
	/* Faltou mem�ria ao tentar criar um v�rtice do grafo */

} GRA_tpCondRet;


/***********************************************************************
*  $FC Fun��o: GRA  &Criar grafo
*
*  $ED Descri��o da fun��o
*     Cria um grafo gen�rico.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado ao grafo.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo vertice
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*	  GrafoRet 		- ponteiro para o grafo.
*					  Este ponteiro ser� utilizado pelas fun��es
*					  que manipulem este grafo.
*
*  $FV Valor retornado
*      GRA_CondRetOK
*	   GRA_CondRetFaltouMemoria
*
***********************************************************************/

GRA_tpCondRet GRA_CriarGrafo(
	void(*ExcluirValor) (void * pDado), GRA_tppGrafo* GrafoRet);


/***********************************************************************
*  $FC Fun��o: GRA  &Destruir grafo
*
*  $ED Descri��o da fun��o
*     Destr�i o grafo fornecida.
*     O par�metro ponteiro para o grafo n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, o grafo resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*
***********************************************************************/

GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo pGrafo);


/***********************************************************************
*  $FC Fun��o: GRA  &Ir para o V�rtice
*
*  $ED Descri��o da fun��o
*     Leva a corrente at� o v�rtice numVert do grafo
*     Explora o grafo at� encontrar o v�rtice identificado por numVert
*     numVert pode ser maior do que o n�mero de vertices existentes no grafo
*     Se numVert for zero somente verifica se o grafo est� vazia
*
*  $EP Par�metros
*     pGrafo  - ponteiro para a grafo a ser manipulada
*     numVert - o n�mero do v�rtice a ser encontrado
*
*  $FV Valor retornado
*     CondRetOK         - se o v�rtice foi encontrado
*     CondRetFimGrafo   - se percorreu todos os vertices de grafo
e n�o encontrou o v�rtice
*     CondRetGrafoVazio - se o grafo est� vazio
*
***********************************************************************/

GRA_tpCondRet GRA_IrVertice(GRA_tppGrafo pGrafo,
	int numVert);


/***********************************************************************
*  $FC Fun��o: GRA  &Obter refer�ncia para o valor contido no v�rtice
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no v�rtice corrente do grafo
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo de onde se quer armazenar o valor
*	  pValorRet - endere�o de um ponteiro para armazenar o valor encontrado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetGrafoVazio
*	  GRA_CondRetNaoAchou
*
***********************************************************************/

GRA_tpCondRet GRA_ObterValor(GRA_tppGrafo pGrafo, void** pValorRet);


/***********************************************************************
*  $FC Fun��o: GRA  &Inserir v�rtice
*
*  $ED Descri��o da fun��o
*     Insere novo v�rtice no grafo.
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo onde deve ser inserido o v�rtice
*     pValor - ponteiro para o valor do novo v�rtice
*              Pode ser NULL
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*
***********************************************************************/

GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo,
	void * pValor);

/***********************************************************************
*  $FC Fun��o: GRA  &Excluir vertice
*
*  $ED Descri��o da fun��o
*     Exclui o v�rtice corrente do grafo dada.
*     Se existir v�rtice a esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o v�rtice � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir o grafo tornou-se vazio.
*
*  $EP Par�metros
*     pGrafo    - ponteiro para o grafo na qual deve excluir.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetGrafoVazio
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo);


/***********************************************************************
*  $FC Fun��o: GRA  &Cria Aresta
*
*  $ED Descri��o da fun��o
*     Cria uma aresta entre dois v�rtices do grafo.
*	  Se algum dos v�rtices n�o for encontrado a fun��o retornar� um erro informando
*	  que n�o encontrou o v�rtice.
*	  A aresta tamb�m n�o ser� criada se o grafo estiver vazio.
*
*  $EP Par�metros
*     pGrafo    - ponteiro para o grafo na qual deve criar a eresta.
*	  numVert1  - o n�mero do primeiro v�rtice.
*	  numVert2  - o n�mero do segundo v�rtice.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetNaoAchou
*     GRA_CondRetGrafoVazio
*
***********************************************************************/

GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2);


/***********************************************************************
*  $FC Fun��o: GRA  &Excluir Aresta
*
*  $ED Descri��o da fun��o
*     Exclu� uma aresta entre dois v�rtices do grafo.
*	  Se algum dos v�rtices n�o for encontrado a fun��o retornar� um erro informando
*	  que n�o encontrou o v�rtice.
*	  Se o grafo estiver vazio ele tamb�m retornar� um erro.
*	  Caso a aresta nao exista a funcao tambem retornara um erro.
*
*  $EP Par�metros
*     pGrafo    - ponteiro para o grafo na qual deve excluir a aresta.
*	  numVert1  - o n�mero do primeiro v�rtice.
*	  numVert2  - o n�mero do segundo v�rtice.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetNaoAchou
*     GRA_CondRetGrafoVazio
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2);

#undef GRAFO_EXT

/********** Fim do m�dulo de defini��o: GRA  Grafo Gen�rico com Cabe�a **********/

#else
#endif