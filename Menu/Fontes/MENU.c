#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
/***************************************************************************
*  $MCI M�dulo de implementa��o: MENU  Modulo Menu
*
*  Arquivo gerado:              MENU.c
*  Letras identificadoras:      MENU
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
#include   "MENSAGEM.H"

int main () {
    
	GRA_tppGrafo *Grafo;
	
	if ((Grafo = (GRA_tppGrafo *)malloc(sizeof(GRA_tppGrafo))) == NULL)
		return exit(0);
    
    MENU_Menu1();
    
    
    return 0;
}


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
 *  Fun��o: MENU  &Menu 1 - Menu inicial
 *
 *      MENU_CondRetOK
 *      MENU_UsuarioNaoExiste
 *      AMI_NaoAceitou
 *      AMI_UsuarioNaoExiste
 *      AMI_ArestaParaSiMesmo
 *      AMI_AmizadeJaExiste
 *      AMI_CondRetRetornoGraIncorreto
 *      AMI_CondRetRetornoPerIncorreto
 *
 *****/

void MENU_Menu1(GRA_tppGrafo pGrafo) {
    
    int menuEscolhido;
    int escolhaInvalida = 0;
    int escolhaPerfilInvalido = 0;
    
    char * emailPerfilProcurado[50];
    char * primNome[50];
    char * ultNome[50];
    char * cidade[50];
    int dia;
    int mes;
    int ano;
    
    PER_tpCondRet condRetObterPerfil;
    
    printf("===============================================================================\n");
    printf("Bem-vindo a rede social bl�bl�bl�\n\n");
    
    printf("O que deseja fazer? \n\n");
    
    printf("1. Criar novo perfil \n");
    printf("2. Ir para perfil \n");
    printf("3. Ver n�mero de perfis cadastrados \n");
    printf("4. Excluir todos os perfis da rede \n\n");
    
    while (escolhaInvalida == 0){
        
        printf("> ");
        scanf("%d", menuEscolhido);
        print("\n\n")
        
        // Menu 3
        if (menuEscolhido == 1){
            
            MENU_Menu3();
            escolhaInvalida = 1;
            
        // Menu 2
        } else if (menuEscolhido == 2) {
            
            while (escolhaPerfilInvalido == 0) {
                printf("Digite o email do perfil que deseja encontrar: ");
                scanf("%d", perfilProcurado);
                printf("\n\n");
                
                condRetObterPerfil = PER_ObterPerfil(pGrafo, perfilProcurado, primNome, ultNome,
                                                     dia, mes, ano, cidade);
                if (condRetObterPerfil == PER_CondRetEmailInexistente){
                    prinf("Usuario procurado n�o existe. Por favor procure novamente. \n\n");
                } else if (condRetObterPerfil == PER_CondRetFaltouMemoria){
                    prinf("Faltou mem�ria para executar a a��o. \n\n");
                    break;
                    exit(0);
                } else if (condRetObterPerfil != PER_CondRetOK){
                    prinf("Retorno do m�dulo perfil inesperado. \n\n");
                    break;
                    exit(0);
                } else {
                    escolhaPerfilInvalido = 1
                    escolhaInvalida = 1
                    
                    MENU_Menu2(pGrafo, PER_tpPerfil, emailPerfilProcurado, primNome, ultNome, cidade, dia, mes, ano);
                }
            }
            
            
        // Menu 4
        } else if (menuEscolhido == 3) {
            
            MENU_Menu4();
            escolhaInvalida = 1;
            
        // Menu 5
        } else if (menuEscolhido == 4) {
            
            MENU_Menu5();
            escolhaInvalida = 1;
            
        } else {
            
            print("Escolha inv�lida de menu. Por favor, digite o menu novamente.\n\n")
            
        }
        
    }
    
}

// Ir para perfil
MENU_tpCondRet MENU_Menu2(GRA_tppGrafo pGrafo, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);

// Criar novo perfil
MENU_tpCondRet MENU_Menu3();

// Ver n�mero de perfis cadastrado
MENU_tpCondRet MENU_Menu4();

// Excluir todos os perfis da rede
MENU_tpCondRet MENU_Menu5();


// =================== TUDO AQUI EMBAIXO NAO � MENU ========================



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
 }/* Fim fun��o: AMI  &Verificar Amizade */
 
 
