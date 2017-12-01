/***************************************************************************
*  $MCI Módulo de implementação: TMEN Teste do modulo mensagem
*
*  Arquivo gerado:              TESTEMENSAGEM.c
*  Letras identificadoras:      TMEN
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Mensagem.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gb, ms, rm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*           rm/ms/gb   16/10/2017 	revisoes finais e pequenas correcoes
*     8       gb   15/out/2017 ALTERAÇÕES
*     7       gb   14/out/2017 ALTERAÇÕES
*     6       gb   01/out/2017 implementacao dos testes da funcao ObterTamanho e utilizando uma estrutura que guarde Nome, Data, Cidade e Email.
*     5       gb   01/out/2017 modificacao no módulo de teste para que as funções do módulo Grafo retornem uma condição de retorno
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"
#include    "MENSAGEM.h"




static const char ESCREVER_MSG_CMD        [ ] = "=escrevermsg"     ;
static const char EXCLUIR_MSG_CMD         [ ] = "=excluirmsg"     ;
static const char EXCLUIR_MSGEMAIL_CMD    [ ] = "=excluirmsgemail"     ;
static const char OBTER_NUM_MSGS_CMD      [ ] = "=obternummsgs"  ;
static const char OBTER_NUM_TODASMSGS_CMD [ ] = "=obternumtodasmsgs"  ;
static const char OBTER_MSGS_CMD          [ ] = "=obtermsgs"   ;
static const char OBTER_TODASMSGS_CMD     [ ] ="=obtertodasmsgs"   ;





#define TRUE  1
#define FALSE 0

#define DIM_VT_PERFIL  8




PER_tpPerfil *   vtPerfis[ DIM_VT_PERFIL ] ;

/***** Protótipos das funções encapuladas no módulo *****/


static int ValidarInxPerfil( int InxPerfil) ;


/*****  Código das funções exportadas pelo módulo  *****/
/***********************************************************************
*
*  $FC Função: TMEN &Testar modulo de mensagnes
*
*  $ED Descrição da função
*     Podem ser criadas até 8 perfis, identificadas pelos índices 0 a 7.
*	  Esses perfis serao passados para as funcoes do modulo MENSAGEM que
*	  serao testadas.
*
*     Comandos disponíveis:
*
*     =escrevermsg                  inxPerfilRemetente inxPerfilDestinatario MensagemEnv CondRetEsp
*     =excluirmsg	                inxPerfil Email FlagMsg Mensagem CondRetEsp
*	  =excluirmsgemail              inxPerfil Email CondRetEsp
*     =obternummsgs                 inxPerfil FlagMsg numElem  CondRetEsp
*     =obternumtodasmsgs            inxPerfil numElem  CondRetEsp
*     =obtermsgs                    inxPerfil tamVetor vetTipos  vetEmails vetMensagens FlagMsg CondRetEsp - Compara os dados recebidos e esperados de até 2 mensagens de um perfil
*     =obtertodasmsgs               inxPerfil tamVetor vetTipos  vetEmails vetMensagens CondRetEsp - Compara os dados recebidos e esperados de até 2 mensagens de um perfil
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{

	int inxPerfil  = -1 ,
		inxPerfilRemetente =-1,
		inxPerfilDestinatario=-1,
		numLidos   = -1 ,
		CondRetEsp = -1  ;
	TST_tpCondRet CondRet ;
	MEN_tpCondRet FlagMsg;

	char Mensagem[400];
	char Email[100];
	char EmailRet[100];
	char DataRet[12];

	char NomeEsp[100];
	char CidadeEsp[50];
	char EmailEsp[100];
	char DataEsp[12];



	int i ;

	int numElem = -1 ;

	char * vtEmail  	[DIM_VT_PERFIL] = {"usuario1@gmail.com", "usuario2@gmail.com", "usuario3@gmail.com", "usuario4@gmail.com", "usuario5@gmail.com",
									  "usuario6@gmail.com", "usuario7@gmail.com", "usuario8@gmail.com"};
	char * vtPrimNome 	DIM_VT_PERFIL] = {"UsuarioA", "UsuarioB", "UsuarioC", "UsuarioD", "UsuarioE", "UsuarioF", "UsuarioG", "UsuarioH"};
	char * vtUltNome 	[DIM_VT_PERFIL] = {"SobrenomeA", "SobrenomeB", "SobrenomeC", "SobrenomeD", "SobrenomeE", "SobrenomeF", "SobrenomeG", "SobrenomeH"};
	char * vtCidade 	[DIM_VT_PERFIL] = {"CidadeA", "CidadeB", "CidadeC", "CidadeD", "CidadeE", "CidadeF", "CidadeG", "CidadeH"};
	int  vtDia 			[DIM_VT_PERFIL] = {1, 2, 3, 4, 5, 6, 7, 8};
	int  vtMes 			[DIM_VT_PERFIL] = {1, 2, 3, 4, 5, 6, 7, 8};
	int  vtAno 			[DIM_VT_PERFIL] = {2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008};

	for (i = 0; i < DIM_VT_PERFIL  ; i++ ){
		PER_CondRetCriarPerfil = PER_CriarPerfil(vtGrafos[0], &vtPerfil[i], vtEmail[i], vtPrimNome[i], vtUltNome[i],
							  vtDia[i], vtMes[i], vtAno[i], vtCidade[i]);
		if (PER_CondRetCriarPerfil == PER_CondRetFaltouMemoria){
			return TST_CondRetMemoria;
			}
		}
	/* Testar Escrever Mensagem */
	 if ( strcmp( ComandoTeste , ESCREVER_MSG_CMD  ) == 0 )
	{

		numLidos = LER_LerParametros( "iisi" ,
			&inxPerfilRemetente,&inxPerfilDestinatario,Mensagem, &CondRetEsp ) ;

		if ( ( numLidos != 4 )
			|| ( ! ValidarInxPerfil( inxPerfilRemetente)) || ( ! ValidarInxPerfil( inxPerfilDestinatario)) )
		{
			return TST_CondRetParm ;
		} /* if */

		CondRet=MEN_EscreverMensagem(vtPerfis[inxPerfilRemetente],VetPerfis[inxPerfilDestinatario],Mensagem) ;

		return TST_CompararInt( CondRetEsp , CondRet ,
			"Erro na condicao de retorno ao escrever mensagem"  ) ;

	} /* fim ativa: Testar Escrever Mensagem */


	/* Testar Excluir Mensagem */

	else if ( strcmp( ComandoTeste , EXCLUIR_MSG_CMD ) == 0 )
	{

			MEN_tpCondRet debug;
            numLidos = LER_LerParametros( "iissi" ,
            &inxPerfil,&FlagMsg,Email,Mensagem,&CondRetEsp ) ;
            if ( ( numLidos != 4 )
              || ( ! ValidarInxPerfil( InxPerfil)))
            {
               return TST_CondRetParm ;
            } /* if */
            debug=MEN_ExcluirMensagem( vtPerfis[InxPerfil],Email,FlagMsg,Mensagem) ;
			return TST_CompararInt( CondRetEsp , CondRet ,
			"Erro na condicao de retorno ao excluir mensagem"  ) ;
           

      }  /* fim ativa: Testar Excluir Mensagem */

		/* Testar Excluir Mensagens de um Email */

	else if ( strcmp( ComandoTeste , EXCLUIR_MSG_CMD ) == 0 )
	{

			MEN_tpCondRet debug;
            numLidos = LER_LerParametros( "isi" ,
            &inxPerfil,Email,,&CondRetEsp ) ;
            if ( ( numLidos != 3 )
              || ( ! ValidarInxPerfil( InxPerfil)))
            {
               return TST_CondRetParm ;
            } /* if */
            debug=MEN_ExcluirMensagensEmail(vtPerfis[InxPerfil],Email) ;
			return TST_CompararInt( CondRetEsp , CondRet ,
			"Erro na condicao de retorno ao excluir mensagem de um email"  ) ;
           

      }  /* fim ativa: Testar Excluir Mensagens de um Email */

	/* Testar Obter Numero de Mensagens */

	else if ( strcmp( ComandoTeste , OBTER_NUM_MSGS_CMD  ) == 0 )
	{

			 MEN_tpCondRet debugMEN;
			 int numRet;

            numLidos = LER_LerParametros( "iiii" , &InxPerfil ,&FlagMsg, &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxPerfil( InxPerfil )) )
            {
               return TST_CondRetParm ;
            } /* if */

			debugMEN=MEN_ObterNumMensagens(vtPerfis[InxPerfil], FlagMsg,&numRet);
			CondRet= TST_CompararInt( CondRetEsp , debugMEN,
            "Condicao de retorno errada ao obter numero de mensagens" ) ;

			if (CondRet != TST_CondRetOK) {
				return CondRet;
			}

			return TST_CompararInt( numElem , numRet
                       , "Numero de elementos retornado inesperado" ) ;


	} /* fim ativa: Obter Numero de Mensagens  */

	/* Testar Obter Numero Total de Mensagens */

	else if ( strcmp( ComandoTeste , OBTER_NUM_TODASMSGS_CMD ) == 0 )
	{
			 MEN_tpCondRet debugMEN;
			 int numRet;

            numLidos = LER_LerParametros( "iii" , &InxPerfil, &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxPerfil( InxPerfil )) )
            {
               return TST_CondRetParm ;
            } /* if */

			debugMEN=MEN_ObterNumTodasMensagens(vtPerfis[InxPerfil],&numRet);
			CondRet= TST_CompararInt( CondRetEsp , debugMEN,
            "Condicao de retorno errada ao obter numero de todas mensagens" ) ;

			if (CondRet != TST_CondRetOK) {
				return CondRet;
			}

			return TST_CompararInt( numElem , numRet
                       , "Numero de elementos retornado inesperado" ) ;

	} /* fim ativa: Obter Numero Total de Mensagens */

	/* Testar Obter Mensagens  */

	else if ( strcmp( ComandoTeste , OBTER_MSGS_CMD   ) == 0 )
	{
		int tamVetor,i;
		char* vetEmailsEsp[2];
		char* vetMensagensEsp[2];
		char** vetEmails;
		char** vetMensagens;
		MEN_tpCondRet debugMEN;

		numLidos = LER_LerParametros( "iissssii" , &InxPerfil,&tamVetor,&vetEmailsEsp[0],&vetMensagensEsp[0],
		&vetEmailsEsp[1],&vetMensagensEsp[1],&FlagMsg,&CondRetEsp) ;

		if ( ( numLidos != 8  )
			|| ( ! ValidarInxPerfil( InxPerfil )) || (tamVetor>2 ) || (tamVetor<0))
		{
			return TST_CondRetParm ;
		} /* Alocando os vetores */

		vetEmails=(char**)malloc(tamVetor*sizeof(char));
		if ( vetEmails == NULL )
		{
			return TST_CondRetMemoria ;
		} 	
		vetEmails[0]=(char*)malloc(101*sizeof(char));
		if ( vetEmails[0] == NULL )
		{
			return TST_CondRetMemoria ;
		} 
		vetEmails[1]=(char*)malloc(101*sizeof(char));
		if ( vetEmails[1] == NULL )
		{
			return TST_CondRetMemoria ;
		} 	

		vetMensagens=(char**)malloc(tamVetor*sizeof(char));
		if ( vetMensagens == NULL )
		{
			return TST_CondRetMemoria ;
		} 
		vetMensagens[0]=(char*)malloc(401*sizeof(char));
		if ( vetMensagens[0] == NULL )
		{
			return TST_CondRetMemoria ;
		} 
		vetMensagens[1]=(char*)malloc(401*sizeof(char));
		if ( vetMensagens[1] == NULL )
		{
			return TST_CondRetMemoria ;
		} 


		debugMEN=MEN_ObterMensagens(vtPerfis[InxPerfil],vetEmails,vetMensagens,&FlagMsg);

		CondRet=TST_CompararInt( CondRetEsp ,debugMEN  ,
			"Condição de retorno errada ao obter mensagens."   ) ;

		if (CondRet != TST_CondRetOK) {
				return CondRet;
			}
		if(tamVetor==0 && debugMEN==MEN_CondRetListaVazia)
			return TST_CondRetOK;


		for(i=0;i<tamVetor;i++)
		{
			CondRet=TST_CompararString( vetEmailsEsp[i] ,vetEmails[i]  ,
			"Email nao e igual ao esperado" ) ;
			if (CondRet != TST_CondRetOK) {
				free(vetEmails[0]);
				free(vetEmails[1]);
				free(vetEmails);
				free(vetMensagens[0]);
				free(vetMensagens[1]);
				free(vetMensagens);
				return CondRet;
			}
			CondRet=TST_CompararString( vetMensagensEsp[i] ,vetMensagens[i]  ,
			"Mensagem nao e igual  a esperada" ) ;
			if (CondRet != TST_CondRetOK) {
				free(vetEmails[0]);
				free(vetEmails[1]);
				free(vetEmails);
				free(vetMensagens[0]);
				free(vetMensagens[1]);
				free(vetMensagens);
				return CondRet;
			}
		}
		free(vetTipos);
		free(vetEmails[0]);
		free(vetEmails[1]);
		free(vetEmails);
		free(vetMensagens[0]);
		free(vetMensagens[1]);
		free(vetMensagens);
		return TST_CondRetOK;

	} /* fim ativa: Obter Mensagens */

	/* Testar Obter Todas Mensagens */

		else if ( strcmp( ComandoTeste , OBTER_TODASMSGS_CMD ) == 0 )
	{
		int tamVetor,i;
		int vetTiposEsp[2];
		char* vetEmailsEsp[2];
		char* vetMensagensEsp[2];
		int* vetTipos;
		char** vetEmails;
		char** vetMensagens;
		MEN_tpCondRet debugMEN;

		numLidos = LER_LerParametros( "iiississi" , &InxPerfil,&tamVetor,&vetTiposEsp[0],&vetEmailsEsp[0],&vetMensagensEsp[0],
		&vetTiposEsp[1],&vetEmailsEsp[1],&vetMensagensEsp[1],&CondRetEsp) ;

		if ( ( numLidos != 9  )
			|| ( ! ValidarInxPerfil( InxPerfil )) || (tamVetor>2 ) || (tamVetor<0))
		{
			return TST_CondRetParm ;
		} /* Alocando os vetores */
		vetTipos=(int*)malloc(tamVetor*sizeof(int));
		if ( vetTipos == NULL )
		{
			return TST_CondRetMemoria ;
		} 


		vetEmails=(char**)malloc(tamVetor*sizeof(char));
		if ( vetEmails == NULL )
		{
			return TST_CondRetMemoria ;
		} 	
		vetEmails[0]=(char*)malloc(101*sizeof(char));
		if ( vetEmails[0] == NULL )
		{
			return TST_CondRetMemoria ;
		} 
		vetEmails[1]=(char*)malloc(101*sizeof(char));
		if ( vetEmails[1] == NULL )
		{
			return TST_CondRetMemoria ;
		} 	

		vetMensagens=(char**)malloc(tamVetor*sizeof(char));
		if ( vetMensagens == NULL )
		{
			return TST_CondRetMemoria ;
		} 
		vetMensagens[0]=(char*)malloc(401*sizeof(char));
		if ( vetMensagens[0] == NULL )
		{
			return TST_CondRetMemoria ;
		} 
		vetMensagens[1]=(char*)malloc(401*sizeof(char));
		if ( vetMensagens[1] == NULL )
		{
			return TST_CondRetMemoria ;
		} 


		debugMEN=MEN_ObterTodasMensagens(vtPerfis[InxPerfil],vetTipos,vetEmails,vetMensagens);

		CondRet=TST_CompararInt( CondRetEsp ,debugMEN  ,
			"Condição de retorno errada ao obter mensagens."   ) ;

		if (CondRet != TST_CondRetOK) {
				return CondRet;
			}
		if(tamVetor==0 && debugMEN==MEN_CondRetListaVazia)
			return TST_CondRetOK;


		for(i=0;i<tamVetor;i++)
		{
			CondRet=TST_CompararInt( vetTiposEsp[i] ,vetTipos[i]  ,
			"Tipo da mensagem nao e igual ao esperado" ) ;
			if (CondRet != TST_CondRetOK) {
				free(vetTipos);
				free(vetEmails[0]);
				free(vetEmails[1]);
				free(vetEmails);
				free(vetMensagens[0]);
				free(vetMensagens[1]);
				free(vetMensagens);
				return CondRet;
			}
			CondRet=TST_CompararString( vetEmailsEsp[i] ,vetEmails[i]  ,
			"Email nao e igual ao esperado" ) ;
			if (CondRet != TST_CondRetOK) {
				free(vetTipos);
				free(vetEmails[0]);
				free(vetEmails[1]);
				free(vetEmails);
				free(vetMensagens[0]);
				free(vetMensagens[1]);
				free(vetMensagens);
				return CondRet;
			}
			CondRet=TST_CompararString( vetMensagensEsp[i] ,vetMensagens[i]  ,
			"Mensagem nao e igual  a esperada" ) ;
			if (CondRet != TST_CondRetOK) {
				free(vetTipos);
				free(vetEmails[0]);
				free(vetEmails[1]);
				free(vetEmails);
				free(vetMensagens[0]);
				free(vetMensagens[1]);
				free(vetMensagens);
				return CondRet;
			}
		}
		free(vetTipos);
		free(vetEmails[0]);
		free(vetEmails[1]);
		free(vetEmails);
		free(vetMensagens[0]);
		free(vetMensagens[1]);
		free(vetMensagens);
		return TST_CondRetOK;

	} /* fim ativa: Obter Todas Mensagens  */
	
	return TST_CondRetNaoConhec;
}

 /* Fim função: TMEN &Testar modulo de mensagnes */


/*****  Código das funções encapsuladas no módulo  *****/





/***********************************************************************
*
*  $FC Função: TMEN -Validar indice de um Perfil
*
***********************************************************************/

int ValidarInxPerfil( int InxPerfil)
{

	if ( ( InxPerfil <  0 )
		|| ( InxPerfil >= DIM_VT_Perfil ))
	{
		return FALSE ;
	} /* if */

	return TRUE ;

} /* Fim função: TMEN -Validar indice de um Perfil */




/********** Fim do módulo de implementação: TMEN Teste do modulo mensagem **********/

