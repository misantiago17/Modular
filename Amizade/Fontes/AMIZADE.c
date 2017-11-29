#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
/***************************************************************************
*  $MCI M�dulo de implementa��o: AMI  Modulo Amizade
*
*  Arquivo gerado:              AMIZADE.c
*  Letras identificadoras:      AMI
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  DI/PUC-Rio
*  Autores: Michelle Santiago (ms)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor   	 Data     	Observa��es
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

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*  Fun��o: AMI  &Criar Amizade
*
*      AMI_CondRetOK
*      AMI_NaoAceitou
*	   AMI_UsuarioNaoExiste
*	   AMI_ArestaParaSiMesmo
*	   AMI_AmizadeJaExiste
*	   AMI_CondRetRetornoGraIncorreto
*	   AMI_CondRetRetornoPerIncorreto
*
*****/

AMI_tpCondRet AMI_CriarAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil * Usuario2, AMI_tpSolitacao Aceitacao){
	
	GRA_tpCondRet GRA_RetornoCriarAresta;
	PER_tpCondRet PER_RetornoEmail1;
	PER_tpCondRet PER_RetornoEmail2;
	int id1;
	int id2;
	char* email1;
	char* email2;
	
	PER_RetornoEmail1 = retornaEmailPerfil(Usuario1,email1);
	PER_RetornoEmail2 = retornaemailPerfil(Usuario2,email2);
	if (PER_RetornoEmail1 == PER_CondRetPerfilInexistente || PER_RetornoEmail2 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
	}
	
	if (Aceitacao == AMI_SolicitacaoRejeitada){
		return AMI_NaoAceitou;
	}
		
	GRA_RetornoCriarAresta = GRA_CriarAresta(pGrafo, id1, id2);
	if (GRA_RetornoCriarAresta == GRA_CondRetArestaJaExiste){
		return AMI_AmizadeJaExiste;
	} else if (GRA_RetornoCriarAresta == GRA_CondRetArestaParaSiMesmo){
		return 	AMI_ArestaParaSiMesmo;
	}else if (GRA_RetornoCriarAresta != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	}
	
	return AMI_CondRetOK;
}/* Fim fun��o: AMI  &Criar Amizade */


/***************************************************************************
*  Fun��o: AMI  &Excluir Amizade
*
*	  AMI_CondRetOK
*	  AMI_UsuarioNaoExiste
*	  AMI_AmizadeNaoExiste
*	  AMI_CondRetRetornoGraIncorreto
*	  AMI_CondRetRetornoPerIncorreto
*	
*****/

AMI_tpCondRet AMI_ExcluirAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil Usuario2){
	
	GRA_tpCondRet GRA_RetornoExcluirAresta;
	PER_tpCondRet PER_RetornoEmail1;
	PER_tpCondRet PER_RetornoEmail2;
	int id1;
	int id2;
	char * email1;
	char * email2;
	
	PER_RetornoEmail1 = retornaEmailPerfil(Usuario1,email1);
	PER_RetornoEmail2 = retornaemailPerfil(Usuario2,email2);
	if (PER_RetornoEmail1 == PER_CondRetPerfilInexistente || PER_RetornoEmail2 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
	}
	
	GRA_RetornoExcluirAresta = GRA_ExcluirAresta(pGrafo, id1, id2);
	if (GRA_RetornoExcluirAresta == GRA_CondRetNaoAchouAresta){
		return AMI_AmizadeNaoExiste;
	} else if (GRA_RetornoExcluirAresta != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	}
	
	return AMI_CondRetOK;
}/* Fim fun��o: AMI  &Excluir Amizade */
 
/***************************************************************************
*  Fun��o: AMI  &Verificar N�mero de Amigos
*
*     AMI_CondRetOK
*	  AMI_UsuarioNaoExiste
*     AMI_NaoPossuiAmizades
*	  AMI_CondRetRetornoPerIncorreto
*	  AMI_CondRetRetornoGraIncorreto
*
*****/
AMI_tpCondRet AMI_VerificarNumAmigos(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, int* numAmizades){
	
	GRA_tpCondRet GRA_RetornoNumAmigos;
	GRA_tpCondRet GRA_RetornoMoverCorrente;
	PER_tpCondRet PER_RetornoEmail;
	int id;
	char * email1;
	
	PER_RetornoEmail1 = retornaEmailPerfil(Usuario1,email1);
	if (PER_RetornoEmail1 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
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
}/* Fim fun��o: AMI  &Verificar N�mero de Amigos */


/***************************************************************************
*  Fun��o: AMI  &Armazenar Amizades
*
*     AMI_CondRetOK
*     AMI_NaoPossuiAmizades
*	  AMI_UsuarioNaoExiste
*	  AMI_CondRetRetornoPerIncorreto
*	  AMI_CondRetRetornoGraIncorreto
*
*****/

AMI_tpCondRet AMI_ArmazenarAmizades(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil **PerfilAmigos){
	
	GRA_tpCondRet GRA_RetornoIndiceAresta;
	GRA_tpCondRet GRA_RetornoObterAmigo;
	AMI_tpCondRet AMI_RetornoNumAmigos;
	PER_tpCondRet PER_RetornoEmail;
	//PER_tpCondRet PER_ObterPerfil;
	int id;
	int numAmigos;
	int* IdAmigos;
	char* email1;
	
	PER_RetornoEmail1 = retornaEmailPerfil(Usuario1,email1);
	if (PER_RetornoEmail1 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
	}
	
	AMI_RetornoNumAmigos = AMI_VerificarNumAmigos(Usuario1, numAmigos);
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
	
}/* Fim fun��o: AMI  &Armazenar Amizades */


/***************************************************************************
*  Fun��o: AMI  &Excluir Todas as Amizades
*
*     AMI_CondRetOK
*	  AMI_UsuarioNaoExiste
*     AMI_NaoPossuiAmizades
*	  AMI_CondRetRetornoPerIncorreto
*	  AMI_CondRetRetornoGraIncorreto
*
*****/

AMI_tpCondRet AMI_ExcluirTodasAmizades(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1){
	
	GRA_tpCondRet GRA_RetornoIndiceAresta;
	GRA_tpCondRet GRA_RetornoExcluirAresta;
	AMI_tpCondRet AMI_RetornoNumAmigos;
	PER_tpCondRet PER_RetornoEmail;
	int id;
	int numAmigos;
	int* IdAmigos;
	char* email1;
	
	PER_RetornoEmail1 = retornaEmailPerfil(Usuario1,email1);
	if (PER_RetornoEmail1 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
	}
	
	AMI_RetornoNumAmigos = AMI_VerificarNumAmigos(Usuario1, numAmigos);
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
	
}/* Fim fun��o: AMI  &Excluir Todas as Amizades */


/***************************************************************************
*  Fun��o: AMI  &Verificar Amizade
*
*     AMI_CondRetOK
*     AMI_UsuarioNaoExiste
*	  AMI_CondRetRetornoPerIncorreto
*	  AMI_CondRetRetornoGraIncorreto
*	  AMI_AmizadeNaoExiste
*
*****/
 
 AMI_tpCondRet AMI_VerificarAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil * Usuario2, AMI_tpVerificacao ExisteAmizade)[
 
	GRA_tpCondRet GRA_RetornoVerificaAmizade;
	PER_tpCondRet PER_RetornoEmail1;
	PER_tpCondRet PER_RetornoEmail2;
	int id1;
	int id2;
	char* email1;
	char* email2;
	
	PER_RetornoEmail1 = retornaEmailPerfil(Usuario1,email1);
	PER_RetornoEmail2 = retornaemailPerfil(Usuario2,email2);
	if (PER_RetornoEmail1 == PER_CondRetPerfilInexistente || PER_RetornoEmail2 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
	}
	
	GRA_RetornoVerificaAmizade = GRA_ExisteAresta(pGrafo, id1, id2);
	if (GRA_RetornoVerificaAmizade == GRA_CondRetNaoAchouAresta){
		return AMI_AmizadeNaoExiste;
	} else if (GRA_RetornoVerificaAmizade != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	}
	
	return AMI_CondRetOK;
 }/* Fim fun��o: AMI  &Verificar Amizade */
 
 
/*****  C�digo das fun��es encapsuladas no m�dulo  *****/
/***********************************************************************
*
*  $FC Fun��o: PER - Busca um email no grafo
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
*  $FC Fun��o: PER - Transforma retorno do grafo
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
*  $FC Fun��o: PER - Transforma retorno do grafo
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
*  $FC Fun��o: PER - Transforma retorno do grafo
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