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
#include   <stdlib.h>
#include   "CESPDIN.H"
#include   "GRAFO.h"
#include   "PERFIL.h"
#include   "AMIZADE.h"
#include   "MENSAGEM.H"

void MENU_Menu1(GRA_tppGrafo pGrafo);
void MENU_Menu2(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);
void MENU_Menu3();
void MENU_Menu4();
void MENU_Menu5();
void DestruirValor( void * pValor );

int main () {
	GRA_tppGrafo Grafo;
    
	GRA_CriarGrafo(DestruirValor, &Grafo);
	
    MENU_Menu1(Grafo);
    
    
    return 0;
}


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
 *  Fun��o: MENU  &Menu 1 - Menu inicial
 *
 *****/

void MENU_Menu1(GRA_tppGrafo pGrafo) {
    
    int menuEscolhido;
    int escolhaInvalida = 0;
    int escolhaPerfilInvalido = 0;
    
    char * emailPerfilProcurado;
	char * emailPerfil;
    char * primNome;
    char * ultNome;
    char * cidade;
    int dia;
    int mes;
    int ano;
	int id;
	
	PER_tpPerfil * pPerfil;
	PER_tpCondRet condRetObterPerfil;
	PER_tpCondRet condRetObterEmail;
	
	if ((emailPerfilProcurado = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N�o h� espa�o para armazenar email do perfil procurado");
		exit(0);
	}
	if ((emailPerfil = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N�o h� espa�o para armazenar email do perfil");
		exit(0);
	}
	if ((primNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N�o h� espa�o para armazenar primeiro nome do perfil");
		exit(0);
	}
	if ((ultNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N�o h� espa�o para armazenar ultimo nome do perfil");
		exit(0);
	}
	if ((cidade = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N�o h� espa�o para armazenar ultimo nome do cidade");
		exit(0);
	}
    
    printf("===============================================================================\n");
    printf("Bem-vindo a rede social bl�bl�bl�\n\n");
    
    printf("O que deseja fazer? \n\n");
    
    printf("1. Criar novo perfil \n");
    printf("2. Ir para perfil \n");
    printf("3. Ver n�mero de perfis cadastrados \n");
    printf("4. Excluir todos os perfis da rede \n\n");
    
    while (escolhaInvalida == 0){
        
        printf("> ");
        scanf("%d", &menuEscolhido);
        printf("\n\n");
        
        // Menu 3
        if (menuEscolhido == 1){
            
            MENU_Menu3();
            escolhaInvalida = 1;
            
        // Menu 2
        } else if (menuEscolhido == 2) {
            
            while (escolhaPerfilInvalido == 0) {
                printf("Digite o email do perfil que deseja encontrar: ");
                scanf("%d", &emailPerfilProcurado);
                printf("\n\n");
				
				condRetObterEmail = PER_BuscaEmail(pGrafo, emailPerfilProcurado, &pPerfil, &id);
                
                if (condRetObterEmail == PER_CondRetEmailInexistente){
                    printf("Usuario procurado n�o existe. Por favor procure novamente. \n\n");
				} else if (condRetObterEmail == PER_CondRetRedeVazia) {
					printf("A rede est� vazia. Crie um usu�rio e tente novamente. \n\n");
				} else if (condRetObterEmail != PER_CondRetOK){
					printf("Retorno do m�dulo perfil inesperado. \n\n");
					exit(0);
				} else {
					condRetObterPerfil = PER_ObterPerfil(pPerfil, emailPerfil, primNome, ultNome,
                                                     &dia, &mes, &ano, cidade);
													 
					if (condRetObterPerfil == PER_CondRetFaltouMemoria){
						printf("Faltou mem�ria para executar a a��o. \n\n");
						exit(0);
					} else if (condRetObterPerfil != PER_CondRetOK){
						printf("Retorno do m�dulo perfil inesperado. \n\n");
						exit(0);
					} else {
						escolhaPerfilInvalido = 1;
						escolhaInvalida = 1;
                    
						MENU_Menu2(pGrafo, pPerfil, emailPerfilProcurado, primNome, ultNome, cidade, dia, mes, ano);
					}
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
            
            printf("Escolha inv�lida de menu. Por favor, digite o menu novamente.\n\n");
            
        }
        
    }
    
}/* Fim fun��o: MENU - Menu 1 - Menu Inicial */

/***************************************************************************
 *  Fun��o: MENU  &Menu 2 - Menu inicial
 *
 *****/

// Ir para perfil
void MENU_Menu2(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);

// Criar novo perfil
void MENU_Menu3();

// Ver n�mero de perfis cadastrado
void MENU_Menu4();

// Excluir todos os perfis da rede
void MENU_Menu5();



/***************************************************************************
 *  Fun��o: MENU  &Destriur Valor
 *
 *****/
 
   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim fun��o: TAMI -Destruir valor */

 // =================== TUDO AQUI EMBAIXO NAO � MENU ========================


 
 
