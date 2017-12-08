#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
/***************************************************************************
*  $MCI MÛdulo de implementaÁ„o: MENU  Modulo Menu
*
*  Arquivo gerado:              MENU.c
*  Letras identificadoras:      MENU
*
*  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 AutomatizaÁ„o dos testes de mÛdulos C
*  Gestor:  DI/PUC-Rio
*  Autores: Michelle Santiago (ms), Renan Moreira (rm)
*
*  $HA HistÛrico de evoluÁ„o:
*     Vers„o    Autor   	 Data     	ObservaÁıes
*       1        ms        20/11/2017 	inicio desenvolvimento
*       2        rm        02/12/2017   funcoes: MENU_MenuVerAmigos, MENU_MenuIrMensagens
*       3        rm        05/12/2017   funcao: MENU_MenuExcluirTodasAmizades
*       4        ms        06/12/2017   modificaçcao nas funçcoes do modulo
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

void MENU_MenuInicial(GRA_tppGrafo pGrafo);
void MENU_MenuIrPerfil(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);
void MENU_MenuCriarPerfil(GRA_tppGrafo pGrafo);
void MENU_MenuNumPerfis(GRA_tppGrafo pGrafo);
void MENU_MenuExcluirTodosPerfis(GRA_tppGrafo pGrafo);
void MENU_MenuModificarDados(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);
void MENU_MenuProcurarNovosAmigos(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, PER_tpPerfil * pPerfil2);
void MENU_MenuVerAmigos(GRA_tppGrafo pGrafo, PER_tpPerfil *pPerfil);
void MENU_MenuIrMensagens(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil);
void MENU_MenuExcluirTodasAmizades(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil);
void MENU_MenuExcluirPerfil(GRA_tppGrafo pGrafo, char * email);
void MENU_MenuModificarEmail(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);
void MENU_MenuModificarNome(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);
void MENU_MenuModificarData(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);
void MENU_MenuModificarCidade(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc);
void MENU_MenuCriarAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, PER_tpPerfil * pPerfil2);
void MENU_MenuExcluirAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, PER_tpPerfil * pPerfil2);



int main () {
	GRA_tppGrafo Grafo;
    
	GRA_CriarGrafo(NULL, &Grafo);
	
    MENU_MenuInicial(Grafo);
    
    return 0;
}


/*****  CÛdigo das funÁıes exportadas pelo mÛdulo  *****/

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 1 - Menu inicial
 *
 *****/

void MENU_MenuInicial(GRA_tppGrafo pGrafo) {
    
    int escolhaInvalida = 0;
    int escolhaPerfilInvalido = 0, tentarNovamente;
	char menuEscolhido;
	char primNome[51], ultNome[51], emailPerfil[101], emailPerfilProcurado[101], cidade[51] = "Rio";
	int dia = 25, mes = 01, ano = 1998;
	int id;
	PER_tpPerfil * pPerfil;
	PER_tpCondRet condRetObterPerfil, retornoPer;
	PER_tpCondRet condRetObterEmail;
	GRA_tpCondRet retornoGra;
    
    printf("===============================================================================\n");
    printf("Bem-vindo a rede social\n\n");
    
	printf("O que deseja fazer? \n\n");

	printf("1. Criar novo perfil \n");
	printf("2. Ir para perfil \n");
	printf("3. Ver numero de perfis cadastrados \n");
	printf("4. Excluir todos os perfis da rede \n");
	printf("5. Destruir rede social\n\n");

	while (escolhaInvalida == 0) {

			printf("> ");
			scanf(" %c", &menuEscolhido);
			printf("\n\n");

			// Menu 3
			if (menuEscolhido == '1') {

				MENU_MenuCriarPerfil(pGrafo);
				escolhaInvalida = 1;

				// Menu 2
			}
			else if (menuEscolhido == '2') {

				while (escolhaPerfilInvalido == 0) {

					printf("Digite o email do perfil que deseja encontrar: ");
					scanf("%s", &emailPerfilProcurado);
					printf("\n\n");
					condRetObterEmail = PER_BuscaEmail(pGrafo, emailPerfilProcurado, &pPerfil, &id);
					if (condRetObterEmail == PER_CondRetEmailInexistente) {
						printf("Usuario procurado nao existe. Por favor procure novamente. \n\n");
						printf("Deseja tentar de novo? (0 = nao, 1 = sim)\n\n>");
						scanf("%d", &tentarNovamente);
						if (tentarNovamente != 1) {
							printf("Retornando ao menu\n");
							MENU_MenuInicial(pGrafo);
						}
					}
					else if (condRetObterEmail == PER_CondRetRedeVazia) {
						printf("A rede esta vazia. Crie um usuario e tente novamente. \n\n");
						printf("Retornando ao menu\n");
						MENU_MenuInicial(pGrafo);
					}
					else if (condRetObterEmail != PER_CondRetEmailJaCadastrado) {
						printf("Retorno do modulo perfil inesperado. \n\n");
						exit(0);
					}
					else {
						condRetObterPerfil = PER_ObterPerfil(pPerfil, emailPerfil, primNome, ultNome,
							&dia, &mes, &ano, cidade);

						if (condRetObterPerfil != PER_CondRetOK) {
							printf("Retorno do modulo perfil inesperado. \n\n");
							exit(0);
						}
						else {
							escolhaPerfilInvalido = 1;
							escolhaInvalida = 1;

							MENU_MenuIrPerfil(pGrafo, pPerfil, emailPerfilProcurado, primNome, ultNome, cidade, dia, mes, ano);
						}
					}
				}

				// Menu 4
			}
			else if (menuEscolhido == '3') {

				MENU_MenuNumPerfis(pGrafo);
				escolhaInvalida = 1;

				// Menu 5
			}
			else if (menuEscolhido == '4') {

				MENU_MenuExcluirTodosPerfis(pGrafo);
				escolhaInvalida = 1;

			}
			else if (menuEscolhido == '5') {
				escolhaInvalida = 1;

				retornoPer = PER_ExcluirTodosPerfis(pGrafo);
				if (retornoPer != PER_CondRetOK) {
					printf("Ocorreu um erro inesperado no mÛdulo perfis.\n");
					exit(0);
				}

				retornoGra = GRA_DestruirGrafo(pGrafo);
				if (retornoGra != GRA_CondRetOK) {
					printf("Erro inesperado ao destruir Grafo\n");
					exit(1);
				}

				printf("\nRede social destruida\n");
				exit(0);
			}
			else {
				printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
			}

		}

}/* Fim funÁ„o: MENU - Menu 1 - Menu Inicial */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 2 - Perfil do Usuario
 *
 *****/

void MENU_MenuIrPerfil(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc) {
	
	int amigos;
	int escolhaValida = 0, tentarNovamente;
	int id2;
	int escolhaEmailValida = 0;
	
	AMI_tpCondRet verificaAmigos;
	PER_tpPerfil * pPerfil2;
	PER_tpCondRet obtemEmailPerfil2;
	char email2[101], menuEscolhido;

	//char ** listaEmailPerfis;
	
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
	printf("Numero de amigos: %d \n",amigos);
	
    printf("O que deseja fazer? \n\n");
    
    printf("1. Modificar dados \n");
    printf("2. Procurar novos amigos \n");
    printf("3. Ver amigos \n");
    printf("4. Ir para mensagens \n");
	printf("5. Excluir uma amizade \n");
	printf("6. Excluir todas as amizades \n");
    printf("7. Excluir perfil \n");
    printf("8. Voltar para o menu \n\n");

	while (escolhaValida == 0){
		
		printf("> ");
		scanf(" %c", &menuEscolhido);
		printf("\n\n");
	
		// Menu 6
		if (menuEscolhido == '1') {
			
			MENU_MenuModificarDados(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaValida = 1;
			
		// Menu 7
		} else if (menuEscolhido == '2'){
			while (escolhaEmailValida == 0){
				printf("Digite o email do perfil que deseja encontrar: ");
				scanf("%s", &email2);
				printf("\n\n");
				
				obtemEmailPerfil2 = PER_BuscaEmail(pGrafo, email2, &pPerfil2, &id2);
				if (obtemEmailPerfil2 == PER_CondRetEmailInexistente){
					printf("O email procurado nao existe na rede. Por favor, procure outro email.\n\n");
					printf("Deseja tentar de novo? (0 = nao, 1 = sim)\n\n>");
					scanf("%d", &tentarNovamente);
					if (tentarNovamente != 1) {
						printf("Retornando ao perfil\n");
						MENU_MenuIrPerfil(pGrafo,  pPerfil, email,  primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
					}
				} else if (obtemEmailPerfil2 != PER_CondRetEmailJaCadastrado){
					printf("Erro inesperado no modulo perfil.\n");
					exit(0);
				} else {
					escolhaEmailValida = 1;
					MENU_MenuProcurarNovosAmigos(pGrafo, pPerfil, pPerfil2);
					escolhaValida = 1;
				}
			}
		
		// Menu 8
		} else if (menuEscolhido == '3'){
			
			// Pegar todos os emails dos amigos do usuario
			MENU_MenuVerAmigos(pGrafo, pPerfil);
			escolhaValida = 1;
		
		// Menu 9
		} else if (menuEscolhido == '4'){
			
			MENU_MenuIrMensagens(pGrafo, pPerfil);
			escolhaValida = 1;
		
		// Menu 10
		}
		else if (menuEscolhido == '5') {
			
			while (escolhaEmailValida == 0) {
				printf("Digite o email do amigo  que voce quer excluir\n");
				scanf("%s", &email2);
				printf("\n\n");

				obtemEmailPerfil2 = PER_BuscaEmail(pGrafo, email2, &pPerfil2, &id2);
				if (obtemEmailPerfil2 == PER_CondRetEmailInexistente) {
					printf("O email procurado nao existe na rede. Por favor, procure outro email.\n\n");
					printf("Deseja tentar de novo? (0 = nao, 1 = sim)\n\n>");
					scanf("%d", &tentarNovamente);
					if (tentarNovamente != 1) {
						printf("Retornando ao perfil\n");
						MENU_MenuIrPerfil(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
					}
				}
				else if (obtemEmailPerfil2 != PER_CondRetEmailJaCadastrado) {
					printf("Erro inesperado no modulo perfil.\n");
					exit(0);
				}
				else {
					escolhaEmailValida = 1;
					MENU_MenuExcluirAmizade(pGrafo, pPerfil, pPerfil2);
					escolhaValida = 1;
				}
			}
			 
		}
		else if (menuEscolhido == '6') {
			
			MENU_MenuExcluirTodasAmizades(pGrafo, pPerfil);
			escolhaValida = 1;
		
		// Menu 11
		} else if (menuEscolhido == '7'){
		
			MENU_MenuExcluirPerfil(pGrafo,email);
			escolhaValida = 1;
		
		// Menu 1
		} else if (menuEscolhido == '8'){
			
			MENU_MenuInicial(pGrafo);
			escolhaValida = 1;
		
		} else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
	
	
} /* Fim funÁ„o: MENU - Menu 2 - Perfil do Usuario */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 3 - Criar Novo Perfil
 *
 *****/

void MENU_MenuCriarPerfil(GRA_tppGrafo pGrafo){
	
	char primNome[51], ultNome[51], email[101], cidade[51], email2[101];
	int dia, mes, ano, i, tentarNovamente;

	int dadosValidos = 0, escolhaEmailValida = 0;
	
	char menuEscolhido;
	int menuValido = 0;
	
	PER_tpPerfil * pPerfil, *pPerfil2;
	PER_tpCondRet criarPerfil, obtemEmailPerfil2;
	printf("===============================================================================\n");
	
	while (dadosValidos == 0){
		printf("Digite as informaÁıes do novo perfil\n\n",primNome);
	
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
		i = 0;
		scanf(" %c", &cidade[i]);
		while (cidade[i] != '\n' && i < 50) {
			i++;
			scanf("%c", &cidade[i]);
		}
		cidade[i] = '\0';

		printf("\n");
	
		criarPerfil = PER_CriarPerfil(pGrafo, &pPerfil, email, primNome, ultNome, dia, mes, ano, cidade);
		if (criarPerfil == PER_CondRetEmailJaCadastrado){
			printf("Ja existe um usuario cadastrado na rede com esse email. Por favor cria um com email diferente.\n\n");
		} else if (criarPerfil == PER_CondRetEmailInvalido || criarPerfil == PER_CondRetNomeInvalido || criarPerfil == PER_CondRetDataInvalida || criarPerfil == PER_CondRetCidadeInvalida){
			printf("Os dados inseridos nao sao validos. Por favor tente registrar com dados diferentes.\n\n");
		} else if (criarPerfil != PER_CondRetOK){
			printf("Ocorreu um erro inesperado no modulo perfil.");
			exit(0);
		} else {
			dadosValidos = 1;
			printf("Perfil de %s foi criado!\n\n",primNome);
			
			while (menuValido == 0){
				printf("O que deseja fazer:\n\n",primNome);
				
				printf("1. Modificar dados \n");
				printf("2. Procurar novos amigos \n");
				printf("3. Voltar ao menu \n\n");
				printf("> ");
				scanf(" %c", &menuEscolhido);
				printf("\n\n");
				
				// Menu 1
				if (menuEscolhido == '1'){
					menuValido = 1;
					MENU_MenuModificarDados(pGrafo, pPerfil, email, primNome, ultNome, cidade, dia, mes, ano);
				
				// Menu 2
				} else if (menuEscolhido == '2'){
					while (escolhaEmailValida == 0) {
						printf("Digite o email do perfil que deseja encontrar: ");
						scanf("%s", &email2);
						printf("\n\n");

						obtemEmailPerfil2 = PER_BuscaEmail(pGrafo, email2, &pPerfil2, &i);
						if (obtemEmailPerfil2 == PER_CondRetEmailInexistente) {
							printf("O email procurado nao existe na rede. Por favor, procure outro email.\n\n");
							printf("Deseja tentar de novo? (0 = nao, 1 = sim)\n\n>");
							scanf("%d", &tentarNovamente);
							if (tentarNovamente != 1) {
								printf("Retornando ao menu\n");
								MENU_MenuInicial(pGrafo);
							}
						}
						else if (obtemEmailPerfil2 != PER_CondRetEmailJaCadastrado) {
							printf("Erro inesperado no modulo perfil.\n");
							exit(0);
						}
						else {
							escolhaEmailValida = 1;
							MENU_MenuProcurarNovosAmigos(pGrafo, pPerfil, pPerfil2);
							menuValido = 1;
						}
					}
					
				} 
				else if (menuEscolhido == '3') {
					menuValido = 1;
					printf("Retornando ao menu\n\n");
					MENU_MenuInicial(pGrafo);
				}
				else {
					printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
				}
			}	
		}
		
	}
	
} /* Fim funÁ„o: MENU - Menu 3 - Criar Novo Perfil */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 4 - Ver N˙mero de Perfis na Rede
 *
 *****/

void MENU_MenuNumPerfis(GRA_tppGrafo pGrafo){
	
	int perfisCadastrados;
	
	PER_tpCondRet numPerfis;
	
	numPerfis =  PER_NumeroPerfis(pGrafo, &perfisCadastrados);
	if (numPerfis != PER_CondRetOK){
		printf("Ocorreu um erro inesperado no modulo perfis.\n");
		exit(0);
	}
	
	printf("===============================================================================\n");
	printf("Ha %d perfis cadastrados na rede.\n\n", perfisCadastrados);
	
	MENU_MenuInicial(pGrafo);
	
} /* Fim funÁ„o: MENU - Menu 4 - Ver N˙mero de Perfis na Rede */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 5 - Excluir todos os perfis da rede
 *
 *****/
 
void MENU_MenuExcluirTodosPerfis(GRA_tppGrafo pGrafo){
	
	PER_tpCondRet excluirPerfis;
	
	excluirPerfis = PER_ExcluirTodosPerfis(pGrafo);
	if (excluirPerfis != PER_CondRetOK){
		printf("Ocorreu um erro inesperado no mÛdulo perfis.\n");
		exit(0);
	}
	
	printf("===============================================================================\n");
	printf("Todos os perfis foram excluÌdos.\n\n");
	
	printf("Voltando para o menu\n\n");
	
	MENU_MenuInicial(pGrafo);
} /* Fim funÁ„o: MENU - Menu 5 - Excluir todos os perfis da rede */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 6 - Modificar dados do perfil
 *
 *****/

void MENU_MenuModificarDados(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc){
	
	int escolhaInvalida = 0;
	char menuEscolhido;
	
	printf("===============================================================================\n");
    printf("Bem-vindo ao perfil de %s\n\n",primNome);
	
	printf("Nome: %s %s\n",primNome,ultNome);
    printf("Email: %s\n", email);
	printf("Data de Nascimento: %d|%d|%d\n", diaNasc,mesNasc,anoNasc);
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
		scanf(" %c", &menuEscolhido);
		printf("\n\n");
				
		// Menu 12
		if (menuEscolhido == '1') {
			
			MENU_MenuModificarEmail(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
			
		// Menu 13
		} else if (menuEscolhido == '2'){
			MENU_MenuModificarNome(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
		
		// Menu 14
		} else if (menuEscolhido == '3'){
			
			MENU_MenuModificarData(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
		
		// Menu 15
		} else if (menuEscolhido == '4'){
			
			MENU_MenuModificarCidade(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
		
		// Menu 2
		} else if (menuEscolhido == '5'){
			
			MENU_MenuIrPerfil(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
		
		// Menu 1
		} else if (menuEscolhido == '6'){
		
			MENU_MenuInicial(pGrafo);
			escolhaInvalida = 1;
		
		} else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
	
} /* Fim funÁ„o: MENU - Menu 6 - Modificar dados do perfil */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 7 - Procurar Novos Amigos
 *
 *****/

void MENU_MenuProcurarNovosAmigos(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil1, PER_tpPerfil * pPerfil2){
	
	int amigos, verificaAmigos, escolhaValida = 0;
	char menuEscolhido;

	char emailPerfil[101];
    char primNome[51];
    char ultNome[51];
    char cidade[51];
    int dia;
    int mes;
    int ano;
	
	char emailPerfil1[101];
    char primNome1[51];
    char ultNome1[51];
    char cidade1[51];
    int dia1;
    int mes1;
    int ano1;
	
	PER_tpCondRet condRetObterPerfil;
	PER_tpCondRet condRetObterPerfil1;
	
	
	condRetObterPerfil = PER_ObterPerfil(pPerfil2, emailPerfil, primNome, ultNome, &dia, &mes, &ano, cidade);
	if (condRetObterPerfil != PER_CondRetOK){
		printf("Erro inesperado no modulo perfil.");
		exit(0);
	}
	
	condRetObterPerfil1 = PER_ObterPerfil(pPerfil1, emailPerfil1, primNome1, ultNome1, &dia1, &mes1, &ano1, cidade1);
	if (condRetObterPerfil1 != PER_CondRetOK){
		printf("Erro inesperado no modulo perfil.");
		exit(0);
	}
	
	verificaAmigos = AMI_VerificarNumAmigos(pGrafo, pPerfil2, &amigos);
	if (verificaAmigos == AMI_NaoPossuiAmizades){
		amigos = 0;
	} else if (verificaAmigos != AMI_CondRetOK){
		printf("Erro inesperado no modulo amizade\n");
		exit(0);
	}
	
	printf("===============================================================================\n");
    printf("Bem-vindo ao perfil de %s\n\n",primNome);
	
	printf("Nome: %s %s\n", primNome, ultNome);
    printf("Email: %s\n", emailPerfil);
	printf("Data de Nascimento: %d|%d|%d\n", dia, mes, ano);
	printf("Cidade: %s\n",cidade);
	printf("Numero de amigos: %d \n",amigos);
	
    printf("O que deseja fazer? \n\n");
    
    printf("1. Criar Amizade \n");
    printf("2. Acessar perfil de %s \n",primNome);
    printf("3. Voltar para perfil de %s \n",primNome1);
    printf("4. Voltar para o menu \n\n");
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf(" %c", &menuEscolhido);
		printf("\n\n");
		
		//Menu 16
		if (menuEscolhido == '1'){
			MENU_MenuCriarAmizade(pGrafo, pPerfil2, pPerfil1);
			escolhaValida = 1;
		// Menu 2
		} else if (menuEscolhido == '2'){
			MENU_MenuIrPerfil(pGrafo, pPerfil2, emailPerfil, primNome, ultNome, cidade, dia, mes, ano);
			escolhaValida = 1;
		// Menu 2
		} else if (menuEscolhido == '3'){
			MENU_MenuIrPerfil(pGrafo, pPerfil1, emailPerfil1, primNome1, ultNome1, cidade1, dia1, mes1, ano1);
			escolhaValida = 1;
		// Menu 1
		} else if (menuEscolhido == '4'){
			
			MENU_MenuInicial(pGrafo);
			escolhaValida = 1;
			
		} else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
	
} /* Fim funÁ„o: MENU - Menu 7 - Procurar Novos Amigos */

  /***************************************************************************
  *  FunÁ„o: MENU  &Menu 8 - Ver amigos
  *
  *****/

void MENU_MenuVerAmigos(GRA_tppGrafo pGrafo, PER_tpPerfil *pPerfil) {
	AMI_tpCondRet retornoAmi;
	PER_tpPerfil **vetAmigos;
	PER_tpCondRet retornoPer;
	int qtd, i, escolhaValida = 0;
	char email[101], primeiroNome[51], ultimoNome[51], cidade[51], menuEscolhido;
	int diaNasc, mesNasc, anoNasc;

	retornoAmi = AMI_VerificarNumAmigos(pGrafo, pPerfil, &qtd);
	if (retornoAmi == AMI_CondRetOK) {
		if ((vetAmigos = (PER_tpPerfil **)malloc(sizeof(PER_tpPerfil *)*qtd)) == NULL) {
			printf("Falha no malloc\n");
			exit(1);
		}
		
		retornoAmi = AMI_ArmazenarAmizades(pGrafo, pPerfil, vetAmigos);
		if (retornoAmi == AMI_NaoPossuiAmizades) {
			printf("Nao possui amizades\n");
			MENU_MenuInicial(pGrafo);
		}
		else if (retornoAmi == AMI_UsuarioNaoExiste) {
			printf("Usuario nao existe\n");
			MENU_MenuInicial(pGrafo);
		}
		else if (retornoAmi != MEN_CondRetOK) {
			printf("Erro ao armazenar amizades\n");
			exit(1);
		}

		printf("Seus amigos: \n\n");
		for (i = 0; i < qtd; i++) {
			retornoPer = PER_ObterPerfil(vetAmigos[i], email, primeiroNome, ultimoNome, &diaNasc, &mesNasc, &anoNasc, cidade);
			if (retornoPer != PER_CondRetOK) {
				printf("Erro ao obter perfil\n");
				exit(1);
			}
			printf("%s\n", email);
		}
		free(vetAmigos);
	}
	else if (retornoAmi == AMI_NaoPossuiAmizades) {
		printf("Nao possui amigos\n");
	}
	else{
		printf("Erro ao obter numero de amigos\n");
		exit(1);
	}

	retornoPer = PER_ObterPerfil(pPerfil, email, primeiroNome, ultimoNome, &diaNasc, &mesNasc, &anoNasc, cidade);
	if (retornoPer != PER_CondRetOK) {
		printf("Erro ao obter perfil\n");
		exit(1);
	}

	printf("O que deseja fazer? \n\n");

	printf("1. Voltar para o perfil de %s \n", primeiroNome);
	printf("2. Voltar para o menu \n");

	while (escolhaValida == 0) {

		printf("> ");
		scanf(" %c", &menuEscolhido);
		printf("\n\n");

		if (menuEscolhido == '1') {
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil, email, primeiroNome, ultimoNome, cidade, diaNasc, mesNasc, anoNasc);

		}
		else if (menuEscolhido == '2') {
			escolhaValida = 1;
			MENU_MenuInicial(pGrafo);

		}
		else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}

	}
}/* Fim funÁ„o: MENU - Menu 8 - Ver amigos */

 /***************************************************************************
 *  FunÁ„o: MENU  &Menu 9 - Ir para mensagens
 *
 *****/

void MENU_MenuIrMensagens(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil) {
	int escolhaMenu = 0;
	int qtd, i, dia, mes, ano, envMsg;
	MEN_tpCondRet retorno;
	MEN_tpCondMsg *vetTipos;
	char **vetEmails, **vetMensagens, email[101], primNome[51], ultNome[51], cidade[51], mensagem[401], escolha;
	PER_tpPerfil *pPerfil2;
	PER_tpCondRet retornoPer;
	AMI_tpCondRet retornoAmi;

	/*Exibir todas  as mensagens*/
	retorno = MEN_ObterNumTodasMensagens(pPerfil, &qtd);
	if (retorno != MEN_CondRetOK) {
		printf("Erro ao obter numero de mensagens\n");
		exit(1);
	}
	if ((vetTipos = (MEN_tpCondMsg *)malloc(sizeof(MEN_tpCondMsg)*qtd)) == NULL) {
		printf("Falha no malloc\n");
		exit(1);
	}
	if ((vetEmails = (char **)malloc(sizeof(char *)*qtd)) == NULL) {
		printf("Falha no malloc\n");
		exit(1);
	}
	for (i = 0; i < qtd; i++) {
		if ((vetEmails[i] = (char *)malloc(sizeof(char) * 101)) == NULL) {
			printf("Falha no malloc\n");
			exit(1);
		}
	}
	if ((vetMensagens = (char **)malloc(sizeof(char *)*qtd)) == NULL) {
		printf("Falha no malloc\n");
		exit(1);
	}
	for (i = 0; i < qtd; i++) {
		if ((vetMensagens[i] = (char *)malloc(sizeof(char) * 401)) == NULL) {
			printf("Falha no malloc\n");
			exit(1);
		}
	}
	retorno = MEN_ObterTodasMensagens(pPerfil, vetTipos, vetEmails, vetMensagens);
	if (retorno == MEN_CondRetListaVazia) {
		printf("Nao ha mensagens antigas\n");
	}
	else if (retorno == MEN_CondRetOK) {
		for (i = 0; i < qtd; i++) {
			printf("Mensagem %d:\n", i);
			if(vetTipos[i] == MEN_CondMsgEnviada)
				printf("Enviada para: %s\t", vetEmails[i]);
			else if (vetTipos[i] == MEN_CondMsgRecebida)
				printf("Enviada por: %s\t", vetEmails[i]);
			printf("%s", vetMensagens[i]);
			printf("\n");
		}
	}
	else{
		printf("Erro ao obter todas as mensagens\n");
		exit(1);
	}
	/*Fim exibir todas  as mensagens*/
	printf("===============================================================================\n");
	printf("O que deseja fazer com suas mensagens?\n\n");

	printf("1. Escrever mensagem\n");
	printf("2. Excluir mensagem \n");
	printf("3. Obter total de mensagens\n");
	printf("4. Obter total de mensagens enviadas\n");
	printf("5. Obter total de mensagens recebidas\n");
	printf("6. Voltar ao menu\n");

	while (escolhaMenu == 0) {

		printf("> ");
		scanf(" %c", &escolha);
		printf("\n\n");

		switch (escolha)
		{
			/*Escrever mensagem*/
		case '1':
			envMsg = 1;
			escolhaMenu = 1;
			printf("Digite o email do amigo que voce quer conversar\n");
			scanf("%s", email);
			retornoPer = PER_BuscaEmail(pGrafo, email, &pPerfil2, &i);
			if (retornoPer == PER_CondRetEmailInexistente) {
					printf("Email inexistente\n");
				}
			else if (retornoPer != PER_CondRetEmailJaCadastrado) {
					printf("Erro ao procurar email\n");
					exit(1);
				}
			else {
					retornoAmi = AMI_VerificarAmizade(pGrafo, pPerfil, pPerfil2);
					if (retornoAmi == AMI_AmizadeNaoExiste) {
						printf("Usuario nao e seu amigo\nSo e possivel conversar com amigos\n");
					}
					else if (retornoAmi != AMI_CondRetOK) {
						printf("Erro ao verificar amizade\n");
						exit(1);
					}
					else {
						envMsg = 1;
						while (envMsg == 1) {
							printf("Escreva sua mensagem:\n");
							i = 0;
							scanf(" %c", &mensagem[i]);
							while (mensagem[i] != '\n' && i < 400) {
								i++;
								scanf("%c", &mensagem[i]);
							}
							mensagem[i] = '\0';
							printf("\n\n");
							retorno = MEN_EscreverMensagem(pPerfil, pPerfil2, mensagem);
							if (retorno != MEN_CondRetOK) {
								printf("Erro ao enviar mensagem\n");
								exit(1);
							}
							printf("Deseja continuar enviando mensagens? (0 = nao, 1 = sim)");
							scanf("%d", &envMsg);
						}
					}
				}
			break;/*Fim Escrever mensagem*/

			/*Excluir mensagem*/
		case '2':
			escolhaMenu = 1;
			printf("Escreva o numero da mensagem que deseja excluir:");
			scanf("%d", &i);
			while (i < 0 || i > qtd) {
				printf("Numero invalido, digite novamente:");
				scanf("%d", &i);
			}
			retorno = MEN_ExcluirMensagem(pPerfil, vetEmails[i], vetTipos[i], vetMensagens[i]);
			if (retorno != MEN_CondRetOK) {
				printf("Erro ao excluir mensagem\n");
				exit(1);
			}
			printf("\nMensagem excluida\n");
			break; /*Fim excluir mensagem*/

				   /*Obter total de mensagens*/
		case '3':
			escolhaMenu = 1;
			printf("Total de mensagens = %d\n", qtd);
			break;/*Fim obter total de mensagens*/

				  /*Obter total de mensagens enviadas*/
		case '4':
			escolhaMenu = 1;
			if (qtd != 0) {
				retorno = MEN_ObterNumMensagens(pPerfil, MEN_CondMsgEnviada, &qtd);
				if (retorno != MEN_CondRetOK) {
					printf("Erro ao obter numero de mensagens\n");
					exit(1);
				}
			}
			printf("Total de mensagens = %d\n", qtd);
			break;/*Fim obter total de mensagens enviadas*/

				  /*Obter total de mensagens recebidas*/
		case '5':
			escolhaMenu = 1;
			if (qtd != 0) {
				retorno = MEN_ObterNumMensagens(pPerfil, MEN_CondMsgRecebida, &qtd);
				if (retorno != MEN_CondRetOK) {
					printf("Erro ao obter numero de mensagens\n");
					exit(1);
				}
			}
			printf("Total de mensagens = %d\n", qtd);
			break;/*Fim obter total de mensagens recebidas*/
			/*Voltar ao menu*/
		case '6':
			free(vetTipos);
			for (i = 0; i < qtd; i++) {
				free(vetEmails[i]);
			}
			free(vetEmails);
			for (i = 0; i < qtd; i++) {
				free(vetMensagens[i]);
			}
			free(vetMensagens);
			MENU_MenuInicial(pGrafo);
			escolhaMenu = 1;
			break;/*Fim voltar ao menu*/
		default:
			printf("Escolha invalida. Por favor, digite o menu novamente.\n\n");
			break;
		}
	}
	
	printf("\nO que deseja fazer?\n\n");

	printf("1. Continuar em mensagem \n");
	printf("2. Voltar para perfil\n");
	printf("3. Voltar ao menu\n");

	escolhaMenu = 0;

	while (escolhaMenu == 0) {

		printf("> ");
		scanf(" %c", &escolha);
		printf("\n\n");

		switch (escolha)
		{
			/*Continuar em mensagem*/
		case '1':
			free(vetTipos);
			for (i = 0; i < qtd; i++) {
				free(vetEmails[i]);
			}
			free(vetEmails);
			for (i = 0; i < qtd; i++) {
				free(vetMensagens[i]);
			}
			free(vetMensagens);
			MENU_MenuIrMensagens(pGrafo, pPerfil);
			escolhaMenu = 1;
			break; /*Fim Continuar em mensagem*/

				   /*Voltar para perfil*/
		case '2':
			free(vetTipos);
			for (i = 0; i < qtd; i++) {
				free(vetEmails[i]);
			}
			free(vetEmails);
			for (i = 0; i < qtd; i++) {
				free(vetMensagens[i]);
			}
			free(vetMensagens);
			if (PER_ObterPerfil(pPerfil, email, primNome, ultNome, &dia, &mes, &ano, cidade) != PER_CondRetOK) {
				printf("Erro ao obter perfil");
				exit(1);
			}
			MENU_MenuIrPerfil(pGrafo, pPerfil, email, primNome, ultNome, cidade, dia, mes, ano);
			escolhaMenu = 1;
			break;/*Fim Voltar para perfil*/

				  /*Voltar ao menu*/
		case '3':
			free(vetTipos);
			for (i = 0; i < qtd; i++) {
				free(vetEmails[i]);
			}
			free(vetEmails);
			for (i = 0; i < qtd; i++) {
				free(vetMensagens[i]);
			}
			free(vetMensagens);
			MENU_MenuInicial(pGrafo);
			escolhaMenu = 1;
			break;/*Fim Voltar ao menu*/
		default:
			printf("Escolha invalida. Por favor, digite o menu novamente.\n\n");
			break;
		}
	}
} /* Fim funÁ„o: MENU - Menu 9 - Ir para mensagens */

  /***************************************************************************
  *  FunÁ„o: MENU  &Menu 10 - Excluir Todas as Amizades
  *
  *****/

void MENU_MenuExcluirTodasAmizades(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil) {
	AMI_tpCondRet retorno;
	PER_tpCondRet retornoPer;
	int escolhaMenu = 0, dia, mes, ano;
	char email[101], primNome[51], ultNome[51], cidade[51], test;

	retorno = AMI_ExcluirTodasAmizades(pGrafo, pPerfil);
	if (retorno != MEN_CondRetOK) {
		printf("Erro ao excluir todas amziades\n");
		exit(1);
	}
	printf("Amizades excluidas\n\n");

	

	while (escolhaMenu == 0) {
		printf("O que deseja fazer?\n\n");

		printf("1. Voltar para perfil\n");
		printf("2. Voltar ao menu inicial\n>");
		scanf(" %c", &test);
		if (test == '1') {
			escolhaMenu = 1;
			retornoPer = PER_ObterPerfil(pPerfil, email, primNome, ultNome, &dia, &mes, &ano, cidade);
			if (retornoPer != PER_CondRetOK) {
				printf("Retorno inesperado de obter perfil\n");
				exit(1);
			}
			MENU_MenuIrPerfil(pGrafo, pPerfil, email, primNome, ultNome, cidade, dia, mes, ano);
		}
		else if (test == '2') {
			escolhaMenu = 1;
			MENU_MenuInicial(pGrafo);
		}
		else {
			printf("Menu esclhido invalido, tente novamente\n");
		}
	}
	
} /* Fim funÁ„o: MENU - Menu 10 - Excluir Todas as Amizades */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 11 - Excluir Perfil
 *
 *****/

void MENU_MenuExcluirPerfil(GRA_tppGrafo pGrafo, char * email){
	
	PER_tpCondRet excluirPerfil;

	excluirPerfil = PER_ExcluirPerfil(pGrafo, email);
	if (excluirPerfil != PER_CondRetOK){
		printf("Erro inesperado no modulo perfil");
		exit(0);
	}
	
	printf("===============================================================================\n");
    printf("O perfil foi excluido.\n\n");
	
	MENU_MenuInicial(pGrafo);
	
	
} /* Fim funÁ„o: MENU - Menu 11 - Excluir Perfil */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 12 - Modificar email do perfil
 *
 *****/
 
void MENU_MenuModificarEmail(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc){
	
	char emailNovo[101];
	int avaliaEmail = 0;
	char menuEscolhido;
	int escolhaValida = 0;
	
	PER_tpCondRet modEmail;
	
	printf("===============================================================================\n");
    printf("Email de %s: %s\n\n",primNome,email);
	
	while (avaliaEmail == 0){
		
		printf("Digite o novo email de %s: ",primNome);
		scanf("%s", &emailNovo);
		printf("\n\n");
		
		modEmail = PER_ModificaEmail(pGrafo, email, emailNovo);
		if (modEmail == PER_CondRetEmailInvalido){
			printf("O email digitado possui um formato invalido. Por favor reescreva o email.\n\n");
		} else if (modEmail == PER_CondRetEmailJaCadastrado){
			printf("Ja existe um usuario com o email digitado.\n\n");
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
		scanf(" %c", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == '1'){
			escolhaValida = 1;
			MENU_MenuModificarDados(pGrafo, pPerfil, emailNovo, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == '2'){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil, emailNovo, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == '3'){
			escolhaValida = 1;
			MENU_MenuInicial(pGrafo);
			
		} else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}

} /* Fim funÁ„o: MENU - Menu 12 - Modificar email do perfil */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 13 - Modificar nome do perfil
 *
 *****/
 
void MENU_MenuModificarNome(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc){
	
	char primNomeNovo[51], ultNomeNovo[51];
	int avaliaNome = 0;
	char menuEscolhido;
	int escolhaValida = 0;
	
	PER_tpCondRet modNome;
	
	printf("===============================================================================\n");
    printf("Nome: %s %s\n\n",primNome,ultNome);
	
	while (avaliaNome == 0){
		
		printf("Digite o novo primeiro nome de %s: ",primNome);
		scanf("%s", &primNomeNovo);
		printf("\n\n");
		
		printf("Digite o novo ultimo nome de %s: ",primNome);
		scanf("%s", &ultNomeNovo);
		printf("\n\n");
		modNome = PER_ModificaNome(pGrafo, email, primNomeNovo,ultNomeNovo);
		if (modNome == PER_CondRetNomeInvalido){
			printf("O nome digitado possui um formato invalido. Por favor reescreva o nome.\n\n");
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
		scanf(" %c", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == '1'){
			escolhaValida = 1;
			MENU_MenuModificarDados(pGrafo, pPerfil, email, primNomeNovo, ultNomeNovo, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == '2'){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil, email, primNomeNovo, ultNomeNovo, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == '3'){
			escolhaValida = 1;
			MENU_MenuInicial(pGrafo);
			
		} else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}	
	}
} /* Fim funÁ„o: MENU - Menu 13 - Modificar nome do perfil */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 14 - Modificar data de nascimento do perfil
 *
 *****/

void MENU_MenuModificarData(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc){
	
	int diaNovo = -1;
	int mesNovo = -1;
	int anoNovo = -1;
	int avaliaData = 0;
	char menuEscolhido;
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
			printf("A data digitada possui um formato invalido. Por favor reescreva a data.\n\n");
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
		scanf(" %c", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == '1'){
			escolhaValida = 1;
			MENU_MenuModificarDados(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNovo, mesNovo, anoNovo);
			
		} else if (menuEscolhido == '2'){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNovo, mesNovo, anoNovo);
			
		} else if (menuEscolhido == '3'){
			escolhaValida = 1;
			MENU_MenuInicial(pGrafo);
			
		} else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}	
	}
	
} /* Fim funÁ„o: MENU - Menu 14 - Modificar data de nascimento do perfil */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 15 - Modificar cidade do perfil
 *
 *****/
 
void MENU_MenuModificarCidade(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc){
	
	char cidadeNovo[51];
	int avaliaCidade = 0, i;
	char menuEscolhido;
	int escolhaValida = 0;
	
	PER_tpCondRet modCidade;
	
	printf("===============================================================================\n");
    printf("Cidade de %s: %s\n\n",primNome,cidade);
	
	while (avaliaCidade == 0){
		
		printf("Digite a nova cidade de %s: ",primNome);
		i = 0;
		scanf(" %c", &cidadeNovo[i]);
		while (cidadeNovo[i] != '\n' && i < 50) {
			i++;
			scanf("%c", &cidadeNovo[i]);
		} 
		cidadeNovo[i] = '\0';
		printf("\n\n");
		
		modCidade = PER_ModificaCidade(pGrafo, email, cidadeNovo);
		if (modCidade == PER_CondRetCidadeInvalida){
			printf("A cidade digitado possui um formato invalido. Por favor reescreva o email.\n\n");
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
		scanf(" %c", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == '1'){
			escolhaValida = 1;
			MENU_MenuModificarDados(pGrafo, pPerfil, email, primNome, ultNome, cidadeNovo, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == '2'){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil, email, primNome, ultNome, cidadeNovo, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == '3'){
			escolhaValida = 1;
			MENU_MenuInicial(pGrafo);
			
		} else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
	
} /* Fim funÁ„o: MENU - Menu 15 - Modificar cidade do perfil */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 16 - Criar Amizade
 *
 *****/

void MENU_MenuCriarAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil1, PER_tpPerfil * pPerfil2){
	
	char menuEscolhido;
	int escolhaValida = 0;
	char aceitou = 0;
	int solicitacaoInvalida = 0;
	
	AMI_tpCondRet criarAmizade;
	
	char emailPerfil[101];
    char primNome[51];
    char ultNome[51];
    char cidade[51];
    int dia;
    int mes;
    int ano;
	
	char emailPerfil1[101];
    char primNome1[51];
    char ultNome1[51];
    char cidade1[51];
    int dia1;
    int mes1;
    int ano1;
	
	PER_tpCondRet condRetObterPerfil;
	PER_tpCondRet condRetObterPerfil1;

	condRetObterPerfil = PER_ObterPerfil(pPerfil2, emailPerfil, primNome, ultNome, &dia, &mes, &ano, cidade);
	if (condRetObterPerfil != PER_CondRetOK){
		printf("Erro inesperado no modulo perfil.");
		exit(0);
	}
	
	condRetObterPerfil1 = PER_ObterPerfil(pPerfil1, emailPerfil1, primNome1, ultNome1, &dia1, &mes1, &ano1, cidade1);
	if (condRetObterPerfil != PER_CondRetOK){
		printf("Erro inesperado no modulo perfil.");
		exit(0);
	}
	
	printf("===============================================================================\n");
	
	while(solicitacaoInvalida == 0){
		
		printf("%s, aceita ser amigo de %s? (0 para nao, 1 para sim)",primNome1, primNome);
		scanf(" %c", &aceitou);
		printf("\n\n");
		
		if (aceitou == '0'){
			solicitacaoInvalida = 1;
			printf("%s negou a solicitaÁ„o de amizade.\n\n",primNome);
		} else if (aceitou == '1'){
			solicitacaoInvalida = 1;
			criarAmizade = AMI_CriarAmizade(pGrafo, pPerfil1, pPerfil2, AMI_SolicitacaoAceita);
			if (criarAmizade == AMI_AmizadeJaExiste){
				printf("A amizade ja existe entre esses usuarios.\n\n");
			} else if (criarAmizade == AMI_ArestaParaSiMesmo) {
				printf("Nao e possivel criar uma amizade com si mesmo.\n\n");
			} else if (criarAmizade != AMI_CondRetOK){
				printf("Erro inesperado do modulo amizade.\n\n");
				exit(0);
			} else {
				printf("A Amizade entre %s e %s foi criada.\n\n",emailPerfil,emailPerfil1);
			}
		} else {
			printf("Por favor coloque uma das duas opcoes solicitadas.\n\n");
		}
		
	}
	
	printf("O que deseja fazer? \n\n");
    
    printf("1. Voltar para o perfil de %s \n",primNome);
	printf("2. Ir para o perfil de %s \n",primNome1);
    printf("3. Voltar para o menu \n");
    
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf(" %c", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == '1'){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil2, emailPerfil, primNome, ultNome, cidade, dia, mes, ano);
			
		} else if (menuEscolhido == '2'){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil1, emailPerfil1, primNome1, ultNome1, cidade1, dia1, mes1, ano1);
			
		} else if (menuEscolhido == '3'){
			escolhaValida = 1;
			MENU_MenuInicial(pGrafo);
			
		} else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
	
} /* Fim funÁ„o: MENU - Menu 16 - Criar Amizade */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 17 - Excluir Amizade
 *
 *****/

void MENU_MenuExcluirAmizade(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, PER_tpPerfil * pPerfil2) {
	
	char menuEscolhido;
	int escolhaValida = 0;
	
	char emailPerfil[101];
    char primNome[51];
    char ultNome[51];
    char cidade[51];
    int dia;
    int mes;
    int ano;
	
	char emailPerfil1[101];
    char primNome1[51];
    char ultNome1[51];
    char cidade1[51];
    int dia1;
    int mes1;
    int ano1;
	
	PER_tpCondRet condRetObterPerfil;
	AMI_tpCondRet retornoAmi;
	
	condRetObterPerfil = PER_ObterPerfil(pPerfil, emailPerfil, primNome, ultNome, &dia, &mes, &ano, cidade);
	if (condRetObterPerfil != PER_CondRetOK) {
		printf("Erro inesperado no modulo perfil.");
		exit(0);
	}

	condRetObterPerfil = PER_ObterPerfil(pPerfil2, emailPerfil1, primNome1, ultNome1, &dia1, &mes1, &ano1, cidade1);
	if (condRetObterPerfil != PER_CondRetOK){
		printf("Erro inesperado no modulo perfil.");
		exit(0);
	}

	retornoAmi = AMI_ExcluirAmizade(pGrafo, pPerfil, pPerfil2);

	printf("===============================================================================\n");
    printf("A Amizade entre %s e %s foi excluida.\n\n",emailPerfil,emailPerfil1);
	
	printf("O que deseja fazer? \n\n");
    
    printf("1. Voltar para o perfil de %s \n",primNome);
	printf("2. Ir para o perfil de %s \n", primNome1);
    printf("3. Voltar para o menu \n");
    
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf(" %c", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == '1'){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil, emailPerfil, primNome, ultNome, cidade, dia, mes, ano);
			
		} else if (menuEscolhido == '2'){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil, emailPerfil1, primNome1, ultNome1, cidade1, dia1, mes1, ano1);
			
		} else if (menuEscolhido == '3'){
			escolhaValida = 1;
			MENU_MenuInicial(pGrafo);
			
		} else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
} /* Fim funÁ„o: MENU - Menu 17 - Excluir Amizade */

 
 
