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
*     1       ms   19/10/2017 in�cio desenvolvimento
*     1       ms   19/10/2017 in�cio desenvolvimento
*     1       ms   19/10/2017 in�cio desenvolvimento
*     1       ms   19/10/2017 in�cio desenvolvimento
*     1       ms   19/10/2017 in�cio desenvolvimento
*     1       ms   19/10/2017 in�cio desenvolvimento
*     1       ms   19/10/2017 in�cio desenvolvimento
*     1       ms   19/10/2017 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*
*	  O m�dulo Grafo implementa um grafo gen�rico e suas principais funcionalidades.
*     O m�dulo Lista foi acoplado a este m�dulo para permitir sua implementacao.
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*     � realizado por uma fun��o fornecida pelo usu�rio.
*     Caso n�o seja necess�rio desalocar o valor referenciado pelo
*     elemento, o ponteiro para a fun��o de libera��o poder� ser NULL
*  
*	  
*
*
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

	GRA_CondRetNaoAchouVertice,
	/* N�o encontrou o vertice procurado */

	GRA_CondRetNaoAchouAresta,
	/* N�o encontrou a aresta procurada */

	GRA_CondRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar um v�rtice do grafo */

	GRA_CondRetRetornoLisIncorreto,
	/* Condicao de retorno do modulo Lista imprevista*/
	
	GRA_CondRetParametroIncorreto,
	/* Parametro passado esta diferente do especificado*/

	GRA_CondRetArestaJaExiste,
	/* Ja existe uma aresta entre os dois vertices passados*/

	GRA_CondRetNumArestasZero,
	/* N�o ha arestas neste vertice*/
	
	GRA_CondRetArestaParaSiMesmo
	/* Aresta de vertice tentando apontar para p proprio vertice*/
} GRA_tpCondRet;


/***********************************************************************
*  $FC Fun��o: GRA  &Criar grafo
*
*  $ED Descri��o da fun��o
*     Cria um grafo gen�rico.
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

GRA_tpCondRet GRA_CriarGrafo(void(*ExcluirValor) (void * pDado), GRA_tppGrafo* GrafoRet);


/***********************************************************************
*  $FC Fun��o: GRA  &Destruir grafo
*
*  $ED Descri��o da fun��o
*     Destr�i o grafo fornecido.
*     O par�metro ponteiro para o grafo n�o � modificado.
*
*  $EP Par�metros
*	  pGrafo 		- ponteiro para o grafo.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetParametroIncorreto
*	  GRA_CondRetRetornoLisIncorreto
*
***********************************************************************/

GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo pGrafo);


/***********************************************************************
*  $FC Fun��o: GRA  &Ir para o V�rtice
*
*  $ED Descri��o da fun��o
*     Explora o grafo at� encontrar o v�rtice identificado por numVert
*     Tal vertice passa a ser entao o corrente do grafo.
*	  Caso o vertice passado nao seja encontrado, o corrente do grafo nao sera alterado
*
*  $EP Par�metros
*     pGrafo  - ponteiro para o grafo a ser manipulado
*     numVert - o identificador do v�rtice a ser encontrado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetRetornoLisIncorreto
*     GRA_CondRetGrafoVazio
*     GRA_CondRetNaoAchouVertice
*
***********************************************************************/

GRA_tpCondRet GRA_IrVertice(GRA_tppGrafo pGrafo, int numVert);

/***********************************************************************
*  $FC Fun��o: GRA  &Obter refer�ncia para o valor contido no v�rtice
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no v�rtice corrente do grafo
*	  
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo de onde se quer descobrir o valor
*	  pValorRet - endere�o de um ponteiro para armazenar o valor encontrado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*
***********************************************************************/

GRA_tpCondRet GRA_ObterValor(GRA_tppGrafo pGrafo, void** pValorRet);

/***********************************************************************
*  $FC Fun��o: GRA  &Obter refer�ncia para o identificador do Vertice Corrente
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o identifacdor do v�rtice corrente do grafo
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo de onde se quer descobrir o valor
*	  numIdent - endere�o de uma variavel de tipo int para armazenar o valor encontrado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*
***********************************************************************/

GRA_tpCondRet GRA_RetornaIdentificador(GRA_tppGrafo pGrafo, int* numIdent) ;
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
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetRetornoLisIncorreto
*     GRA_CondRetFaltouMemoria
*
***********************************************************************/

GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo, void * pValor);

/***********************************************************************
*  $FC Fun��o: GRA  &Excluir vertice
*
*  $ED Descri��o da fun��o
*     Exclui o v�rtice corrente do grafo dado.
*     Caso exista um vertice cujo identificador e imediatamente menor do que o identificador do vertice apagado,este ser� o novo corrente.
*     Se n�o existir e existir um vertice cujo identificador e imediatamente maior, este se tornar� o novo corrente.
*     Se este tamb�m n�o existir o grafo tornou-se vazio e o corrente se torna NULL.
*     Quando um vertice e excluido, todos os identificadores que sao sucessores do identificador deste vertice
*	  sao decrescidos de uma unidade.
*
*  $EP Par�metros
*     pGrafo    - ponteiro para o grafo na qual deve-se excluir o corrente.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*     GRA_CondRetRetornoLisIncorreto
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
*     O elemento corrente do grafo nao sera alterado.
*     S� � possivel criar uma aresta entre dois vertices.
*     N�o � possivel criar uma aresta de um vertice para si mesmo.
*
*  $EP Par�metros
*     pGrafo    - ponteiro para o grafo na qual deve-se criar a aresta.
*	  numVert1  - identificador do primeiro v�rtice.
*	  numVert2  - identificador do segundo v�rtice.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetArestaParaSiMesmo
*     GRA_CondRetParametroIncorreto
*	  GRA_CondRetRetornoLisIncorreto
*     GRA_CondRetGrafoVazio
*     GRA_CondRetNaoAchouVertice
*     GRA_CondRetArestaJaExiste
*     GRA_CondRetFaltouMemoria
*
***********************************************************************/

GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2);

/***********************************************************************
*  $FC Fun��o: GRA  &Existe Aresta
*
*  $ED Descri��o da fun��o
*     Verifica se ha uma aresta entre dois vertices do grafo.
*	  Se algum dos v�rtices n�o for encontrado a fun��o retornar� um erro informando
*	  que n�o encontrou o v�rtice.
*     O elemento corrente do grafo nao sera alterado.
*
*  $EP Par�metros
*     pGrafo    - ponteiro para o grafo na qual deve-se criar a aresta.
*	  numVert1  - identificador do primeiro v�rtice.
*	  numVert2  - identificador do segundo v�rtice.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*     GRA_CondRetNaoAchouVertice
*     GRA_CondRetNaoAchouAresta
*
***********************************************************************/

GRA_tpCondRet GRA_ExisteAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2);

/***********************************************************************
*  $FC Fun��o: GRA  &Excluir Aresta
*
*  $ED Descri��o da fun��o
*     Exclui uma aresta entre dois v�rtices do grafo.
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
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*     GRA_CondRetNaoAchouAresta
*     GRA_CondRetNaoAchouVertice
*     GRA_CondRetRetornoLisIncorreto
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2);

/***********************************************************************
*  $FC Fun��o: GRA  &Retornar Numero de Arestas
*
*  $ED Descri��o da fun��o
*     Retorna por referencia o numero de arestas que o vertice corrente possui.
*	  
*  $EP Par�metros
*     pGrafo       - ponteiro para o grafo no qual se deseja descobrir o numero de arestas do vertice.
*	  pNumArestas  - endere�o de um ponteiro para armazenar o numero de arestas encontrado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*     GRA_CondRetRetornoLisIncorreto
*
***********************************************************************/

GRA_tpCondRet GRA_NumArestas(GRA_tppGrafo pGrafo,int *pNumArestas);

/***********************************************************************
*  $FC Fun��o: GRA  &Retornar Numero de Vertices
*
*  $ED Descri��o da fun��o
*     Retorna por referencia o numero de vertices que o grafo possui.
*
*  $EP Par�metros
*     pGrafo     - ponteiro para o grafo no qual se deseja descobrir o numero de vertices total.
*	  pNumVerts  - endere�o de um ponteiro para armazenar o numero de vertices encontrado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetParametroIncorreto
*     GRA_CondRetRetornoLisIncorreto
*
***********************************************************************/

GRA_tpCondRet GRA_NumVertices(GRA_tppGrafo pGrafo, int *pNumVerts);

/***********************************************************************
*  $FC Fun��o: GRA  &RetornarIndicesAresta
*
*  $ED Descri��o da fun��o
*     Retorna um vetor com os identificadores de cada vertice que possui aresta com o vertice corrente
*
*  $EP Par�metros
*     pGrafo    - ponteiro para o grafo que possui o vertice desejado.
*	  pDado     - vetor de inteiros ja alocado que armazena o identificador de cada vertice
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetNumArestasZero
*	  GRA_CondRetParametroIncorreto
*	  GRA_CondRetRetornoLisIncorreto
*
***********************************************************************/

GRA_tpCondRet GRA_RetornaIndiceAresta(GRA_tppGrafo pGrafo, int* pDado);

#undef GRAFO_EXT

/********** Fim do m�dulo de defini��o: GRA  Grafo Gen�rico com Cabe�a **********/

#else
#endif