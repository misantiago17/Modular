/***************************************************************************
*  $MCI Módulo de implementação: TGRA Teste grafo com cabeça
*
*  Arquivo gerado:              TesteGrafo.c
*  Letras identificadoras:      TGRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Grafo.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gb, ms, rm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     9      rm/ms/gb   16/10/2017 	revisoes finais e pequenas correcoes
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"
#include    "Perfil.h"
#include    "Grafo.h"
#include    "Lista.h"
#include    "Generico.h"
#include    "LerParm.h"

static const char RESET_PERFIL_CMD[] = "=resetteste";
static const char CRIAR_PERFIL_CMD[] = "=criarperfil";
static const char EXCLUIR_PERFIL_CMD[] = "=excluirperfil";
static const char OBTER_PERFIL_CMD[] = "=obterperfil";
static const char NUMERO_PERFIS_CMD[] = "=numeroperfis";
static const char MODIFICA_EMAIL_CMD[] = "=modificaemail";
static const char MODIFICA_NOME_CMD[] = "=modificanome";
static const char MODIFICA_DATA_CMD[] = "=modificadata";
static const char MODIFICA_CIDADE_CMD[] = "=modificacidade";
static const char BUSCA_EMAIL_CMD[] = "=buscaemail";
static const char EXCLUIR_TODOS_PERFIS_CMD[] = "=excluirtodosperfis";
static const char RETORNA_LIS_MENSAGENS_CMD[] = "=retornalismensagens";
static const char RETORNA_ID_PERFIL_CMD[] = "=retornaidperfil";

#define TRUE  1
#define FALSE 0

#define DIM_VT_PERFIL   10

PER_tpPerfil *vtPerfil[DIM_VT_PERFIL];
GRA_tppGrafo pGrafo;
/***** Protótipos das funções encapuladas no módulo *****/
static void DestruirValor(void * pValor);
static int ValidarInxPerfil(int inxPerfil);

/*****  Código das funções exportadas pelo módulo  *****/
/***********************************************************************
*
*  $FC Função: TGRA &Testar perfil
*
*  $ED Descrição da função
*
*     Comandos disponíveis:
*
*     =resetteste - anula o vetor de grafos. Provoca vazamento de memória
*
*
***********************************************************************/


TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {
	int i, numLidos = -1, inxPerfil = -1, CondRetEsp = -1, diaNasc, mesNasc, anoNasc, qtd, id;
	int diaNascEsp, mesNascEsp, anoNascEsp, qtdEsp, idEsp;
	char email[100], primeiroNome[50], ultimoNome[50], cidade[50], emailNovo[100];
	char emailEsp[100], primeiroNomeEsp[50], ultimoNomeEsp[50], cidadeEsp[50];
	TST_tpCondRet CondRet;
	PER_tpCondRet debug;

	/* Efetuar reset de teste de PERFIL */

	if (strcmp(ComandoTeste, RESET_PERFIL_CMD) == 0)
	{

		for (i = 0; i < DIM_VT_PERFIL; i++)
		{
			vtPerfil[i] = NULL;
		} /* for */

		GRA_DestruirGrafo(pGrafo);
		GRA_CriarGrafo(DestruirValor, &pGrafo);
		return TST_CondRetOK;

	} /* fim ativa: Efetuar reset de teste de Perfil */

	  /* Testar Criar Perfil */

	else if (strcmp(ComandoTeste, CRIAR_PERFIL_CMD) == 0)
	{

		numLidos = LER_LerParametros("isssiiisi", &inxPerfil, email, primeiroNome, ultimoNome,
									&diaNasc, &mesNasc, &anoNasc, cidade, &CondRetEsp);

		if ((numLidos != 9) || (!ValidarInxPerfil(inxPerfil)))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = PER_CriarPerfil(pGrafo, &vtPerfil[inxPerfil], email, primeiroNome, ultimoNome,
								  diaNasc, mesNasc, anoNasc, cidade);

		return TST_CompararInt(CondRetEsp, CondRet, "Erro na condicao de retorno ao criar o Perfil");

	} /* fim ativa: Testar CriarPerfil */

	  /* Testar Excluir Perfil */

	else if (strcmp(ComandoTeste, EXCLUIR_PERFIL_CMD) == 0)
	{

		numLidos = LER_LerParametros("si", email, &CondRetEsp);
		if ((numLidos != 2))
		{
			return TST_CondRetParm;
		} /* if */


		debug = PER_ExcluirPerfil(pGrafo, email);
		CondRet = TST_CompararInt(CondRetEsp, debug, "Condicao de retorno errada ao excluir o perfil.");
		if (CondRet != TST_CondRetOK)
			return CondRet;

		if (debug == PER_CondRetOK)
			vtPerfil[inxPerfil] = NULL;

		return TST_CondRetOK;


	}  /* fim ativa: Testar Excluir Perfil */
	   /* Testar Obter Perfil */

	else if (strcmp(ComandoTeste, OBTER_PERFIL_CMD) == 0)
	{

		numLidos = LER_LerParametros("isssiiisi", &inxPerfil, emailEsp, primeiroNomeEsp, ultimoNomeEsp, &diaNascEsp, &mesNascEsp, 
								     &anoNascEsp, cidadeEsp, &CondRetEsp);

		if ((numLidos != 9) || (!ValidarInxPerfil(inxPerfil)))
		{
			return TST_CondRetParm;
		} /* if */


		debug = PER_ObterPerfil(vtPerfil[inxPerfil], email, primeiroNome, ultimoNome, &diaNasc, &mesNasc, &anoNasc, cidade);

		CondRet = TST_CompararInt(CondRetEsp, debug, "Condicao de retorno errada ao obter o Perfil.");
		if (CondRet != TST_CondRetOK || debug != PER_CondRetOK)
			return CondRet;

		debug = TST_CompararString(emailEsp, email, "Campo email nao e igual ao esperado");
		if (debug != TST_CondRetOK)
			return debug;

		debug = TST_CompararString(primeiroNomeEsp, primeiroNome,"Campo Primeiro Nome nao e igual ao esperado");
		if (debug != TST_CondRetOK)
			return debug;

		debug = TST_CompararString(ultimoNomeEsp, ultimoNome, "Campo Ultimo Nome nao e igual ao esperado");
		if (debug != TST_CondRetOK)
			return debug;

		debug = TST_CompararInt(diaNascEsp, diaNasc, "Campo Dia Nasc nao e igual ao esperado");
		if (debug != TST_CondRetOK)
			return debug;

		debug = TST_CompararInt(mesNascEsp, mesNasc, "Campo Mes Nasc nao e igual ao esperado");
		if (debug != TST_CondRetOK)
			return debug;

		debug = TST_CompararInt(anoNascEsp, anoNasc, "Campo Ano Nasc nao e igual ao esperado");
		if (debug != TST_CondRetOK)
			return debug;

		debug = TST_CompararString(cidadeEsp, cidade, "Campo Cidade nao e igual ao esperado");

		return debug;
	} /* fim ativa: Testar Obter Perfil */

	  /* Testar Numero Perfis */

	else if (strcmp(ComandoTeste, NUMERO_PERFIS_CMD) == 0)
	{
		numLidos = LER_LerParametros("ii", &qtdEsp, &CondRetEsp);

		if (numLidos != 2)
		{
			return TST_CondRetParm;
		} /* if */

		debug = PER_NumeroPerfis(pGrafo, &qtd);

		CondRet = TST_CompararInt(CondRetEsp, debug, "Condicao de retorno errada ao obter o numero de perfis.");
		if (CondRet != TST_CondRetOK)
			return CondRet;

		CondRet = TST_CompararInt(qtdEsp, qtd, "Campo qtd diferente do esperado.");
		return CondRet;

	} /* fim ativa: Testar Numero Perfis */

	  /* Testar Modifica Email */

	else if (strcmp(ComandoTeste, MODIFICA_EMAIL_CMD) == 0)
	{

		numLidos = LER_LerParametros("ssi", email, emailNovo, &CondRetEsp);

		if (numLidos != 3)
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = PER_ModificaEmail(pGrafo, email, emailNovo);

		return TST_CompararInt(CondRetEsp, CondRet, "Erro na condicao de retorno ao Modificar Email");

	} /* fim ativa: Testar Modifica Email */

	  /* Testar Modifica Nome */

	else if (strcmp(ComandoTeste, MODIFICA_NOME_CMD) == 0)
	{

		numLidos = LER_LerParametros("sssi", email, primeiroNome, ultimoNome, &CondRetEsp);

		if (numLidos != 4)
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = PER_ModificaNome(pGrafo, email, primeiroNome, ultimoNome);

		return TST_CompararInt(CondRetEsp, CondRet, "Erro na condicao de retorno ao modificar nomes");

	} /* fim ativa: Testar Modifica Nome */
	
	  /* Testar Modifica Data */

	else if (strcmp(ComandoTeste, MODIFICA_DATA_CMD) == 0)
	{

		numLidos = LER_LerParametros("siiii", email, &diaNasc, &mesNasc, &anoNasc, &CondRetEsp);

		if (numLidos != 5)
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = PER_ModificaDataNasc(pGrafo, email, diaNasc, mesNasc, anoNasc);

		return TST_CompararInt(CondRetEsp, CondRet, "Erro na condicao de retorno ao modificar data");

	} /* fim ativa: Testar Modifica Data */

	  /* Testar Modifica Cidade */

	else if (strcmp(ComandoTeste, MODIFICA_CIDADE_CMD) == 0)
	{

		numLidos = LER_LerParametros("ssi", email, cidade, &CondRetEsp);

		if (numLidos != 3)
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = PER_ModificaCidade(pGrafo, email, cidade);

		return TST_CompararInt(CondRetEsp, CondRet, "Erro na condicao de retorno ao modificar cidade");

	} /* fim ativa: Testar Modifica Cidade */

	  /* Testar Busca Email */

	else if (strcmp(ComandoTeste, BUSCA_EMAIL_CMD) == 0)
	{
		PER_tpPerfil *perfil;
		numLidos = LER_LerParametros("siii", email, &inxPerfil, &idEsp, &CondRetEsp);

		if (numLidos != 4)
		{
			return TST_CondRetParm;
		} /* if */

		debug = PER_BuscaEmail(pGrafo, email, &perfil, &id);
		CondRet = TST_CompararInt(CondRetEsp, debug, "Condicao de retorno errada ao buscar email.");
		if (CondRet != TST_CondRetOK || CondRetEsp != PER_CondRetEmailJaCadastrado)
			return CondRet;

		CondRet = TST_CompararInt(idEsp, id, "Campo id nao e igual ao esperado");
		if (CondRet != TST_CondRetOK)
			return CondRet;
		
		debug = PER_ObterPerfil(vtPerfil[inxPerfil], emailEsp, primeiroNomeEsp, ultimoNomeEsp, &diaNascEsp, 
								&mesNascEsp, &anoNascEsp, cidadeEsp);
		CondRet = TST_CompararInt(PER_CondRetOK, debug, "Condicao de retorno errada ao obter perfil.");
		if (CondRet != TST_CondRetOK)
			return CondRet;

		debug = TST_CompararString(emailEsp, email, "Campo email nao e igual ao esperado");
		if (debug != TST_CondRetOK)
			return debug;
		return CondRet;

	} /* fim ativa: Testar Busca Email */

	  /* Testar Excluir todos os perfis */

	else if (strcmp(ComandoTeste, EXCLUIR_TODOS_PERFIS_CMD) == 0)
	{
		numLidos = LER_LerParametros("i", &CondRetEsp);

		if (numLidos != 1)
		{
			return TST_CondRetParm;
		} /* if */

		debug = PER_ExcluirTodosPerfis(pGrafo);
		CondRet = TST_CompararInt(CondRetEsp, debug, "Condicao de retorno errada ao excluir o perfil.");
		if (CondRet != TST_CondRetOK)
			return CondRet;

		if (debug == PER_CondRetOK) {
			for (i = 0; i < DIM_VT_PERFIL; i++) {
				vtPerfil[i] = NULL;
			} /* for */
		} /* if */

		return TST_CondRetOK;

	} /* fim ativa: Testar Excluir todos os perfis */
	
	  /* Testar Retornar Lista de mensagens */
	else if (strcmp(ComandoTeste, RETORNA_LIS_MENSAGENS_CMD) == 0)
	{
		LIS_tppLista mensagens;
		numLidos = LER_LerParametros("ii", &inxPerfil, &CondRetEsp);
		if ((numLidos != 2) || (!ValidarInxPerfil(inxPerfil)))
		{
			return TST_CondRetParm;
		} /* if */
		CondRet = PER_retornaLisMensagens(vtPerfil[inxPerfil], &mensagens);
		return TST_CompararInt(CondRetEsp, CondRet, "Erro na condicao de retorno ao retornar mensagem");

	} /* fim ativa: Testar Retornar id do perfil */
	else if (strcmp(ComandoTeste, RETORNA_ID_PERFIL_CMD) == 0)
	{
		numLidos = LER_LerParametros("iii", &inxPerfil, &idEsp, &CondRetEsp);
		if ((numLidos != 3) || (!ValidarInxPerfil(inxPerfil)))
		{
			return TST_CondRetParm;
		} /* if */

		debug = PER_retornaIdPerfil(pGrafo, vtPerfil[inxPerfil], &id);

		CondRet = TST_CompararInt(CondRetEsp, debug, "Erro na condicao de retorno ao retornar id.");
		if (CondRet != TST_CondRetOK)
			return CondRet;

		CondRet = TST_CompararInt(idEsp, id, "Campo id nao e igual ao esperado");
		if (CondRet != TST_CondRetOK)
			return CondRet;

		return CondRet;
	}
	return TST_CondRetNaoConhec;
}

/*****  Código das funções encapsuladas no módulo  *****/
/***********************************************************************
*
*  $FC Função: TPER -Destruir valor
*
***********************************************************************/

void DestruirValor(void * pValor)
{
	PER_tpPerfil *perfil = (PER_tpPerfil *)pValor;
	LIS_tppLista mensagens;
	PER_tpCondRet retorno;

	retorno = PER_retornaLisMensagens(perfil, &mensagens);
	if (retorno != PER_CondRetOK)
		return;
	LIS_DestruirLista(mensagens);
	free(perfil);
} /* Fim função: TPER -Destruir valor */

  /***********************************************************************
  *
  *  $FC Função: TPER -Validar indice de Perfil
  *
  ***********************************************************************/

int ValidarInxPerfil(int inxPerfil)
{

	if ((inxPerfil <  0) || (inxPerfil >= DIM_VT_PERFIL))
	{
		return FALSE;
	} /* if */

	return TRUE;

} /* Fim função: TPER -Validar indice de Perfil */