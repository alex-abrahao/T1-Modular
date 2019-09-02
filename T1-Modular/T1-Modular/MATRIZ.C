/***************************************************************************
*  $MCI Módulo de implementação: Módulo matriz
*
*  Arquivo gerado:              MATRIZ.C
*  Letras identificadoras:      MTZ
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define MATRIZ_OWN
#include "MATRIZ.H"
#include "LISTA.H"
#undef MARIZ_OWN

/***********************************************************************
*
*  $TC Tipo de dados: MTZ Descritor do casa da matriz
*
*
*  $ED Descrição do tipo
*     Descreve a organização do casa
*
***********************************************************************/

   typedef struct tgCasaMatriz {

         struct tgCasaMatriz * pCasasAdjacentes[8] ;
               /* Vetor de ponteiros para as casas adjacentes */

         LIS_tppLista * lista ;
               /* Lista da casa */
       
   } tpCasaMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MTZ Descritor da cabeça de uma matriz
*
*
*  $ED Descrição do tipo
*     A cabe‡a da matriz é o ponto de acesso para uma determinada matriz.
*     Por intermédio da referência para o casa corrente e do ponteiro
*     pai pode-se navegar a matriz sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a matriz em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgMatriz {

         tpCasaMatriz * pCasaCorr ;
               /* Ponteiro para o casa corrente da matriz */

   } tpMatriz ;

/*****  Dados encapsulados no módulo  *****/

      static tpMatriz * pMatriz = NULL ;
            /* Ponteiro para a cabe‡a da matriz */

/***** Protótipos das funções encapuladas no módulo *****/

   static tpCasaMatriz * CriarNo( char ValorParm ) ;

   static MTZ_tpCondRet CriarNoRaiz( char ValorParm ) ;

   static void DestroiMatriz( tpCasaMatriz * pNo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MTZ Criar matriz
*  ****/

   MTZ_tpCondRet MTZ_CriarMatriz( void )
   {

      if ( pMatriz != NULL )
      {
         MTZ_DestruirMatriz( ) ;
      } /* if */

      pMatriz = ( tpMatriz * ) malloc( sizeof( tpMatriz )) ;
      if ( pMatriz == NULL )
      {
         return MTZ_CondRetFaltouMemoria ;
      } /* if */
      
      pMatriz->pNoRaiz = NULL ;
      pMatriz->pNoCorr = NULL ;

      return MTZ_CondRetOK ;

   } /* Fim função: MTZ Criar matriz */

/***************************************************************************
*
*  Função: MTZ Destruir matriz
*  ****/

   void MTZ_DestruirMatriz( void )
   {

      if ( pMatriz != NULL )
      {
         if ( pMatriz->pNoRaiz != NULL )
         {
            DestroiMatriz( pMatriz->pNoRaiz ) ;
         } /* if */
         free( pMatriz ) ;
         pMatriz = NULL ;
      } /* if */

   } /* Fim função: MTZ Destruir matriz */

/***************************************************************************
*
*  Função: MTZ Adicionar filho à esquerda
*  ****/

   MTZ_tpCondRet MTZ_InserirEsquerda( char ValorParm )
   {

      MTZ_tpCondRet CondRet ;

      tpCasaMatriz * pCorr ;
      tpCasaMatriz * pNo ;

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != MTZ_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar casa à esquerda de folha */

         pCorr = pMatriz->pNoCorr ;
         if ( pCorr == NULL )
         {
            return MTZ_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return MTZ_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pMatriz->pNoCorr = pNo ;

            return MTZ_CondRetOK ;
         } /* if */

      /* Tratar não folha à esquerda */

         return MTZ_CondRetNaoEhFolha ;

   } /* Fim função: MTZ Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: MTZ Adicionar filho à direita
*  ****/

   MTZ_tpCondRet MTZ_InserirDireita( char ValorParm )
   {

      MTZ_tpCondRet CondRet ;

      tpCasaMatriz * pCorr ;
      tpCasaMatriz * pNo ;

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != MTZ_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar casa à direita de folha */

         pCorr = pMatriz->pNoCorr ;
         if ( pCorr == NULL )
         {
            return MTZ_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return MTZ_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pMatriz->pNoCorr = pNo ;

            return MTZ_CondRetOK ;
         } /* if */

      /* Tratar não folha à direita */

         return MTZ_CondRetNaoEhFolha ;

   } /* Fim função: MTZ Adicionar filho à direita */

/***************************************************************************
*
*  Função: MTZ Ir para casa pai
*  ****/

   MTZ_tpCondRet MTZ_IrPai( void )
   {

      if ( pMatriz == NULL )
      {
         return MTZ_CondRetMatrizNaoExiste ;
      } /* if */
      if ( pMatriz->pNoCorr == NULL )
      {
         return MTZ_CondRetMatrizVazia ;
      } /* if */

      if ( pMatriz->pNoCorr->pNoPai != NULL )
      {
         pMatriz->pNoCorr = pMatriz->pNoCorr->pNoPai ;
         return MTZ_CondRetOK ;
      } else {
         return MTZ_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim função: MTZ Ir para casa pai */

/***************************************************************************
*
*  Função: MTZ Ir para casa à esquerda
*  ****/

   MTZ_tpCondRet MTZ_IrNoEsquerda( void )
   {

      if ( pMatriz == NULL )
      {
         return MTZ_CondRetMatrizNaoExiste ;
      } /* if */

      if ( pMatriz->pNoCorr == NULL )
      {
         return MTZ_CondRetMatrizVazia ;
      } /* if */

      if ( pMatriz->pNoCorr->pNoEsq == NULL )
      {
         return MTZ_CondRetNaoPossuiFilho ;
      } /* if */

      pMatriz->pNoCorr = pMatriz->pNoCorr->pNoEsq ;
      return MTZ_CondRetOK ;

   } /* Fim função: MTZ Ir para casa à esquerda */

/***************************************************************************
*
*  Função: MTZ Ir para casa à direita
*  ****/

   MTZ_tpCondRet MTZ_IrNoDireita( void )
   {

      if ( pMatriz == NULL )
      {
         return MTZ_CondRetMatrizNaoExiste ;
      } /* if */

      if ( pMatriz->pNoCorr == NULL )
      {
         return MTZ_CondRetMatrizVazia ;
      } /* if */

      if ( pMatriz->pNoCorr->pNoDir == NULL )
      {
         return MTZ_CondRetNaoPossuiFilho ;
      } /* if */

      pMatriz->pNoCorr = pMatriz->pNoCorr->pNoDir ;
      return MTZ_CondRetOK ;

   } /* Fim função: MTZ Ir para casa à direita */

/***************************************************************************
*
*  Função: MTZ Obter valor corrente
*  ****/

   MTZ_tpCondRet MTZ_ObterValorCorr( char * ValorParm )
   {

      if ( pMatriz == NULL )
      {
         return MTZ_CondRetMatrizNaoExiste ;
      } /* if */
      if ( pMatriz->pNoCorr == NULL )
      {
         return MTZ_CondRetMatrizVazia ;
      } /* if */
      * ValorParm = pMatriz->pNoCorr->Valor ;

      return MTZ_CondRetOK ;

   } /* Fim função: MTZ Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: MTZ Criar casa da matriz
*
*  $FV Valor retornado
*     Ponteiro para o casa criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do casa criado estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

   tpCasaMatriz * CriarNo( char ValorParm )
   {

      tpCasaMatriz * pNo ;

      pNo = ( tpCasaMatriz * ) malloc( sizeof( tpCasaMatriz )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
      pNo->Valor  = ValorParm ;
      return pNo ;

   } /* Fim função: MTZ Criar casa da matriz */


/***********************************************************************
*
*  $FC Função: MTZ Criar casa raiz da matriz
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetFaltouMemoria
*     MTZ_CondRetNaoCriouRaiz
*
***********************************************************************/

   MTZ_tpCondRet CriarNoRaiz( char ValorParm )
   {

      MTZ_tpCondRet CondRet ;
      tpCasaMatriz * pNo ;

      if ( pMatriz == NULL )
      {
         CondRet = MTZ_CriarMatriz( ) ;

         if ( CondRet != MTZ_CondRetOK )
         {
            return CondRet ;
         } /* if */
      } /* if */

      if ( pMatriz->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm ) ;
         if ( pNo == NULL )
         {
            return MTZ_CondRetFaltouMemoria ;
         } /* if */
         pMatriz->pNoRaiz = pNo ;
         pMatriz->pNoCorr = pNo ;

         return MTZ_CondRetOK ;
      } /* if */

      return MTZ_CondRetNaoCriouRaiz ;

   } /* Fim função: MTZ Criar casa raiz da matriz */


/***********************************************************************
*
*  $FC Função: MTZ Destruir a estrutura da matriz
*
*  $EAE Assertivas de entradas esperadas
*     pNoMatriz != NULL
*
***********************************************************************/

   void DestroiMatriz( tpCasaMatriz * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiMatriz( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiMatriz( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim função: MTZ Destruir a estrutura da matriz */

/********** Fim do módulo de implementação: Módulo matriz **********/

