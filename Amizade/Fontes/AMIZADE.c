#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
/***************************************************************************
*  $MCI Módulo de implementação: AMI  Modulo Amizade
*
*  Arquivo gerado:              AMIZADE.c
*  Letras identificadoras:      AMI
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  DI/PUC-Rio
*  Autores: Michelle Santiago (ms)
*
*  $HA Histórico de evolução:
*     Versão  Autor   	 Data     	Observações
*     1        ms    20/11/2017 	inicio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "CESPDIN.H"
#include   "GRAFO.h"
#include   "PERFIL.h"
#include   "AMIZADE.h"

/***********************************************************************
*
*  $TC Tipo de dados: ??????????
*
***********************************************************************/
/*
typedef struct AMI_tagAmizade {

	PER_tpPerfil *Usuario1;
	/* Primeiro usuário que compõe a amizade */
	
	PER_tpPerfil *Usuario2;
	/* Segundo usuário que compõe a amizade */

	GRA_tppGrafo *pGrafo;
	/*  */
} AMI_tpAmizade;
*/

/***** Protótipos das funções encapuladas no módulo *****/

AMI_tpCondRet AMI_CriarAmizade(Perfil Usuario1, Perfil Usuario2, AMI_tpSolitacao Aceitacao);
AMI_tpCondRet AMI_ExcluirAmizade(Perfil Usuario1, Perfil Usuario2);
AMI_tpCondRet AMI_VerificarNumAmigos(Perfil Usuario, int numAmizades);
AMI_tpCondRet AMI_ExibirAmizades(Perfil Usuario);
AMI_tpCondRet AMI_ExcluirTodasAmizades(Perfil Usuario);
AMI_tpCondRet AMI_VerificarAmizade(Perfil Usuario1, Perfil Usuario2, AMI_tpVerificacao ExisteAmizade) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*  Função: AMI  &Criar Amizade
*
*      AMI_CondRetOK
*      AMI_NaoAceitou
*	   AMI_UsuarioNaoExiste
*	   AMI_CondRetRetornoGraIncorreto
*	   AMI_CondRetRetornoPerIncorreto
*
*****/

AMI_tpCondRet AMI_CriarAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil Usuario1, PER_tpPerfil Usuario2, AMI_tpSolitacao Aceitacao){
	
	GRA_tpCondRet GRA_RetornoCriarAresta;
	PER_tpCondRet PER_RetornoEmail1;
	PER_tpCondRet PER_RetornoEmail2;
	int id1;
	int id2;
	
	PER_RetornoEmail1 = buscaEmail(pGrafo, Usuario1->email, &Usuario1, &id1);
	PER_RetornoEmail2 = buscaEmail(pGrafo, Usuario2->email, &Usuario2, &id2);
	if (PER_RetornoEmail1 == PER_CondRetEmailInexistente || PER_RetornoEmail2 == PER_CondRetEmailInexistente){
		return AMI_UsuarioNaoExiste;
	} else if (PER_RetornoEmail1 != PER_CondRetEmailJaCadastrado || PER_RetornoEmail2 != PER_CondRetEmailJaCadastrado){
		return AMI_CondRetRetornoPerIncorreto;
	}
	
	if (Aceitacao == AMI_SolicitacaoRejeitada){
		return AMI_NaoAceitou;
	}
		
	GRA_RetornoCriarAresta = GRA_CriarAresta(pGrafo, id1, id2);
	if (GRA_RetornoCriarAresta != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	} 
	
	return AMI_CondRetOK;
}/* Fim função: AMI  &Criar Amizade */


/***************************************************************************
*  Função: AMI  &Excluir Amizade
*
*	  AMI_CondRetOK
*	  AMI_UsuarioNaoExiste
*	  AMI_CondRetRetornoGraIncorreto
*	  AMI_CondRetRetornoPerIncorreto
*	
*****/

AMI_tpCondRet AMI_ExcluirAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil Usuario1, PER_tpPerfil Usuario2){
	
	GRA_tpCondRet GRA_RetornoExcluirAresta;
	PER_tpCondRet PER_RetornoEmail1;
	PER_tpCondRet PER_RetornoEmail2;
	int id1;
	int id2;
	
	PER_RetornoEmail1 = buscaEmail(pGrafo, Usuario1->email, &Usuario1, &id1);
	PER_RetornoEmail2 = buscaEmail(pGrafo, Usuario2->email, &Usuario2, &id2);
	if (PER_RetornoEmail1 == PER_CondRetEmailInexistente || PER_RetornoEmail2 == PER_CondRetEmailInexistente){
		return AMI_UsuarioNaoExiste;
	} else if (PER_RetornoEmail1 != PER_CondRetEmailJaCadastrado || PER_RetornoEmail2 != PER_CondRetEmailJaCadastrado){
		return AMI_CondRetRetornoPerIncorreto;
	}
	
	GRA_RetornoExcluirAresta = GRA_ExcluirAresta(pGrafo, id1, id2);
	if (GRA_RetornoExcluirAresta != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	} 
	
	return AMI_CondRetOK;
}/* Fim função: AMI  &Excluir Amizade */
 
/***************************************************************************
*  Função: AMI  &Verificar Número de Amigos
*
*     AMI_CondRetOK
*	  AMI_UsuarioNaoExiste
*     AMI_NaoPossuiAmizades
*	  AMI_CondRetRetornoPerIncorreto
*	  AMI_CondRetRetornoGraIncorreto
*
*****/
AMI_tpCondRet AMI_VerificarNumAmigos(GRA_tppGrafo pGrafo, PER_tpPerfil Usuario, int* numAmizades){
	
	GRA_tpCondRet GRA_RetornoNumAmigos;
	GRA_tpCondRet GRA_RetornoMoverCorrente;
	PER_tpCondRet PER_RetornoEmail;
	int id;
	
	PER_RetornoEmail = buscaEmail(pGrafo, Usuario->email, &Usuario, &id);
	if (PER_RetornoEmail == PER_CondRetEmailInexistente){
		return AMI_UsuarioNaoExiste;
	} else if (PER_RetornoEmail1 != PER_CondRetEmailJaCadastrado || PER_RetornoEmail2 != PER_CondRetEmailJaCadastrado){
		return AMI_CondRetRetornoPerIncorreto;
	}
	
	GRA_RetornoMoverCorrente = GRA_IrVertice(pGrafo, id);
	if (GRA_RetornoMoverCorrente != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	}
	
	GRA_RetornoNumAmigos = GRA_NumVertices(pGrafo, numAmizades);
	if (GRA_RetornoNumAmigos == GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	}
	
	if (numAmizades == 0){
		return AMI_NaoPossuiAmizades;
	}
	
	return AMI_CondRetOK;
}/* Fim função: AMI  &Verificar Número de Amigos */


/***************************************************************************
*  Função: AMI  &Armazenar Amizades
*
*     AMI_CondRetOK
*     AMI_NaoPossuiAmizades
*	  AMI_UsuarioNaoExiste
*	  AMI_CondRetRetornoPerIncorreto
*	  AMI_CondRetRetornoGraIncorreto
*
*****/
// Usar a função GRA_NumArestas(GRA_tppGrafo pGrafo,int *pNumArestas); para criar um espaço 
// pra cada vetor que vai a	armazenar as informações do cara e depois utilizar 
// GRA_RetornaIndiceAresta(GRA_tppGrafo pGrafo, int* pDado); pra pegar o vetor 
// com os indices de cada aresta de um cara, com isso fazer um for pra cada valor desse vetor
// e usar a função GRA_IrVertice(GRA_tppGrafo pGrafo, int numVert); e 
// GRA_ObterValor(GRA_tppGrafo pGrafo, void** pValorRet); para obter o perfil de cada um deles
// armazenar cada valor do perfil em um array separado (um array pro nome, outro pro email, etc)

AMI_tpCondRet AMI_ArmazenarAmizades(GRA_tppGrafo pGrafo, PER_tpPerfil Usuario, PER_tpPerfil **PerfilAmigos){
	
	GRA_tpCondRet GRA_RetornoIndiceAresta;
	GRA_tpCondRet GRA_RetornoObterAmigo;
	AMI_tpCondRet AMI_RetornoNumAmigos;
	PER_tpCondRet PER_RetornoEmail;
	//PER_tpCondRet PER_ObterPerfil;
	int id;
	int numAmigos;
	int* IdAmigos;
	
	PER_RetornoEmail = buscaEmail(pGrafo, Usuario->email, &Usuario, &id);
	if (PER_RetornoEmail == PER_CondRetEmailInexistente){
		return AMI_UsuarioNaoExiste;
	} else if (PER_RetornoEmail1 != PER_CondRetEmailJaCadastrado || PER_RetornoEmail2 != PER_CondRetEmailJaCadastrado){
		return AMI_CondRetRetornoPerIncorreto;
	}
	
	AMI_RetornoNumAmigos = AMI_VerificarNumAmigos(Usuario, numAmigos);
	if (AMI_RetornoNumAmigos != AMI_CondRetOK){
		return AMI_RetornoNumAmigos;
	}
	if (numAmigos == 0){
		return AMI_NaoPossuiAmizades;
	}
	
	GRA_RetornoIndiceAresta = GRA_RetornaIndiceAresta(GRA_tppGrafo pGrafo, IdAmigos);
	if (GRA_RetornoIndiceAresta != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	}
	
	for(i=0;i<numAmigos;i++) {
		PER_tpPerfil **perfil;
		char *email;
		
		GRA_RetornoObterAmigo = GRA_ObterValor(pGrafo, perfil);
		if (GRA_RetornoObterAmigo != GRA_CondRetOK){
			return AMI_CondRetRetornoGraIncorreto;
		}
		PerfilAmigos[i] = *perfil
		//strcpy((*perfil)->email, email);
	}
	
	return AMI_CondRetOK;
	
}/* Fim função: AMI  &Armazenar Amizades */


/***************************************************************************
*  Função: AMI  &Excluir Todas as Amizades
*
*     AMI_CondRetOK
*	  AMI_UsuarioNaoExiste
*     AMI_NaoPossuiAmizades
*	  AMI_CondRetRetornoPerIncorreto
*	  AMI_CondRetRetornoGraIncorreto
*
*****/

AMI_tpCondRet AMI_ExcluirTodasAmizades(GRA_tppGrafo pGrafo, PER_tpPerfil Usuario){
	
	GRA_tpCondRet GRA_RetornoIndiceAresta;
	GRA_tpCondRet GRA_RetornoExcluirAresta;
	AMI_tpCondRet AMI_RetornoNumAmigos;
	PER_tpCondRet PER_RetornoEmail;
	int id;
	int numAmigos;
	int* IdAmigos;
	
	PER_RetornoEmail = buscaEmail(pGrafo, Usuario->email, &Usuario, &id);
	if (PER_RetornoEmail == PER_CondRetEmailInexistente){
		return AMI_UsuarioNaoExiste;
	} else if (PER_RetornoEmail1 != PER_CondRetEmailJaCadastrado || PER_RetornoEmail2 != PER_CondRetEmailJaCadastrado){
		return AMI_CondRetRetornoPerIncorreto;
	}
	
	AMI_RetornoNumAmigos = AMI_VerificarNumAmigos(Usuario, numAmigos);
	if (AMI_RetornoNumAmigos != AMI_CondRetOK){
		return AMI_RetornoNumAmigos;
	}
	if (numAmigos == 0){
		return AMI_NaoPossuiAmizades;
	}
	
	GRA_RetornoIndiceAresta = GRA_RetornaIndiceAresta(GRA_tppGrafo pGrafo, IdAmigos);
	if (GRA_RetornoIndiceAresta != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	}
	
	for(i=0;i<numAmigos;i++) {
		GRA_RetornoExcluirAresta = GRA_ExcluirAresta(pGrafo, id, IdAmigos[i]);
		if (GRA_RetornoExcluirAresta != GRA_CondRetOK){
			return AMI_CondRetRetornoGraIncorreto;
		}
	}
	
	return AMI_CondRetOK;
	
}/* Fim função: AMI  &Excluir Todas as Amizades */


/***************************************************************************
*  Função: AMI  &Verificar Amizade
*
*     AMI_CondRetOK
*     AMI_UsuarioNaoExiste
*	  AMI_CondRetRetornoPerIncorreto
*	  AMI_CondRetRetornoGraIncorreto
*	  AMI_AmizadeNaoExiste
*
*****/
 
 AMI_tpCondRet AMI_VerificarAmizade(GRA_tppGrafo pGrafo, Usuario1, PER_tpPerfil Usuario2, AMI_tpVerificacao ExisteAmizade)[
 
	GRA_tpCondRet GRA_RetornoVerificaAmizade;
	PER_tpCondRet PER_RetornoEmail1;
	PER_tpCondRet PER_RetornoEmail2;
	int id1;
	int id2;
	
	PER_RetornoEmail1 = buscaEmail(pGrafo, Usuario1->email, &Usuario1, &id1);
	PER_RetornoEmail2 = buscaEmail(pGrafo, Usuario2->email, &Usuario2, &id2);
	if (PER_RetornoEmail1 == PER_CondRetEmailInexistente || PER_RetornoEmail2 == PER_CondRetEmailInexistente){
		return AMI_UsuarioNaoExiste;
	} else if (PER_RetornoEmail1 != PER_CondRetEmailJaCadastrado || PER_RetornoEmail2 != PER_CondRetEmailJaCadastrado){
		return AMI_CondRetRetornoPerIncorreto;
	}
	
	GRA_RetornoVerificaAmizade = GRA_ExisteAresta(pGrafo, id1, id2);
	if (GRA_RetornoVerificaAmizade == GRA_CondRetNaoAchouAresta){
		return AMI_AmizadeNaoExiste;
	} else if (GRA_RetornoVerificaAmizade != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	}
	
	return AMI_CondRetOK;
 }/* Fim função: AMI  &Verificar Amizade */
 
 
/*****  Código das funções encapsuladas no módulo  *****/
/***********************************************************************
*
*  $FC Função: PER - Busca um email no grafo
*
***********************************************************************/
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
*  $FC Função: PER - Transforma retorno do grafo
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
*  $FC Função: PER - Transforma retorno do grafo
*
***********************************************************************/
/*
*     PER_CondRetOK
*     PER_CondRetParametroGRAIncorreto
*     PER_CondRetRetornoLisIncorreto
*/
PER_tpCondRet restauraCorrenteGrafo(GRA_tppGrafo pGrafo, int id) {
	GRA_tpCondRet retorno;
	retorno = GRA_IrVertice(pGrafo, id);
	return transformaRetGRA(retorno);
}