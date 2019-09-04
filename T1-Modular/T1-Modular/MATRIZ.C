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
#undef MATRIZ_OWN

/***********************************************************************
*
*  $TC Tipo de dados: MTZ Descritor do casa da matriz
*
*
*  $ED Descrição do tipo
*     Descreve a organização de uma casa da matriz
*
***********************************************************************/

   typedef struct tgCasaMatriz {

         struct tgCasaMatriz * pCasasAdjacentes[8] ;
               /* Vetor de ponteiros para as casas adjacentes */
       
         void * conteudo ;
               /* Conteúdo da casa */
       
   } tpCasaMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MTZ Descritor da cabeça de uma matriz
*
*
*  $ED Descrição do tipo
*     A cabeça da matriz é o ponto de acesso para uma determinada matriz.
*     Por intermédio da referência para o casa corrente e do ponteiro
*     pai pode-se navegar a matriz sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a matriz em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgMatriz {
       
         tpCasaMatriz * pPrimeiro ;
               /* Ponteiro para a casa (0, 0) da matriz */

         tpCasaMatriz * pCasaCorr ;
               /* Ponteiro para o casa corrente da matriz */
       
         char id;
               /* Caracter identificador da matriz (opcional) */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } tpMatriz ;

/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapuladas no módulo *****/

   static tpCasaMatriz * CriarCasa( ) ;

   static void DestroiMatriz( tpCasaMatriz * pNo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MTZ Criar matriz
*  ****/

   MTZ_tpCondRet MTZ_CriarMatriz(MTZ_tppMatriz * ppMtz, int n, void ( * ExcluirValor ) ( void * pValor ) ) {

      // Verificar se n é positivo
      if (n <= 0) return MTZ_CondRetErroEstrutura;

      // Se já havia uma matriz anteriormente, destrua-a primeiro
      if (*ppMtz != NULL)
         MTZ_DestruirMatriz(*ppMtz);

      // Alocar espaço para a head
      *ppMtz = ( tpMatriz * ) malloc( sizeof( tpMatriz )) ;
      if (*ppMtz == NULL)
         return MTZ_CondRetFaltouMemoria;

      // Setup da head
      *ppMtz->id = 0;
      *ppMtz->ExcluirValor = ExcluirValor;
      *ppMtz->pCasaCorr = NULL;

      // Criar a primeira casa
      *ppMtz->pPrimeiro = CriarCasa();
      if (*ppMtz->pPrimeiro == NULL) {
         // Libera a head
         free(*ppMtz);
         return MTZ_CondRetFaltouMemoria;
      }

      // Começa a preencher as demais casas, linha por linha
      int linha, coluna;
      // Só é preciso setar os ponteiros para as casas oeste, norte, noroeste e nordeste, assim como
      // setar nessas casas as direcoes inversas para o ponteiro da casa atual que está sendo criada.
      tpCasaMatriz * pCasaOeste, * pCasaInicioLinha, * pCasaAtual, * pCasaNorte;

      // Para cada linha
      for (linha = 0; linha < n; linha++) {

         if (linha == 0) {
            pCasaInicioLinha = *ppMtz->pPrimeiro;
            pCasaNorte = NULL;            

         } else {
            pCasaAtual = CriarCasa();

            if (pCasaAtual == NULL) {

               /* PREENCHER COM SE FALTAR MEMORIA */

               return MTZ_CondRetFaltouMemoria;
            }
            // Apontar a linha anterior como o norte da casa de inicio da nova linha, e vice-versa
            pCasaInicioLinha->pCasasAdjacentes[MTZ_DirSul] = pCasaInicioLinha;
            pCasaAtual->pCasasAdjacentes[MTZ_DirNorte] = pCasaInicioLinha;
            // Apontar nordeste (e sudeste da linha de cima)
            // Não será nulo, pois se passou para a segunda linha existe pelo menos 2 casas na linha de cima
            pCasaAtual->pCasasAdjacentes[MTZ_DirNordeste] = pCasaInicioLinha->pCasasAdjacentes[MTZ_DirLeste];
            pCasaInicioLinha->pCasasAdjacentes[MTZ_DirLeste]->pCasasAdjacentes[MTZ_DirSudoeste] = pCasaAtual;
            // A casa norte no inicio do loop de coluna será o norte da casa anterior, ou seja, o noroeste da nova casa a ser criada
            pCasaNorte = pCasaInicioLinha;
            // Agora o inicio da linha é a casa que acabou de ser criada
            pCasaInicioLinha = pCasaAtual;
         }
         pCasaOeste = pCasaInicioLinha;

         // Para cada coluna (elemento da primeira coluna já foi criado)
         for (coluna = 1; coluna < n; coluna++) {

            pCasaAtual = CriarCasa();
            if (pCasaAtual == NULL) {

               /* PREENCHER COM SE FALTAR MEMORIA */

               return MTZ_CondRetFaltouMemoria;
            }
            if (pCasaNorte != NULL) {
               // Preenche o noroeste
               pCasaAtual->pCasasAdjacentes[MTZ_DirNoroeste] = pCasaNorte;
               pCasaNorte->pCasasAdjacentes[MTZ_DirSudeste] = pCasaAtual;
               // Atualiza o norte e preenche (sempre deverá existir o leste do norte atual)
               pCasaNorte = pCasaNorte->pCasasAdjacentes[MTZ_DirLeste];
               pCasaNorte->pCasasAdjacentes[MTZ_DirSul] = pCasaAtual;
               pCasaAtual->pCasasAdjacentes[MTZ_DirNorte] = pCasaNorte;
               // Preenche a casa nordeste
               if (pCasaNorte->pCasasAdjacentes[MTZ_DirLeste] != NULL) {
                  tpCasaMatriz * pCasaNordeste = pCasaNorte->pCasasAdjacentes[MTZ_DirLeste];
                  pCasaNordeste->pCasasAdjacentes[MTZ_DirSudoeste] = pCasaAtual;
                  pCasaAtual->pCasasAdjacentes[MTZ_DirNordeste] = pCasaNordeste;
               }
            }
            // Preenche a casa oeste
            pCasaAtual->pCasasAdjacentes[MTZ_DirOeste] = pCasaOeste;
            pCasaOeste->pCasasAdjacentes[MTZ_DirLeste] = pCasaAtual;
            // Atualiza a casa oeste para a proxima iteração
            pCasaOeste = pCasaAtual;
         }
      }


      // Apontar o ponteiro corrente para a primeira casa
      *ppMtz->pCasaCorr = *ppMtz->pPrimeiro;

      return MTZ_CondRetOK ;

   } /* Fim função: MTZ Criar matriz */

/***************************************************************************
*
*  Função: MTZ Destruir matriz
*  ****/

   MTZ_tpCondRet MTZ_DestruirMatriz( MTZ_tppMatriz pMtz ) {

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
*  Função: MTZ Andar em Direção
*  ****/

   MTZ_tpCondRet MTZ_AndarDirecao( MTZ_tppMatriz pMtz, MTZ_tpDirecao direcao ) {
   



   } /* Fim função: MTZ Andar em Direção */

/***************************************************************************
*
*  Função: MTZ Inserir lista na casa corrente
*  ****/

   MTZ_tpCondRet MTZ_InserirElementoNaCasaCorrente( MTZ_tppMatriz pMtz, void * elemento ) {

      
   } /* Fim função: MTZ Inserir lista na casa corrente */

/***************************************************************************
*
*  Função: MTZ Obter valor corrente
*  ****/

   MTZ_tpCondRet MTZ_ObterValorCorrente( MTZ_tppMatriz pMtz, void * valor ) {

      

   } /* Fim função: MTZ Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: MTZ Criar casa da matriz
*
*  $FV Valor retornado
*     Ponteiro para a casa criada.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros de direção da casa criada e o conteudo estarão nulos.
*
***********************************************************************/

   tpCasaMatriz * CriarCasa(  ) {

      tpCasaMatriz * pCasa ;

      pNo = ( tpCasaMatriz * ) malloc( sizeof( tpCasaMatriz )) ;
      if ( pCasa == NULL )
      {
         return NULL ;
      } /* if */

      int i = 0;

      // Preenche os ponteiros com nulos
      for (; i < 8; i++) {
         pCasa->pCasasAdjacentes[i] = NULL;
      }
      pCasa->conteudo = NULL ;
      return pCasa ;

   } /* Fim função: MTZ Criar casa da matriz */


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

