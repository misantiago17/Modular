/***************************************************************************
*  $MCI MÛdulo de implementaÁ„o: MEN  Mensagem generico com cabeca
*
*  Arquivo gerado:              Mensagem.c
*  Letras identificadoras:      MEN
*
*  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 AutomatizaÁ„o dos testes de mÛdulos C
*  Gestor:  DI/PUC-Rio
*  Autores: Gabriel Busquim (gb), Michelle Santiago (ms), Renan Moreira (rm)
*
*  $HA HistÛrico de evoluÁ„o:
*  Vers„o     Autor   	  Data     	ObservaÁıes
*     9        ms       06/12/2017  edição de descrições ao longo do código
*     8        gb       03/11/2017 	alteração no nome de funções
*     7        gb       02/11/2017 	alteração da condição de retorno
*     6        ms       02/11/2017 	alteração nas funções utilizadas do modulo perfil
*     5        gb       02/11/2017 	verificação da existencia do perfil e número de mensagem
*     4        gb       01/11/2017 	alterações do código de todas as funções
*     3        gb       27/11/2017 	alteração da descricao de funções
*	  2        gb       20/11/2017  desenvolvimento da função excluir mensagem
*     1        gb       15/11/2017 	inicio do desenvolvimento
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


/***************************************************************************
*
*  FunÁ„o: FunÁ„o: MEN  &Escrever Mensagem
*
*       MEN_CondRetOK
*       MEN_CondRetRetornoLisIncorreto
*       MEN_CondRetMensagemExcedeuTamanho
*       MEN_CondRetMensagemVazia
*       MEN_CondRetMesmoPerfil
*       MEN_CondRetPerfilInvalido
*       MEN_CondRetFaltouMemoria
*
*  ****/

MEN_tpCondRet MEN_EscreverMensagem(PER_tpPerfil * Remetente,PER_tpPerfil *Destinatario,char MensagemEnv[]) 
{
	int tamMsg;
	char* emailRem;
	char* emailDest;
	char *primeiroNome;
	char *ultimoNome;
	char *cidade;
	int diaNasc; 
	int mesNasc;
	int anoNasc;
	MEN_tpMensagem* MsgRem;
	MEN_tpMensagem* MsgDest;
	LIS_tppLista LisRem;
	LIS_tppLista LisDest;
	LIS_tpCondRet CondRet;
    
    /* Alocação de memória para o perfil Remetente e Desinatario */
	emailRem=(char*)malloc(101*sizeof(char));
	if (emailRem == NULL)
		return MEN_CondRetFaltouMemoria;
    
	emailDest=(char*)malloc(101*sizeof(char));
	if (emailDest == NULL)
		return MEN_CondRetFaltouMemoria;
    
	primeiroNome=(char*)malloc(101*sizeof(char));
	if (primeiroNome == NULL)
		return MEN_CondRetFaltouMemoria;
    
	ultimoNome=(char*)malloc(101*sizeof(char));
	if (ultimoNome == NULL)
		return MEN_CondRetFaltouMemoria;
    
	cidade=(char*)malloc(101*sizeof(char));
	if (cidade == NULL)
		return MEN_CondRetFaltouMemoria;
    
    /* Obtenção dos perfis remetentes e destinatários */
    
	if(PER_ObterPerfil(Remetente, emailRem,primeiroNome, ultimoNome,
		&diaNasc, &mesNasc, &anoNasc, cidade)==PER_CondRetPerfilInvalido)
		return MEN_CondRetPerfilInvalido;
    
	if (PER_ObterPerfil(Destinatario, emailDest,primeiroNome, ultimoNome,
		&diaNasc, &mesNasc, &anoNasc, cidade)==PER_CondRetPerfilInvalido)
		return MEN_CondRetPerfilInvalido;
    
    /* Verifica se o perfil é o mesmo */
    
    if(strcmp(emailRem,emailDest)==0)
		return MEN_CondRetMesmoPerfil;
    
    /* Verifica se excedeu o número de caracteres em uma mensagem ou se ela está vazia */
    
	tamMsg=strlen(MensagemEnv);
    if(tamMsg==0) {
		return MEN_CondRetMensagemVazia;
    } else if(tamMsg>400) {
		return MEN_CondRetMensagemExcedeuTamanho;
    }

    /* Obtem lista de mensagem de ambos os perfis */
    
	PER_retornaLisMensagens(Remetente,&LisRem);
	PER_retornaLisMensagens(Destinatario,&LisDest);
    
    /* Alocamento da mensagem para o rementente e destinatário */

	MsgRem = (MEN_tpMensagem*)malloc(sizeof(MEN_tpMensagem));
	if (MsgRem == NULL) {
		free(cidade);
		free(primeiroNome);
		free(ultimoNome);
		free(emailDest);
		free(emailRem);
		return MEN_CondRetFaltouMemoria;
	}
    
	MsgDest = (MEN_tpMensagem*)malloc(sizeof(MEN_tpMensagem));
	if (MsgDest == NULL) {
		free(cidade);
		free(primeiroNome);
		free(ultimoNome);
		free(emailDest);
		free(emailRem);
		return MEN_CondRetFaltouMemoria;
	}
	
    /* Armazenar dados da mensagem no struct da mensagem */
    
	strcpy_s(MsgRem->Mensagem,401,MensagemEnv);
	MsgRem->Flag=MEN_CondMsgEnviada;
	strcpy_s(MsgRem->Email,101,emailDest);
	
	strcpy_s(MsgDest->Mensagem,401,MensagemEnv);
	MsgDest->Flag=MEN_CondMsgRecebida;
	strcpy_s(MsgDest->Email,101,emailRem);

    /* Adiciona a mensagem à lista do remetente */
    
	CondRet=LIS_IrFinalLista(LisRem);
    if(CondRet!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;

	if(LIS_InserirElementoApos(LisRem ,(void*)MsgRem) != LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;

    /* Adiciona a mensagem à lista do destinatário */
    
	CondRet=LIS_IrFinalLista(LisDest);
    if(CondRet!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;

    if(LIS_InserirElementoApos(LisDest ,(void*)MsgDest) != LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
    
    /* Libera o espaço armazenado */
    
	free(cidade);
	free(primeiroNome);
	free(ultimoNome);
	free(emailDest);
	free(emailRem);
    
	return MEN_CondRetOK;
	
} /* Fim funÁ„o: MEN  &Escrever Mensagem */


/***********************************************************************
*
*  $FC FunÁ„o: MEN  &Excluir Mensagem
*
*       MEN_CondRetOK
*       MEN_CondRetRetornoLisIncorreto
*       MEN_CondRetListaVazia
*       MEN_CondRetNaoEncontrouMensagem
*       MEN_CondRetPerfilInvalido
*
*  ****/

MEN_tpCondRet MEN_ExcluirMensagem(PER_tpPerfil * Perfil,char Email[],MEN_tpCondMsg flagMsg,char Mensagem[])
{ 
	int numTotalMsgs;
	LIS_tpCondRet CondRetLis=LIS_CondRetOK;
	MEN_tppMensagem tpMsg;
	LIS_tppLista pMensagem;
    
    /* obtem numero de mensagens do perfil */
    
	if(MEN_ObterNumTodasMensagens(Perfil,&numTotalMsgs) == MEN_CondRetRetornoLisIncorreto)
		return MEN_CondRetRetornoLisIncorreto;
    
    /* verifica se a lista de mensagens está vazia */
    
	if(numTotalMsgs == 0)
		return MEN_CondRetListaVazia;
    
    /* Verifica se o perfil existe */

	if(PER_retornaLisMensagens(Perfil,&pMensagem) == PER_CondRetPerfilInexistente)
		return MEN_CondRetPerfilInvalido;
    
    /* Procura a mensagem a ser excluída dentro da lista */
    
	if(LIS_IrInicioLista(pMensagem) != LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
    
	while(CondRetLis != LIS_CondRetFimLista)
	{
		if(LIS_ObterValor(pMensagem,(void**)&tpMsg) != LIS_CondRetOK)
			return MEN_CondRetRetornoLisIncorreto;
        
        if(strcmp(tpMsg->Email,Email) == 0 && strcmp(tpMsg->Mensagem,Mensagem) == 0 && tpMsg->Flag == flagMsg) {
            
			if(LIS_ExcluirElemento(pMensagem) != LIS_CondRetOK)
				return MEN_CondRetRetornoLisIncorreto;
            
			 return MEN_CondRetOK;
		} /* if */
        
		CondRetLis = LIS_AvancarElementoCorrente(pMensagem,1);
	} /* while */
    
	return MEN_CondRetNaoEncontrouMensagem;
    
} /* Fim funÁ„o: MEN  &Excluir Mensagem*/

/***********************************************************************
*
*  $FC FunÁ„o: MEN  &Excluir Mensagens de um Email
*
*       MEN_CondRetOK
*       MEN_CondRetRetornoLisIncorreto
*       MEN_CondRetPerfilInvalido
*
*  ****/

MEN_tpCondRet MEN_ExcluirMensagensEmail(PER_tpPerfil * Perfil,char Email[])
{ 
	int numTotalMsgs;
	LIS_tpCondRet CondRetLis = LIS_CondRetOK;
	MEN_tppMensagem tpMsg;
	LIS_tppLista pMensagem;
    
    /* Obter número de mensagens de um perfil */
    
	if(MEN_ObterNumTodasMensagens(Perfil,&numTotalMsgs) == MEN_CondRetRetornoLisIncorreto)
		return MEN_CondRetRetornoLisIncorreto;
    
    /* Verifica se a lista de mensagens já está vazia */
    
	if(numTotalMsgs==0)
		return MEN_CondRetOK;
    
    /* Verifica se o perfil existe */

	if(PER_retornaLisMensagens(Perfil,&pMensagem) == PER_CondRetPerfilInexistente)
		return MEN_CondRetPerfilInvalido;
    
    /* Excluí todos as mensagens de um determinado perfil */
    
	if(LIS_IrInicioLista(pMensagem) != LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
    
	while(CondRetLis != LIS_CondRetFimLista) {
        
		if(LIS_ObterValor(pMensagem,(void**)&tpMsg) == LIS_CondRetListaVazia)
			return MEN_CondRetOK;
        
		if(strcmp(tpMsg->Email,Email) == 0)
		{
			if(LIS_ExcluirElemento(pMensagem) != LIS_CondRetOK)
				return MEN_CondRetRetornoLisIncorreto;
				continue;
		} /* if */
        
		CondRetLis=LIS_AvancarElementoCorrente(pMensagem,1);
	} /* while */
    
	return MEN_CondRetOK;
    
} /* Fim funÁ„o: MEN  &Excluir Mensagem*/

/***********************************************************************
*
*  $FC FunÁ„o: MEN  &Alterar Email da Lista de Mensagem
*
*       MEN_CondRetOK
*       MEN_CondRetRetornoLisIncorreto
*       MEN_CondRetPerfilInvalido
*
*  ****/

MEN_tpCondRet MEN_ModificarEmailLista(PER_tpPerfil * Perfil,char antigoEmail[],char novoEmail[])
{ 
	int numTotalMsgs;
	LIS_tpCondRet CondRetLis=LIS_CondRetOK;
	MEN_tppMensagem tpMsg;
	LIS_tppLista pMensagem;
    
    /* Obtem número de mensagens */
    
	if(MEN_ObterNumTodasMensagens(Perfil,&numTotalMsgs)==MEN_CondRetRetornoLisIncorreto)
		return MEN_CondRetRetornoLisIncorreto;
    
    /* Verifica se a lista de mensagens já está vazia */
    
	if(numTotalMsgs==0)
		return MEN_CondRetOK;
	
    /* Verifica se o perfil existe */

	if(PER_retornaLisMensagens(Perfil,&pMensagem)==PER_CondRetPerfilInexistente)
		return MEN_CondRetPerfilInvalido;
    
    /* Modifica o email de toda a lista */
    
	if(LIS_IrInicioLista(pMensagem)!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
    
	while(CondRetLis!=LIS_CondRetFimLista) {
        
		if(LIS_ObterValor(pMensagem,(void**)&tpMsg) == LIS_CondRetListaVazia)
			return MEN_CondRetOK;
        
		if(strcmp(tpMsg->Email,antigoEmail)==0)
			strcpy_s(tpMsg->Email,101,novoEmail);
        
		CondRetLis=LIS_AvancarElementoCorrente(pMensagem,1);
	} /* while */
    
	return MEN_CondRetOK;
    
} /* Fim funÁ„o: MEN  &Alterar Email da Lista de Mensagem*/

/***************************************************************************
*
*  FunÁ„o: FunÁ„o: MEN  &ObterNumTodasMensagens
*
*       MEN_CondRetOK
*       MEN_CondRetParametroIncorreto
*       MEN_CondRetRetornoLisIncorreto
*       MEN_CondRetPerfilInvalido
*
*  ****/

MEN_tpCondRet MEN_ObterNumTodasMensagens(PER_tpPerfil * Perfil, int* numTotalMsgs) 
{
	LIS_tppLista pMensagem;
    
    /* Verifica se o perfil existe */

	if(PER_retornaLisMensagens(Perfil,&pMensagem)==PER_CondRetPerfilInexistente)
		return MEN_CondRetPerfilInvalido;
    
	if(pMensagem==NULL)
		return MEN_CondRetParametroIncorreto;
    
    /* Obtem o numero de mensagens */
    
	if(LIS_ObterTamanho(pMensagem,numTotalMsgs)!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
    
	return MEN_CondRetOK;
	
}/* Fim funÁ„o: MEN  &ObterNumTodasMensagens*/


/***************************************************************************
*
*  FunÁ„o:  &ObterNumMensagens
*
*       MEN_CondRetOK
*       MEN_CondRetParametroIncorreto
*       MEN_CondRetRetornoLisIncorreto
*       MEN_CondRetListaVazia
*       MEN_CondRetPerfilInvalido
*
*  ****/

MEN_tpCondRet MEN_ObterNumMensagens(PER_tpPerfil * Perfil,MEN_tpCondMsg flagMsg, int* numMsgs) 
{
	LIS_tpCondRet CondRetLis=LIS_CondRetOK;
	int numTotalMsgs,contador=0;
	MEN_tppMensagem tpMsg;
	LIS_tppLista pMensagem;
    
	/* Assertivas */
    
	if(flagMsg!=MEN_CondMsgEnviada && flagMsg!=MEN_CondMsgRecebida )
		return MEN_CondRetParametroIncorreto;
    
	if(MEN_ObterNumTodasMensagens(Perfil,&numTotalMsgs)==MEN_CondRetRetornoLisIncorreto)
		return MEN_CondRetRetornoLisIncorreto;
    
    /* Verifica se lista de mensagens tá vazia ou não */
    
	if(numTotalMsgs==0) {
		*numMsgs=0;
		return MEN_CondRetListaVazia;
	}
    
    /* Verifica se o perfil existe */

	if(PER_retornaLisMensagens(Perfil,&pMensagem)==PER_CondRetPerfilInexistente)
		return MEN_CondRetPerfilInvalido;
    
    /* Contabiliza o número de mensagens da lista */
    
	if(LIS_IrInicioLista(pMensagem)!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
    
	while(CondRetLis!=LIS_CondRetFimLista)
	{
		if(LIS_ObterValor(pMensagem,(void**)&tpMsg) != LIS_CondRetOK)
			return MEN_CondRetRetornoLisIncorreto;
        
		if(tpMsg->Flag==flagMsg)
			contador++;
        
		CondRetLis=LIS_AvancarElementoCorrente(pMensagem,1);
        
	} /* while */
    
	*numMsgs=contador;
    
	if(LIS_IrInicioLista(pMensagem)!=LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
    
	return MEN_CondRetOK;
    
} /* Fim funÁ„o: MEN  &ObterNumMensagens*/


/***************************************************************************
*
*  FunÁ„o: MEN  &Obter Todas Mensagens
*  ****/

MEN_tpCondRet MEN_ObterTodasMensagens(PER_tpPerfil * Perfil, MEN_tpCondMsg vetTipos[],char* vetEmails[], char* vetMensagens[] )
{
	LIS_tpCondRet CondRetLis=LIS_CondRetOK;
	int numTotalMsgs,i=0;
	MEN_tppMensagem tpMsg;
	LIS_tppLista pMensagem;
    
	/* Assertiva */
    
	if (vetMensagens== NULL || vetTipos== NULL || vetEmails == NULL )
		return MEN_CondRetParametroIncorreto;
    
    /* Obtem o número de mensagens de um perfil */
    
	if(MEN_ObterNumTodasMensagens(Perfil,&numTotalMsgs) == MEN_CondRetRetornoLisIncorreto)
		return MEN_CondRetRetornoLisIncorreto;
    
    /* Verifica se a lista já está vazia */
    
	if(numTotalMsgs==0)
		return MEN_CondRetListaVazia;
    
    /* Verifica se o perfil existe */

	if(PER_retornaLisMensagens(Perfil,&pMensagem)==PER_CondRetPerfilInexistente)
		return MEN_CondRetPerfilInvalido;
    
    /* Armazena todas as mensagens do perfil em uma lista */
    
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
        
	} /* while */
	
	return MEN_CondRetOK;

} /* Fim funÁ„o: MEN  &Armazenar Todas Mensagens */


/***************************************************************************
*
*  FunÁ„o: MEN  &Obter Mensagens
*  ****/

MEN_tpCondRet MEN_ObterMensagens(PER_tpPerfil * Perfil, char* vetEmails[], char* vetMensagens[],MEN_tpCondMsg flagMsg)
{
	LIS_tpCondRet CondRetLis = LIS_CondRetOK;
	int numTotalMsgs,i = 0;
	MEN_tppMensagem tpMsg;
	LIS_tppLista pMensagem;
    
	/* Assertiva */
	if (vetMensagens== NULL || vetEmails == NULL)
		return MEN_CondRetParametroIncorreto;
	
    /* Obtem número de mensagens de um perfil */
    
	if(MEN_ObterNumTodasMensagens(Perfil,&numTotalMsgs) == MEN_CondRetRetornoLisIncorreto)
		return MEN_CondRetRetornoLisIncorreto;
    
    /* Verifica se a lista já está vazia */
    
	if(numTotalMsgs==0)
		return MEN_CondRetListaVazia;
    
    /* Verifica se o perfil existe */
	
	if(PER_retornaLisMensagens(Perfil,&pMensagem) == PER_CondRetPerfilInexistente)
		return MEN_CondRetPerfilInvalido;
    
    /* Obtem a lista de mensagens de um perfil */
    
	if(LIS_IrInicioLista(pMensagem) != LIS_CondRetOK)
		return MEN_CondRetRetornoLisIncorreto;
    
	while(CondRetLis != LIS_CondRetFimLista) {
        
		if(LIS_ObterValor(pMensagem,(void**)&tpMsg) != LIS_CondRetOK)
			return MEN_CondRetRetornoLisIncorreto;
        
		if(tpMsg->Flag == flagMsg){
			strcpy_s(vetMensagens[i],401,tpMsg->Mensagem);
			strcpy_s(vetEmails[i],101,tpMsg->Email);
			i++;
		} /* if */
        
		CondRetLis=LIS_AvancarElementoCorrente(pMensagem,1);
        
	} /* while */
    
	return MEN_CondRetOK;

} /* Fim funÁ„o: MEN  &Armazenar Mensagens */

/********** Fim do mÛdulo de implementaÁ„o: MEN  Lista de Mensagens **********/
