#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*  $MCD Módulo de definição: GRA  Grafo Generico com Cabeça
*
*  Arquivo gerado:              GRAFO.h
*  Letras identificadoras:      GRA
*
*  Projeto: INF 1301 / Desenvolvimento de uma rede de relacionamentos em C
*  Gestor:  DI/PUC-Rio
*  Autores: Gabriel Busquim (gb), Michelle Santiago (ms), Renan Moreira (rm)
*
*  $HA Histórico de evolução:
*     Versão  Autor   	 Data     	Observações GRA_RetornaIdentificador
*     9      rm/ms/gb   16/10/2017 	revisoes finais e pequenas correcoes
*     8        ms       16/10/2017 	alteracao na descricao de GRA_RetornaIdentificador
*     7        rm       15/10/2017 	descricao das funcoes GRA_NumVertices, GRA_NumArestas, GRA_RetornaIndiceAresta
*     6        gb       14/10/2017 	inclusao GRA_NumVertices, GRA_NumArestas, GRA_RetornaIndiceAresta
*     5        gb       10/10/2017 	inclusao GRA_RetornaIdentificador
*     4        gb       06/10/2017 	inclusao funcao GRA_ExisteAresta
*     3        rm       05/10/2017 	alteracao nas funcoes referente a mudanca das structs
*     2      rm/ms/gb   30/09/2017 	inclusao das funcoes
*     1      rm/ms/gb   27/09/2017 	inicio desenvolvimento
*
*  $ED Descrição do módulo
*
*	 O modulo Grafo implementa um grafo genérico com cabeca e suas respectivas funcionalidades.
*    O modulo Lista foi acoplado a ele para que sua implementacao fosse possivel.
*	 O controle da destruição do valor de um elemento a ser excluído é realizado por uma função fornecida pelo usuário.
*	 Caso não seja necessário desalocar o valor referenciado pelo elemento, o ponteiro para a função de liberação poderá ser NULL .
*	 
*
***************************************************************************/

#if defined( GRAFO_OWN )
#define GRAFO_EXT
#else
#define GRAFO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */

typedef struct GRA_tagGrafo * GRA_tppGrafo;

/***********************************************************************
*  $TC Tipo de dados: GRA Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da grafo
*
***********************************************************************/

typedef enum {

	GRA_CondRetOK,
	/* Concluiu corretamente */

	GRA_CondRetGrafoVazio,
	/* O grafo não contém vértices */

	GRA_CondRetNaoAchouVertice,
	/* Não encontrou o vertice procurado */

	GRA_CondRetNaoAchouAresta,
	/* Não encontrou a aresta procurada */

	GRA_CondRetFaltouMemoria,
	/* Faltou memória ao tentar criar um vértice do grafo */
	
	GRA_CondRetParametroIncorreto,
	/* Parametro passado esta diferente do especificado*/

	GRA_CondRetArestaJaExiste,
	/* Ja existe uma aresta entre os dois vertices passados*/

	GRA_CondRetNumArestasZero,
	/* Não ha arestas neste vertice*/
	
	GRA_CondRetArestaParaSiMesmo
	/* Aresta de vertice tentando apontar para p proprio vertice*/
} GRA_tpCondRet;


/***********************************************************************
*  $FC Função: GRA  &Criar grafo
*
*  $ED Descrição da função
*     Cria um grafo genérico.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo vertice
*                     a ser excluído.
*                     Ver descrição do módulo.
*	  GrafoRet 		- ponteiro para o grafo.
*					  Este ponteiro será utilizado pelas funções
*					  que manipulem este grafo.
*
*  $FV Valor retornado
*      GRA_CondRetOK
*	   GRA_CondRetFaltouMemoria
*
***********************************************************************/

GRA_tpCondRet GRA_CriarGrafo(void(*ExcluirValor) (void * pDado), GRA_tppGrafo* GrafoRet);


/***********************************************************************
*  $FC Função: GRA  &Destruir grafo
*
*  $ED Descrição da função
*     Destrói o grafo fornecida.
*     O parâmetro ponteiro para o grafo não é modificado.
*		
*
*  $EP Parâmetros
*	  pGrafo 		- ponteiro para o grafo(nao-nulo).
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetParametroIncorreto
*
***********************************************************************/

GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo pGrafo);


/***********************************************************************
*  $FC Função: GRA  &Ir para o Vértice
*
*  $ED Descrição da função
*     Leva o corrente do grafo até o vértice de identificador numVert do grafo
*     Caso o identificador nao seja encontrado,o corrente permancera o mesmo. 
*
*  $EP Parâmetros
*     pGrafo  - ponteiro para o grafo a ser manipulado(nao-nulo)
*     numVert - o identificador do vértice a ser encontrado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*     GRA_CondRetNaoAchouVertice
*
***********************************************************************/

GRA_tpCondRet GRA_IrVertice(GRA_tppGrafo pGrafo, int numVert);

/***********************************************************************
*  $FC Função: GRA  &Retorna Identificador
*
*  $ED Descrição da função
*     Retorna o identificador do vértice.
*
*  $EP Parâmetros
*     pGrafo  - ponteiro para o grafo a ser manipulado(nao-nulo)
*     numIdent - ponteiro para armazenar o valor do identificador
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*
***********************************************************************/

GRA_tpCondRet GRA_RetornaIdentificador(GRA_tppGrafo pGrafo, int* numIdent);

/***********************************************************************
*  $FC Função: GRA  &Obter referência para o valor contido no vértice
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no vértice corrente do grafo
*	  Caso o grafo esteja vazio,retorna um erro
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo de onde se quer descobrir o valor(nao-nulo)
*	  pValorRet - endereço de um ponteiro para armazenar o valor encontrado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*
***********************************************************************/

GRA_tpCondRet GRA_ObterValor(GRA_tppGrafo pGrafo, void** pValorRet);

/***********************************************************************
*  $FC Função: GRA  &Obter referência para o identificador do Vertice Corrente
*
*  $ED Descrição da função
*     Obtem a referência para o identifacdor do vértice corrente do grafo
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo de onde se quer descobrir o valor(nao-nulo)
*	  numIdent - ponteiro de uma variavel de tipo int para armazenar o valor encontrado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*
***********************************************************************/

GRA_tpCondRet GRA_RetornaIdentificador(GRA_tppGrafo pGrafo, int* numIdent);

/***********************************************************************
*  $FC Função: GRA  &Inserir vértice
*
*  $ED Descrição da função
*     Insere novo vértice no grafo.
*	  
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo onde deve ser inserido o vértice(nao-nulo)
*     pValor - ponteiro para o valor do novo vértice
*              Pode ser NULL
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetFaltouMemoria
*
***********************************************************************/

GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo, void * pValor);

/***********************************************************************
*  $FC Função: GRA  &Excluir vertice
*
*  $ED Descrição da função
*     Exclui o vértice corrente do grafo dado.
*     Caso exista um vertice cujo identificador e imediatamente menor do que o identificador do vertice apagado,este será o novo corrente.
*     Se não existir e existir um vertice cujo identificador e imediatamente maior, este se tornará o novo corrente.
*     Se este também não existir o grafo tornou-se vazio e o corrente se torna NULL.
*     Quando um vertice e excluido, todos os identificadores que sao sucessores do identificador do vertice excluido
*      sao decrescidos de uma unidade.
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para o grafo na qual deve excluir.(nao-nulo)
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo);


/***********************************************************************
*  $FC Função: GRA  &Cria Aresta
*
*  $ED Descrição da função
*     Cria uma aresta entre dois vértices do grafo.
*	  Se algum dos vértices não for encontrado a função retornará um erro informando
*	  que não encontrou o vértice.
*	  A aresta também não será criada se o grafo estiver vazio.
*     O elemento corrente do grafo nao sera alterado.
*     Só é possivel criar uma aresta entre dois vertices.
*     Não é possivel criar uma aresta de um vertice para si mesmo.
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para o grafo na qual deve-se criar a aresta.(nao-nulo)
*	  numVert1  - identificador do primeiro vértice.
*	  numVert2  - identificador do segundo vértice.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetArestaParaSiMesmo
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*     GRA_CondRetNaoAchouVertice
*     GRA_CondRetArestaJaExiste
*     GRA_CondRetFaltouMemoria
*
***********************************************************************/

GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2);

/***********************************************************************
*  $FC Função: GRA  &Existe Aresta
*
*  $ED Descrição da função
*     Verifica se ha uma aresta entre dois vertices do grafo.
*	  Se algum dos vértices não for encontrado a função retornará um erro informando
*	  que não encontrou o vértice.
*     O elemento corrente do grafo nao sera alterado.
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para o grafo na qual deve-se criar a aresta.(nao-nulo)
*	  numVert1  - identificador do primeiro vértice.
*	  numVert2  - identificador do segundo vértice.
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
*  $FC Função: GRA  &Excluir Aresta
*
*  $ED Descrição da função
*     Exclui uma aresta entre dois vértices do grafo.
*	  Se algum dos vértices não for encontrado a função retornará um erro informando
*	  que não encontrou o vértice.
*	  Se o grafo estiver vazio ele também retornará um erro.
*	  Caso a aresta nao exista a funcao tambem retornara um erro.
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para o grafo na qual deve excluir a aresta(nao-nulo).
*	  numVert1  - o número do primeiro vértice.
*	  numVert2  - o número do segundo vértice.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*     GRA_CondRetNaoAchouAresta
*     GRA_CondRetNaoAchouVertice
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2);

/***********************************************************************
*  $FC Função: GRA  &Retornar Numero de Arestas
*
*  $ED Descrição da função
*     Retorna por referencia o numero de arestas que o vertice corrente possui.
*	  
*  $EP Parâmetros
*     pGrafo       - ponteiro para o grafo no qual se deseja descobrir o numero de arestas do vertice(nao-nulo).
*	  pNumArestas  -  ponteiro para armazenar o numero de arestas encontrado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetParametroIncorreto
*     GRA_CondRetGrafoVazio
*
***********************************************************************/

GRA_tpCondRet GRA_NumArestas(GRA_tppGrafo pGrafo,int *pNumArestas);

/***********************************************************************
*  $FC Função: GRA  &Retornar Numero de Vertices
*
*  $ED Descrição da função
*     Retorna por referencia o numero de vertices que o grafo possui.
*
*  $EP Parâmetros
*     pGrafo     - ponteiro para o grafo no qual se deseja descobrir o numero de vertices total(nao-nulo).
*	  pNumVerts  - ponteiro para armazenar o numero de vertices encontrado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetParametroIncorreto
*
***********************************************************************/

GRA_tpCondRet GRA_NumVertices(GRA_tppGrafo pGrafo, int *pNumVerts);

/***********************************************************************
*  $FC Função: GRA  &RetornarIndicesAresta
*
*  $ED Descrição da função
*     Retorna um vetor com o identificador de cada vertice que possui aresta com o vertice corrente
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para o grafo que possui o vertice desejado(nao-nulo).
*	  pDado     - vetor ja alocado para armazenar os identificadores encontrados
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetGrafoVazio
*	  GRA_CondRetNumArestasZero
*	  GRA_CondRetParametroIncorreto
*
***********************************************************************/

GRA_tpCondRet GRA_RetornaIndiceAresta(GRA_tppGrafo pGrafo, int* pDado);

#undef GRAFO_EXT

/********** Fim do módulo de definição: GRA  Grafo Genérico com Cabeça **********/

#else
#endif