#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
/***************************************************************************
*  $MCI Módulo de implementação: GRA  Grafo generico com cabeca
*
*  Arquivo gerado:              Perfil.c
*  Letras identificadoras:      PER
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  DI/PUC-Rio
*  Autores: Renan Moreira (rm)
*
*  $HA Histórico de evolução:
*     Versão  Autor   	 Data     	Observações
*     1        rm    27/09/2017 	inicio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "CESPDIN.H"
#include   "GRAFO.h"
#include   "LISTA.h"
#include   "PERFIL.h"

/***********************************************************************
*
*  $TC Tipo de dados: ??????????
*
***********************************************************************/

typedef struct PER_tagPerfil {
	char *email;
	/* */

	char *primeiroNome;
	/* */

	char *ultimoNome;
	/* */
	
	int diaNasc;
	/* */

	int mesNasc;
	/* */

	int anoNasc;
	/* */

	char *cidade;
	/* */

	LIS_tppLista *pLisMensagens;
	/*  */
} PER_tpPerfil;


/***** Protótipos das funções encapuladas no módulo *****/

PER_tpCondRet confereEmail(GRA_tppGrafo pGrafo, char *email);
PER_tpCondRet confereNome(char *nome);
PER_tpCondRet confereDataNasc(int diaNasc, int mesNasc, int anoNasc);
PER_tpCondRet confereCidade(char *cidade);
PER_tpCondRet confereTudo(GRA_tppGrafo pGrafo, PER_tpPerfil *perfil, char *email, char *primeiroNome, char *ultimoNome, int diaNasc, int mesNasc,
						  int anoNasc, char *cidade);
PER_tpCondRet buscaEmail(GRA_tppGrafo pGrafo, char *email, PER_tpPerfil **perfil, int *id);
PER_tpCondRet transformaRetGRA(GRA_tpCondRet retornoGRA);
PER_tpCondRet salvaCorrenteGrafo(GRA_tppGrafo pGrafo, int *id);
PER_tpCondRet restauraCorrenteGrafo(GRA_tppGrafo pGrafo, int id);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PER  &Criar perfil
*  ****/
/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetEmailJaCadastrado
*     PER_CondRetEmailInvalido
*     PER_CondRetNomeInvalido
*     PER_CondRetDataInvalida
*     PER_CondRetCidadeInvalida
*     PER_CondRetFaltouMemoria
*/
PER_tpCondRet PER_CriarPerfil(GRA_tppGrafo pGrafo, PER_tpPerfil *perfil, char *email, char *primeiroNome, char *ultimoNome, 
							  int diaNasc, int mesNasc, int anoNasc, char *cidade)
{
	PER_tpCondRet retorno;

	retorno = confereTudo(pGrafo, perfil, email, primeiroNome, ultimoNome, diaNasc, mesNasc, anoNasc, cidade);
	if (retorno != PER_CondRetOK)
		return retorno;

	if ((perfil = (PER_tpPerfil *)malloc(sizeof(PER_tpPerfil))) == NULL)
		return PER_CondRetFaltouMemoria;
	
	if ((perfil->email = (char *)malloc(sizeof(char)*strlen(email))) == NULL)
		return PER_CondRetFaltouMemoria;
	strcpy(perfil->email, email);

	if ((perfil->primeiroNome = (char *)malloc(sizeof(char)*strlen(primeiroNome))) == NULL)
		return PER_CondRetFaltouMemoria;
	strcpy(perfil->primeiroNome, primeiroNome);

	if ((perfil->ultimoNome = (char *)malloc(sizeof(char)*strlen(ultimoNome))) == NULL)
		return PER_CondRetFaltouMemoria;
	strcpy(perfil->ultimoNome, ultimoNome);

	if ((perfil->cidade = (char *)malloc(sizeof(char)*strlen(cidade))) == NULL)
		return PER_CondRetFaltouMemoria;
	strcpy(perfil->cidade, cidade);

	perfil->diaNasc = diaNasc;

	perfil->mesNasc = mesNasc;

	perfil->anoNasc = anoNasc;

	if ((perfil->pLisMensagens = (LIS_tppLista *)malloc(sizeof(LIS_tppLista))) == NULL)
		return PER_CondRetFaltouMemoria;

	retorno = GRA_InserirVertice(pGrafo, (void *)perfil);
	if (retorno != GRA_CondRetOK)
		return transformaRetGRA(retorno);

	return PER_CondRetOK;
} /* Fim função: PER  &Criar perfil */

/***************************************************************************
*
*  Função: PER  &Excluir Perfil
*  ****/

/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetEmailInexistente
*/

PER_tpCondRet PER_ExcluirPerfil(GRA_tppGrafo pGrafo, char *email) {
	int correnteGrafo, id;
	PER_tpPerfil *perfil;
	PER_tpCondRet retorno;

	retorno = buscaEmail(pGrafo, email, &perfil, &id);
	if (retorno == PER_CondRetRedeVazia)
		return PER_CondRetEmailInexistente;
	else if (retorno != PER_CondRetEmailJaCadastrado)
		return retorno;

	retorno = deletaPerfil(pGrafo, id);
	return retorno;
	/*
	free(perfil->email);
	free(perfil->primeiroNome);
	free(perfil->ultimoNome);
	free(perfil->cidade);

	if (LIS_DestruirLista(perfil->pLisMensagens) != LIS_CondRetOK)
		return PER_CondRetRetornoLisIncorreto;

	free(perfil);

	retorno = salvaCorrenteGrafo(pGrafo, &correnteGrafo);
	if (retorno != GRA_CondRetOK)
		return retorno;
	
	retorno = GRA_IrVertice(pGrafo, id);
	if (retorno != GRA_CondRetOK)
		return retorno;

	retorno = GRA_ExcluirVertice(pGrafo);
	if (retorno != GRA_CondRetOK)
		return transformaRetGRA(retorno);
	
	retorno = retornaCorrenteGrafo(pGrafo, correnteGrafo);
	if (retorno != GRA_CondRetOK)
		return retorno;

	return PER_CondRetOK;
	*/
}/* Fim função: PER  &Excluir Perfil */
 
/***************************************************************************
*
*  Função: PER  &Obter referência para os dados contidos no perfil
*  ****/

/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetEmailInexistente
*     PER_CondRetFaltouMemoria
*/
PER_tpCondRet PER_ObterPerfil(GRA_tppGrafo pGrafo, char *email, char **primeiroNome, char **ultimoNome,
								int *diaNasc, int *mesNasc, int *anoNasc, char **cidade) 
{
	int id;
	PER_tpPerfil *perfil;
	PER_tpCondRet retorno;

	retorno = buscaEmail(pGrafo, email, &perfil, &id);
	if (retorno == PER_CondRetRedeVazia)
		return PER_CondRetEmailInexistente;
	else if (retorno != PER_CondRetEmailJaCadastrado)
		return retorno;

	if ((*primeiroNome = (char *)malloc(sizeof(char)*strlen(perfil->primeiroNome))) == NULL)
		return PER_CondRetFaltouMemoria;
	strcpy(primeiroNome, perfil->primeiroNome);

	if ((*ultimoNome = (char *)malloc(sizeof(char)*strlen(perfil->ultimoNome))) == NULL)
		return PER_CondRetFaltouMemoria;
	strcpy(ultimoNome, perfil->ultimoNome);

	if ((*cidade = (char *)malloc(sizeof(char)*strlen(perfil->cidade))) == NULL)
		return PER_CondRetFaltouMemoria;
	strcpy(cidade, perfil->cidade);

	*diaNasc = perfil->diaNasc;

	*mesNasc = perfil->mesNasc;

	*anoNasc = perfil->anoNasc;

	return PER_CondRetOK;
}/* Fim função: PER  &Obter referência para os dados contidos no perfil */

/***************************************************************************
* 
*  Função: PER  &Obter numero de perfis existentes
*  ****/
/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetRedeVazia
*/
PER_tpCondRet PER_NumeroPerfis(GRA_tppGrafo pGrafo, int *qtd){
	GRA_tpCondRet retorno;
	int i = 0, id;

	retorno = salvaCorrenteGrafo(pGrafo, &id);
	if (retorno != GRA_CondRetOK)
		return retorno;

	retorno = GRA_IrVertice(pGrafo, i);
	if (retorno != GRA_CondRetOK)
		return transformaRetGRA(retorno);
	i++;
	while (retorno != GRA_CondRetNaoAchouVertice) {
		retorno = GRA_IrVertice(pGrafo, i);
		if (retorno != GRA_CondRetOK && retorno != GRA_CondRetNaoAchouVertice)
			return transformaRetGRA(retorno);
		i++;
	}

	*qtd = i;

	retorno = retornaCorrenteGrafo(pGrafo, id);
	if (retorno != GRA_CondRetOK)
		return retorno;

	return PER_CondRetOK;
}/* Fim função: PER  &Obter numero de perfis existentes */

/***************************************************************************
*
*  Função: PER  &Modifica o email do perfil
*  ****/
/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetEmailJaCadastrado
*     PER_CondRetEmailInvalido
*     PER_CondRetEmailInexistente
*     PER_CondRetFaltouMemoria
*/
PER_tpCondRet PER_ModificaEmail(GRA_tppGrafo pGrafo, char *emailAtual, char *emailNovo)
{
	PER_tpCondRet retorno;
	PER_tpPerfil *perfil;
	int id;

	retorno = confereEmail(pGrafo, emailNovo);
	if (retorno != GRA_CondRetOK)
		return retorno;

	retorno = buscaEmail(pGrafo, emailAtual, &perfil, &id);
	if (retorno == PER_CondRetRedeVazia)
		return PER_CondRetEmailInexistente;
	else if (retorno != PER_CondRetEmailJaCadastrado)
		return retorno;

	if ((perfil->email = (char *)malloc(sizeof(char)*strlen(emailNovo))) == NULL)
		return PER_CondRetFaltouMemoria;
	free(perfil->email);
	strcpy(perfil->email, emailNovo);

	return PER_CondRetOK;
}/* Fim função: PER  &Modifica o email do perfil */

 /***************************************************************************
 *
 *  Função: PER  &Modifica o nome do perfil
 *  ****/
 /*
 *     PER_CondRetOK
 *     PER_CondRetNomeInvalido
 *     PER_CondRetEmailInexistente
 *     PER_CondRetParametroGRAIncorreto
 *     PER_CondRetRetornoLisIncorreto
 *     PER_CondRetFaltouMemoria
 */
PER_tpCondRet PER_ModificaNome(GRA_tppGrafo pGrafo, char *email, char *primeiroNome, char *ultimoNome) {
	PER_tpCondRet retorno;
	PER_tpPerfil *perfil;
	int id;

	retorno = confereNome(primeiroNome);
	if (retorno != GRA_CondRetOK)
		return retorno;

	retorno = confereNome(ultimoNome);
	if (retorno != GRA_CondRetOK)
		return retorno;

	retorno = buscaEmail(pGrafo, email, &perfil, &id);
	if (retorno == PER_CondRetRedeVazia)
		return PER_CondRetEmailInexistente;
	else if (retorno != PER_CondRetEmailJaCadastrado)
		return retorno;
	
	free(perfil->primeiroNome);
	free(perfil->ultimoNome);

	if ((perfil->primeiroNome = (char *)malloc(sizeof(char)*strlen(primeiroNome))) == NULL)
		return PER_CondRetFaltouMemoria;
	strcpy(perfil->primeiroNome, primeiroNome);

	if ((perfil->ultimoNome = (char *)malloc(sizeof(char)*strlen(ultimoNome))) == NULL)
		return PER_CondRetFaltouMemoria;
	strcpy(perfil->ultimoNome, ultimoNome);

	return PER_CondRetOK;
}/* Fim função: PER  &Modifica o nome do perfil */

 /***************************************************************************
 *
 *  Função: PER  &Modifica a data de nascimento do perfil
 *  ****/
 /*
 *     PER_CondRetOK
 *     PER_CondRetDataInvalida
 *     PER_CondRetEmailInexistente
 *     PER_CondRetParametroGRAIncorreto
 *     PER_CondRetRetornoLisIncorreto
 */
PER_tpCondRet PER_ModificaDataNasc(GRA_tppGrafo pGrafo, char *email, int diaNasc, int mesNasc, int anoNasc) {
	PER_tpCondRet retorno;
	PER_tpPerfil *perfil;
	int id;

	retorno = confereDataNasc(diaNasc, mesNasc, anoNasc);
	if (retorno != GRA_CondRetOK)
		return retorno;

	retorno = buscaEmail(pGrafo, email, &perfil, &id);
	if (retorno == PER_CondRetRedeVazia)
		return PER_CondRetEmailInexistente;
	else if (retorno != PER_CondRetEmailJaCadastrado)
		return retorno;

	perfil->diaNasc = diaNasc;
	perfil->mesNasc = mesNasc;
	perfil->anoNasc = anoNasc;

	return PER_CondRetOK;
}/* Fim função: PER  &Modifica a data de nascimento do perfil */

 /***************************************************************************
 *
 *  Função: PER  &Modifica a cidade do perfil
 *  ****/
 /*
 *     PER_CondRetOK
 *     PER_CondRetCidadeInvalida
 *     PER_CondRetEmailInexistente
 *     PER_CondRetParametroGRAIncorreto
 *     PER_CondRetRetornoLisIncorreto
 *     PER_CondRetFaltouMemoria
 */
PER_tpCondRet PER_ModificaCidade(GRA_tppGrafo pGrafo, char *email, char *cidade) {
	PER_tpCondRet retorno;
	PER_tpPerfil *perfil;
	int id;
	
	retorno = confereCidade(cidade);
	if (retorno != GRA_CondRetOK)
		return retorno;

	retorno = buscaEmail(pGrafo, email, &perfil, &id);
	if (retorno == PER_CondRetRedeVazia)
		return PER_CondRetEmailInexistente;
	else if (retorno != PER_CondRetEmailJaCadastrado)
		return retorno;

	free(perfil->cidade);
	if ((perfil->cidade = (char *)malloc(sizeof(char)*strlen(cidade))) == NULL)
		return PER_CondRetFaltouMemoria;
	strcpy(perfil->cidade, cidade);

	return PER_CondRetOK;
}/* Fim função: PER  &Modifica a cidade do perfil */

 /***************************************************************************
 *
 *  Função: PER  &Busca um email no grafo
 *  ****/

 /*
 *     PER_CondRetEmailInexistente
 *     PER_CondRetParametroGRAIncorreto
 *     PER_CondRetRetornoLisIncorreto
 *     PER_CondRetRedeVazia
 *     PER_CondRetEmailJaCadastrado
 */
PER_tpCondRet buscaEmail(GRA_tppGrafo pGrafo, char *email, PER_tpPerfil **perfil, int *id) {

	GRA_tpCondRet retornoBusca, retornoDados;
	int idCorrente, i = 0;

	retornoDados = salvaCorrenteGrafo(pGrafo, &idCorrente);
	if (retornoDados != PER_CondRetOK)
		return retornoDados;

	retornoBusca = GRA_IrVertice(pGrafo, i);
	if (retornoBusca != GRA_CondRetOK)
		return transformaRetGRA(retornoBusca);
	i++;
	while (retornoBusca != GRA_CondRetNaoAchouVertice) {
		retornoDados = GRA_ObterValor(pGrafo, perfil);
		if (retornoDados != GRA_CondRetOK) {
			retornoDados = restauraCorrenteGrafo(pGrafo, idCorrente);
			if (retornoDados != PER_CondRetOK)
				return retornoDados;

			return transformaRetGRA(retornoDados);
		}

		retornoDados = GRA_RetornaIdentificador(pGrafo, &id);
		if (retornoDados != GRA_CondRetOK) {
			retornoDados = restauraCorrenteGrafo(pGrafo, idCorrente);
			if (retornoDados != PER_CondRetOK)
				return retornoDados;

			return transformaRetGRA(retornoDados);
		}

		if (strcmp((*perfil)->email, email) == 0) {
			retornoDados = restauraCorrenteGrafo(pGrafo, idCorrente);
			if (retornoDados != PER_CondRetOK)
				return retornoDados;

			return PER_CondRetEmailJaCadastrado;
		}

		i++;

		retornoBusca = GRA_IrVertice(pGrafo, i);
		if (retornoBusca != GRA_CondRetOK && retornoBusca != GRA_CondRetNaoAchouVertice) {
			retornoDados = restauraCorrenteGrafo(pGrafo, idCorrente);
			if (retornoDados != PER_CondRetOK)
				return retornoDados;

			return transformaRetGRA(retornoBusca);
		}
	}

	retornoDados = restauraCorrenteGrafo(pGrafo, idCorrente);
	if (retornoDados != PER_CondRetOK)
		return retornoDados;

	return PER_CondRetEmailInexistente;
} /* Fim função: PER  &Busca um email no grafo */


 /***************************************************************************
 *
 *  Função: PER  &Exclui todos os perfis existentes
 *  ****/

PER_tpCondRet PER_ExcluirTodosPerfis(GRA_tppGrafo pGrafo) {
	PER_tpCondRet retorno;
	retorno = deletaPerfil(pGrafo, 0);
	if (retorno != PER_CondRetOK && retorno != PER_CondRetRedeVazia)
		return retorno;
	while (retorno != PER_CondRetRedeVazia) {
		retorno = deletaPerfil(pGrafo, 0);
		if (retorno != PER_CondRetOK && retorno != PER_CondRetRedeVazia)
			return retorno;
	}
	return PER_CondRetOK;
}/* Fim função: PER  &Exclui todos os perfis existentes */

 /***************************************************************************
 *
 *  Função: PER  &Retorna lista de mensagens
 *  ****/
 /*
 *     PER_CondRetEmailInexistente
 *     PER_CondRetParametroGRAIncorreto
 *     PER_CondRetRetornoLisIncorreto
 *     PER_CondRetRedeVazia
 *     PER_CondRetEmailJaCadastrado
 */
PER_tpCondRet PER_retornaLisMensagens(GRA_tppGrafo pGrafo, char *email, LIS_tppLista *mensagens) {
	PER_tpCondRet retorno;
	PER_tpPerfil *perfil;
	int id;
	
	retorno = buscaEmail(pGrafo, email, &perfil, &id);
	if (retorno != PER_CondRetEmailJaCadastrado)
		return retorno;
	*mensagens = perfil->pLisMensagens;
	return PER_CondRetOK;
}/* Fim função: PER  &Retorna lista de mensagens */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: PER - Confere se o email é valido
*
***********************************************************************/
/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetEmailJaCadastrado
*     PER_CondRetEmailInvalido
*/
PER_tpCondRet confereEmail(GRA_tppGrafo pGrafo, char *email) {
	int i = 0, id;
	char test = email[0];
	PER_tpCondRet retorno;
	PER_tpPerfil *perfil;

	while (test != '@') {
		if (test == '\0')
			return PER_CondRetEmailInvalido;
		i++;
		test = email[i];
	}

	while (test != '.') {
		if (test == '\0')
			return PER_CondRetEmailInvalido;
		i++;
		test = email[i];
	}

	retorno = buscaEmail(pGrafo, email, &perfil, &id);
	if (retorno != PER_CondRetEmailInexistente && retorno != PER_CondRetRedeVazia)
		return retorno;

	return PER_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: PER - Confere se o nome é valido
*
***********************************************************************/
/*
*     PER_CondRetOK
*     PER_CondRetNomeInvalido
*/
PER_tpCondRet confereNome(char *nome) {
	int i = 0;
	char test = nome[0];

	if (nome == NULL)
		PER_CondRetNomeInvalido;

	while (test != '\0') {
		if (test >= '0' && test <= '9')
			return PER_CondRetNomeInvalido;
		i++;
		test = nome[i];
	}
	return PER_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: PER - Confere se a data de nascimento é valida
*
***********************************************************************/
/*
*     PER_CondRetOK
*     PER_CondRetDataInvalida
*/
PER_tpCondRet confereDataNasc(int diaNasc, int mesNasc, int anoNasc) {
	int diaMax;

	if (mesNasc <= 0 || mesNasc > 12)
		return PER_CondRetDataInvalida;

	if (anoNasc < 0)
		return PER_CondRetDataInvalida;

	if ((mesNasc <= 7 && mesNasc % 2 == 1) || (mesNasc > 7 && mesNasc % 2 == 0))
		diaMax = 31;
	else if (mesNasc != 2)
		diaMax = 30;
	else {
		if ((anoNasc % 100 == 0 && anoNasc % 400 == 0) || (anoNasc % 100 != 0 && anoNasc % 4 == 0))
			diaMax = 29;
		else
			diaMax = 28;
	}

	if (diaNasc <= 0 || diaNasc >= diaMax)
		return PER_CondRetDataInvalida;

	return PER_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: PER - Confere se a cidade é valida
*
***********************************************************************/
/*
*     PER_CondRetOK
*     PER_CondRetCidadeInvalida
*/
PER_tpCondRet confereCidade(char *cidade) {
	if (cidade == NULL)
		PER_CondRetCidadeInvalida;

	return PER_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: PER - Confere se os dados do perfil são validos
*
***********************************************************************/
/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetEmailJaCadastrado
*     PER_CondRetEmailInvalido
*     PER_CondRetNomeInvalido
*     PER_CondRetDataInvalida
*     PER_CondRetCidadeInvalida
*/
PER_tpCondRet confereTudo(GRA_tppGrafo pGrafo, PER_tpPerfil *perfil, char *email, char *primeiroNome, char *ultimoNome, int diaNasc, int mesNasc,
						  int anoNasc, char *cidade)
{
	PER_tpCondRet retorno;

	if (perfil == NULL)
		return PER_CondRetPonteiroParaRetornoInvalido;

	if (pGrafo == NULL)
		return PER_CondRetGrafoInvalido;

	retorno = confereEmail(pGrafo, email);
	if (retorno != PER_CondRetOK)
		return retorno;

	retorno = confereNome(primeiroNome);
	if (retorno != PER_CondRetOK)
		return retorno;

	retorno = confereNome(ultimoNome);
	if (retorno != PER_CondRetOK)
		return retorno;

	retorno = confereDataNasc(diaNasc, mesNasc, anoNasc);
	if (retorno != PER_CondRetOK)
		return retorno;

	retorno = confereCidade(cidade);
	if (retorno != PER_CondRetOK)
		return retorno;

	return PER_CondRetOK;
}


/***********************************************************************
*
*  $FC Função: PER - Transforma retorno do grafo
*
***********************************************************************/

PER_tpCondRet transformaRetGRA(GRA_tpCondRet retornoGRA) {

	if (retornoGRA == GRA_CondRetOK)
		return PER_CondRetOK;//

	if (retornoGRA == GRA_CondRetGrafoVazio)
		return PER_CondRetRedeVazia;//

	if (retornoGRA == GRA_CondRetNaoAchouVertice)
		return PER_CondRetPerfilInexistente;

	if (retornoGRA == GRA_CondRetNaoAchouAresta)
		return PER_CondRetNaoHaAmizade;
	
	if (retornoGRA == GRA_CondRetFaltouMemoria)
		return PER_CondRetFaltouMemoria;//

	if (retornoGRA == GRA_CondRetRetornoLisIncorreto)
		return PER_CondRetRetornoLisIncorreto;//

	if (retornoGRA == GRA_CondRetParametroIncorreto)
		return PER_CondRetParametroGRAIncorreto;//

	if (retornoGRA == GRA_CondRetArestaJaExiste)
		return PER_CondRetAmizadeJaCriada;
}

/***********************************************************************
*
*  $FC Função: PER - Salva corrente do grafo
*
***********************************************************************/
/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetRedeVazia
*/
PER_tpCondRet salvaCorrenteGrafo(GRA_tppGrafo pGrafo, int *id) {
	GRA_tpCondRet retorno;
	retorno = GRA_RetornaIdentificador(pGrafo, &id);
	return transformaRetGRA(retorno);
}

/***********************************************************************
*
*  $FC Função: PER - Restaura corrente do grafo
*
***********************************************************************/
/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetPerfilInexistente
*/
PER_tpCondRet restauraCorrenteGrafo(GRA_tppGrafo pGrafo, int id) {
	GRA_tpCondRet retorno;
	retorno = GRA_IrVertice(pGrafo, id);
	return transformaRetGRA(retorno);
}

/***********************************************************************
*
*  $FC Função: PER - Excluir Perfil
*
***********************************************************************/
/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*     PER_CondRetRedeVazia
*/
PER_tpCondRet deletaPerfil(GRA_tppGrafo pGrafo, int id) {
	PER_tpCondRet retorno_per;
	GRA_tpCondRet retorno_gra;
	int correnteGrafo;
	PER_tpPerfil *perfil;

	retorno_per = salvaCorrenteGrafo(pGrafo, &correnteGrafo);
	if (retorno_per != PER_CondRetOK)
		return retorno_per;

	retorno_gra = GRA_IrVertice(pGrafo, id);
	if (retorno_gra != GRA_CondRetOK)
		return transformaRetGRA(retorno_gra);

	retorno_gra = GRA_ObterValor(pGrafo, &perfil);
	if (retorno_gra != GRA_CondRetOK)
		return transformaRetGRA(retorno_gra);

	free(perfil->email);
	free(perfil->primeiroNome);
	free(perfil->ultimoNome);
	free(perfil->cidade);

	if (LIS_DestruirLista(perfil->pLisMensagens) != LIS_CondRetOK)
		return PER_CondRetRetornoLisIncorreto;

	free(perfil);

	retorno_gra = GRA_ExcluirVertice(pGrafo);
	if (retorno_gra != GRA_CondRetOK)
		return transformaRetGRA(retorno_gra);

	retorno_per = retornaCorrenteGrafo(pGrafo, &correnteGrafo);
	if (retorno_per != PER_CondRetOK && retorno_per != PER_CondRetPerfilInexistente)
		return retorno_per;
	return PER_CondRetOK;
}