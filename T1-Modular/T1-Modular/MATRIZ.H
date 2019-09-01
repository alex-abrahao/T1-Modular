#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MTZ
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: aaf - Alexandre Abrahão Ferreira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   aaf   26/08/2019 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar árvores binárias.
*     A árvore possui uma cabeça que contém uma referência para a raíz da
*     árvore e outra para um nó corrente da árvore.
*     A cada momento o módulo admite no máximo uma única árvore.
*     Ao iniciar a execução do programa não existe árvore.
*     A árvore poderá estar vazia. Neste caso a raiz e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se a árvore estiver vazia.
*
***************************************************************************/
 
#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif

#include "LISTA.H"

/***********************************************************************
*
*  $TC Tipo de dados: MTZ Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MTZ_CondRetOK = 0 ,
               /* Executou correto */

         MTZ_CondRetNaoCriouHead = 1 ,
               /* Não criou a cabeca */

         MTZ_CondRetErroEstrutura = 2 ,
               /* Estrutura da matriz está errada */

         MTZ_CondRetDirecaoNaoExisteOuInvalida = 3 ,
               /* Direcao nao existe ou Ž invalida (sai da matriz) */

         MTZ_CondRetMatrizNaoExiste = 4 ,
               /* Matriz não existe */

         MTZ_CondRetCasaVazia = 5 ,
               /* Casa da matriz está vazia */

         MTZ_CondRetNohEhRaiz = 6 ,
               /* Nó corrente é raiz */

         MTZ_CondRetNaoPossuiFilho = 7 ,
               /* Nó corrente não possui filho na direção desejada */

         MTZ_CondRetFaltouMemoria = 8
               /* Faltou memória ao alocar dados */

   } MTZ_tpCondRet ;


/***********************************************************************
 *
 *  $TC Tipo de dados: MTZ Direcoes
 *
 *
 ***********************************************************************/

    typedef enum {
        
        MTZ_DirNorte = 0 ,
            /* Andar na direcao Norte */
        
        MTZ_DirNordeste = 1 ,
            /* Andar na direcao Nordeste */
        
        MTZ_DirLeste = 2 ,
            /* Andar na direcao Leste */
        
        MTZ_DirSudeste = 3 ,
            /* Andar na direcao Sudeste */
        
        MTZ_DirSul = 4 ,
            /* Andar na direcao Sul */
        
        MTZ_DirSudoeste = 5 ,
            /* Andar na direcao Sudoeste */
        
        MTZ_DirOeste = 6 ,
            /* Andar na direcao Oeste */
        
        MTZ_DirNoroeste = 7 ,
            /* Andar na direcao Noroeste */
        
    } MTZ_tpDirecao ;


/***********************************************************************
*
*  $FC Função: MTZ Criar matriz
*
*  $ED Descrição da função
*     Cria uma nova matriz n x n.
*     Caso já exista uma matriz no indice especificado, esta será destruída.
*
*  $EP Parametros
*     $P n - Tamanho da matriz quadrada
*     $P indiceMtz - Indice da matriz a ser criada, entre 0 e 9
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetFaltouMemoria
*     MTZ_CondRetMatrizNaoExiste  - Caso o indice esteja fora do permitido
*
***********************************************************************/

   MTZ_tpCondRet MTZ_CriarMatriz( unsigned n, int indiceMtz ) ;


/***********************************************************************
*
*  $FC Função: MTZ Destruir matriz
*
*  $ED Descrição da função
*     Destrói a cabeça da matriz, anulando a matriz especificada.
*     Faz nada caso o indice nao contenha uma matriz.
*
*  $EP Parametros
*     $P indiceMtz - Indice da matriz a ser destruida, entre 0 e 9
*
***********************************************************************/

   void MTZ_DestruirMatriz( int indiceMtz ) ;


/***********************************************************************
*
*  $FC Função: MTZ Andar em direcao
*
*  $EP Parâmetros
*     $P indiceMtz - Indice da matriz.
*     $P direcao - Direcao a andar.
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetDirecaoNaoExisteOuInvalida
*     MTZ_CondRetMatrizNaoExiste
*
***********************************************************************/

   MTZ_tpCondRet MTZ_AndarDirecao( int indiceMtz, MTZ_tpDirecao direcao ) ;


/***********************************************************************
*
*  $FC Função: MTZ Adicionar filho à direita
*
*  $EP Parâmetros
*     $P ValorParm - valor a ser inserido no novo nó
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetErroEstrutura
*     MTZ_CondRetFaltouMemoria
*     MTZ_CondRetNaoEhFolha     - caso não seja folha para a direita
*
***********************************************************************/

   MTZ_tpCondRet MTZ_InserirDireita( char ValorParm ) ;


/***********************************************************************
*
*  $FC Função: MTZ Ir para nó pai
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetArvoreNaoExiste
*     MTZ_CondRetArvoreVazia
*     MTZ_CondRetNoEhRaiz
*
***********************************************************************/

   MTZ_tpCondRet MTZ_IrPai( void ) ;


/***********************************************************************
*
*  $FC Função: MTZ Ir para nó à esquerda
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetArvoreNaoExiste
*     MTZ_CondRetArvoreVazia
*     MTZ_CondRetNaoPossuiFilho   - nó corrente não possui filho à esquerda
*
***********************************************************************/

   MTZ_tpCondRet MTZ_IrNoEsquerda( void ) ;


/***********************************************************************
*
*  $FC Função: MTZ Ir para nó à direita
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetArvoreNaoExiste
*     MTZ_CondRetArvoreVazia
*     MTZ_CondRetNaoPossuiFilho   - nó corrente não possui filho à direita
*
***********************************************************************/

   MTZ_tpCondRet MTZ_IrNoDireita( void ) ;


/***********************************************************************
*
*  $FC Função: MTZ Obter valor corrente
*
*  $EP Parâmetros
*     $P indiceMtz - Indice da matriz selecionada, entre 0 e 9
*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetMatrizNaoExiste
*     MTZ_CondRetMatrizVazia
*
***********************************************************************/

   MTZ_tpCondRet MTZ_ObterValorCorr( char * ValorParm ) ;

#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
