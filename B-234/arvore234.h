/******************************************************************************
 * Arquivo: arvore234.h
 *
 * Descrição: Interface da árvore 2-3-4 e suas métricas
 *
 * Criadores:
 *            - LUCAS ALEXANDRE DOS SANTOS BAESSO - 2024007172
 *            - RAFAEL FERNANDO AURELIO RIBEIRO - 2024009426
 *
 * Data: 29/06/2025
 ******************************************************************************/

#ifndef B234_H
#define B234_H

// *** FUNÇÕES ÁRVORE 2-3-4 *** //

typedef struct NO no234;
typedef struct Metricas234 Metricas234;

// Função que aloca um novo nó da árvore 234, indicando se é folha ou não
no234 *alocaNo234(int folha);

// Função que divide o filho 'filho' de 'pai' no índice index
void splitFilho234(no234 *pai, int index, Metricas234 *m);

// Função que insere uma chave em um nó não cheio (ordenadamente)
void insereNaoCheio234(no234 *no, int chave, Metricas234 *m);

// Função que insere uma chave na árvore (ajusta a raiz se necessário)
void insere234(no234 **raiz, int chave, Metricas234 *m);

// Função que busca e verifica que se uma chave é existente na árvore
int buscar234(no234 *raiz, int chave);

// Função que retorna o primerio índice i tal que no->chaves[i] >= chave
int buscaChave234 (no234 *no, int chave);

// Função que remove a chave no índice 'index' de um nó folha
void removeFolha234(no234 *no, int index);

// Função que localiza e retorna o predecessor (maior chave do filho 'index')
int getPredecessor234(no234 *no, int index);

// Função que localiza e retorna o sucessor (menor chave do filho 'index' + 1)
int getSucessor234(no234 *no, int index);

// Função que realiza a 'rotação', ou seja, empresta a chave do irmão à esquerda (filho 'index' recede de 'index' - 1)
void emprestaEsq234(no234 *no, int index, Metricas234 *m);

// Função que realiza a 'rotação', ou seja, empresta a chave do irmão à direita (filho 'index' recebe de 'index' + 1)
void emprestaDir234(no234 *no, int index, Metricas234 *m);

// Função que funde (merge) o filho 'index' com 'index + 1' (puxa a chave 'index' do pai para o meio)
void merge234(no234 *no, int index, Metricas234 *m);

// Função que verifica e garante que filho 'index' tenha pelo menos t (nro mínimo) chaves
void verificaNroChaves234(no234 *no, int index, Metricas234 *m);

// Função que remove a chave k da sub-árvore com raiz 'no'
void removeHandler234(no234 *no, int k, Metricas234 *m);

// Função pública de remoção da árvore
void remove234(no234 **raiz, int k, Metricas234 *m);

// Função que imprime a árvore em pré-ordem
void percorreEmPreOrdem234(no234 *raiz);

// Função que imprime a árvore por camadas
void percorrePorCamadas234(no234 *raiz);

// Função que da free (libera) na árvore
void liberaArvore234(no234 *raiz);

// *** FUNÇÕES PARA MÉTRICAS DA ÁRVORE 2-3-4 *** //

// Função que aloca uma nova estrutura de métricas
Metricas234 *alocaMetricas();

// Função utilizada para inicializar todas as métricas com 0
void inicializacaoMetricas(Metricas234 *m);

// Função que calcula a altura da árvore
int altura234(no234 *no);

// Função que calcula a quantidade de blocos da árvore
int nos234(no234 *no);

// Função que chama as funçoes 'altura234' e 'nos234' para realizar os calculos de altura e quantidade de blocos
void metricasAlturaBlocos(Metricas234 *m, no234 *raiz);

// ** FUNÇÕES ACESSORAS ** //

// Função que retorna o número de chaves de um nó 'n'
int getBNumChaves(no234 *n);

// Função que retorna a i-ésima chave (0 ≤ i < getBNumChaves)
int getBChave(no234 *n, int i);

// Função que retorna o j-ésimo filho (0 ≤ j ≤ getBNumChaves)
no234 *getBFilho(no234 *n, int j);

// Função que retorna a quantidade de splits realizados pela árvore
int getSplits(Metricas234 *m);

// Função que retorna a quantidade de rotações realizadas pela árvore
int getRotacoes(Metricas234 *m);

// Função que retorna a quantidade de merges realizados pela árvore
int getMerges(Metricas234 *m);

// Função que retorna a altura da árvore
int getAltura(Metricas234 *m);

// Função que retorna a quantidade de blocos da árvore
int getBlocos(Metricas234 *m);

#endif //B234_H