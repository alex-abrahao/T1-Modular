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
*           jmb - João Marcello Bessa
*           phd - Pedro Henrique Dias
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


/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma matriz */

typedef struct tgCasaMatriz * MTZ_tppMatriz ;


/***********************************************************************
*
*  $TC Tipo de dados: MTZ Condiçoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MTZ_CondRetOK = 0 ,
               /* Executou correto */

         MTZ_CondRetNaoCriouHead = 1 ,
               /* Não criou a cabeça */

         MTZ_CondRetErroEstrutura = 2 ,
               /* Estrutura da matriz está errada */

         MTZ_CondRetDirecaoNaoExisteOuInvalida = 3 ,
               /* Direcao nao existe ou é invalida (sai da matriz) */

         MTZ_CondRetMatrizNaoExiste = 4 ,
               /* Matriz não existe */

         MTZ_CondRetCasaVazia = 5 ,
               /* Casa da matriz está vazia */

         MTZ_CondRetFaltouMemoria = 6 ,
               /* Faltou memória ao alocar dados */

   } MTZ_tpCondRet ;


/***********************************************************************
 *
 *  $TC Tipo de dados: MTZ Direções
 *
 *
 ***********************************************************************/

    typedef enum {
        
        MTZ_DirNorte = 0 ,
            /* Andar na direção Norte */
        
        MTZ_DirNordeste = 1 ,
            /* Andar na direção Nordeste */
        
        MTZ_DirLeste = 2 ,
            /* Andar na direção Leste */
        
        MTZ_DirSudeste = 3 ,
            /* Andar na direção Sudeste */
        
        MTZ_DirSul = 4 ,
            /* Andar na direção Sul */
        
        MTZ_DirSudoeste = 5 ,
            /* Andar na direção Sudoeste */
        
        MTZ_DirOeste = 6 ,
            /* Andar na direção Oeste */
        
        MTZ_DirNoroeste = 7 ,
            /* Andar na direção Noroeste */
        
    } MTZ_tpDirecao ;


/***********************************************************************
*
*  $FC Função: MTZ Criar matriz
*
*  $ED Descrição da função
*     Cria uma nova matriz n x n.
*     Caso já exista uma matriz no ponteiro especificado, esta será destruída.
*
*  $EP Parametros
*     $P ppMtz - Ponteiro para o ponteiro para uma matriz
*     $P n - Dimensão n x n da matriz quadrada
*     $P ExcluirValor - ponteiro para a função que processa a
*                       exclusão do valor referenciado pelo elemento
*                       a ser excluído.
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetFaltouMemoria
*     MTZ_CondRetErroEstrutura   - Caso a dimensão da matriz seja menor que zero
*
***********************************************************************/

MTZ_tpCondRet MTZ_CriarMatriz(MTZ_tppMatriz * ppMtz, int n, void ( * ExcluirValor ) ( void * pValor ) ) ;


/***********************************************************************
*
*  $FC Função: MTZ Destruir matriz
*
*  $ED Descrição da função
*     Destrói a cabeça da matriz, anulando a matriz especificada.
*     Faz nada caso o indice nao contenha uma matriz.
*
*  $EP Parametros
*     $P pMtz - Ponteiro para uma matriz
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetMatrizNaoExiste
*
***********************************************************************/

   MTZ_tpCondRet MTZ_DestruirMatriz( MTZ_tppMatriz pMtz ) ;


/***********************************************************************
*
*  $FC Função: MTZ Andar em Direção
*
*  $EP Parâmetros
*     $P pMtz - Ponteiro para uma matriz
*     $P direcao - Direção a andar.
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
*  $FC Função: MTZ Inserir lista na casa corrente
*
*  $ED Descrição da função
*     Insere um elemento na casa corrente da matriz.
*
*  $EP Parâmetros
*     $P pMtz - Ponteiro para uma matriz
*     $P elemento - Ponteiro para valor a ser inserido na casa corrente
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetErroEstrutura
*     MTZ_CondRetFaltouMemoria
*
***********************************************************************/

   MTZ_tpCondRet MTZ_InserirElementoNaCasaCorrente( MTZ_tppMatriz pMtz, void * elemento ) ;


/***********************************************************************
*
*  $FC Função: MTZ Obter valor corrente
*
*  $ED Descrição da função
*     Obtem o valor presente na casa corrente da matriz selecionada.
*
*  $EP Parâmetros
*     $P pMtz - Ponteiro para uma matriz
*     $P valor - Ponteiro para o valor a ser obtido
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetMatrizNaoExiste
*     MTZ_CondRetCasaVazia
*
***********************************************************************/

   MTZ_tpCondRet MTZ_ObterValorCorrente( MTZ_tppMatriz pMtz, void * valor ) ;


#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
