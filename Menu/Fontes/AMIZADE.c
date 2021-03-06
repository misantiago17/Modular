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
*     Vers�o  	Autor   	 Data     	Observa��es
*	  	4		 ms		   06/12/2017	pequenas corre��es
*	  	3		 ms	   	   29/11/2017	mudan�a de retorno das fun��es
*     	2        ms        20/11/2017 	inicio desenvolvimento
*     	1        ms        14/11/2017 	cria���o do arquivo
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
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
*
*****/

AMI_tpCondRet AMI_CriarAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil * Usuario2, AMI_tpSolitacao Aceitacao){
	
	GRA_tpCondRet GRA_RetornoCriarAresta;
	PER_tpCondRet PER_RetornoId1;
	PER_tpCondRet PER_RetornoId2;
	int id1;
	int id2;
	
	/* Obtem os dois perfis */
	
	PER_RetornoId1 = PER_retornaIdPerfil(pGrafo, Usuario1,&id1);
	PER_RetornoId2 = PER_retornaIdPerfil(pGrafo, Usuario2,&id2);

	/* Verifica se os dois perfis existem */
	
	if (PER_RetornoId1 == PER_CondRetPerfilInexistente || PER_RetornoId2 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
	}
	
	/* Verifica se a solicita��o foi aceita */
	
	if (Aceitacao == AMI_SolicitacaoRejeitada){
		return AMI_NaoAceitou;
	}
		
	/* Cria Amizade entre os dois perfis */
	
	GRA_RetornoCriarAresta = GRA_CriarAresta(pGrafo, id1, id2);

	if (GRA_RetornoCriarAresta == GRA_CondRetArestaJaExiste){
		return AMI_AmizadeJaExiste;
	} else if (GRA_RetornoCriarAresta == GRA_CondRetArestaParaSiMesmo){
		return 	AMI_ArestaParaSiMesmo;
	}else if (GRA_RetornoCriarAresta != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	} /* if */

	return AMI_CondRetOK;
	
} /* Fim fun��o: AMI  &Criar Amizade */


/***************************************************************************
*  Fun��o: AMI  &Excluir Amizade
*
*	  AMI_CondRetOK
*	  AMI_UsuarioNaoExiste
*	  AMI_AmizadeNaoExiste
*	  AMI_CondRetRetornoGraIncorreto
*
*****/

AMI_tpCondRet AMI_ExcluirAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil* Usuario2){
	
	GRA_tpCondRet GRA_RetornoExcluirAresta;
	PER_tpCondRet PER_RetornoId1;
	PER_tpCondRet PER_RetornoId2;
	int id1;
	int id2;
	
	/* Obtem os dois perfis */
	
	PER_RetornoId1 = PER_retornaIdPerfil(pGrafo, Usuario1,&id1);
	PER_RetornoId2 = PER_retornaIdPerfil(pGrafo, Usuario2,&id2);
	
	/* Verifica se os dois perfis existem */

	if (PER_RetornoId1 == PER_CondRetPerfilInexistente || PER_RetornoId2 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
	}
	
	/* Exclu� amizade entre os dois perfis */
	
	GRA_RetornoExcluirAresta = GRA_ExcluirAresta(pGrafo, id1, id2);
	if (GRA_RetornoExcluirAresta == GRA_CondRetNaoAchouAresta){
		return AMI_AmizadeNaoExiste;
	} else if (GRA_RetornoExcluirAresta != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	} /* if */
	
	return AMI_CondRetOK;
	
} /* Fim fun��o: AMI  &Excluir Amizade */
 
 
/***************************************************************************
*  Fun��o: AMI  &Verificar N�mero de Amigos
*
*     AMI_CondRetOK
*	  AMI_UsuarioNaoExiste
*     AMI_NaoPossuiAmizades
*	  AMI_CondRetRetornoGraIncorreto
*
*****/

AMI_tpCondRet AMI_VerificarNumAmigos(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, int* numAmizades){
	
	GRA_tpCondRet GRA_RetornoNumAmigos;
	GRA_tpCondRet GRA_RetornoMoverCorrente;
	PER_tpCondRet PER_RetornoId1;
	int id;
	int NumAmigos;
	
	/* Obtem perfil */
	
	PER_RetornoId1 = PER_retornaIdPerfil(pGrafo, Usuario1,&id);

	/* Verifica se perfil existe */
	
	if (PER_RetornoId1 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
	}
	
	/* Verifica numero de amigos de um determinado perfil */
	
	GRA_RetornoMoverCorrente = GRA_IrVertice(pGrafo, id);
	if (GRA_RetornoMoverCorrente != GRA_CondRetOK){		
		return AMI_CondRetRetornoGraIncorreto;
	}
	
	GRA_RetornoNumAmigos = GRA_NumArestas(pGrafo, &NumAmigos);
	if (GRA_RetornoNumAmigos != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	}

	*numAmizades=NumAmigos;
	if (NumAmigos == 0){
		return AMI_NaoPossuiAmizades;
	}

	return AMI_CondRetOK;
	
} /* Fim fun��o: AMI  &Verificar N�mero de Amigos */


/***************************************************************************
*  Fun��o: AMI  &Armazenar Amizades
*
*     AMI_CondRetOK
*     AMI_NaoPossuiAmizades
*	  AMI_UsuarioNaoExiste
*     AMI_CondRetFaltouMemoria
*	  AMI_CondRetRetornoGraIncorreto
*
*****/

AMI_tpCondRet AMI_ArmazenarAmizades(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil *PerfilAmigos[]){
	
	GRA_tpCondRet GRA_RetornoIndiceAresta;
	GRA_tpCondRet GRA_RetornoObterAmigo;
	AMI_tpCondRet AMI_RetornoNumAmigos;
	PER_tpCondRet PER_RetornoId1;
	int id;
	int numAmigos;
	int* IdAmigos;
	PER_tpPerfil *perfil;
	int i;
	
	/* Verifica se perfil existe */
	
	PER_RetornoId1 = PER_retornaIdPerfil(pGrafo, Usuario1,&id);
	if (PER_RetornoId1 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
	}
	
	/* Obtem n�mero de amigos */

	AMI_RetornoNumAmigos = AMI_VerificarNumAmigos(pGrafo,Usuario1,&numAmigos);

	if (AMI_RetornoNumAmigos != AMI_CondRetOK){
		return AMI_RetornoNumAmigos;
	}
	if (numAmigos == 0){
		return AMI_NaoPossuiAmizades;
	}
	
	/* Aloca mem�ria para armazenar o ID do amigo */
	
	IdAmigos = (int*)malloc(numAmigos*sizeof(int));
	
	if(IdAmigos == NULL)
		return AMI_CondRetFaltouMemoria;
	
	/* Obtem ID do amigo */
	
	GRA_RetornoIndiceAresta = GRA_RetornaIndiceAresta(pGrafo, IdAmigos);
	if (GRA_RetornoIndiceAresta != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	}
	
	/* Armazena o perfil do amigo no vetor passado por par�metro */
	
	for(i=0;i<numAmigos;i++) {
		
		if(GRA_IrVertice(pGrafo,IdAmigos[i]) != GRA_CondRetOK)
			return AMI_CondRetRetornoGraIncorreto;
		
		GRA_RetornoObterAmigo = GRA_ObterValor(pGrafo,(void**)&perfil);
		
		if (GRA_RetornoObterAmigo != GRA_CondRetOK)
			return AMI_CondRetRetornoGraIncorreto;
		
		 PerfilAmigos[i]= perfil;
	} /* if */
	
	free(IdAmigos);
	
	return AMI_CondRetOK;
	
} /* Fim fun��o: AMI  &Armazenar Amizades */


/***************************************************************************
*  Fun��o: AMI  &Excluir Todas as Amizades
*
*     AMI_CondRetOK
*	  AMI_UsuarioNaoExiste
*     AMI_NaoPossuiAmizades
*     AMI_CondRetFaltouMemoria
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
	int i;
	
	/* Verifica se o perfil existe */
	
	PER_RetornoId1 = PER_retornaIdPerfil(pGrafo, Usuario1,&id);

	if (PER_RetornoId1 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
	}
	
	/* Obtem o n�mero de amigos */

	AMI_RetornoNumAmigos = AMI_VerificarNumAmigos(pGrafo,Usuario1, &numAmigos);

	if (AMI_RetornoNumAmigos != AMI_CondRetOK){
		return AMI_RetornoNumAmigos;
	}
	if (numAmigos == 0){
		return AMI_NaoPossuiAmizades;
	}
	
	/* Aloca mem�ria para armazenar o ID de cada amigo */
	
	IdAmigos=(int*)malloc(numAmigos*sizeof(int));
	if(IdAmigos==NULL)
		return AMI_CondRetFaltouMemoria;
	
	GRA_RetornoIndiceAresta = GRA_RetornaIndiceAresta(pGrafo, IdAmigos);
	
	if (GRA_RetornoIndiceAresta != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	}
	
	/* Exclu� amizade com cada amigo obtido */
	
	for(i=0;i<numAmigos;i++) {
		GRA_RetornoExcluirAresta = GRA_ExcluirAresta(pGrafo, id, IdAmigos[i]);
		if (GRA_RetornoExcluirAresta != GRA_CondRetOK){
			return AMI_CondRetRetornoGraIncorreto;
		}
	} /* for */
	
	return AMI_CondRetOK;
	
}/* Fim fun��o: AMI  &Excluir Todas as Amizades */


/***************************************************************************
*  Fun��o: AMI  &Verificar Amizade
*
*     AMI_CondRetOK
*     AMI_UsuarioNaoExiste
*	  AMI_CondRetRetornoGraIncorreto
*	  AMI_AmizadeNaoExiste
*
*****/

 AMI_tpCondRet AMI_VerificarAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * Usuario1, PER_tpPerfil * Usuario2){
	 
	GRA_tpCondRet GRA_RetornoVerificaAmizade;
	PER_tpCondRet PER_RetornoId1;
	PER_tpCondRet PER_RetornoId2;
	int id1;
	int id2;
	
	/* Verifica se os dois perfis existem */
	
	PER_RetornoId1 = PER_retornaIdPerfil(pGrafo, Usuario1,&id1);
	PER_RetornoId2 = PER_retornaIdPerfil(pGrafo, Usuario2,&id2);

	if (PER_RetornoId1 == PER_CondRetPerfilInexistente || PER_RetornoId2 == PER_CondRetPerfilInexistente){
		return AMI_UsuarioNaoExiste;
	}
	
	/* Verifica se a amizade existe */
	
	GRA_RetornoVerificaAmizade = GRA_ExisteAresta(pGrafo, id1, id2);
	if (GRA_RetornoVerificaAmizade == GRA_CondRetNaoAchouAresta){
		return AMI_AmizadeNaoExiste;
	} else if (GRA_RetornoVerificaAmizade != GRA_CondRetOK){
		return AMI_CondRetRetornoGraIncorreto;
	} /* if */
	
	return AMI_CondRetOK;
 }/* Fim fun��o: AMI  &Verificar Amizade */
 
 /********** Fim do m�dulo de implementa��o: AMI  Modulo Amizade **********/