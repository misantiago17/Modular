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
*  Autores: Michelle Santiago (ms)
*
*  $HA HistÛrico de evoluÁ„o:
*     Vers„o    Autor   	 Data     	ObservaÁıes
*       1        ms        20/11/2017 	inicio desenvolvimento
*       2        ms        06/12/2017   modificação nas funções do modulo
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

void DestruirValor( void * pValor );

int main () {
	GRA_tppGrafo Grafo;
    
	GRA_CriarGrafo(DestruirValor, &Grafo);
	
    MENU_MenuInicial(Grafo);
    
    
    return 0;
}


/*****  CÛdigo das funÁıes exportadas pelo mÛdulo  *****/

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 1 - Menu inicial
 *
 *****/

void MENU_MenuInicial(GRA_tppGrafo pGrafo) {
    
    int menuEscolhido;
    int escolhaInvalida = 0;
    int escolhaPerfilInvalido = 0;

	char primNome[51], ultNome[51], emailPerfil[101], emailPerfilProcurado[101], cidade[51] = "Rio";
	int dia = 25, mes = 01, ano = 1998;
	int id;
	PER_tpPerfil * pPerfil;
	PER_tpCondRet condRetObterPerfil;
	PER_tpCondRet condRetObterEmail;
	
    /*TIRAR ISSO DEPOIS */
	strcpy(primNome, "Renan"); strcpy(ultNome, "Moreira"); strcpy(emailPerfil, "Awybin@gmail.com"); strcpy(cidade, "Rio de Janeiro");
	dia = 25; mes = 01; ano = 1998;
	PER_CriarPerfil(pGrafo, &pPerfil, emailPerfil, primNome, ultNome, dia, mes, ano, cidade);
	printf("Perfil de %s foi criado!\n\n", primNome);
	strcpy(primNome, "aaa"); strcpy(ultNome, "bbb"); strcpy(emailPerfil, "aaa@bbb.com"); strcpy(cidade, "Macaus");
	dia = 10; mes = 01; ano = 1998;
	PER_CriarPerfil(pGrafo, &pPerfil, emailPerfil, primNome, ultNome, dia, mes, ano, cidade);
	printf("Perfil de %s foi criado!\n\n", primNome);
	strcpy(primNome, "ccc"); strcpy(ultNome, "ddd"); strcpy(emailPerfil, "ccc@ddd.com"); strcpy(cidade, "Meca");
	dia = 10; mes = 01; ano = 1998;
	PER_CriarPerfil(pGrafo, &pPerfil, emailPerfil, primNome, ultNome, dia, mes, ano, cidade);
	printf("Perfil de %s foi criado!\n\n", primNome);
	/*FIM: TIRAR ISSO DEPOIS */
    printf("===============================================================================\n");
    printf("Bem-vindo a rede social blablabla\n\n");
    
	printf("O que deseja fazer? \n\n");

	printf("1. Criar novo perfil \n");
	printf("2. Ir para perfil \n");
	printf("3. Ver numero de perfis cadastrados \n");
	printf("4. Excluir todos os perfis da rede \n");
	printf("5. Destruir rede social (nao implementado) \n\n");
	while (escolhaInvalida == 0) {

			printf("> ");
			scanf("%d", &menuEscolhido);
			printf("\n\n");

			// Menu 3
			if (menuEscolhido == 1) {

				MENU_MenuCriarPerfil(pGrafo);
				escolhaInvalida = 1;

				// Menu 2
			}
			else if (menuEscolhido == 2) {

				while (escolhaPerfilInvalido == 0) {

					printf("Digite o email do perfil que deseja encontrar: ");
					scanf("%s", &emailPerfilProcurado);
					printf("\n\n");
					condRetObterEmail = PER_BuscaEmail(pGrafo, emailPerfilProcurado, &pPerfil, &id);
					if (condRetObterEmail == PER_CondRetEmailInexistente) {
						printf("Usuario procurado nao existe. Por favor procure novamente. \n\n");
					}
					else if (condRetObterEmail == PER_CondRetRedeVazia) {
						printf("A rede esta vazia. Crie um usuario e tente novamente. \n\n");
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
			else if (menuEscolhido == 3) {

				MENU_MenuNumPerfis(pGrafo);
				escolhaInvalida = 1;

				// Menu 5
			}
			else if (menuEscolhido == 4) {

				MENU_MenuExcluirTodosPerfis(pGrafo);
				escolhaInvalida = 1;

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
	int menuEscolhido;
	int escolhaValida = 0;
	int id2;
	int escolhaEmailValida = 0;
	
	AMI_tpCondRet verificaAmigos;
	PER_tpPerfil * pPerfil2;
	PER_tpCondRet obtemEmailPerfil2;
	char email2[101];
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
	printf("N˙mero de amigos: %d \n",amigos);
	
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
			
			MENU_MenuModificarDados(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaValida = 1;
			
		// Menu 7
		} else if (menuEscolhido == 2){
			while (escolhaEmailValida == 0){
				printf("Digite o email do perfil que deseja encontrar: ");
				scanf("%s", &email2);
				printf("\n\n");
				
				obtemEmailPerfil2 = PER_BuscaEmail(pGrafo, email2, &pPerfil2, &id2);
				if (obtemEmailPerfil2 == PER_CondRetEmailInexistente){
					printf("O email procurado nao existe na rede. Por favor, procure outro email.\n\n");
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
		} else if (menuEscolhido == 3){
			
			// Pegar todos os emails dos amigos do cara
			MENU_MenuVerAmigos(pGrafo, pPerfil);
			escolhaValida = 1;
		
		// Menu 9
		} else if (menuEscolhido == 4){
			
			MENU_MenuIrMensagens(pGrafo, pPerfil);
			escolhaValida = 1;
		
		// Menu 10
		} else if (menuEscolhido == 5){
			
			//MENU_Menu10(pGrafo,pPerfil);
			escolhaValida = 1;
		
		// Menu 11
		} else if (menuEscolhido == 6){
		
			MENU_MenuExcluirPerfil(pGrafo,email);
			escolhaValida = 1;
		
		// Menu 1
		} else if (menuEscolhido == 7){
			
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
	int dia, mes, ano, i;

	int dadosValidos = 0, escolhaEmailValida = 0;
	
	int menuEscolhido;
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
		i = -1;
		scanf("%c", &cidade[0]);
		do{
			i++;
			scanf("%c", &cidade[i]);
		}while (cidade[i] != '\n' && i < 50);
		cidade[i + 1] = '\0';

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
				scanf("%d", &menuEscolhido);
				printf("\n\n");
				
				// Menu 1
				if (menuEscolhido == 1){
					menuValido = 1;
					MENU_MenuModificarDados(pGrafo, pPerfil, email, primNome, ultNome, cidade, dia, mes, ano);
				
				// Menu 2
				} else if (menuEscolhido == 2){
					while (escolhaEmailValida == 0) {
						printf("Digite o email do perfil que deseja encontrar: ");
						scanf("%s", &email2);
						printf("\n\n");

						obtemEmailPerfil2 = PER_BuscaEmail(pGrafo, email2, &pPerfil2, &i);
						if (obtemEmailPerfil2 == PER_CondRetEmailInexistente) {
							printf("O email procurado nao existe na rede. Por favor, procure outro email.\n\n");
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
				else if (menuEscolhido == 3) {
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
	int menuEscolhido;
	int escolhaValida = 0;
	
	PER_tpCondRet numPerfis;
	
	numPerfis =  PER_NumeroPerfis(pGrafo, &perfisCadastrados);
	if (numPerfis != PER_CondRetOK){
		printf("Ocorreu um erro inesperado no mÛdulo perfis.\n");
		exit(0);
	}
	
	printf("===============================================================================\n");
	printf("H· %d perfis cadastrados na rede.\n\n",perfisCadastrados);
	
	printf("1. Voltar para o menu\n\n");
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n");
	
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_MenuInicial(pGrafo);
			
		} else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
	
} /* Fim funÁ„o: MENU - Menu 4 - Ver N˙mero de Perfis na Rede */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 5 - Excluir todos os perfis da rede
 *
 *****/
 
void MENU_MenuExcluirTodosPerfis(GRA_tppGrafo pGrafo){
	
	int menuEscolhido;
	int escolhaValida = 0;
	
	PER_tpCondRet excluirPerfis;
	
	excluirPerfis = PER_ExcluirTodosPerfis(pGrafo);
	if (excluirPerfis != PER_CondRetOK){
		printf("Ocorreu um erro inesperado no mÛdulo perfis.\n");
		exit(0);
	}
	
	printf("===============================================================================\n");
	printf("Todos os perfis foram excluÌdos.\n\n");
	
	printf("1. Voltar para o menu\n\n");
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n");
	
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_MenuInicial(pGrafo);
			
		} else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
} /* Fim funÁ„o: MENU - Menu 5 - Excluir todos os perfis da rede */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 6 - Modificar dados do perfil
 *
 *****/

void MENU_MenuModificarDados(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc){
	
	int escolhaInvalida = 0;
	int menuEscolhido;
	
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
		scanf("%d", &menuEscolhido);
		printf("\n\n");
				
		// Menu 12
		if (menuEscolhido == 1) {
			
			MENU_MenuModificarEmail(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
			
		// Menu 13
		} else if (menuEscolhido == 2){
			MENU_MenuModificarNome(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
		
		// Menu 14
		} else if (menuEscolhido == 3){
			
			MENU_MenuModificarData(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
		
		// Menu 15
		} else if (menuEscolhido == 4){
			
			MENU_MenuModificarCidade(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
		
		// Menu 2
		} else if (menuEscolhido == 5){
			
			MENU_MenuIrPerfil(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			escolhaInvalida = 1;
		
		// Menu 1
		} else if (menuEscolhido == 6){
		
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
	
	int amigos, verificaAmigos, escolhaValida = 0, menuEscolhido;
	
	char * emailPerfil;
    char * primNome;
    char * ultNome;
    char * cidade;
    int dia;
    int mes;
    int ano;
	
	char * emailPerfil1;
    char * primNome1;
    char * ultNome1;
    char * cidade1;
    int dia1;
    int mes1;
    int ano1;
	
	PER_tpCondRet condRetObterPerfil;
	PER_tpCondRet condRetObterPerfil1;
	
	if ((emailPerfil = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar email do perfil");
		exit(0);
	}
	if ((primNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar primeiro nome do perfil");
		exit(0);
	}
	if ((ultNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar ultimo nome do perfil");
		exit(0);
	}
	if ((cidade = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar ultimo nome do cidade");
		exit(0);
	}
	
	if ((emailPerfil1 = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar email do perfil");
		exit(0);
	}
	if ((primNome1 = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar primeiro nome do perfil");
		exit(0);
	}
	if ((ultNome1 = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar ultimo nome do perfil");
		exit(0);
	}
	if ((cidade1 = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar ultimo nome do cidade");
		exit(0);
	}
	
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
	printf("N˙mero de amigos: %d \n",amigos);
	
    printf("O que deseja fazer? \n\n");
    
    printf("1. Criar Amizade \n");
    printf("2. Acessar perfil de %s \n",primNome);
    printf("3. Voltar para perfil de %s \n",primNome1);
    printf("4. Voltar para o menu \n\n");
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
		//Menu 16
		if (menuEscolhido == 1){
			MENU_MenuCriarAmizade(pGrafo, pPerfil2, pPerfil1);
			escolhaValida = 1;
		// Menu 2
		} else if (menuEscolhido == 2){
			MENU_MenuIrPerfil(pGrafo, pPerfil2, emailPerfil, primNome, ultNome, cidade, dia, mes, ano);
			escolhaValida = 1;
		// Menu 2
		} else if (menuEscolhido == 3){
			MENU_MenuIrPerfil(pGrafo, pPerfil1, emailPerfil1, primNome1, ultNome1, cidade1, dia1, mes1, ano1);
			escolhaValida = 1;
		// Menu 1
		} else if (menuEscolhido == 4){
			
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
	int qtd, i, escolhaValida = 0, menuEscolhido;
	char email[101], primeiroNome[51], ultimoNome[51], cidade[51];
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
		scanf("%d", &menuEscolhido);
		printf("\n\n");

		if (menuEscolhido == 1) {
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil, email, primeiroNome, ultimoNome, cidade, diaNasc, mesNasc, anoNasc);

		}
		else if (menuEscolhido == 2) {
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
	int escolhaInvalida = 0;
	int escolha, qtd, i, j = 0, num;
	MEN_tpCondRet retorno;
	MEN_tpCondMsg *vetTipos;
	char **vetEmails, **vetMensagens;

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
	if ((vetEmails = (char **)malloc(sizeof(char)*qtd)) == NULL) {
		printf("Falha no malloc\n");
		exit(1);
	}
	if ((vetMensagens = (char **)malloc(sizeof(char)*qtd)) == NULL) {
		printf("Falha no malloc\n");
		exit(1);
	}
	retorno = MEN_ObterTodasMensagens(pPerfil, vetTipos, vetEmails, vetMensagens);
	if (retorno != MEN_CondRetOK) {
		printf("Erro ao obter todas as mensagens\n");
		exit(1);
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
				printf("Erro ao excluir mensagem\n");
				exit(1);
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
				printf("Erro ao obter numero de mensagens\n");
				exit(1);
			}
			printf("Total de mensagens = %d\n", qtd);
			break;/*Fim obter total de mensagens enviadas*/

				  /*Obter total de mensagens recebidas*/
		case 4:
			escolhaInvalida = 1;
			retorno = MEN_ObterNumMensagens(pPerfil, MEN_CondMsgRecebida, &qtd);
			if (retorno != MEN_CondRetOK) {
				printf("Erro ao obter numero de mensagens\n");
				exit(1);
			}
			printf("Total de mensagens = %d\n", qtd);
			break;/*Fim obter total de mensagens recebidas*/

		default:
			printf("Escolha invalida. Por favor, digite o menu novamente.\n\n");
			break;
		}
	}
	MENU_MenuInicial(pGrafo);
} /* Fim funÁ„o: MENU - Menu 9 - Ir para mensagens */

  /***************************************************************************
  *  FunÁ„o: MENU  &Menu 10 - Excluir Todas as Amizades
  *
  *****/

void MENU_MenuExcluirTodasAmizades(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil) {
	AMI_tpCondRet retorno;

	retorno = AMI_ExcluirTodasAmizades(pGrafo, pPerfil);
	if (retorno != MEN_CondRetOK) {
		printf("Erro ao excluir todas amziades\n");
		exit(1);
	}
	printf("Amizades excluidas");
	MENU_MenuInicial(pGrafo);
} /* Fim funÁ„o: MENU - Menu 10 - Excluir Todas as Amizades */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 11 - Excluir Perfil
 *
 *****/

void MENU_MenuExcluirPerfil(GRA_tppGrafo pGrafo, char * email){
	
	PER_tpCondRet excluirPerfil;
	
	int menuEscolhido;
	int escolhaValida = 0;
	
	excluirPerfil = PER_ExcluirPerfil(pGrafo, email);
	if (excluirPerfil != PER_CondRetOK){
		printf("Erro inesperado no modulo perfil");
		exit(0);
	}
	
	printf("===============================================================================\n");
    printf("O perfil foi excluido.\n\n");
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_MenuInicial(pGrafo);
			
		} else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
	
	
} /* Fim funÁ„o: MENU - Menu 11 - Excluir Perfil */

/***************************************************************************
 *  FunÁ„o: MENU  &Menu 12 - Modificar email do perfil
 *
 *****/
 
void MENU_MenuModificarEmail(GRA_tppGrafo pGrafo, PER_tpPerfil * pPerfil, char * email, char * primNome, char * ultNome, char * cidade, int diaNasc, int mesNasc, int anoNasc){
	
	char emailNovo[101];
	int avaliaEmail = 0;
	int menuEscolhido;
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
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_MenuModificarDados(pGrafo, pPerfil, emailNovo, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 2){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil, emailNovo, primNome, ultNome, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 3){
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
	int menuEscolhido;
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
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_MenuModificarDados(pGrafo, pPerfil, email, primNomeNovo, ultNomeNovo, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 2){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil, email, primNomeNovo, ultNomeNovo, cidade, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 3){
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
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_MenuModificarDados(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNovo, mesNovo, anoNovo);
			
		} else if (menuEscolhido == 2){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil, email, primNome, ultNome, cidade, diaNovo, mesNovo, anoNovo);
			
		} else if (menuEscolhido == 3){
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
	int menuEscolhido;
	int escolhaValida = 0;
	
	PER_tpCondRet modCidade;
	
	printf("===============================================================================\n");
    printf("Cidade de %s: %s\n\n",primNome,cidade);
	
	while (avaliaCidade == 0){
		
		printf("Digite a nova cidade de %s: ",primNome);
		i = 0;
		scanf(" %c", &cidadeNovo[0]);
		while (cidadeNovo[i] != '\n' && i < 50) {
			i++;
			scanf("%c", &cidadeNovo[i]);
		} 
		cidade[i + 1] = '\0';
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
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_MenuModificarDados(pGrafo, pPerfil, email, primNome, ultNome, cidadeNovo, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 2){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil, email, primNome, ultNome, cidadeNovo, diaNasc, mesNasc, anoNasc);
			
		} else if (menuEscolhido == 3){
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
	
	int menuEscolhido;
	int escolhaValida = 0;
	int aceitou = 0;
	int solicitacaoInvalida = 0;
	
	AMI_tpCondRet criarAmizade;
	
	char * emailPerfil;
    char * primNome;
    char * ultNome;
    char * cidade;
    int dia;
    int mes;
    int ano;
	
	char * emailPerfil1;
    char * primNome1;
    char * ultNome1;
    char * cidade1;
    int dia1;
    int mes1;
    int ano1;
	
	PER_tpCondRet condRetObterPerfil;
	PER_tpCondRet condRetObterPerfil1;
	
	if ((emailPerfil = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Nao ha espaco para armazenar email do perfil");
		exit(0);
	}
	if ((primNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Nao ha espaco para armazenar primeiro nome do perfil");
		exit(0);
	}
	if ((ultNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Nao ha espaco para armazenar ultimo nome do perfil");
		exit(0);
	}
	if ((cidade = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Nao ha espaco para armazenar ultimo nome do cidade");
		exit(0);
	}
	
	if ((emailPerfil1 = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Nao ha espaco para armazenar email do perfil");
		exit(0);
	}
	if ((primNome1 = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Nao ha espaco para armazenar primeiro nome do perfil");
		exit(0);
	}
	if ((ultNome1 = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Nao ha espaco para armazenar ultimo nome do perfil");
		exit(0);
	}
	if ((cidade1 = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("Nao ha espaco para armazenar ultimo nome do cidade");
		exit(0);
	}
	
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
		scanf("%d", &aceitou);
		printf("\n\n");
		
		if (aceitou == 0){
			solicitacaoInvalida = 1;
			printf("%s negou a solicitaÁ„o de amizade.\n\n",primNome);
		} else if (aceitou == 1){
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
	printf("2. Voltar para o perfil de %s \n",primNome1);
    printf("3. Voltar para o menu \n");
    
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil2, emailPerfil, primNome, ultNome, cidade, dia, mes, ano);
			
		} else if (menuEscolhido == 2){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil1, emailPerfil1, primNome1, ultNome1, cidade1, dia1, mes1, ano1);
			
		} else if (menuEscolhido == 3){
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
	
	int menuEscolhido;
	int escolhaValida = 0;
	
	char * emailPerfil;
    char * primNome;
    char * ultNome;
    char * cidade;
    int dia;
    int mes;
    int ano;
	
	char * emailPerfil1;
    char * primNome1;
    char * ultNome1;
    char * cidade1;
    int dia1;
    int mes1;
    int ano1;
	
	PER_tpCondRet condRetObterPerfil;
	PER_tpCondRet condRetObterPerfil1;
	
	if ((emailPerfil = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar email do perfil");
		exit(0);
	}
	if ((primNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar primeiro nome do perfil");
		exit(0);
	}
	if ((ultNome = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar ultimo nome do perfil");
		exit(0);
	}
	if ((cidade = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar ultimo nome do cidade");
		exit(0);
	}
	
	if ((emailPerfil1 = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar email do perfil");
		exit(0);
	}
	if ((primNome1 = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar primeiro nome do perfil");
		exit(0);
	}
	if ((ultNome1 = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar ultimo nome do perfil");
		exit(0);
	}
	if ((cidade1 = (char *)malloc(sizeof(char)*50)) == NULL){
		printf("N„o h· espaÁo para armazenar ultimo nome do cidade");
		exit(0);
	}
	
	condRetObterPerfil = PER_ObterPerfil(pPerfil2, emailPerfil, primNome, ultNome, &dia, &mes, &ano, cidade);
	if (condRetObterPerfil != PER_CondRetOK){
		printf("Erro inesperado no modulo perfil.");
		exit(0);
	}
	
	condRetObterPerfil1 = PER_ObterPerfil(pPerfil, emailPerfil1, primNome1, ultNome1, &dia1, &mes1, &ano1, cidade1);
	if (condRetObterPerfil != PER_CondRetOK){
		printf("Erro inesperado no modulo perfil.");
		exit(0);
	}
	
	printf("===============================================================================\n");
    printf("A Amizade entre %s e %s foi criada.\n\n",emailPerfil,emailPerfil1);
	
	printf("O que deseja fazer? \n\n");
    
    printf("2. Voltar para o perfil de %s \n",primNome);
	printf("2. Voltar para o perfil de %s \n",primNome1);
    printf("3. Voltar para o menu \n");
    
	
	while (escolhaValida == 0){
		
		printf("> ");
		scanf("%d", &menuEscolhido);
		printf("\n\n");
		
		if (menuEscolhido == 1){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil2, emailPerfil, primNome, ultNome, cidade, dia, mes, ano);
			
		} else if (menuEscolhido == 2){
			escolhaValida = 1;
			MENU_MenuIrPerfil(pGrafo, pPerfil, emailPerfil1, primNome1, ultNome1, cidade1, dia1, mes1, ano1);
			
		} else if (menuEscolhido == 3){
			escolhaValida = 1;
			MENU_MenuInicial(pGrafo);
			
		} else {
			printf("Escolha invalida de menu. Por favor, digite o menu novamente.\n\n");
		}
		
	}
} /* Fim funÁ„o: MENU - Menu 17 - Excluir Amizade */

/***************************************************************************
 *  FunÁ„o: MENU  &Destriur Valor
 *
 *****/
 
   void DestruirValor( void * pValor )
   {
      free( pValor ) ;
   } /* Fim funÁ„o: TAMI -Destruir valor */



 
 
