/******************************************************************************
 * Arquivo: arvorerubronegra.h
 *
 * Descrição: Interface da árvore rubro-negra
 *
 * Criadores:
 *            - LUCAS ALEXANDRE DOS SANTOS BAESSO - 2024007172
 *            - RAFAEL FERNANDO AURELIO RIBEIRO - 2024009426
 *
 * Data: 29/06/2025
 ******************************************************************************/

#ifndef RB_RB_H
#define RB_RB_H

typedef struct RB rb;
typedef struct NO noRB;

//Função que aloca uma árvore RB
rb *alocaArvoreRubroNegra();

//Função que aloca um novo nó da árvore RB
noRB *alocaNoRubroNegra(rb *arv, int chave);

//Função iterativa que insere um novo nó na árvore e chama a função que ajusta o balanceamento
void insereNoRubroNegra(rb *arv, noRB *novoNo);

//Função que remove um nó da árvore RB
//Retorna 1 se o nó foi removido
//Retorna 0 se o elemento não foi encontrado na árvore
int removeNoRubroNegra(rb *arv, int valor);

//Percorre a árvore em ordem
//printf("%d -- %s\n", chave, cor)
void percorreEmPreOrdemRubroNegra(rb *arv, noRB *aux);

//Função que retorna a raiz da árvore
noRB *retornaRaizRubroNegra(rb *arv);

// ** FUNÇÕES DE BALANCEAMENTO DA RUBRO NEGRA ** //

//Função que corrige o balanceamento após a inserção
void balanceamentoInsercaoRubroNegra(rb *arv, noRB *novoNo);

//Função que corrige o balanceamento após a remoção
void balanceamentoRemocaoRubroNegra(rb *arv, noRB *noSucessor, noRB *noPai);

//Rotação à direita
void rotacaoDireitaRubroNegra(rb *arv, noRB *noDesbalanceado);

//Rotação à esquerda
void rotacaoEsquerdaRubroNegra(rb *arv, noRB *noDesbalanceado);

// ** FUNÇÕES ACESSORAS ** //

// Retorna o ponteiro para o nó sentinela folha (NULL interno)
noRB *getRBSentinelaFolha(rb *arv);

// Retorna o ponteiro para o nó sentinela raiz
noRB *getRBSentinelaRaiz(rb *arv);

// ** FUNÇÕES AUXILIARES PARA O CONVERSOR ** //

// Ajusta a cor de um nó RB ('P' ou 'V')
void setRBCor(noRB *no, char cor);

// Ajusta o ponteiro pai de um nó
void setRBPai(noRB *no, noRB *pai);

// Ajusta o filho esquerdo de um nó
void setRBFilhoEsq(noRB *no, noRB *filho);

// Ajusta o filho direito de um nó
void setRBFilhoDir(noRB *no, noRB *filho);

#endif //RB_RB_H