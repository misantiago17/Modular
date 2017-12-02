#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
/***************************************************************************
*  $MCI Módulo de implementação: PER Gerenciamento de perfil
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
#include   "GRAFO.h"
#include   "LISTA.h"
#include   "PERFIL.h"

/***********************************************************************
*
*  $TC Tipo de dados: ??????????
*
***********************************************************************/

typedef struct PER_tagPerfil {
	char email[101];
	/*Email do usuario, deve ser unico e o identifica*/

	char primeiroNome[51];
	/*Primeiro nome do usuario*/

	char ultimoNome[51];
	/*Ultimo nome do usuario*/
	
	int diaNasc;
	/*Dia de nascimento do usuario */

	int mesNasc;
	/*Mês de nascimento do usuario */

	int anoNasc;
	/*Ano de nascimento do usuario*/

	char cidade[51];
	/*Cidade em que o usuario vive*/

	LIS_tppLista pLisMensagens;
	/*Lista de mensagens que o usuario trocou com outros*/
} PER_tpPerfil;


/***** Protótipos das funções encapuladas no módulo *****/

PER_tpCondRet confereEmail(GRA_tppGrafo pGrafo, char *email);
PER_tpCondRet confereNome(char *nome);
PER_tpCondRet confereDataNasc(int diaNasc, int mesNasc, int anoNasc);
PER_tpCondRet confereCidade(char *cidade);
PER_tpCondRet confereTudo(GRA_tppGrafo pGrafo, char *email, char *primeiroNome, char *ultimoNome, int diaNasc, int mesNasc,
						  int anoNasc, char *cidade);
PER_tpCondRet transformaRetGRA(GRA_tpCondRet retornoGRA);
PER_tpCondRet salvaCorrenteGrafo(GRA_tppGrafo pGrafo, int *id);
PER_tpCondRet restauraCorrenteGrafo(GRA_tppGrafo pGrafo, int id);
PER_tpCondRet deletaPerfil(GRA_tppGrafo pGrafo, int id);
/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PER  &Criar perfil
*  ****/

PER_tpCondRet PER_CriarPerfil(GRA_tppGrafo pGrafo, PER_tpPerfil **perfil, char *email, char *primeiroNome, char *ultimoNome, 
							  int diaNasc, int mesNasc, int anoNasc, char *cidade)
{
	PER_tpCondRet retorno;
	GRA_tpCondRet retornoGra;
	PER_tpPerfil *perfilRet;

	retorno = confereTudo(pGrafo, email, primeiroNome, ultimoNome, diaNasc, mesNasc, anoNasc, cidade);
	if (retorno != PER_CondRetOK)
		return retorno;

	if ((perfilRet = (PER_tpPerfil *)malloc(sizeof(PER_tpPerfil))) == NULL)
		return PER_CondRetFaltouMemoria;
	
	strcpy(perfilRet->email, email);

	strcpy(perfilRet->primeiroNome, primeiroNome);

	strcpy(perfilRet->ultimoNome, ultimoNome);

	strcpy(perfilRet->cidade, cidade);

	perfilRet->diaNasc = diaNasc;

	perfilRet->mesNasc = mesNasc;

	perfilRet->anoNasc = anoNasc;

	if (LIS_CriarLista(NULL, &perfilRet->pLisMensagens) != LIS_CondRetOK)
		return PER_CondRetFaltouMemoria;

	retornoGra = GRA_InserirVertice(pGrafo, (void *)perfilRet);
	if (retornoGra != GRA_CondRetOK)
		return transformaRetGRA(retorno);

	*perfil = perfilRet;
	return PER_CondRetOK;
} /* Fim função: PER  &Criar perfil */

/***************************************************************************
*
*  Função: PER  &Excluir Perfil
*  ****/



PER_tpCondRet PER_ExcluirPerfil(GRA_tppGrafo pGrafo, char *email) {
	int id;
	PER_tpPerfil *perfil;
	PER_tpCondRet retorno;

	retorno = PER_BuscaEmail(pGrafo, email, &perfil, &id);
	if (retorno == PER_CondRetRedeVazia)
		return PER_CondRetEmailInexistente;
	else if (retorno != PER_CondRetEmailJaCadastrado)
		return retorno;

	retorno = deletaPerfil(pGrafo, id);
	return retorno;
}/* Fim função: PER  &Excluir Perfil */

/***************************************************************************
*
*  Função: PER  &Obter referência para os dados contidos no perfil
*  ****/

PER_tpCondRet PER_ObterPerfil(PER_tpPerfil *perfil, char *email, char *primeiroNome, char *ultimoNome,
								int *diaNasc, int *mesNasc, int *anoNasc, char *cidade)
{
	PER_tpCondRet retorno;
	if (perfil == NULL)
		return PER_CondRetPerfilInvalido;

	strcpy(primeiroNome, perfil->primeiroNome);

	strcpy(ultimoNome, perfil->ultimoNome);

	strcpy(email, perfil->email);

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

PER_tpCondRet PER_NumeroPerfis(GRA_tppGrafo pGrafo, int *qtd){
	GRA_tpCondRet retorno_gra;

	retorno_gra = GRA_NumVertices(pGrafo, qtd);
	if (retorno_gra != GRA_CondRetOK)
		return transformaRetGRA(retorno_gra);

	return PER_CondRetOK;
}/* Fim função: PER  &Obter numero de perfis existentes */

/***************************************************************************
*
*  Função: PER  &Modifica o email do perfil
*  ****/

PER_tpCondRet PER_ModificaEmail(GRA_tppGrafo pGrafo, char *emailAtual, char *emailNovo)
{
	PER_tpCondRet retorno;
	PER_tpPerfil *perfil;
	int id;

	retorno = confereEmail(pGrafo, emailNovo);
	if (retorno != GRA_CondRetOK)
		return retorno;

	retorno = PER_BuscaEmail(pGrafo, emailAtual, &perfil, &id);
	if (retorno == PER_CondRetRedeVazia)
		return PER_CondRetEmailInexistente;
	else if (retorno != PER_CondRetEmailJaCadastrado)
		return retorno;
	strcpy(perfil->email, emailNovo);
	return PER_CondRetOK;
}/* Fim função: PER  &Modifica o email do perfil */

 /***************************************************************************
 *
 *  Função: PER  &Modifica o nome do perfil
 *  ****/

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

	retorno = PER_BuscaEmail(pGrafo, email, &perfil, &id);
	if (retorno == PER_CondRetRedeVazia)
		return PER_CondRetEmailInexistente;
	else if (retorno != PER_CondRetEmailJaCadastrado)
		return retorno;
	
	strcpy(perfil->primeiroNome, primeiroNome);

	strcpy(perfil->ultimoNome, ultimoNome);

	return PER_CondRetOK;
}/* Fim função: PER  &Modifica o nome do perfil */

 /***************************************************************************
 *
 *  Função: PER  &Modifica a data de nascimento do perfil
 *  ****/

PER_tpCondRet PER_ModificaDataNasc(GRA_tppGrafo pGrafo, char *email, int diaNasc, int mesNasc, int anoNasc) {
	PER_tpCondRet retorno;
	PER_tpPerfil *perfil;
	int id;

	retorno = confereDataNasc(diaNasc, mesNasc, anoNasc);
	if (retorno != GRA_CondRetOK)
		return retorno;

	retorno = PER_BuscaEmail(pGrafo, email, &perfil, &id);
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

PER_tpCondRet PER_ModificaCidade(GRA_tppGrafo pGrafo, char *email, char *cidade) {
	PER_tpCondRet retorno;
	PER_tpPerfil *perfil;
	int id;
	
	retorno = confereCidade(cidade);
	if (retorno != GRA_CondRetOK)
		return retorno;

	retorno = PER_BuscaEmail(pGrafo, email, &perfil, &id);
	if (retorno == PER_CondRetRedeVazia)
		return PER_CondRetEmailInexistente;
	else if (retorno != PER_CondRetEmailJaCadastrado)
		return retorno;

	strcpy(perfil->cidade, cidade);

	return PER_CondRetOK;
}/* Fim função: PER  &Modifica a cidade do perfil */

 /***************************************************************************
 *
 *  Função: PER  &Busca um email no grafo
 *  ****/

PER_tpCondRet PER_BuscaEmail(GRA_tppGrafo pGrafo, char *email, PER_tpPerfil **perfil, int *id) {

	GRA_tpCondRet retornoBusca, retornoDados;
	PER_tpCondRet retornoPer;
	int idCorrente, i = 1, tam;
	
	retornoPer = PER_NumeroPerfis(pGrafo, &tam);
	if (retornoPer != PER_CondRetOK)
		return retornoPer;

	retornoDados = salvaCorrenteGrafo(pGrafo, &idCorrente);
	if (retornoDados != PER_CondRetOK)
		return retornoDados;

	while (i <= tam  + 1) {
		retornoDados = GRA_ObterValor(pGrafo, perfil);
		if (retornoDados != GRA_CondRetOK) {
			retornoDados = restauraCorrenteGrafo(pGrafo, idCorrente);
			if (retornoDados != PER_CondRetOK)
				return retornoDados;
			return transformaRetGRA(retornoDados);
		}
		retornoDados = GRA_RetornaIdentificador(pGrafo, id);
		if (retornoDados != GRA_CondRetOK) {
			retornoDados = restauraCorrenteGrafo(pGrafo, idCorrente);
			if (retornoDados != PER_CondRetOK)
				return retornoDados;
			return transformaRetGRA(retornoDados);
		}
		if (strcmp((*perfil)->email, email) == 0) {
			retornoPer = restauraCorrenteGrafo(pGrafo, idCorrente);
			if (retornoPer != PER_CondRetOK)
				return retornoPer;
			return PER_CondRetEmailJaCadastrado;
		}

		retornoBusca = GRA_IrVertice(pGrafo, i);
		if (retornoBusca != GRA_CondRetOK && retornoBusca != GRA_CondRetNaoAchouVertice) {
			retornoPer = restauraCorrenteGrafo(pGrafo, idCorrente);
			if (retornoPer != PER_CondRetOK)
				return retornoPer;
			return retornoPer;
		}
		i++;
	}

	retornoPer = restauraCorrenteGrafo(pGrafo, idCorrente);
	if (retornoPer != PER_CondRetOK)
		return retornoPer;
	return PER_CondRetEmailInexistente;
} /* Fim função: PER  &Busca um email no grafo */


 /***************************************************************************
 *
 *  Função: PER  &Exclui todos os perfis existentes
 *  ****/

PER_tpCondRet PER_ExcluirTodosPerfis(GRA_tppGrafo pGrafo) {
	PER_tpCondRet retorno;
	do  {
		retorno = deletaPerfil(pGrafo, 1);
		if (retorno != PER_CondRetOK && retorno != PER_CondRetRedeVazia)
			return retorno;
	} while (retorno != PER_CondRetRedeVazia);

	return PER_CondRetOK;
}/* Fim função: PER  &Exclui todos os perfis existentes */

 /***************************************************************************
 *
 *  Função: PER  &Retorna lista de mensagens
 *  ****/

	PER_tpCondRet PER_retornaLisMensagens(PER_tpPerfil *perfil, LIS_tppLista *mensagens) {
	if (perfil == NULL)
		return PER_CondRetPerfilInexistente;
	*mensagens = perfil->pLisMensagens;
	return PER_CondRetOK;
}/* Fim função: PER  &Retorna lista de mensagens */

 /***************************************************************************
 *
 *  Função: PER  &Retorna Identificador de um perfil
 *  ****/

PER_tpCondRet PER_retornaIdPerfil(GRA_tppGrafo pGrafo, PER_tpPerfil *perfil, int *id) {
	PER_tpCondRet retorno;
	retorno = PER_BuscaEmail(pGrafo, perfil->email, &perfil, id);
	if (retorno == PER_CondRetEmailJaCadastrado)
		return PER_CondRetOK;
	else if(retorno == PER_CondRetRedeVazia || retorno == PER_CondRetEmailInexistente)
		return PER_CondRetPerfilInexistente;
	return retorno;

} /* Fim função : PER  &Retorna Identificador de um perfil * /

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: PER - Confere se o email é valido
*
***********************************************************************/
/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetEmailJaCadastrado
*     PER_CondRetEmailInvalido
*/
PER_tpCondRet confereEmail(GRA_tppGrafo pGrafo, char *email) {
	int i = 0, id;
	char test = email[3];
	PER_tpCondRet retorno;
	PER_tpPerfil *perfil;

	while (test != '@') {
		if (test == '\0')
			return PER_CondRetEmailInvalido;
		i++;
		test = email[i];
	}
	i+=2;
	while (test != '.') {
		if (test == '\0')
			return PER_CondRetEmailInvalido;
		i++;
		test = email[i];
	}
	i++;
	if (test == '\0')
		return PER_CondRetEmailInvalido;

	retorno = PER_BuscaEmail(pGrafo, email, &perfil, &id);
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

	if (anoNasc < 1900 || anoNasc > 2017)
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
*     PER_CondRetEmailJaCadastrado
*     PER_CondRetEmailInvalido
*     PER_CondRetNomeInvalido
*     PER_CondRetDataInvalida
*     PER_CondRetCidadeInvalida
*/
PER_tpCondRet confereTudo(GRA_tppGrafo pGrafo, char *email, char *primeiroNome, char *ultimoNome, int diaNasc, int mesNasc,
						  int anoNasc, char *cidade)
{
	PER_tpCondRet retorno;

	if (pGrafo == NULL)
		return PER_CondRetParametroGRAIncorreto;

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
		return PER_CondRetOK;

	if (retornoGRA == GRA_CondRetGrafoVazio)
		return PER_CondRetRedeVazia;

	if (retornoGRA == GRA_CondRetNaoAchouVertice)
		return PER_CondRetPerfilInexistente;
	
	if (retornoGRA == GRA_CondRetFaltouMemoria)
		return PER_CondRetFaltouMemoria;
	
	if (retornoGRA == GRA_CondRetParametroIncorreto)
		return PER_CondRetParametroGRAIncorreto;

	return PER_CondRetRetornoGRAInesperado;
}

/***********************************************************************
*
*  $FC Função: PER - Salva corrente do grafo
*
***********************************************************************/
/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRedeVazia
*/

PER_tpCondRet salvaCorrenteGrafo(GRA_tppGrafo pGrafo, int *id) {
	GRA_tpCondRet retorno;
	retorno = GRA_RetornaIdentificador(pGrafo, id);
	if(retorno != GRA_CondRetOK)
		return transformaRetGRA(retorno);
	return PER_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: PER - Restaura corrente do grafo
*
***********************************************************************/
/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*/
PER_tpCondRet restauraCorrenteGrafo(GRA_tppGrafo pGrafo, int id) {
	GRA_tpCondRet retorno;
	retorno = GRA_IrVertice(pGrafo, id);
	if (retorno != GRA_CondRetOK)
		return transformaRetGRA(retorno);
	return PER_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: PER - deleta dados do Perfil
*
***********************************************************************/
/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRedeVazia
*/
PER_tpCondRet deletaPerfil(GRA_tppGrafo pGrafo, int id) {
	GRA_tpCondRet retorno_gra;
	PER_tpPerfil *perfil;
	
	retorno_gra = GRA_IrVertice(pGrafo, id);
	if (retorno_gra != GRA_CondRetOK)
		return transformaRetGRA(retorno_gra);

	retorno_gra = GRA_ObterValor(pGrafo, &perfil);
	if (retorno_gra != GRA_CondRetOK)
		return transformaRetGRA(retorno_gra);

	
	if (LIS_DestruirLista(perfil->pLisMensagens) != LIS_CondRetOK)
		return PER_CondRetRetornoLisIncorreto;
	
	free(perfil);

	retorno_gra = GRA_ExcluirVertice(pGrafo);
	if (retorno_gra != GRA_CondRetOK)
		return transformaRetGRA(retorno_gra);
	return PER_CondRetOK;
}