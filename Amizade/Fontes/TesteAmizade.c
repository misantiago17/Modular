/***************************************************************************
*  $MCI M�dulo de implementa��o: TAMI Teste m�dulo amizade
*
*  Arquivo gerado:              TesteAmizade.c
*  Letras identificadoras:      TAMI
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Amizade.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ms
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       ms   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"
#include    "AMIZADE.h"
#include	"PERFIL.h"
#include	"GRAFO.h"
#include "lista.h"

static const char RESET_AMIZADE_CMD				[ ] = "=resetteste";
static const char CRIAR_AMIZADE_CMD       		[ ] = "=criaramizade";
static const char EXCLUIR_AMIZADE_CMD     		[ ] = "=excluiramizade";
static const char VERIFICAR_NUM_AMIGOS_CMD      [ ] = "=verificarnumamigos";
static const char ARMAZENAR_AMIZADES_CMD        [ ] = "=armazenaramizades";
static const char EXCLUIR_TODAS_AMIZADES_CMD    [ ] = "=excluirtodasamizades";
static const char VERIFICAR_AMIZADES_CMD        [ ] = "=verificaramizades";



#define TRUE  1
#define FALSE 0

#define DIM_VT_PERFIL  	8
#define DIM_VT_EMAIL  	8
#define DIM_VT_PRIMNOME 8
#define DIM_VT_ULTNOME 	8
#define DIM_VT_CIDADE  	8
#define DIM_VT_DIA  	8
#define DIM_VT_MES  	8
#define DIM_VT_ANO  	8


PER_tpPerfil *  vtPerfil[ DIM_VT_PERFIL ]; 
PER_tpPerfil *  vtPerfilTeste[ 3 ];
GRA_tppGrafo   vtGrafos[1] ;


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static void DestruirValor( void * pValor );
static int ValidarInxPerfil( int inxPerfil);



/*****  C�digo das fun��es exportadas pelo m�dulo  *****/
/***********************************************************************
*
*  $FC Fun��o: TAMI &Testar amizade
*
*  $ED Descri��o da fun��o
*	  Podem ser criadas at� 8 perfis, identificados pelos �ndices 0 a 8
*
*     Comandos dispon�veis:
*
*     =resetteste - anula o vetor de grafos e perfiis. Provoca vazamento de mem�ria.
*     =criaramizade                   	inxPerfil1 	inxPerfil2 	Solicitacao   CondRetEsp
*     =excluiramizade                	inxPerfil1 	inxPerfil2 	CondRetEsp
*     =verificarnumamigos               inxPerfil 	numAmizades CondRetEsp
*     =armazenaramizades               	inxPerfil	vetPerfil	CondRetEsp 					
*		- a fun��o armazenar amizades compara apenas 3 perfis
*     =excluirtodasamizades             inxPerfil	CondRetEsp
*     =verificaramizades                inxPerfil1 	inxPerfil2 	existeAmizade CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{

	int inxPerfil = -1 ,
		inxPerfil1 = -1 ,
		inxPerfil2 = -1 ,
		numLidos   = -1 ,
		CondRetEsp = -1  ;
	AMI_tpCondRet CondRet ;
	GRA_tpCondRet GRA_CondRetCriarGrafo;

	int i ;
	AMI_tpSolitacao Solicitacao;
	int numAmigos = -1;

	
	PER_tpCondRet PER_CondRetCriarPerfil;

	
	char * vtEmail  	[DIM_VT_EMAIL] = {"usuario1@gmail.com", "usuario2@gmail.com", "usuario3@gmail.com", "usuario4@gmail.com", "usuario5@gmail.com",
									  "usuario6@gmail.com", "usuario7@gmail.com", "usuario8@gmail.com"};
	char * vtPrimNome 	[DIM_VT_PRIMNOME] = {"UsuarioA", "UsuarioB", "UsuarioC", "UsuarioD", "UsuarioE", "UsuarioF", "UsuarioG", "UsuarioH"};
	char * vtUltNome 	[DIM_VT_ULTNOME] = {"SobrenomeA", "SobrenomeB", "SobrenomeC", "SobrenomeD", "SobrenomeE", "SobrenomeF", "SobrenomeG", "SobrenomeH"};
	char * vtCidade 	[DIM_VT_CIDADE] = {"CidadeA", "CidadeB", "CidadeC", "CidadeD", "CidadeE", "CidadeF", "CidadeG", "CidadeH"};
	int  vtDia 			[DIM_VT_DIA] = {1, 2, 3, 4, 5, 6, 7, 8};
	int  vtMes 			[DIM_VT_MES] = {1, 2, 3, 4, 5, 6, 7, 8};
	int  vtAno 			[DIM_VT_ANO] = {2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008};
	

	

	/* Efetuar reset de teste de Amizade */
	
	if ( strcmp( ComandoTeste , RESET_AMIZADE_CMD ) == 0 )
	{

			GRA_DestruirGrafo(vtGrafos[0]);
			GRA_CondRetCriarGrafo = GRA_CriarGrafo(DestruirValor, &vtGrafos[0]);
			if (GRA_CondRetCriarGrafo == GRA_CondRetFaltouMemoria){
				return TST_CondRetMemoria;
				}
			
	
			for (i = 0; i < DIM_VT_PERFIL  ; i++ ){
			PER_CondRetCriarPerfil = PER_CriarPerfil(vtGrafos[0], &vtPerfil[i], vtEmail[i], vtPrimNome[i], vtUltNome[i],
							  vtDia[i], vtMes[i], vtAno[i], vtCidade[i]);
			if (PER_CondRetCriarPerfil == PER_CondRetFaltouMemoria){
				return TST_CondRetMemoria;
				}
			}


		return TST_CondRetOK ;

	} /* fim ativa: Efetuar reset de teste de Amizade */
	
	/* Testar Criar Amizade */

	else if ( strcmp( ComandoTeste , CRIAR_AMIZADE_CMD ) == 0 )
	{

	
		TST_tpCondRet debug;


		numLidos = LER_LerParametros( "iiii" ,&inxPerfil1, &inxPerfil2, &Solicitacao, &CondRetEsp ) ;
		
		if ( ( numLidos != 4 ) || ( ! ValidarInxPerfil( inxPerfil1)) || ( ! ValidarInxPerfil( inxPerfil2))){
			return TST_CondRetParm ;
		} /* if */

		CondRet = AMI_CriarAmizade(vtGrafos[0], vtPerfil[inxPerfil1], vtPerfil[inxPerfil2], Solicitacao);

		debug =  TST_CompararInt( CondRetEsp , CondRet ,
			"Erro na condicao de retorno ao criar o Amizade" ) ;
		if (debug != TST_CondRetOK){
			return debug;
		}
		

		return TST_CondRetOK;
		
	} /* fim ativa: Testar Criar Amizade */


	/* Testar Excluir Amizade */

	else if ( strcmp( ComandoTeste , EXCLUIR_AMIZADE_CMD ) == 0 )
	{
		
        numLidos = LER_LerParametros("iii" , &inxPerfil1, &inxPerfil2, &CondRetEsp) ;
		if (( numLidos != 3 ) || ( ! ValidarInxPerfil( inxPerfil1)) || ( ! ValidarInxPerfil( inxPerfil2))){
			return TST_CondRetParm ;
		} /* if */


		CondRet = AMI_ExcluirAmizade(vtGrafos[0], vtPerfil[inxPerfil1], vtPerfil[inxPerfil2]);

		
		return TST_CompararInt( CondRetEsp , CondRet ,
            "Condicao de retorno errada ao excluir amizade.") ;

    }  /* fim ativa: Testar Excluir Amizade */

	
	/* Testar Verificar N�mero de Amigos*/

	else if ( strcmp( ComandoTeste , VERIFICAR_NUM_AMIGOS_CMD ) == 0 )
	{	
		TST_tpCondRet NumAmigosCondRet; 
		TST_tpCondRet debug;
		int numAmigosFuncao;
		
		numLidos = LER_LerParametros( "iii" , &inxPerfil1, &numAmigos, &CondRetEsp ) ;
		if ( ( numLidos != 3 )|| (!ValidarInxPerfil( inxPerfil1))){
			return TST_CondRetParm ;
		} /* if */


		CondRet = AMI_VerificarNumAmigos(vtGrafos[0], vtPerfil[inxPerfil1], &numAmigosFuncao);


		NumAmigosCondRet = TST_CompararInt( CondRetEsp , CondRet ,
			"Condicao de retorno errada ao verificar n�mero de amigos." ) ;
			
		if (NumAmigosCondRet != TST_CondRetOK){
			return NumAmigosCondRet;
		}

		debug = TST_CompararInt(numAmigos, numAmigosFuncao, "Numero de amigos diferente do esperado.");

		if (debug != TST_CondRetOK){
			return debug;
		}
		
		return TST_CondRetOK;

	} /* fim ativa: Testar Verificar N�mero de Amigos */

	
	/* Testar armazenar amizades */

	else if ( strcmp( ComandoTeste , ARMAZENAR_AMIZADES_CMD ) == 0 )
	{
	

		TST_tpCondRet TST_CondRetVerifica;
		TST_tpCondRet debug;
		
		char * emailRetornado1;
		char * primNomeRetornado1;
		char * ultNomeRetornado1;
		char * cidadeRetornado1;
		int diaRetornado1;
		int mesRetornado1;
		int anoRetornado1;
		
		char * emailRetornado2;
		char * primNomeRetornado2;
		char * ultNomeRetornado2;
		char * cidadeRetornado2;
		int diaRetornado2;
		int mesRetornado2;
		int anoRetornado2;
		
		char * emailRetornado3;
		char * primNomeRetornado3;
		char * ultNomeRetornado3;
		char * cidadeRetornado3;
		int diaRetornado3;
		int mesRetornado3;
		int anoRetornado3;

		char email1[50];
		char primNome1[50];
		char ultNome1[50];
		char cidade1[50];
		int dia1;
		int mes1;
		int ano1;
	
		char email2[50];
		char primNome2[50];
		char ultNome2[50];
		char cidade2[50];
		int dia2;
		int mes2;
		int ano2;
	
		char email3[50];
		char primNome3[50];
		char ultNome3[50];
		char cidade3[50];
		int dia3;
		int mes3;
		int ano3;

		
		if ((emailRetornado1 = (char *)malloc(sizeof(char)*50)) == NULL){
			return TST_CondRetMemoria;
		}
		if ((primNomeRetornado1 = (char *)malloc(sizeof(char)*50)) == NULL){
			return TST_CondRetMemoria;
		}
		if ((ultNomeRetornado1 = (char *)malloc(sizeof(char)*50)) == NULL){
			return TST_CondRetMemoria;
		}
		if ((cidadeRetornado1 = (char *)malloc(sizeof(char)*50)) == NULL){
			return TST_CondRetMemoria;
		}
		if ((emailRetornado2 = (char *)malloc(sizeof(char)*50)) == NULL){
			return TST_CondRetMemoria;
		}
		if ((primNomeRetornado2 = (char *)malloc(sizeof(char)*50)) == NULL){
			return TST_CondRetMemoria;
		}
		if ((ultNomeRetornado2 = (char *)malloc(sizeof(char)*50)) == NULL){
			return TST_CondRetMemoria;
		}
		if ((cidadeRetornado2 = (char *)malloc(sizeof(char)*50)) == NULL){
			return TST_CondRetMemoria;
		}
		if ((emailRetornado3 = (char *)malloc(sizeof(char)*50)) == NULL){
			return TST_CondRetMemoria;
		}
		if ((primNomeRetornado3 = (char *)malloc(sizeof(char)*50)) == NULL){
			return TST_CondRetMemoria;
		}
		if ((ultNomeRetornado3 = (char *)malloc(sizeof(char)*50)) == NULL){
			return TST_CondRetMemoria;
		}
		if ((cidadeRetornado3 = (char *)malloc(sizeof(char)*50)) == NULL){
			return TST_CondRetMemoria;
		}
		
		numLidos = LER_LerParametros( "issssiiissssiiissssiiii" ,
			&inxPerfil1, email1, primNome1, ultNome1, cidade1, &dia1, &mes1, &ano1,
						 email2, primNome2, ultNome2, cidade2, &dia2, &mes2, &ano2,
						 email3, primNome3, ultNome3, cidade3, &dia3, &mes3, &ano3, &CondRetEsp );
						 

		if (( numLidos != 23 ) || (!ValidarInxPerfil( inxPerfil1)))
		{
			return TST_CondRetParm ;
		}
		



		CondRet = AMI_ArmazenarAmizades(vtGrafos[0], vtPerfil[inxPerfil1], vtPerfilTeste);
	

		TST_CondRetVerifica = TST_CompararInt( CondRetEsp, CondRet,
			"Condi��o de retorno errada ao armazenar amizades."   );
			
		if (TST_CondRetVerifica != TST_CondRetOK){
			return TST_CondRetVerifica;
		}

		if(CondRet!=AMI_CondRetOK)
			return CondRet;

			
			PER_ObterPerfil(vtPerfilTeste[0], emailRetornado1, primNomeRetornado1, ultNomeRetornado1,
							  &diaRetornado1, &mesRetornado1, &anoRetornado1, cidadeRetornado1);
	

		
			debug = TST_CompararString(email1, emailRetornado1, "Campo email nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararString(primNome1, primNomeRetornado1, "Campo primeiro nome nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararString(ultNome1, ultNomeRetornado1, "Campo ultimo nome nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararString(cidade1, cidadeRetornado1, "Campo cidade nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararInt( dia1, diaRetornado1, "Campo dia nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararInt( mes1, mesRetornado1, "Campo mes nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararInt( ano1, anoRetornado1, "Campo ano nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			

			PER_ObterPerfil(vtPerfilTeste[1], emailRetornado2, primNomeRetornado2, ultNomeRetornado2,
							  &diaRetornado2, &mesRetornado2, &anoRetornado2, cidadeRetornado2);

			debug = TST_CompararString(email2, emailRetornado2, "Campo email nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararString(primNome2, primNomeRetornado2, "Campo primeiro nome nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararString(ultNome2, ultNomeRetornado2, "Campo ultimo nome nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararString(cidade2, cidadeRetornado2, "Campo cidade nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararInt( dia2, diaRetornado2, "Campo dia nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararInt( mes2, mesRetornado2, "Campo mes nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararInt( ano2, anoRetornado2, "Campo ano nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			

			PER_ObterPerfil(vtPerfilTeste[2], emailRetornado3, primNomeRetornado3, ultNomeRetornado3,
							  &diaRetornado3, &mesRetornado3, &anoRetornado3, cidadeRetornado3);

		
			debug = TST_CompararString(email3, emailRetornado3, "Campo email nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararString(primNome3, primNomeRetornado3, "Campo primeiro nome nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararString(ultNome3, ultNomeRetornado3, "Campo ultimo nome nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararString(cidade3, cidadeRetornado3, "Campo cidade nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararInt( dia3, diaRetornado3, "Campo dia nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararInt( mes3, mesRetornado3, "Campo mes nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}
			debug = TST_CompararInt( ano3, anoRetornado3, "Campo ano nao e igual ao esperado");
			if (debug != TST_CondRetOK){
				return debug;
			}

		free(emailRetornado1);
		free(cidadeRetornado1);
		free(ultNomeRetornado1);

		free(primNomeRetornado2);
		free(emailRetornado2);
		free(cidadeRetornado2);
		free(ultNomeRetornado2);

		free(primNomeRetornado3);
		free(emailRetornado3);
		free(cidadeRetornado3);
		free(ultNomeRetornado3);

	
		return TST_CondRetOK;
	
	} /* fim ativa: Testar armazenar amizades */

	
	/* Testar excluir Todas as Amizades */
	else if ( strcmp( ComandoTeste , EXCLUIR_TODAS_AMIZADES_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii" ,
			&inxPerfil, &CondRetEsp ) ;

		if (( numLidos != 2 )|| (!ValidarInxPerfil( inxPerfil)))
		{
			return TST_CondRetParm ;
		} /* if */
		

		CondRet = AMI_ExcluirTodasAmizades(vtGrafos[0], vtPerfil[inxPerfil]);

		return TST_CompararInt( CondRetEsp , CondRet ,
			"Condicao de retorno errada ao excluir todas as amizades." ) ;

	} /* fim ativa: Testar excluir Todas as Amizades */


	/* Testar verificar amizade */
	else if ( strcmp( ComandoTeste , VERIFICAR_AMIZADES_CMD ) == 0 )
	{

		
		TST_tpCondRet debug;
		
		numLidos = LER_LerParametros( "iii" ,
			&inxPerfil1,&inxPerfil2, &CondRetEsp ) ;


		if (( numLidos != 3 ) || (!ValidarInxPerfil( inxPerfil1))|| (!ValidarInxPerfil( inxPerfil2)))
		{
			return TST_CondRetParm ;
		} /* if */

		CondRet = AMI_VerificarAmizade(vtGrafos[0], vtPerfil[inxPerfil1], vtPerfil[inxPerfil2]);

		
		debug =  TST_CompararInt( CondRetEsp , CondRet ,
			"Condicao de retorno errada ao verificar amizade." ) ;
		if (debug != TST_CondRetOK){
			return debug;
		}
		

		return TST_CondRetOK;

	} /* fim ativa: Testar verificar amizade */


	return TST_CondRetNaoConhec; 

}
 /* Fim fun��o: TAMI &Testar Amizade */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TAMI -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim fun��o: TAMI -Destruir valor */



/***********************************************************************
*
*  $FC Fun��o: TAMI -Validar indice de Perfil
*
***********************************************************************/

int ValidarInxPerfil( int inxPerfil)
{

	if ( ( inxPerfil <  0 )
		|| ( inxPerfil >= DIM_VT_PERFIL ))
	{
		return FALSE ;
	} /* if */

	return TRUE ;

} /* Fim fun��o: TAMI -Validar indice de Perfil */


/********** Fim do m�dulo de implementa��o: TAMI Teste m�dulo Amizade **********/

