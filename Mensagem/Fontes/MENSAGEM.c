/***************************************************************************
*  $MCI Módulo de implementação: MEN  Mensagem generico com cabeca
*
*  Arquivo gerado:              Mensagem.c
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  DI/PUC-Rio
*  Autores: Gabriel Busquim (gb), Michelle Santiago (ms), Renan Moreira (rm)
*
*  $HA Histórico de evolução:
*     Versão  Autor   	 Data     	Observações
*    18      rm/ms/gb   16/10/2017 	revisoes finais e pequenas correcoes
*    17        gb    	14/10/2017 	funcoes: MEN_NumArestas, MEN_RetornaIndiceAresta
*    16        ms    	13/10/2017 	alteracao MEN_IrVertice, MEN_CriarAresta, MEN_ExisteAresta, MEN_ExcluirAresta
*    15        gb    	12/10/2017 	alteracao MEN_CriarAresta, MEN_InserirAresta
*    14        gb    	11/10/2017 	alteracao MEN_InserirVertice
*    13        rm    	11/10/2017 	alteracao MEN_IrVertice, MEN_DestruirMensagem
*    12      rm/ms/gb   11/10/2017 	revisao nas structs
*    11        rm    	10/10/2017 	funcoes: MEN_IrVertice e MEN_DestruirMensagem
*    10        ms       10/10/2017 	funcao: LiberarVertice; revisao na: MEN_ExcluirVertice
*     9        gb       09/10/2017 	funcoes: MEN_RetornaIdentificador
*     8        gb       08/10/2017 	funcoes: MEN_ExcluirAresta
*     7        gb       06/10/2017 	funcoes: MEN_CriarAresta, MEN_ExisteAresta
*     6        gb       06/10/2017 	alteracao nas funcoes: MEN_InserirVertice, MEN_ExcluirVertice
*     5        ms       05/10/2017 	alteracao nas funcoes: MEN_ObterValor, MEN_InserirVertice
*     4        ms       05/10/2017 	funcoes: MEN_ExcluirVertice, CriarSubVertice
*     3      rm/ms/gb   04/10/2017 	revisao nas structs; remocao: CriarElemento e LimparCabeca
*	  2        rm       30/09/2017  funcoes: MEN_CriarMensagem, MEN_IrVertice, MEN_ObterValor, MEN_InserirVertice, CriarElemento, LimparCabeca
*     1      rm/ms/gb   27/09/2017 	inicio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <stdlib.h>
#include   "MENSAGEM.h"

/***********************************************************************
*
*  $TC Tipo de dados: MEN Elemento da lista de mensagens
*
***********************************************************************/

typedef struct MEN_tagMensagem {

	char Mensagem[400] ;
	/* Vetor que armazena a mensagem */

	MEN_tpCondMsg Flag;
	/* Flag que indica se a mensagem foi enviada(caso tenha valor 0) ou recebida(caso tenha valor 1)*/

	char Email[100];
	/* Email do perfil remetente ou destinatario da mensagem, dependendo do valor de Flag */
	
} MEN_tpMensagem;



/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: Função: MEN  &Escrever Mensagem 
*  ****/
MEN_tpCondRet MEN_EscreverMensagem(PER_tpPerfil * Remetente,PER_tpPerfil *Destinatario,char MensagemEnv[]) 
{
	int tamMsg;
	char* emailRem;
	char* emailDest;
	char *primeiroNome;
	char *ultimoNome;
	char *cidade;
	int *diaNasc; 
	int *mesNasc;
	int *anoNasc;
	MEN_tpMensagem* MsgRem;
	MEN_tpMensagem* MsgDest;
	LIS_tppLista LisRem;
	LIS_tppLista LisDest;
	LIS_tpCondRet CondRet;
	emailRem=(char*)malloc(101*sizeof(char));
	if (EmailRem == NULL)
	{
		return MEN_CondRetFaltouMemoria;
	}
	emailDest=(char*)malloc(101*sizeof(char));
	if (EmailDest == NULL)
	{
		return MEN_CondRetFaltouMemoria;
	}
	if(PER_ObterPerfil(Remetente, emailRem,primeiroNome, ultimoNome,
		&diaNasc, &mesNasc, &anoNasc, cidade)==PER_CondRetPonteiroParaRetornoInvalido)
		return MEN_CondRetPerfilInvalido;
	if (PER_ObterPerfil(Destinatario, emailDest,primeiroNome, ultimoNome,
		&diaNasc, &mesNasc, &anoNasc, cidade)==PER_CondRetPonteiroParaRetornoInvalido)
		return MEN_CondRetPerfilInvalido;
	if(strcmp(emailRem,emailDest)==0)
		return MEN_CondRetMesmoPerfil;
	tamMsg=strlen(MensagemEnv);
	if(tamMsg==0)
		return MEN_CondRetMensagemVazia;
	else if(tamMsg>400)
		return MEN_CondRetMensagemExcedeuTamanho;

	PER_retornaLisMensagens(Remetente,&LisRem);
	PER_retornaLisMensagens(Destinatario,&LisDest);

	MsgRem = (MEN_tpMensagem*)malloc(sizeof(MEN_tpMensagem));
	if (MsgRem == NULL)
	{
		free(emailDest);
		free(EmailRem);
		return MEN_CondRetFaltouMemoria;
	}
	MsgDest = (MEN_tpMensagem*)malloc(sizeof(MEN_tpMensagem));
	if (MsgDest == NULL)
	{
		free(emailDest);
		free(EmailRem);
		return MEN_CondRetFaltouMemoria;
	}
	
	
	strcpy_s(MsgRem->Mensagem,401,MensagemEnv);
	MsgRem->Flag=MEN_CondMsgEnviada;
	strcpy_s(MsgRem->Email,101,emailDest);
	

	
	strcpy_s(MsgDest->Mensagem,401,MensagemEnv);
	MsgDest->Flag=MEN_CondMsgRecebida;
	strcpy_s(MsgDest->Email,101,emailRem);




	CondRet=LIS_IrFinalLista(LisRem);
	if(CondRet!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;

	if(LIS_InserirElementoApos( LisRem ,(void*)MsgRem)
		!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;

	CondRet=LIS_IrFinalLista(LisDest);
	if(CondRet!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;

	if(LIS_InserirElementoApos(LisDest ,(void*)MsgDest)
		!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
	free(emailDest);
	free(EmailRem);	
	return MEN_CondRetOK;
	
} /* Fim função: MEN  &Escrever Mensagem */


  /***********************************************************************
  *
  *  $FC Função: MEN  &Excluir Mensagem
  *  ****/

MEN_tpCondRet MEN_ExcluirMensagem(PER_tpPerfil * Perfil,char Email[],MEN_tpCondMsg flagMsg,char Mensagem[])
{ 
	int numTotalMsgs;
	LIS_tpCondRet CondRetLis=LIS_CondRetOK;
	MEN_tppMensagem tpMsg;
	LIS_tppLista pMensagem;
	if(PER_retornaLisMensagens(Perfil,&pMensagem)==PER_CondRetPerfilInexistente)
		return MEN_CondRetPerfilInvalido;
	if(MEN_ObterNumTodasMensagens(pMensagem,&numTotalMsgs)==MEN_CondRetRetornoLisIncorreto)
		return MEN_CondRetRetornoLisIncorreto;
	if(numTotalMsgs==0)
	{
		return MEN_CondRetListaVazia;
	}
	if(LIS_IrInicioLista(pMensagem)!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
	while(CondRetLis!=LIS_CondRetFimLista)
	{
		if(LIS_ObterValor(pMensagem,(void**)&tpMsg) != LIS_CondRetOK)
			return MEN_CondRetRetornoLisIncorreto;
		if(strcmp(tpMsg->Email,Email)==0 && strcmp(tpMsg->Mensagem,Mensagem)==0 && tpMsg->Flag==flagMsg)
		{
			if(LIS_ExcluirElemento(pMensagem)!=LIS_CondRetOK)
				return MEN_CondRetRetornoLisIncorreto;
			 return MEN_CondRetOK;
		}
		CondRetLis=LIS_AvancarElementoCorrente(pMensagem,1);
	}
	return MEN_CondRetNaoEncontrouMensagem;
}

	
/* Fim função: MEN  &Excluir Mensagem*/

 /***********************************************************************
  *
  *  $FC Função: MEN  &Excluir Mensagens de um Email
  *  ****/

MEN_tpCondRet MEN_ExcluirMensagensEmail(PER_tpPerfil * Perfil,char Email[]);
{ 
	int numTotalMsgs;
	LIS_tpCondRet CondRetLis=LIS_CondRetOK;
	MEN_tppMensagem tpMsg;
	LIS_tppLista pMensagem;
	if(PER_retornaLisMensagens(Perfil,&pMensagem)==PER_CondRetPerfilInexistente)
		return MEN_CondRetPerfilInvalido;
	if(MEN_ObterNumTodasMensagens(pMensagem,&numTotalMsgs)==MEN_CondRetRetornoLisIncorreto)
		return MEN_CondRetRetornoLisIncorreto;
	if(numTotalMsgs==0)
	{
		return MEN_CondRetOK;
	}
	if(LIS_IrInicioLista(pMensagem)!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
	while(CondRetLis!=LIS_CondRetFimLista)
	{
		if(LIS_ObterValor(pMensagem,(void**)&tpMsg) != LIS_CondRetOK)
			return MEN_CondRetRetornoLisIncorreto;
		if(strcmp(tpMsg->Email,Email)==0)
		{
			if(LIS_ExcluirElemento(pMensagem)!=LIS_CondRetOK)
				return MEN_CondRetRetornoLisIncorreto;
				continue;
		}
		CondRetLis=LIS_AvancarElementoCorrente(pMensagem,1);
	}
	return MEN_CondRetOK;
}

	
/* Fim função: MEN  &Excluir Mensagem*/

 /***************************************************************************
 *
 *  Função: Função: MEN  &ObterNumTodasMensagens
 *  ****/

MEN_tpCondRet MEN_ObterNumTodasMensagens(PER_tpPerfil * Perfil, int* numTotalMsgs) 
{
	LIS_tppLista pMensagem;
	if(PER_retornaLisMensagens(Perfil,&pMensagem)==PER_CondRetPerfilInexistente)
		return MEN_CondRetPerfilInvalido;
	if(pMensagem==NULL)
		return MEN_CondRetParametroIncorreto;
	if(LIS_ObterTamanho(pMensagem,numTotalMsgs)!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
	return MEN_CondRetOK;
	
}/* Fim função: MEN  &ObterNumTodasMensagens*/


/***************************************************************************
 *
 *  Função:  &ObterNumMensagens
 *  ****/

MEN_tpCondRet MEN_ObterNumMensagens(PER_tpPerfil * Perfil,MEN_tpCondMsg flagMsg, int* numMsgs) 
{
	LIS_tpCondRet CondRetLis=LIS_CondRetOK;
	int numTotalMsgs,contador=0;
	MEN_tppMensagem tpMsg;
	LIS_tppLista pMensagem;
	//Assertivas:
	if(PER_retornaLisMensagens(Perfil,&pMensagem)==PER_CondRetPerfilInexistente)
		return MEN_CondRetPerfilInvalido;
	if(flagMsg!=MEN_CondMsgEnviada && flagMsg!=MEN_CondMsgRecebida )
		return MEN_CondRetParametroIncorreto;
	if(MEN_ObterNumTodasMensagens(pMensagem,&numTotalMsgs)==MEN_CondRetRetornoLisIncorreto)
		return MEN_CondRetRetornoLisIncorreto;
	
	if(numTotalMsgs==0)
	{
		*numMsgs=0;
		return MEN_CondRetOK;
	}
	if(LIS_IrInicioLista(pMensagem)!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
	while(CondRetLis!=LIS_CondRetFimLista)
	{
		if(LIS_ObterValor(pMensagem,(void**)&tpMsg) != LIS_CondRetOK)
			return MEN_CondRetRetornoLisIncorreto;
		if(tpMsg->Flag==flagMsg){
			contador++;}
		CondRetLis=LIS_AvancarElementoCorrente(pMensagem,1);
		
	}
	*numMsgs=contador;
	if(LIS_IrInicioLista(pMensagem)!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
	return MEN_CondRetOK;
}/* Fim função: MEN  &ObterNumMensagens*/


/***************************************************************************
*
*  Função: MEN  &Obter Todas Mensagens
*  ****/

MEN_tpCondRet MEN_ObterTodasMensagens(PER_tpPerfil * Perfil, MEN_tpCondMsg vetTipos[],char* vetEmails[], char* vetMensagens[] )
{
	LIS_tpCondRet CondRetLis=LIS_CondRetOK;
	int numTotalMsgs,i=0;
	MEN_tppMensagem tpMsg;
	LIS_tppLista pMensagem;
	//Assertiva
	if (vetMensagens== NULL || vetTipos== NULL || vetEmails== NULL )
	{
		return MEN_CondRetParametroIncorreto;
	}
	if(PER_retornaLisMensagens(Perfil,&pMensagem)==PER_CondRetPerfilInexistente)
		return MEN_CondRetPerfilInvalido;
	if(MEN_ObterNumTodasMensagens(pMensagem,&numTotalMsgs)==MEN_CondRetRetornoLisIncorreto)
		return MEN_CondRetRetornoLisIncorreto;
	if(numTotalMsgs==0)
	{
		return MEN_CondRetListaVazia;
	}
	if(LIS_IrInicioLista(pMensagem)!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
	while(CondRetLis!=LIS_CondRetFimLista)
	{
		if(LIS_ObterValor(pMensagem,(void**)&tpMsg) != LIS_CondRetOK)
			return MEN_CondRetRetornoLisIncorreto;
		strcpy_s(vetMensagens[i],401,tpMsg->Mensagem);
		strcpy_s(vetEmails[i],101,tpMsg->Email);
	    vetTipos[i]=tpMsg->Flag;

		i++;
		CondRetLis=LIS_AvancarElementoCorrente(pMensagem,1);
	}
	
	return MEN_CondRetOK;

} /* Fim função: MEN  &Armazenar Todas Mensagens */


/***************************************************************************
*
*  Função: MEN  &Obter Mensagens
*  ****/

MEN_tpCondRet MEN_ObterMensagens(PER_tpPerfil * Perfil, char* vetEmails[], char* vetMensagens[],MEN_tpCondMsg flagMsg)
{
	LIS_tpCondRet CondRetLis=LIS_CondRetOK;
	int numTotalMsgs,i=0;
	MEN_tppMensagem tpMsg;
	LIS_tppLista pMensagem;
	//Assertiva
	if (vetMensagens== NULL || vetEmails== NULL)
	{
		return MEN_CondRetParametroIncorreto;
	} 
	if(PER_retornaLisMensagens(Perfil,&pMensagem)==PER_CondRetPerfilInexistente)
		return MEN_CondRetPerfilInvalido;
	if(MEN_ObterNumTodasMensagens(pMensagem,&numTotalMsgs)==MEN_CondRetRetornoLisIncorreto)
		return MEN_CondRetRetornoLisIncorreto;
	if(numTotalMsgs==0)
	{
		return MEN_CondRetListaVazia;
	}
	if(LIS_IrInicioLista(pMensagem)!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
	while(CondRetLis!=LIS_CondRetFimLista)
	{
		if(LIS_ObterValor(pMensagem,(void**)&tpMsg) != LIS_CondRetOK)
			return MEN_CondRetRetornoLisIncorreto;
		if(tpMsg->Flag==flagMsg){
			strcpy_s(vetMensagens[i],401,tpMsg->Mensagem);
			strcpy_s(vetEmails[i],101,tpMsg->Email);
			i++;
		}
		CondRetLis=LIS_AvancarElementoCorrente(pMensagem,1);
	}
	return MEN_CondRetOK;

} /* Fim função: MEN  &Armazenar Mensagens */

/********** Fim do módulo de implementação: MEN  Lista de Mensagens **********/