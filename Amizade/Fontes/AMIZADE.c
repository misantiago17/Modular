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

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*  Função: AMI  &Criar Amizade
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
	PER_tpCondRet PER_RetornoId1;
	PER_tpCondRet PER_RetornoId2;
	int id1;
	int id2;
	
	PER_RetornoId1 = PER_retornaIdPerfil(pGrafo, Usuario1,id1);
	PER_RetornoId2 = PER_retornaIdPerfil(pGrafo, Usuario2,id2);
	if (PER_RetornoId1 == PER_CondRetPerfilInexistente || PER_RetornoId2 == PER_CondRetPerfilInexistente){
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
}/* Fim função: AMI  &Criar Amizade */


/***************************************************************************
*  Função: AMI  &Excluir Amizade
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
	PER_tpCondRet PER_RetornoId1;
	PER_tpCondRet PER_RetornoId2;
	int id1;
	int id2;
	
	PER_RetornoId1 = PER_retornaIdPerfil(pGrafo, Usuario1,id1);
	PER_RetornoId2 = PER_retornaIdPerfil(pGrafo, Usuario2,id2);
	if (PER_RetornoId1 == PER_CondRetPerfilInexistente || PER_RetornoId2 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
	}
	
	GRA_RetornoExcluirAresta = GRA_ExcluirAresta(pGrafo, id1, id2);
	if (GRA_RetornoExcluirAresta == GRA_CondRetNaoAchouAresta){
		return AMI_AmizadeNaoExiste;
	} else if (GRA_RetornoExcluirAresta != GRA_CondRetOK){
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
AMI_tpCondRet AMI_VerificarNumAmigos(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, int* numAmizades){
	
	GRA_tpCondRet GRA_RetornoNumAmigos;
	GRA_tpCondRet GRA_RetornoMoverCorrente;
	PER_tpCondRet PER_RetornoId1;
	int id;
	
	PER_RetornoId1 = PER_retornaIdPerfil(pGrafo, Usuario1,id);
	if (PER_RetornoId1 == PER_CondRetPerfilInexistente){
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

AMI_tpCondRet AMI_ArmazenarAmizades(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil **PerfilAmigos){
	
	GRA_tpCondRet GRA_RetornoIndiceAresta;
	GRA_tpCondRet GRA_RetornoObterAmigo;
	AMI_tpCondRet AMI_RetornoNumAmigos;
	PER_tpCondRet PER_RetornoId1;
	int id;
	int numAmigos;
	int* IdAmigos;
	
	PER_RetornoId1 = PER_retornaIdPerfil(pGrafo, Usuario1,id);
	if (PER_RetornoId1 == PER_CondRetPerfilInexistente){
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

AMI_tpCondRet AMI_ExcluirTodasAmizades(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1){
	
	GRA_tpCondRet GRA_RetornoIndiceAresta;
	GRA_tpCondRet GRA_RetornoExcluirAresta;
	AMI_tpCondRet AMI_RetornoNumAmigos;
	PER_tpCondRet PER_RetornoId1;
	int id;
	int numAmigos;
	int* IdAmigos;
	
	PER_RetornoId1 = PER_retornaIdPerfil(pGrafo, Usuario1,id);
	if (PER_RetornoId1 == PER_CondRetPerfilInexistente){
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
 
 AMI_tpCondRet AMI_VerificarAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil * Usuario2, AMI_tpVerificacao ExisteAmizade)[
 
	GRA_tpCondRet GRA_RetornoVerificaAmizade;
	PER_tpCondRet PER_RetornoId1;
	PER_tpCondRet PER_RetornoId2;
	int id1;
	int id2;
	
	PER_RetornoId1 = PER_retornaIdPerfil(pGrafo, Usuario1,id1);
	PER_RetornoId2 = PER_retornaIdPerfil(pGrafo, Usuario2,id2);
	if (PER_RetornoId1 == PER_CondRetPerfilInexistente || PER_RetornoId2 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
	}
	
	GRA_RetornoVerificaAmizade = GRA_ExisteAresta(pGrafo, id1, id2);
	if (GRA_RetornoVerificaAmizade == GRA_CondRetNaoAchouAresta){
		return AMI_AmizadeNaoExiste;
	} else if (GRA_RetornoVerificaAmizade != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	}
	
	return AMI_CondRetOK;
 }/* Fim função: AMI  &Verificar Amizade */
 
 
