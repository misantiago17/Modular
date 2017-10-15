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
*     Versão  Autor    Data     Observações
*     1       ms   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*
*	  Implementa um grafo genérico.
*	  Apenas um grafo irá existir e ele irá aglomerar todas as listas presentes.
*	  O Grafo possuí uma cabeça que acopla o módulo Lista com o módulo Grafo.
*
*****************************************************************************
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
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

	GRA_CondRetRetornoLisIncorreto,
	/* Condicao de retorno do modulo Lista imprevista*/
	
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
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado ao grafo.
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
*     Se ocorrer algum erro durante a destruição, o grafo resultado
*     estará estruturalmente incorreto.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetParametroIncorreto
*	  GRA_CondRetRetornoLisIncorreto
*
***********************************************************************/

GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo pGrafo);


/***********************************************************************
*  $FC Função: GRA  &Ir para o Vértice
*
*  $ED Descrição da função
*     Leva o corrente até o vértice numVert do grafo
*     Explora o grafo até encontrar o vértice identificado por numVert
*
*  $EP Parâmetros
*     pGrafo  - ponteiro para o grafo a ser manipulado
*     numVert - o número do vértice a ser encontrado
*
*  $FV Valor retornado
*     CondRetOK
*     GRA_CondRetParametroIncorreto
*     GRA_CondRetRetornoLisIncorreto
*     GRA_CondRetGrafoVazio
*     GRA_CondRetNaoAchouVertice
*
***********************************************************************/

GRA_tpCondRet GRA_IrVertice(GRA_tppGrafo pGrafo, int numVert);


/***********************************************************************
*  $FC Função: GRA  &Obter referência para o valor contido no vértice
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no vértice corrente do grafo
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo de onde se quer descobrir o valor
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
*  $FC Função: GRA  &Inserir vértice
*
*  $ED Descrição da função
*     Insere novo vértice no grafo.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo onde deve ser inserido o vértice
*     pValor - ponteiro para o valor do novo vértice
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
*  $FC Função: GRA  &Excluir vertice
*
*  $ED Descrição da função
*     Exclui o vértice corrente do grafo dada.
*     Se existir vértice a esquerda do corrente será o novo corrente.
*     Se não existir e existir o vértice à direita, este se tornará corrente.
*     Se este também não existir o grafo tornou-se vazio e o corrente se torna NULL.
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para o grafo na qual deve excluir.
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
*     pGrafo    - ponteiro para o grafo na qual deve-se criar a aresta.
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
*     pGrafo    - ponteiro para o grafo na qual deve-se criar a aresta.
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
*     pGrafo    - ponteiro para o grafo na qual deve excluir a aresta.
*	  numVert1  - o número do primeiro vértice.
*	  numVert2  - o número do segundo vértice.
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
*  $FC Função: GRA  &Retornar Numero de Arestas
*
*  $ED Descrição da função
*     Retorna por referencia o numero de arestas que o vertice corrente possui.
*	  
*
*  $EP Parâmetros
*     pGrafo       - ponteiro para o grafo no qual se deseja descobrir o numero de arestas do vertice.
*	  pNumArestas  - endereço de um ponteiro para armazenar o numero de arestas encontrado
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
*  $FC Função: GRA  &Retornar Numero de Vertices
*
*  $ED Descrição da função
*     Retorna por referencia o numero de vertices que o grafo possui.
*
*  $EP Parâmetros
*     pGrafo     - ponteiro para o grafo no qual se deseja descobrir o numero de vertices total.
*	  pNumVerts  - endereço de um ponteiro para armazenar o numero de vertices encontrado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetParametroIncorreto
*     GRA_CondRetRetornoLisIncorreto
*
***********************************************************************/

GRA_tpCondRet GRA_NumVertices(GRA_tppGrafo pGrafo, int *pNumVerts);

/***********************************************************************
*  $FC Função: GRA  &RetornarIndicesAresta
*
*  $ED Descrição da função
*     Retorna um vetor com o indice do vertice ligado a cada aresta que o vertice corrente possui
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para o grafo que possui o vertice desejado.
*	  pDado     - endereço de um ponteiro para armazenar o vetor dos identificadores encontrados
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

/********** Fim do módulo de definição: GRA  Grafo Genérico com Cabeça **********/

#else
#endif