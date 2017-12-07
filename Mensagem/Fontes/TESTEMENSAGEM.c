/***************************************************************************
*  $MCI MÛdulo de implementaÁ„o: TMEN Teste do modulo mensagem
*
*  Arquivo gerado:              TESTEMENSAGEM.c
*  Letras identificadoras:      TMEN
*
*  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Mensagem.BSW
*
*  Projeto: INF 1301 / 1628 AutomatizaÁ„o dos testes de mÛdulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Gabriel Busquim (gb), Michelle santiago(ms)
*
*  $HA HistÛrico de evoluÁ„o:
*     Vers„o  Autor     Data      ObservaÁıes
*       3       ms    06/11/2017  revisoes finais e pequenas correcoes
*       2       gb    02/11/2017  alteração na descrição das funções
*       1       gb    01/11/2017  inicio do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"
#include    "MENSAGEM.h"
#include     "perfil.h"

static const char RESET_MENSAGEM_CMD		[ ] = "=resetteste";
static const char ESCREVER_MSG_CMD        	[ ] = "=escrevermsg";
static const char EXCLUIR_MSG_CMD         	[ ] = "=excluirmsg";
static const char EXCLUIR_MSGEMAIL_CMD    	[ ] = "=excluirmsgemail";
static const char MODIFICAR_EMAIL_CMD    	[ ] = "=modificaremail";
static const char OBTER_NUM_MSGS_CMD      	[ ] = "=obternummsgs";
static const char OBTER_NUM_TODASMSGS_CMD 	[ ] = "=obternumtodasmsgs";
static const char OBTER_MSGS_CMD          	[ ] = "=obtermsgs";
static const char OBTER_TODASMSGS_CMD     	[ ] ="=obtertodasmsgs";

#define TRUE  1
#define FALSE 0

#define DIM_VT_PERFIL  8

PER_tpPerfil * vtPerfis[ DIM_VT_PERFIL ] ;

/***** ProtÛtipos das funÁıes encapuladas no mÛdulo *****/

static void DestruirValor( void * pValor );
static int ValidarInxPerfil( int InxPerfil) ;


/*****  CÛdigo das funÁıes exportadas pelo mÛdulo  *****/
/***********************************************************************
*
*  $FC FunÁ„o: TMEN &Testar modulo de mensagnes
*
*  $ED DescriÁ„o da funÁ„o
*     Podem ser criadas atÈ 8 perfis, identificadas pelos Ìndices 0 a 7.
*	  Esses perfis serao passados para as funcoes do modulo MENSAGEM que
*	  serao testadas.
*
*     Comandos disponÌveis:
*	  =resetteste					Destroi o grafo e cria novamente os perfis
*     =escrevermsg                  InxPerfilRemetente InxPerfilDestinatario MensagemEnv CondRetEsp
*     =excluirmsg	                InxPerfil Email FlagMsg Mensagem CondRetEsp
*	  =excluirmsgemail              InxPerfil Email CondRetEsp
*     =obternummsgs                 InxPerfil FlagMsg numElem  CondRetEsp
*     =obternumtodasmsgs            InxPerfil numElem  CondRetEsp
*     =obtermsgs                    InxPerfil  vetTipos  vetEmails vetMensagens FlagMsg CondRetEsp 
*			- Compara os dados recebidos e esperados para listas de exatamente 2 elementos do tipo procurado
*     =obtertodasmsgs               InxPerfil  vetTipos  vetEmails vetMensagens CondRetEsp - 
*			- Compara os dados recebidos e esperados para listas de exatamente 2 elementos
*	  =modificaremail				InxPerfil  Email	novoEmail CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{

	int InxPerfil  = -1 ,
		InxPerfilRemetente =-1,
		InxPerfilDestinatario=-1,
		numLidos   = -1 ,
		CondRetEsp = -1  ;
	TST_tpCondRet CondRet=-1 ;
	MEN_tpCondRet FlagMsg;
	GRA_tpCondRet GRA_CondRetCriarGrafo;
	GRA_tppGrafo gr = NULL;
	PER_tpCondRet PER_CondRetCriarPerfil;
	char Mensagem[400];
	char Email[100];
	
	int i ;

	int numElem = -1 ;
	char * vtEmail  	[DIM_VT_PERFIL] = {"usuario1@gmail.com", "usuario2@gmail.com", "usuario3@gmail.com", 
										   "usuario4@gmail.com", "usuario5@gmail.com","usuario6@gmail.com", 
										   "usuario7@gmail.com", "usuario8@gmail.com"};
	char * vtPrimNome 	[DIM_VT_PERFIL] = {"UsuarioA", "UsuarioB", "UsuarioC", "UsuarioD", "UsuarioE", 
										   "UsuarioF", "UsuarioG", "UsuarioH"};
	char * vtUltNome 	[DIM_VT_PERFIL] = {"SobrenomeA", "SobrenomeB", "SobrenomeC", "SobrenomeD", 
										   "SobrenomeE", "SobrenomeF", "SobrenomeG", "SobrenomeH"};
	char * vtCidade 	[DIM_VT_PERFIL] = {"CidadeA", "CidadeB", "CidadeC", "CidadeD", "CidadeE", 
										   "CidadeF", "CidadeG", "CidadeH"};
	int  vtDia 			[DIM_VT_PERFIL] = {1, 2, 3, 4, 5, 6, 7, 8};
	int  vtMes 			[DIM_VT_PERFIL] = {1, 2, 3, 4, 5, 6, 7, 8};
	int  vtAno 			[DIM_VT_PERFIL] = {2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008};

	/* Efetuar reset de teste de mensagem */
	
	if ( strcmp( ComandoTeste , RESET_MENSAGEM_CMD ) == 0 )
	{
			GRA_DestruirGrafo(gr);
			GRA_CondRetCriarGrafo = GRA_CriarGrafo(DestruirValor, &gr);
			if (GRA_CondRetCriarGrafo == GRA_CondRetFaltouMemoria)
				return TST_CondRetMemoria;
			
			for (i = 0; i < DIM_VT_PERFIL  ; i++ ){
				PER_CondRetCriarPerfil = PER_CriarPerfil(gr, &vtPerfis[i], vtEmail[i], vtPrimNome[i], 
												 vtUltNome[i],vtDia[i], vtMes[i], vtAno[i], vtCidade[i]);
				if (PER_CondRetCriarPerfil == PER_CondRetFaltouMemoria)
					return TST_CondRetMemoria;
			} /* if */

		return TST_CondRetOK ;
	} /* if */
	
	/* fim ativa: Efetuar reset de teste de mensagem */

	
	/* Testar Escrever Mensagem */

	 else if ( strcmp( ComandoTeste , ESCREVER_MSG_CMD  ) == 0 )
	{
		numLidos = LER_LerParametros("iisi", &InxPerfilRemetente, &InxPerfilDestinatario,
									  Mensagem, &CondRetEsp ) ;

		if (( numLidos != 4 ) || ( ! ValidarInxPerfil( InxPerfilRemetente)) || 
			(! ValidarInxPerfil( InxPerfilDestinatario))){
			return TST_CondRetParm ;
		} /* if */

		CondRet = MEN_EscreverMensagem(vtPerfis[InxPerfilRemetente],vtPerfis[InxPerfilDestinatario],Mensagem) ;

		return TST_CompararInt( CondRetEsp , CondRet ,
			"Erro na condicao de retorno ao escrever mensagem"  ) ;

	} /* fim ativa: Testar Escrever Mensagem */


	/* Testar Excluir Mensagem */

	else if ( strcmp( ComandoTeste , EXCLUIR_MSG_CMD ) == 0 )
	{
		MEN_tpCondRet debug;
			
        numLidos = LER_LerParametros("iissi", &InxPerfil, &FlagMsg, Email, Mensagem, &CondRetEsp );
        if (( numLidos != 5 ) || ( ! ValidarInxPerfil(InxPerfil))) {
            return TST_CondRetParm ;
        } /* if */
			
        debug = MEN_ExcluirMensagem( vtPerfis[InxPerfil],Email,FlagMsg,Mensagem);
		return TST_CompararInt( CondRetEsp , debug ,
		"Erro na condicao de retorno ao excluir mensagem"  ) ;
			
    } /* fim ativa: Testar Excluir Mensagem */

	
	/* Testar Excluir Mensagens de um Email */

	else if (strcmp(ComandoTeste , EXCLUIR_MSGEMAIL_CMD ) == 0 )
	{
		MEN_tpCondRet debug;
			
        numLidos = LER_LerParametros( "isi" ,&InxPerfil,Email,&CondRetEsp );
        if (( numLidos != 3 ) || ( ! ValidarInxPerfil(InxPerfil))){
            return TST_CondRetParm ;
        } /* if */
			
        debug = MEN_ExcluirMensagensEmail(vtPerfis[InxPerfil],Email);
			
		return TST_CompararInt( CondRetEsp , debug ,
		"Erro na condicao de retorno ao excluir todas mensagens de um email"  ) ;
           
    } /* fim ativa: Testar Excluir Mensagens de um Email */

	
	/* Testar Modificar Mensagens de um Email */

	else if (strcmp(ComandoTeste , MODIFICAR_EMAIL_CMD) == 0){

		MEN_tpCondRet debug;
		char novoEmail[101];
			
        numLidos = LER_LerParametros( "issi" ,&InxPerfil,Email,novoEmail,&CondRetEsp );
        if ( ( numLidos != 4 ) || ( ! ValidarInxPerfil(InxPerfil))){
            return TST_CondRetParm ;
        } /* if */
			
        debug = MEN_ModificarEmailLista(vtPerfis[InxPerfil],Email,novoEmail);
		return TST_CompararInt( CondRetEsp , debug ,
		"Erro na condicao de retorno ao modificar os emails"  ) ;
           
    } /* fim ativa: Testar Modificar Mensagens de um Email */

	  
	/* Testar Obter Numero de Mensagens */

	else if (strcmp(ComandoTeste , OBTER_NUM_MSGS_CMD) == 0){

		MEN_tpCondRet debugMEN;
		int numRet;

        numLidos = LER_LerParametros("iiii" , &InxPerfil ,&FlagMsg, &numElem , &CondRetEsp);

        if (( numLidos != 4) || ( ! ValidarInxPerfil(InxPerfil))){
            return TST_CondRetParm ;
        } /* if */

		debugMEN=MEN_ObterNumMensagens(vtPerfis[InxPerfil], FlagMsg,&numRet);
		CondRet= TST_CompararInt( CondRetEsp , debugMEN,
        "Condicao de retorno errada ao obter numero de mensagens" ) ;

		if (CondRet != TST_CondRetOK) {
			return CondRet;
		}

		return TST_CompararInt( numElem , numRet,
		"Numero de elementos retornado inesperado");

	} /* fim ativa: Obter Numero de Mensagens  */

	
	/* Testar Obter Numero Total de Mensagens */

	else if (strcmp(ComandoTeste , OBTER_NUM_TODASMSGS_CMD) == 0){
		MEN_tpCondRet debugMEN;
		int numRet;

        numLidos = LER_LerParametros("iii" , &InxPerfil, &numElem ,
                                &CondRetEsp);

        if (( numLidos != 3 ) || ( ! ValidarInxPerfil(InxPerfil))){
            return TST_CondRetParm ;
        } /* if */

		debugMEN = MEN_ObterNumTodasMensagens(vtPerfis[InxPerfil],&numRet);
		CondRet = TST_CompararInt(CondRetEsp , debugMEN,
        "Condicao de retorno errada ao obter numero de todas mensagens" ) ;

		if (CondRet != TST_CondRetOK){
			return CondRet;
		}

		return TST_CompararInt( numElem , numRet, 
		"Numero de elementos retornado inesperado");

	} /* fim ativa: Obter Numero Total de Mensagens */

	
	/* Testar Obter Mensagens  */

	else if (strcmp(ComandoTeste , OBTER_MSGS_CMD) == 0){
		
		char Mensagem0[401],Mensagem1[401];
		char Email0[101],Email1[101];
		char** vetEmails;
		char** vetMensagens;
		MEN_tpCondRet debugMEN;

		vetEmails=(char**)malloc(2*sizeof(char));
		if ( vetEmails == NULL)
			return TST_CondRetMemoria ;
			
		vetEmails[0]=(char*)malloc(101*sizeof(char));
		if ( vetEmails[0] == NULL)
			return TST_CondRetMemoria ;
		
		vetEmails[1]=(char*)malloc(101*sizeof(char));
		if ( vetEmails[1] == NULL)
			return TST_CondRetMemoria ; 	

		vetMensagens=(char**)malloc(2*sizeof(char));
		if ( vetMensagens == NULL)
			return TST_CondRetMemoria ;
		 
		vetMensagens[0]=(char*)malloc(401*sizeof(char));
		if ( vetMensagens[0] == NULL)
			return TST_CondRetMemoria ;
		
		vetMensagens[1]=(char*)malloc(401*sizeof(char));
		if ( vetMensagens[1] == NULL)
			return TST_CondRetMemoria ;

        numLidos = LER_LerParametros( "issssii" , &InxPerfil,Email0,Mensagem0,
		Email1,Mensagem1,&FlagMsg,&CondRetEsp);  

		if ((numLidos != 7) || (! ValidarInxPerfil( InxPerfil ))){
			return TST_CondRetParm ;
		} /* Alocando os vetores */

		debugMEN = MEN_ObterMensagens(vtPerfis[InxPerfil],vetEmails,vetMensagens,FlagMsg);
		CondRet = TST_CompararInt( CondRetEsp, debugMEN,
			"CondiÁ„o de retorno errada ao obter mensagens.");

		if (CondRet != TST_CondRetOK)
			return CondRet;
		if(debugMEN == MEN_CondRetListaVazia)
			return TST_CondRetOK;

		CondRet=TST_CompararString(Email0 , vetEmails[0],
		"Email 0 nao e igual ao esperado");
		if (CondRet != TST_CondRetOK) 
			return CondRet;
		CondRet=TST_CompararString( Email1, vetEmails[1],
		"Email 1 nao e igual ao esperado");
		if (CondRet != TST_CondRetOK) 
			return CondRet;
		CondRet=TST_CompararString( Mensagem0, vetMensagens[0],
		"Mensagem 0 nao e igual  a esperada" ) ;
		if (CondRet != TST_CondRetOK) 
			return CondRet;
		CondRet=TST_CompararString( Mensagem1, vetMensagens[1],
		"Mensagem 1 nao e igual  a esperada" );
		if (CondRet != TST_CondRetOK) 
			return CondRet;

		free(vetEmails[0]);
		free(vetEmails[1]);
		free(vetEmails);
		free(vetMensagens[0]);
		free(vetMensagens[1]);
		free(vetMensagens);
		return TST_CondRetOK;

	} /* fim ativa: Obter Mensagens */

	
	/* Testar Obter Todas Mensagens */

	else if (strcmp(ComandoTeste , OBTER_TODASMSGS_CMD) == 0){
		
		MEN_tpCondRet tpMsg0,tpMsg1;
		char Mensagem0[401],Mensagem1[401];
		char Email0[101],Email1[101];
		MEN_tpCondRet* vetTipos;
		char** vetEmails;
		char** vetMensagens;
		MEN_tpCondRet debugMEN;

		vetTipos = (MEN_tpCondRet*)malloc(2*sizeof(MEN_tpCondRet));
		if (vetTipos == NULL)
			return TST_CondRetMemoria; 
		vetEmails = (char**)malloc(2*sizeof(char));
		if (vetEmails == NULL)
			return TST_CondRetMemoria;	
		vetEmails[0] = (char*)malloc(101*sizeof(char));
		if (vetEmails[0] == NULL)
			return TST_CondRetMemoria;
		vetEmails[1] = (char*)malloc(101*sizeof(char));
		if (vetEmails[1] == NULL)
			return TST_CondRetMemoria;
		vetMensagens = (char**)malloc(2*sizeof(char));
		if (vetMensagens == NULL)
			return TST_CondRetMemoria;
		vetMensagens[0] = (char*)malloc(401*sizeof(char));
		if (vetMensagens[0] == NULL)
			return TST_CondRetMemoria;
		vetMensagens[1]=(char*)malloc(401*sizeof(char));
		if (vetMensagens[1] == NULL)
			return TST_CondRetMemoria;

		numLidos = LER_LerParametros( "iississi" , &InxPerfil, &tpMsg0, Email0, Mensagem0,
		&tpMsg1, Email1, Mensagem1, &CondRetEsp) ;

		if (( numLidos != 8) || (! ValidarInxPerfil( InxPerfil )))
			return TST_CondRetParm ;

		debugMEN=MEN_ObterTodasMensagens(vtPerfis[InxPerfil],vetTipos,vetEmails,vetMensagens);
		CondRet=TST_CompararInt(CondRetEsp , debugMEN,
			"CondiÁ„o de retorno errada ao obter mensagens.");

		if (CondRet != TST_CondRetOK) 
			return CondRet;
		if(debugMEN == MEN_CondRetListaVazia)
			return TST_CondRetOK;

	CondRet=TST_CompararInt(tpMsg0 , vetTipos[0],
	"Tipo da mensagem 0 nao e igual ao esperado" ) ;
	if (CondRet != TST_CondRetOK)
		return CondRet;
	
	CondRet=TST_CompararInt(tpMsg1 , vetTipos[1],
	"Tipo da mensagem 1 nao e igual ao esperado" ) ;
	if (CondRet != TST_CondRetOK) 
		return CondRet;

	CondRet=TST_CompararString(Email0 , vetEmails[0],
	"Email 0 nao e igual ao esperado" ) ;
	if (CondRet != TST_CondRetOK) 
		return CondRet;

	CondRet=TST_CompararString(Email1 , vetEmails[1],
	"Email 1 nao e igual ao esperado" ) ;
	if (CondRet != TST_CondRetOK) 
		return CondRet;
	
	CondRet=TST_CompararString(Mensagem0 , vetMensagens[0],
	"Mensagem 0 nao e igual  a esperada" ) ;
	if (CondRet != TST_CondRetOK) 
		return CondRet;
	
	CondRet=TST_CompararString(Mensagem1 , vetMensagens[1],
	"Mensagem 1 nao e igual  a esperada" ) ;
	if (CondRet != TST_CondRetOK) 
		return CondRet;
	
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

 /* Fim funÁ„o: TMEN &Testar modulo de mensagens */


/*****  CÛdigo das funÁıes encapsuladas no mÛdulo  *****/
/***********************************************************************
*
*  $FC FunÁ„o: TMEN - Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {
      free( pValor ) ;
   } /* Fim funÁ„o: TMEN -Destruir valor */


/***********************************************************************
*
*  $FC FunÁ„o: TMEN - Validar indice de um Perfil
*
***********************************************************************/

int ValidarInxPerfil( int InxPerfil)
{

	if (( InxPerfil <  0 ) || ( InxPerfil >= DIM_VT_PERFIL )){
		return FALSE ;
	} /* if */

	return TRUE ;
} /* Fim funÁ„o: TMEN -Validar indice de um Perfil */


/********** Fim do mÛdulo de implementaÁ„o: TMEN Teste do modulo mensagem **********/

