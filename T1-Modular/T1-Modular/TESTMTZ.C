/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTMTZ.C
*  Letras identificadoras:      TMTZ
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: aaf - Alexandre Abrahão Ferreira
*           jmb - João Marcello Bessa
*           phd - Pedro Henrique Dias
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo matriz. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo matriz:
*
*     "=criar"  <Int> <Int>
*                   - chama a função MTZ_CriarMatriz( )
*     "=inselm" <Int> <String>
*                   - chama a função MTZ_InserirElementoNaCasaCorrente( <String> )
*                     Obs. notação: <String> é o valor do parâmetro
*                     que se encontra no comando de teste.
*     "=andar" <Int>    
*                   - chama a função MTZ_AndarDirecao( )
*     "=obter" <Int> <Char>
*                   - chama a função MTZ_ObterValorCorrente( ) e compara
*                     o primeiro valor retornado da lista com o valor <Char>
*     "=destroi" <Int>
*                   - chama a função MTZ_DestruirMatriz( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"
#include    "generico.h"
#include    "lerparm.h"

#include    "MATRIZ.h"
#include    "LISTA.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_MTZ_CMD       "=criar"
#define     INS_ELM_CMD         "=inselm"
#define     ANDAR_CMD           "=andar"
#define     OBTER_VAL_CMD       "=obter"
#define     DESTROI_CMD         "=destruir"

/*****  Dados encapsulados no módulo  *****/

static MTZ_tppMatriz vetorMatrizes[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL} ;

/***** Protótipos das funções encapuladas no módulo *****/

static void ExcluirCaracter( void * pValor ) ;

static void ExcluirLista( void * pValor ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TMTZ Efetuar operações de teste específicas para matriz
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     matriz sendo testado.
*
*  $EP Parâmetros
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

	   int indiceMtz;
      char StringDado[ 100 ] ;

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

            CondRetObtido = MTZ_CriarMatriz( &vetorMatrizes[indiceMtz] , dim , ExcluirLista ) ; 

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar matriz." );

         } /* fim ativa: Testar MTZ Criar matriz */

      /* Testar MTZ Inserir elemento na casa corrente */

         else if ( strcmp( ComandoTeste , INS_ELM_CMD ) == 0 )
         {
            LIS_tppLista listaTemp;
            int i = 0, tamString;

            listaTemp = LIS_CriarLista(ExcluirCaracter);
            if (listaTemp == NULL)
               return TST_CondRetMemoria;

            NumLidos = LER_LerParametros( "isi" ,
                               &indiceMtz, StringDado , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            tamString = strlen( StringDado );
            for (i = 0; i < tamString; i++) {
               char * aux = (char *) malloc(sizeof(char));
               *aux = StringDado[i];
               LIS_InserirElementoApos(listaTemp, aux);
            }

			IrInicioLista( listaTemp );

            CondRetObtido = MTZ_InserirElementoNaCasaCorrente( vetorMatrizes[indiceMtz] , (void *) listaTemp ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado inserir o elemento." );

         } /* fim ativa: Inserir elemento na casa corrente */

      /* Testar MTZ Obter valor corrente */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {
            LIS_tppLista pLista[1];
			char * pChar = NULL;

			pLista[0] = NULL;

            NumLidos = LER_LerParametros( "ici" ,
                               &indiceMtz, &ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MTZ_ObterValorCorrente( vetorMatrizes[indiceMtz], (void **) pLista ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

			if ( CondRetObtido == MTZ_CondRetMatrizNaoExiste && vetorMatrizes[indiceMtz] == NULL ) {
				return TST_CondRetOK;
			}

			if ( CondRetObtido == MTZ_CondRetCasaVazia && pLista[0] == NULL ) {
				return TST_CondRetOK;
			}

			Ret = TST_CompararPonteiroNulo( 1 , pLista[0],
                                           "Retorno errado: Ponteiro para lista nulo") ;

			pChar = (char *) LIS_ObterValor( pLista[0] );

			ValorObtido = *pChar;

            return TST_CompararChar( ValorEsperado , ValorObtido ,
                                     "O valor está errado." ) ;

         } /* fim ativa: Testar MTZ Obter valor corrente */

      /* Testar MTZ Andar em Direção */

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

         } /* fim ativa: Testar MTZ Andar em Direção */

      /* Testar MTZ Destruir Matriz */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros( "ii" ,
                               &indiceMtz, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MTZ_DestruirMatriz( &vetorMatrizes[indiceMtz] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao destruir matriz." ); ;

         } /* fim ativa: Testar MTZ Destruir Matriz */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TMTZ Efetuar operações de teste específicas para matriz */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TMTZ Excluir caracter
*
***********************************************************************/

   void ExcluirCaracter( void * pValor )
   {

     if (pValor != NULL)
      free( pValor ) ;

   } /* Fim função: TMTZ Excluir caracter */

/***********************************************************************
*
*  $FC Função: TMTZ Excluir lista
*
***********************************************************************/

   void ExcluirLista( void * pValor )
   {

     if (pValor != NULL) {
      LIS_DestruirLista((LIS_tppLista) pValor);
     }

   } /* Fim função: TMTZ Excluir lista */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
