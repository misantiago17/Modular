#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
/***************************************************************************
*  $MCI Módulo de implementação: MENU  Modulo Menu
*
*  Arquivo gerado:              MENU.c
*  Letras identificadoras:      MENU
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
#include   <stdlib.h>
#include   "GRAFO.h"
#include   "PERFIL.h"
#include   "AMIZADE.h"
#include   "MENSAGEM.H"

void MENU_Menu1(GRA_tppGrafo pGrafo);
void MENU_Menu2(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);
void MENU_Menu3(GRA_tppGrafo pGrafo);
void MENU_Menu4(GRA_tppGrafo pGrafo);
void MENU_Menu5(GRA_tppGrafo pGrafo);
void MENU_Menu6(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);
void MENU_Menu7(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, PER_tpPerfil * pPerfil2);
void MENU_Menu8(GRA_tppGrafo pGrafo, char ** listaEmails);
void MENU_Menu9(PER_tpPerfil * pPerfil);
void MENU_Menu10(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil);
void MENU_Menu11(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil);
void MENU_Menu11(GRA_tppGrafo pGrafo, char * email);
void MENU_Menu12(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);
void MENU_Menu13(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);
void MENU_Menu14(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);
void MENU_Menu15(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);
void MENU_Menu16(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, PER_tpPerfil * pPerfil2);
void MENU_Menu17(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, PER_tpPerfil * pPerfil2);

void DestruirValor( void * pValor );

int main () {
	GRA_tppGrafo Grafo;
    
	GRA_CriarGrafo(DestruirValor, &Grafo);
	
    MENU_Menu1(Grafo);
    
    
    return 0;
}


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *  Função: MENU  &Menu 1 - Menu inicial
 *
 *****/

 // Menu Inicial - COMPLETE
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
		printf("Não há espaço para armazenar email do perfil procurado");
		exit(0);
	}
	if ((emailPerfil = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para armazenar email do perfil");
		exit(0);
	}
	if ((primNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para armazenar primeiro nome do perfil");
		exit(0);
	}
	if ((ultNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para armazenar ultimo nome do perfil");
		exit(0);
	}
	if ((cidade = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para armazenar ultimo nome do cidade");
		exit(0);
	}
    
    printf("===============================================================================\n");
    printf("Bem-vindo a rede social bl‡bl‡bl‡\n\n");
    
    printf("O que deseja fazer? \n\n");
    
    printf("1. Criar novo perfil \n");
    printf("2. Ir para perfil \n");
    printf("3. Ver nœmero de perfis cadastrados \n");
    printf("4. Excluir todos os perfis da rede \n\n");
    
    while (escolhaInvalida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n\n");
        
        // Menu 3
        if (menuEscolhido == 1){
            
            MENU_Menu3(pGrafo);
            escolhaInvalida = 1;
            
        // Menu 2
        } else if (menuEscolhido == 2) {
            
            while (escolhaPerfilInvalido == 0) {
				
                printf("Digite o email do perfil que deseja encontrar: ");
                scanf("%s", &emailPerfilProcurado);
                printf("\n\n");
				
				condRetObterEmail = PER_BuscaEmail(pGrafo, emailPerfilProcurado, &pPerfil, &id);
                
                if (condRetObterEmail == PER_CondRetEmailInexistente){
                    printf("Usuario procurado n‹o existe. Por favor procure novamente. \n\n");
				} else if (condRetObterEmail == PER_CondRetRedeVazia) {
					printf("A rede está vazia. Crie um usuário e tente novamente. \n\n");
				} else if (condRetObterEmail != PER_CondRetOK){
					printf("Retorno do m—dulo perfil inesperado. \n\n");
					exit(0);
				} else {
					condRetObterPerfil = PER_ObterPerfil(pPerfil, emailPerfil, primNome, ultNome,
                                                     &dia, &mes, &ano, cidade);
													 
					if (condRetObterPerfil == PER_CondRetFaltouMemoria){
						printf("Faltou mem—ria para executar a a‹o. \n\n");
						exit(0);
					} else if (condRetObterPerfil != PER_CondRetOK){
						printf("Retorno do m—dulo perfil inesperado. \n\n");
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
            
            MENU_Menu4(pGrafo);
            escolhaInvalida = 1;
            
        // Menu 5
        } else if (menuEscolhido == 4) {
            
            MENU_Menu5(pGrafo);
            escolhaInvalida = 1;
            
        } else {
            printf("Escolha inválida de menu. Por favor, digite o menu novamente.\n\n");
        }
        
    }
    
}/* Fim função: MENU - Menu 1 - Menu Inicial */

/***************************************************************************
 *  Função: MENU  &Menu 2 - Perfil do Usuario
 *
 *****/

// Ir para perfil - Perfil do Usuario
void MENU_Menu2(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc) {
	
	int amigos;
	int menuEscolhido;
	int escolhaValida = 0;
	int id2;
	int escolhaEmailValida = 0;
	
	AMI_tpCondRet verificaAmigos;
	PER_tpPerfil * pPerfil2;
	PER_tpCondRet obtemEmailPerfil2;
	char * email2;
	//char ** listaEmailPerfis;
	
	if ((email2 = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para armazenar email do perfil");
		exit(0);
	}
	
	verificaAmigos = AMI_VerificarNumAmigos(pGrafo, pPerfil, &amigos);
	if (verificaAmigos == AMI_NaoPossuiAmizades){
		amigos = 0;
	} else if (verificaAmigos != AMI_CondRetOK){
		printf("Erro inesperado no modulo amizade\n");
		exit(0);
	}
	
	printf("===============================================================================\n");
    printf("Bem-vindo ao perfil de %s\n\n",primNome);
	
	printf("Nome: %s %s\n",primNome,ultNome);
    printf("Email: %s\n",email);
	printf("Data de Nascimento: %d|%d|%d\n",diaNasc,mesNasc,anoNasc);
	printf("Cidade: %s\n",cidade);
	printf("Número de amigos: %d \n",amigos);
	
    printf("O que deseja fazer? \n\n");
    
    printf("1. Modificar dados \n");
    printf("2. Procurar novos amigos \n");
    printf("3. Ver amigos \n");
    printf("4. Ir para mensagens \n");
	printf("5. Excluir todas as amizades \n");
    printf("6. Excluir perfil \n");
    printf("7. Voltar para o menu \n\n");
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n\n");
	
		// Menu 6
		if (menuEscolhido == 1) {
			
			MENU_Menu6(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaValida = 1;
			
		// Menu 7
		} else if (menuEscolhido == 2){
			
			while (escolhaEmailValida == 0){
				
				printf("Digite o email do perfil que deseja encontrar: ");
				scanf("%s", &email2);
				printf("\n\n");
				
				obtemEmailPerfil2 = PER_BuscaEmail(pGrafo, email2, pPerfil2, id2);
				if (obtemEmailPerfil2 == PER_CondRetEmailInexistente){
					printf("O email procurado nao existe na rede. Por favor, procure outro email.\n\n");
				} else if (obtemEmailPerfil2 != PER_CondRetEmailJaCadastrado){
					printf("Erro inesperado no modulo perfil.\n");
					exit(0);
				} else {
					escolhaEmailValida = 1;
					MENU_Menu7(pGrafo, pPerfil, pPerfil2);
					escolhaValida = 1;
				}
			}
		
		// Menu 8
		} else if (menuEscolhido == 3){
			
			// Pegar todos os emails dos amigos do cara
			
			//MENU_Menu8(pGrafo, listaEmailPerfis);
			escolhaValida = 1;
		
		// Menu 9
		} else if (menuEscolhido == 4){
			
			MENU_Menu9(pPerfil);
			escolhaValida = 1;
		
		// Menu 10
		} else if (menuEscolhido == 5){
			
			//MENU_Menu10(pGrafo,pPerfil);
			escolhaValida = 1;
		
		// Menu 11
		} else if (menuEscolhido == 6){
		
			MENU_Menu11(pGrafo,email);
			escolhaValida = 1;
		
		// Menu 1
		} else if (menuEscolhido == 7){
			
			MENU_Menu1(pGrafo);
			escolhaValida = 1;
		
		} else {
			printf("Escolha inválida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
	
	
} /* Fim função: MENU - Menu 2 - Perfil do Usuario */

/***************************************************************************
 *  Função: MENU  &Menu 3 - Criar Novo Perfil
 *
 *****/

// Criar novo perfil - COMPLETO
void MENU_Menu3(GRA_tppGrafo pGrafo){
	
	char * primNome;
	char * ultNome;
	char * email;
	char * cidade;
	int dia;
	int mes;
	int ano;
	
	int dadosValidos = 0;
	
	int menuEscolhido;
	int menuValido = 0;
	
	PER_tpPerfil * pPerfil;
	PER_tpCondRet criarPerfil;
	
	if ((email = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para armazenar email do perfil");
		exit(0);
	}
	if ((primNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para armazenar primeiro nome do perfil");
		exit(0);
	}
	if ((ultNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para armazenar ultimo nome do perfil");
		exit(0);
	}
	if ((cidade = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para armazenar ultimo nome do cidade");
		exit(0);
	}
	
	printf("===============================================================================\n");
	
	while (dadosValidos == 0){
		printf("Digite as informações do novo perfil\n\n",primNome);
	
		printf("Primeiro Nome: ");
		scanf("%s", &primNome);
		printf("\n");
		printf("Ultimo Nome: ");
		scanf("%s", &ultNome);
		printf("\n");
		printf("Email: ");
		scanf("%s", &email);
		printf("\n");
		printf("Dia de Nascimento: ");
		scanf("%d", &dia);
		printf("\n");
		printf("Mes de Nascimento: ");
		scanf("%d", &mes);
		printf("\n");
		printf("Ano de Nascimento: ");
		scanf("%d", &ano);
		printf("\n");
		printf("Cidade: ");
		scanf("%s", &cidade);
		printf("\n");
	
		criarPerfil = PER_CriarPerfil(pGrafo, &pPerfil, email, primNome, ultNome, dia, mes, ano, cidade);
		if (criarPerfil == PER_CondRetEmailJaCadastrado){
			printf("Já existe um usuário cadastrado na rede com esse email. Por favor cria um com email diferente.\n\n");
		} else if (criarPerfil == PER_CondRetEmailInvalido || criarPerfil == PER_CondRetNomeInvalido || criarPerfil == PER_CondRetDataInvalida || criarPerfil == PER_CondRetCidadeInvalida){
			printf("Os dados inseridos não são válidos. Por favor tente registrar com dados diferentes.\n\n");
		} else if (criarPerfil != PER_CondRetOK){
			printf("Ocorreu um erro inesperado no modulo perfil.");
			exit(0);
		} else {
			dadosValidos = 1;
			printf("Perfil de %s foi criado!\n\n",primNome);
			
			while (menuValido == 0){
				printf("O que deseja fazer:\n\n",primNome);
				
				printf("1. Modificar dados \n");
				printf("2. Procurar novos amigos \n\n");
				
				printf("> ");
				scanf("%d", &menuEscolhido);
				printf("\n\n");
				
				// Menu 1
				if (menuEscolhido == 1){
					menuValido = 1;
					MENU_Menu1(pGrafo);
				
				// Menu 2
				} else if (menuEscolhido == 2){
					menuValido = 1;
					MENU_Menu2(pGrafo, pPerfil, email, primNome, ultNome, cidade, dia, mes, ano);
					
				} else {
					printf("Escolha inválida de menu. Por favor, digite o menu novamente.\n\n");
				}
			}	
		}
		
	}
	
} /* Fim função: MENU - Menu 3 - Criar Novo Perfil */

/***************************************************************************
 *  Função: MENU  &Menu 4 - Ver Número de Perfis na Rede
 *
 *****/

// Ver número de perfis cadastrado - COMPLETE
void MENU_Menu4(GRA_tppGrafo pGrafo){
	
	int perfisCadastrados;
	int menuEscolhido;
	int escolhaValida = 0;
	
	PER_tpCondRet numPerfis;
	
	numPerfis =  PER_NumeroPerfis(pGrafo, &perfisCadastrados);
	if (numPerfis != PER_CondRetOK){
		printf("Ocorreu um erro inesperado no módulo perfis.\n");
		exit(0);
	}
	
	printf("===============================================================================\n");
	printf("Há %d perfis cadastrados na rede.\n\n",perfisCadastrados);
	
	printf("1. Voltar para o menu\n\n");
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n");
	
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_Menu1(pGrafo);
			
		} else {
			printf("Escolha inválida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
	
} /* Fim função: MENU - Menu 4 - Ver Número de Perfis na Rede */

/***************************************************************************
 *  Função: MENU  &Menu 5 - Excluir todos os perfis da rede
 *
 *****/
 
// Excluir todos os perfis da rede - COMPLETE
void MENU_Menu5(GRA_tppGrafo pGrafo){
	
	int menuEscolhido;
	int escolhaValida = 0;
	
	PER_tpCondRet excluirPerfis;
	
	excluirPerfis = PER_ExcluirTodosPerfis(pGrafo);
	if (excluirPerfis != PER_CondRetOK){
		printf("Ocorreu um erro inesperado no módulo perfis.\n");
		exit(0);
	}
	
	printf("===============================================================================\n");
	printf("Todos os perfis foram excluídos.\n\n");
	
	printf("1. Voltar para o menu\n\n");
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n");
	
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_Menu1(pGrafo);
			
		} else {
			printf("Escolha inválida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
} /* Fim função: MENU - Menu 5 - Excluir todos os perfis da rede */

/***************************************************************************
 *  Função: MENU  &Menu 6 - Modificar dados do perfil
 *
 *****/

// Modificar dados - COMPLETE
void MENU_Menu6(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc){
	
	int escolhaInvalida = 0;
	int menuEscolhido;
	
	printf("===============================================================================\n");
    printf("Bem-vindo ao perfil de %s\n\n",primNome);
	
	printf("Nome: %s %s\n",primNome,ultNome);
    printf("Email: %s\n",primNome,email);
	printf("Data de Nascimento: %d|%d|%d\n",primNome,diaNasc,mesNasc,anoNasc);
	printf("Cidade: %s\n",cidade);
	
    printf("O que deseja fazer? \n\n");
    
    printf("1. Modificar email \n");
    printf("2. Modificar nome \n");
    printf("3. Modificar data de nascimento  \n");
    printf("4. Modificar cidade \n");
	printf("5. Voltar para o perfil de %s \n", primNome);
    printf("6. Voltar para o menu \n");
	
	while (escolhaInvalida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n\n");
				
		// Menu 12
		if (menuEscolhido == 1) {
			
			MENU_Menu12(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
			
		// Menu 13
		} else if (menuEscolhido == 2){
			
			MENU_Menu13(pGrafo, pPerfil, primNome, email, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
		
		// Menu 14
		} else if (menuEscolhido == 3){
			
			MENU_Menu14(pGrafo, pPerfil, primNome, email, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
		
		// Menu 15
		} else if (menuEscolhido == 4){
			
			MENU_Menu15(pGrafo, pPerfil, primNome, email, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
		
		// Menu 2
		} else if (menuEscolhido == 5){
			
			MENU_Menu2(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
		
		// Menu 1
		} else if (menuEscolhido == 6){
		
			MENU_Menu1(pGrafo);
			escolhaInvalida = 1;
		
		} else {
			printf("Escolha inválida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
	
} /* Fim função: MENU - Menu 6 - Modificar dados do perfil */

/***************************************************************************
 *  Função: MENU  &Menu 7 - Procurar Novos Amigos
 *
 *****/
// Procurar novos amigos
void MENU_Menu7(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, PER_tpPerfil * pPerfil2){
	
	char * emailPerfil;
    char * primNome;
    char * ultNome;
    char * cidade;
    int dia;
    int mes;
    int ano;
	
	PER_tpCondRet condRetObterPerfil;
	
	if ((emailPerfil = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para armazenar email do perfil");
		exit(0);
	}
	if ((primNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para armazenar primeiro nome do perfil");
		exit(0);
	}
	if ((ultNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para armazenar ultimo nome do perfil");
		exit(0);
	}
	if ((cidade = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para armazenar ultimo nome do cidade");
		exit(0);
	}
	
	condRetObterPerfil = PER_ObterPerfil(pPerfil2, emailPerfil, primNome, ultNome, dia, mes, ano, cidade);
	if (condRetObterPerfil != PER_CondRetOK){
		printf("Erro inesperado no modulo perfil.");
		exit(0);
	}
							  
	
	
	printf("===============================================================================\n");
    printf("Bem-vindo ao perfil de %s\n\n",primNome);
	
	printf("Nome: %s %s\n",primNome,ultNome);
    printf("Email: %s\n",email);
	printf("Data de Nascimento: %d|%d|%d\n",diaNasc,mesNasc,anoNasc);
	printf("Cidade: %s\n",cidade);
	printf("Número de amigos: %d \n",amigos);
	
    printf("O que deseja fazer? \n\n");
    
    printf("1. Modificar dados \n");
    printf("2. Procurar novos amigos \n");
    printf("3. Ver amigos \n");
    printf("4. Ir para mensagens \n");
	printf("5. Excluir todas as amizades \n");
    printf("6. Excluir perfil \n");
    printf("7. Voltar para o menu \n\n");
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
	}
	
} /* Fim função: MENU - Menu 7 - Procurar Novos Amigos */

// Ver amigos
void MENU_Menu8(GRA_tppGrafo pGrafo, char ** listaEmails);

// Ir para mensagens
void MENU_Menu9(PER_tpPerfil * pPerfil) {
	int escolhaInvalida = 0;
	int escolha, qtd, i, j = 0, num;
	MEN_tpCondRet retorno;
	MEN_tpCondMsg *vetTipos;
	char **vetEmails, **vetMensagens;

	/*Exibir todas  as mensagens*/
	retorno = MEN_ObterNumTodasMensagens(pPerfil, &qtd);
	if (retorno != MEN_CondRetOK) {
		perror("Obter Todas Mensagens");
		exit(EXIT_FAILURE);
	}
	if ((vetTipos = (MEN_tpCondMsg *)malloc(sizeof(MEN_tpCondMsg)*qtd)) == NULL) {
		perror("Malloc");
		exit(EXIT_FAILURE);
	}
	if ((vetEmails = (char **)malloc(sizeof(char)*qtd)) == NULL) {
		perror("Malloc");
		exit(EXIT_FAILURE);
	}
	if ((vetMensagens = (char **)malloc(sizeof(char)*qtd)) == NULL) {
		perror("Malloc");
		exit(EXIT_FAILURE);
	}
	retorno = MEN_ObterTodasMensagens(pPerfil, vetTipos, vetEmails, vetMensagens);
	if (retorno != MEN_CondRetOK) {
		perror("Obter Todas Mensagens");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < qtd; i++) {
		printf("Mensagem %d:\n", i);
		while (vetMensagens[i][j] != '\0') {
			printf("%c", vetMensagens[i][j]);
			j++;
		}
		printf("\n");
	}
	/*Fim exibir todas  as mensagens*/
	printf("===============================================================================\n");
	printf("O que deseja fazer com suas mensagens?\n\n");

	printf("1. Excluir mensagem \n");
	printf("2. Obter total de mensagens\n");
	printf("3. Obter total de mensagens enviadas\n");
	printf("4. Obter total de mensagens recebidas\n");

	while (escolhaInvalida == 0) {

		printf("> ");
		scanf("%d", &escolha);
		printf("\n\n");

		switch (escolha)
		{
			/*Excluir mensagem*/
		case 1:
			escolhaInvalida = 1;
			printf("Escreva o numero da mensagem que deseja excluir:");
			scanf("%d", &num);
			while (num < 0 || num > qtd) {
				printf("Numero invalido, digite novamente:");
				scanf("%d", &num);
			}
			retorno = MEN_ExcluirMensagem(pPerfil, vetEmails[i], vetTipos[i], vetMensagens[i]);
			if (retorno != MEN_CondRetOK) {
				perror("Excluir mensagem");
				exit(EXIT_FAILURE);
			}
			printf("\nMensagem excluida\n");
			break; /*Fim excluir mensagem*/

				   /*Obter total de mensagens*/
		case 2:
			escolhaInvalida = 1;
			printf("Total de mensagens = %d\n", qtd);
			break;/*Fim obter total de mensagens*/

				  /*Obter total de mensagens enviadas*/
		case 3:
			escolhaInvalida = 1;
			retorno = MEN_ObterNumMensagens(pPerfil, MEN_CondMsgEnviada, &qtd);
			if (retorno != MEN_CondRetOK) {
				perror("Excluir mensagem");
				exit(EXIT_FAILURE);
			}
			printf("Total de mensagens = %d\n", qtd);
			break;/*Fim obter total de mensagens enviadas*/

				  /*Obter total de mensagens recebidas*/
		case 4:
			escolhaInvalida = 1;
			retorno = MEN_ObterNumMensagens(pPerfil, MEN_CondMsgRecebida, &qtd);
			if (retorno != MEN_CondRetOK) {
				perror("Excluir mensagem");
				exit(EXIT_FAILURE);
			}
			printf("Total de mensagens = %d\n", qtd);
			break;/*Fim obter total de mensagens recebidas*/
		default:
			printf("Escolha inválida. Por favor, digite o menu novamente.\n\n");
			break;
		}

	}
}

/***************************************************************************
 *  Função: MENU  &Menu 10 - Excluir Todas as Amizades
 *
 *****/
 
// Excluir todas as amizades
void MENU_Menu10(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil){
	
	
	
} /* Fim função: MENU - Menu 10 - Excluir Todas as Amizades */

/***************************************************************************
 *  Função: MENU  &Menu 11 - Excluir Perfil
 *
 *****/

// Excluir perfil - COMPLETE
void MENU_Menu11(GRA_tppGrafo pGrafo, char * email){
	
	PER_tpCondRet excluirPerfil;
	
	int menuEscolhido;
	int escolhaValida = 0;
	
	excluirPerfil = PER_ExcluirPerfil(pGrafo, email);
	if (excluirPerfil =! PER_CondRetOK){
		printf("Erro inesperado no modulo perfil");
		exit(0);
	}
	
	printf("===============================================================================\n");
    printf("O perfil foi excluído.\n\n");
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_Menu1(pGrafo);
			
		} else {
			printf("Escolha inválida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
	
	
} /* Fim função: MENU - Menu 11 - Excluir Perfil */

/***************************************************************************
 *  Função: MENU  &Menu 12 - Modificar email do perfil
 *
 *****/
 
// Modificar email - COMPLETE
void MENU_Menu12(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc){
	
	char * emailNovo;
	int avaliaEmail = 0;
	int menuEscolhido;
	int escolhaValida = 0;
	
	PER_tpCondRet modEmail;
	
	if ((emailNovo = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para modificar email do perfil procurado");
		exit(0);
	}
	
	printf("===============================================================================\n");
    printf("Email de %s: %s %s\n\n",primNome,email);
	
	while (avaliaEmail == 0){
		
		printf("Digite o novo email de %s: ",primNome);
		scanf("%s", &emailNovo);
		printf("\n\n");
		
		modEmail = PER_ModificaEmail(pGrafo, email, emailNovo);
		if (modEmail == PER_CondRetEmailInvalido){
			printf("O email digitado possui um formato inválido. Por favor reescreva o email.\n\n");
		} else if (modEmail == PER_CondRetEmailJaCadastrado){
			printf("Já existe um usuário com o email digitado.\n\n");
		} else if (modEmail != PER_CondRetOK){
			printf("Ocorreu um erro inesperado no modulo perfil\n\n");
			exit(0);
		} else {
			printf("Email modificado com sucesso. \n\n");
			avaliaEmail = 1;
		}
	}
	
	printf("O que deseja fazer? \n\n");
    
    printf("1. Voltar para modificar dados \n");
    printf("2. Voltar para o perfil de %s \n",primNome);
    printf("3. Voltar para o menu \n");
    
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_Menu6(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 2){
			escolhaValida = 1;
			MENU_Menu2(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 3){
			escolhaValida = 1;
			MENU_Menu1(pGrafo);
			
		} else {
			printf("Escolha inválida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}

} /* Fim função: MENU - Menu 12 - Modificar email do perfil */

/***************************************************************************
 *  Função: MENU  &Menu 13 - Modificar nome do perfil
 *
 *****/
 
// Modificar nome - COMPLETE
void MENU_Menu13(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc){
	
	char * primNomeNovo;
	char * ultNomeNovo;
	int avaliaNome = 0;
	int menuEscolhido;
	int escolhaValida = 0;
	
	PER_tpCondRet modNome;
	
	if ((primNomeNovo = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para modificar nome do perfil procurado");
		exit(0);
	}
	if ((ultNomeNovo = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para modificar nome do perfil procurado");
		exit(0);
	}
	
	printf("===============================================================================\n");
    printf("nome de %s: %s %s\n\n",primNome,ultNome);
	
	while (avaliaNome == 0){
		
		printf("Digite o novo primeiro nome de %s: ",primNome);
		scanf("%s", &primNomeNovo);
		printf("\n\n");
		
		printf("Digite o novo ultimo nome de %s: ",primNome);
		scanf("%s", &ultNomeNovo);
		printf("\n\n");
		
		modNome = PER_ModificaNome(pGrafo, email, primNomeNovo,ultNomeNovo);
		if (modNome == PER_CondRetNomeInvalido){
			printf("O nome digitado possui um formato inválido. Por favor reescreva o nome.\n\n");
		} else if (modNome != PER_CondRetOK){
			printf("Ocorreu um erro inesperado no modulo perfil\n\n");
			exit(0);
		} else {
			printf("Nome modificado com sucesso. \n\n");
			avaliaNome = 1;
		}
	}
	
	printf("O que deseja fazer? \n\n");
    
    printf("1. Voltar para modificar dados \n");
    printf("2. Voltar para o perfil de %s \n",primNome);
    printf("3. Voltar para o menu \n");
    
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_Menu6(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 2){
			escolhaValida = 1;
			MENU_Menu2(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 3){
			escolhaValida = 1;
			MENU_Menu1(pGrafo);
			
		} else {
			printf("Escolha inválida de menu. Por favor, digite o menu novamente.\n\n");
		}	
	}
} /* Fim função: MENU - Menu 13 - Modificar nome do perfil */

/***************************************************************************
 *  Função: MENU  &Menu 14 - Modificar data de nascimento do perfil
 *
 *****/

// Modificar data de nascimento - COMPLETE
void MENU_Menu14(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc){
	
	int diaNovo;
	int mesNovo;
	int anoNovo;
	int avaliaData = 0;
	int menuEscolhido;
	int escolhaValida = 0;
	
	PER_tpCondRet modData;
	
	
	printf("===============================================================================\n");
    printf("Dia de nascimento de %s: %d|%d|%d\n\n",primNome,diaNasc,mesNasc,anoNasc);
	
	while (avaliaData == 0){
		
		printf("Digite o novo dia de nascimento de %s: ",primNome);
		scanf("%d", &diaNovo);
		printf("\n\n");
		
		printf("Digite o novo mes de nascimento de %s: ",primNome);
		scanf("%d", &mesNovo);
		printf("\n\n");
		
		printf("Digite o novo ano de nascimento de %s: ",primNome);
		scanf("%d", &anoNovo);
		printf("\n\n");
		
		modData = PER_ModificaDataNasc(pGrafo, email, diaNovo, mesNovo, anoNovo);
		if (modData == PER_CondRetDataInvalida){
			printf("A data digitada possui um formato inválido. Por favor reescreva a data.\n\n");
		} else if (modData != PER_CondRetOK){
			printf("Ocorreu um erro inesperado no modulo perfil\n\n");
			exit(0);
		} else {
			printf("Dia de nascimento modificado com sucesso. \n\n");
			avaliaData = 1;
		}
	}
	
	printf("O que deseja fazer? \n\n");
    
    printf("1. Voltar para modificar dados \n");
    printf("2. Voltar para o perfil de %s \n",primNome);
    printf("3. Voltar para o menu \n");
    
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_Menu6(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 2){
			escolhaValida = 1;
			MENU_Menu2(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 3){
			escolhaValida = 1;
			MENU_Menu1(pGrafo);
			
		} else {
			printf("Escolha inválida de menu. Por favor, digite o menu novamente.\n\n");
		}	
	}
	
} /* Fim função: MENU - Menu 14 - Modificar data de nascimento do perfil */

/***************************************************************************
 *  Função: MENU  &Menu 15 - Modificar cidade do perfil
 *
 *****/
 
// Modificar cidade - COMPLETE
void MENU_Menu15(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc){
	
	char * cidadeNovo;
	int avaliaCidade = 0;
	int menuEscolhido;
	int escolhaValida = 0;
	
	PER_tpCondRet modCidade;
	
	if ((cidadeNovo = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Não há espaço para modificar cidade do perfil procurado");
		exit(0);
	}
	
	printf("===============================================================================\n");
    printf("Cidade de %s: %s %s\n\n",primNome,cidade);
	
	while (avaliaCidade == 0){
		
		printf("Digite a nova cidade de %s: ",primNome);
		scanf("%s", &cidadeNovo);
		printf("\n\n");
		
		modCidade = PER_ModificaCidade(pGrafo, email, cidadeNovo);
		if (modCidade == PER_CondRetCidadeInvalida){
			printf("A cidade digitado possui um formato inválido. Por favor reescreva o email.\n\n");
		} else if (modCidade != PER_CondRetOK){
			printf("Ocorreu um erro inesperado no modulo perfil\n\n");
			exit(0);
		} else {
			printf("Cidade modificada com sucesso. \n\n");
			avaliaCidade = 1;
		}
	}
	
	printf("O que deseja fazer? \n\n");
    
    printf("1. Voltar para modificar dados \n");
    printf("2. Voltar para o perfil de %s \n",primNome);
    printf("3. Voltar para o menu \n");
    
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_Menu6(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 2){
			escolhaValida = 1;
			MENU_Menu2(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 3){
			escolhaValida = 1;
			MENU_Menu1(pGrafo);
			
		} else {
			printf("Escolha inválida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
	
} /* Fim função: MENU - Menu 15 - Modificar cidade do perfil */

// Criar amizade
void MENU_Menu16(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, PER_tpPerfil * pPerfil2);

// Excluir amizade
void MENU_Menu17(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, PER_tpPerfil * pPerfil2);

/***************************************************************************
 *  Função: MENU  &Destriur Valor
 *
 *****/
 
   void DestruirValor( void * pValor )
   {
      free( pValor ) ;
   } /* Fim função: TAMI -Destruir valor */

 // =================== TUDO AQUI EMBAIXO NAO ƒ MENU ========================


 
 
