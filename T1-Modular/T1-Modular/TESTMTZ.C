/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTMTZ.C
*  Letras identificadoras:      TMTZ
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: aaf - Alexandre Abrah�o Ferreira
*           jmb - Jo�o Marcello Bessa
*           phd - Pedro Henrique Dias
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo matriz. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo matriz:
*
*     "=criar"        - chama a fun��o MTZ_CriarMatriz( )
*     "=inselm" <Char>
*                   - chama a fun��o MTZ_ObterValorCorrente( <Char> )
*                     Obs. nota��o: <Char>  � o valor do par�metro
*                     que se encontra no comando de teste.
*     "=andar"     - chama a fun��o MTZ_IrPai( )
*     "=obter" <Char>
*                   - chama a fun��o MTZ_ObterValorCorrente( ) e compara
*                     o valor retornado com o valor <Char>
*     "=destroi"    - chama a fun��o MTZ_DestruirMatriz( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
//WIP
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "MATRIZ.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_MTZ_CMD       "=criar"
#define     INS_ELM_CMD         "=inselm"
#define     ANDAR_CMD           "=andar"
#define     OBTER_VAL_CMD       "=obter"
#define     DESTROI_CMD         "=destruir"

//WIP
static void ExcluirValor( void * pValor ) ;

/* Cria o vetor de matrizes sem lixo previamente dentro dele */
static MTZ_tppMatriz vetorMatrizes[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL} ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TMTZ Efetuar opera��es de teste espec�ficas para matriz
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     matriz sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      MTZ_tpCondRet CondRetObtido   = MTZ_CondRetOK ;
      MTZ_tpCondRet CondRetEsperada = MTZ_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

	  //WIP
	  int indiceMtz;
	  MTZ_tppMatriz * pMtz;

	  printf("Comecando a testar \n");

	  pMtz = ( MTZ_tppMatriz * ) malloc( sizeof( MTZ_tppMatriz )) ;
      if (pMtz == NULL)
         return TST_CondRetMemoria;
	  *pMtz = NULL;
      /* Testar MTZ Criar matriz */

         if ( strcmp( ComandoTeste , CRIAR_MTZ_CMD ) == 0 )
         {
			int dim;

            NumLidos = LER_LerParametros( "iii" ,
                               &indiceMtz, &dim, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MTZ_CriarMatriz( &vetorMatrizes[indiceMtz] , dim , ExcluirValor ) ; 

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar matriz." );

         } /* fim ativa: Testar MTZ Criar matriz */

      /* Testar MTZ Inserir elemento na casa corrente */

         else if ( strcmp( ComandoTeste , INS_ELM_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
                               &ValorDado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			//WIP
            CondRetObtido = MTZ_InserirElementoNaCasaCorrente( *pMtz , (void *) ValorDado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado inserir o elemento." );

         } /* fim ativa: Inserir elemento na casa corrente */

      /* Testar MTZ Obter valor corrente */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
                               &ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MTZ_ObterValorCorrente( *pMtz , (void **) ValorObtido ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararChar( ValorEsperado , ValorObtido ,
                                     "O valor est� errado." ) ;

         } /* fim ativa: Testar MTZ Obter valor corrente */

      /* Testar MTZ Andar em Dire��o */

         else if ( strcmp( ComandoTeste , ANDAR_CMD ) == 0 )
         {
			MTZ_tpDirecao dir;

            NumLidos = LER_LerParametros( "iii" ,
                               &indiceMtz, &dir, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MTZ_AndarDirecao( vetorMatrizes[indiceMtz] , dir ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao andar." );

         } /* fim ativa: Testar MTZ Andar em Dire��o */

      /* Testar MTZ Destruir Matriz */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

            MTZ_DestruirMatriz( *pMtz ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar MTZ Destruir Matriz */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TMTZ Efetuar opera��es de teste espec�ficas para matriz */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

   //WIP
   void ExcluirValor( void * pValor )
   {

      free( pValor ) ;

   }