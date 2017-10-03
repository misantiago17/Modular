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

	GRA_CondRetFimGrafo,
	/* Foi percorrido todo o grafo */

	GRA_CondRetNaoAchouVertice,
	/* Não encontrou o vertice procurado */

	GRA_CondRetNaoAchouAresta,
	/* Não encontrou a aresta procurada */

	GRA_CondRetFaltouMemoria
	/* Faltou memória ao tentar criar um vértice do grafo */

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

GRA_tpCondRet GRA_CriarGrafo(
	void(*ExcluirValor) (void * pDado), GRA_tppGrafo* GrafoRet);


/***********************************************************************
*  $FC Função: GRA  &Destruir grafo
*
*  $ED Descrição da função
*     Destrói o grafo fornecida.
*     O parâmetro ponteiro para o grafo não é modificado.
*     Se ocorrer algum erro durante a destruição, o grafo resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*
***********************************************************************/

GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo pGrafo);


/***********************************************************************
*  $FC Função: GRA  &Ir para o Vértice
*
*  $ED Descrição da função
*     Leva a corrente até o vértice numVert do grafo
*     Explora o grafo até encontrar o vértice identificado por numVert
*     numVert pode ser maior do que o número de vertices existentes no grafo
*     Se numVert for zero somente verifica se o grafo está vazia
*
*  $EP Parâmetros
*     pGrafo  - ponteiro para a grafo a ser manipulada
*     numVert - o número do vértice a ser encontrado
*
*  $FV Valor retornado
*     CondRetOK         - se o vértice foi encontrado
*     CondRetFimGrafo   - se percorreu todos os vertices de grafo
e não encontrou o vértice
*     CondRetGrafoVazio - se o grafo está vazio
*
***********************************************************************/

GRA_tpCondRet GRA_IrVertice(GRA_tppGrafo pGrafo,
	int numVert);


/***********************************************************************
*  $FC Função: GRA  &Obter referência para o valor contido no vértice
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no vértice corrente do grafo
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo de onde se quer armazenar o valor
*	  pValorRet - endereço de um ponteiro para armazenar o valor encontrado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetGrafoVazio
*	  GRA_CondRetNaoAchou
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
*     GRA_CondRetFaltouMemoria
*
***********************************************************************/

GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo,
	void * pValor);

/***********************************************************************
*  $FC Função: GRA  &Excluir vertice
*
*  $ED Descrição da função
*     Exclui o vértice corrente do grafo dada.
*     Se existir vértice a esquerda do corrente será o novo corrente.
*     Se não existir e existir o vértice à direita, este se tornará corrente.
*     Se este também não existir o grafo tornou-se vazio.
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para o grafo na qual deve excluir.
*
*  $FV Valor retornado
*     GRA_CondRetOK
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
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para o grafo na qual deve criar a eresta.
*	  numVert1  - o número do primeiro vértice.
*	  numVert2  - o número do segundo vértice.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetNaoAchou
*     GRA_CondRetGrafoVazio
*
***********************************************************************/

GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2);


/***********************************************************************
*  $FC Função: GRA  &Excluir Aresta
*
*  $ED Descrição da função
*     Excluí uma aresta entre dois vértices do grafo.
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
*	  GRA_CondRetNaoAchou
*     GRA_CondRetGrafoVazio
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirAresta(GRA_tppGrafo pGrafo, int numVert1, int numVert2);

#undef GRAFO_EXT

/********** Fim do módulo de definição: GRA  Grafo Genérico com Cabeça **********/

#else
#endif