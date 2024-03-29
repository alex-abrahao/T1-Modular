#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo matriz
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MTZ
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
*       1.00   aaf   26/08/2019 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa matrizes gen�ricas duplamente encadeadas.
*     Podem existir n matrizes em opera��o simultaneamente.
*     As matrizes possuem uma cabe�a encapsulando o seu estado.
*
*     Cada matriz � homog�nea quanto ao tipo dos dados que armazena.
*     Cada casa da matriz referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da matriz.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada matriz referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar uma casa
*        de uma matriz.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da matriz seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif


/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma matriz */

typedef struct tgMatriz * MTZ_tppMatriz ;


/***********************************************************************
*
*  $TC Tipo de dados: MTZ Condi�oes de retorno
*
*
***********************************************************************/

   typedef enum {

         MTZ_CondRetOK = 0 ,
               /* Executou correto */

         MTZ_CondRetNaoCriouHead = 1 ,
               /* N�o criou a cabe�a */

         MTZ_CondRetErroEstrutura = 2 ,
               /* Estrutura da matriz est� errada */

         MTZ_CondRetDirecaoNaoExisteOuInvalida = 3 ,
               /* Direcao nao existe ou � invalida (sai da matriz) */

         MTZ_CondRetMatrizNaoExiste = 4 ,
               /* Matriz n�o existe */

         MTZ_CondRetCasaVazia = 5 ,
               /* Casa da matriz est� vazia */

         MTZ_CondRetFaltouMemoria = 6
               /* Faltou mem�ria ao alocar dados */

   } MTZ_tpCondRet ;


/***********************************************************************
 *
 *  $TC Tipo de dados: MTZ Dire��es
 *
 *
 ***********************************************************************/

    typedef enum {
        
        MTZ_DirNorte = 0 ,
            /* Andar na dire��o Norte */
        
        MTZ_DirNordeste = 1 ,
            /* Andar na dire��o Nordeste */
        
        MTZ_DirLeste = 2 ,
            /* Andar na dire��o Leste */
        
        MTZ_DirSudeste = 3 ,
            /* Andar na dire��o Sudeste */
        
        MTZ_DirSul = 4 ,
            /* Andar na dire��o Sul */
        
        MTZ_DirSudoeste = 5 ,
            /* Andar na dire��o Sudoeste */
        
        MTZ_DirOeste = 6 ,
            /* Andar na dire��o Oeste */
        
        MTZ_DirNoroeste = 7
            /* Andar na dire��o Noroeste */
        
    } MTZ_tpDirecao ;


/***********************************************************************
*
*  $FC Fun��o: MTZ Criar matriz
*
*  $ED Descri��o da fun��o
*     Cria uma nova matriz n x n.
*     Caso j� exista uma matriz no ponteiro especificado, esta ser� destru�da.
*
*  $EP Parametros
*     $P ppMtz - Ponteiro para o ponteiro para uma matriz
*     $P n - Dimens�o n x n da matriz quadrada
*     $P ExcluirValor - ponteiro para a fun��o que processa a
*                       exclus�o do valor referenciado pelo elemento
*                       a ser exclu�do.
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetFaltouMemoria
*     MTZ_CondRetErroEstrutura   - Caso a dimens�o da matriz seja menor que zero ou o ponteiro seja nulo
*
***********************************************************************/

MTZ_tpCondRet MTZ_CriarMatriz(MTZ_tppMatriz * ppMtz, int n, void ( * ExcluirValor ) ( void * pValor ) ) ;


/***********************************************************************
*
*  $FC Fun��o: MTZ Destruir matriz
*
*  $ED Descri��o da fun��o
*     Destr�i a cabe�a da matriz, anulando a matriz especificada.
*     Faz nada caso o indice nao contenha uma matriz.
*
*  $EP Parametros
*     $P ppMtz - Ponteiro para uma matriz
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetMatrizNaoExiste
*     MTZ_CondRetErroEstrutura   - Caso o ponteiro seja nulo
*
***********************************************************************/

   MTZ_tpCondRet MTZ_DestruirMatriz( MTZ_tppMatriz * pptz ) ;


/***********************************************************************
*
*  $FC Fun��o: MTZ Andar em Dire��o
*
*  $EP Par�metros
*     $P pMtz - Ponteiro para uma matriz
*     $P direcao - Dire��o a andar.
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetDirecaoNaoExisteOuInvalida
*     MTZ_CondRetMatrizNaoExiste
*
***********************************************************************/

   MTZ_tpCondRet MTZ_AndarDirecao( MTZ_tppMatriz pMtz, MTZ_tpDirecao direcao ) ;


/***********************************************************************
*
*  $FC Fun��o: MTZ Inserir elemento na casa corrente
*
*  $ED Descri��o da fun��o
*     Insere um elemento na casa corrente da matriz.
*     Se j� houver um elemento na casa corrente, este ser� liberado e sustitu�do.
*
*  $EP Par�metros
*     $P pMtz - Ponteiro para uma matriz
*     $P pElemento - Ponteiro para valor a ser inserido na casa corrente
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetErroEstrutura
*	    MTZ_CondRetMatrizNaoExiste
*
***********************************************************************/

   MTZ_tpCondRet MTZ_InserirElementoNaCasaCorrente( MTZ_tppMatriz pMtz, void * pElemento ) ;


/***********************************************************************
*
*  $FC Fun��o: MTZ Obter valor corrente
*
*  $ED Descri��o da fun��o
*     Obtem o valor presente na casa corrente da matriz selecionada.
*
*  $EP Par�metros
*     $P pMtz - Ponteiro para uma matriz
*     $P valor - Ponteiro de ponteiro para o valor a ser obtido
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetMatrizNaoExiste
*     MTZ_CondRetCasaVazia
*     MTZ_CondRetErroEstrutura   - Caso o ponteiro para valor seja nulo
*
***********************************************************************/

   MTZ_tpCondRet MTZ_ObterValorCorrente( MTZ_tppMatriz pMtz, void ** valor ) ;


#undef MATRIZ_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
