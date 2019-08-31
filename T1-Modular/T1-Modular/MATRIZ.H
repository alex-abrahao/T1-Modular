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


/***********************************************************************
*
*  $TC Tipo de dados: MTZ Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MTZ_CondRetOK = 0 ,
               /* Executou correto */

         MTZ_CondRetNaoCriouRaiz = 1 ,
               /* Não criou nó raiz */

         MTZ_CondRetErroEstrutura = 2 ,
               /* Estrutura da árvore está errada */

         MTZ_CondRetNaoEhFolha = 3 ,
               /* Não é folha relativa à direção de inserção desejada */

         MTZ_CondRetArvoreNaoExiste = 4 ,
               /* Árvore não existe */

         MTZ_CondRetArvoreVazia = 5 ,
               /* Árvore está vazia */

         MTZ_CondRetNohEhRaiz = 6 ,
               /* Nó corrente é raiz */

         MTZ_CondRetNaoPossuiFilho = 7 ,
               /* Nó corrente não possui filho na direção desejada */

         MTZ_CondRetFaltouMemoria = 8
               /* Faltou memória ao alocar dados */

   } MTZ_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MTZ Criar árvore
*
*  $ED Descrição da função
*     Cria uma nova árvore vazia.
*     Caso já exista uma árvore, esta será destruída.
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetFaltouMemoria
*
***********************************************************************/

   MTZ_tpCondRet MTZ_CriarArvore( void ) ;


/***********************************************************************
*
*  $FC Função: MTZ Destruir árvore
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da árvore, anulando a árvore corrente.
*     Faz nada caso a árvore corrente não exista.
*
***********************************************************************/

   void MTZ_DestruirArvore( void ) ;


/***********************************************************************
*
*  $FC Função: MTZ Adicionar filho à esquerda
*
*  $EP Parâmetros
*     $P ValorParm - valor a ser inserido no novo nó.
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetErroEstrutura
*     MTZ_CondRetFaltouMemoria
*     MTZ_CondRetNaoEhFolha     - caso não seja folha para a esquerda
*
***********************************************************************/

   MTZ_tpCondRet MTZ_InserirEsquerda( char ValorParm ) ;


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
*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     MTZ_CondRetOK
*     MTZ_CondRetArvoreNaoExiste
*     MTZ_CondRetArvoreVazia
*
***********************************************************************/

   MTZ_tpCondRet MTZ_ObterValorCorr( char * ValorParm ) ;

#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
