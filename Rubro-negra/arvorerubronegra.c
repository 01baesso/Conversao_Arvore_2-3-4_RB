/******************************************************************************
 * Arquivo: arvorerubronegra.c
 *
 * Descrição: Implementação da árvore rubro-negra
 *
 * Criadores:
 *            - LUCAS ALEXANDRE DOS SANTOS BAESSO - 2024007172
 *            - RAFAEL FERNANDO AURELIO RIBEIRO - 2024009426
 *
 * Data: 29/06/2025
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "arvorerubronegra.h"

/* Estrutura da árvore rubro-negra */
struct RB {
    noRB *sentinelaRaiz, *sentinelaFolha;
};

/* Estrutura do nó da árvore rubro-negra */
struct NO {
    int chave;
    char cor;
    noRB *filhoesq, *filhodir, *pai;
};

rb *alocaArvoreRubroNegra() {
    rb *arv = (rb*) malloc (sizeof(rb));
    if (!arv) return NULL;

    noRB *sentFolha = (noRB*) malloc (sizeof(noRB));
    if (!sentFolha) return NULL;
    sentFolha->chave = -1000;
    sentFolha->cor = 'P';
    sentFolha->filhoesq = sentFolha->filhodir = sentFolha->pai = NULL;
    arv->sentinelaFolha = sentFolha;

    noRB *sentRaiz = (noRB*) malloc (sizeof(noRB));
    if (!sentRaiz) return NULL;
    sentRaiz->chave = -1000;
    sentRaiz->cor = 'P';
    sentRaiz->filhoesq = sentRaiz->filhodir = arv->sentinelaFolha;
    sentRaiz->pai = NULL;
    arv->sentinelaRaiz = sentRaiz;

    return arv;
}

noRB *alocaNoRubroNegra(rb *arv, int chave) {
    noRB *novoNo = (noRB*) malloc (sizeof(noRB));
    if (!novoNo) return NULL;

    novoNo->chave = chave;
    novoNo->cor = 'V';
    novoNo->filhoesq = novoNo->filhodir = arv->sentinelaFolha;
    novoNo->pai = NULL;

    return novoNo;
}

void insereNoRubroNegra(rb *arv, noRB *novoNo) {
    noRB *pai = arv->sentinelaRaiz;
    noRB *aux = arv->sentinelaRaiz->filhodir;

    if (aux == arv->sentinelaFolha) {
        arv->sentinelaRaiz->filhodir = novoNo;
        novoNo->pai = arv->sentinelaRaiz;
        novoNo->cor = 'P';
        return;
    }

    while (aux != arv->sentinelaFolha) {
        pai = aux;
        aux = (novoNo->chave < aux->chave) ? aux->filhoesq : aux->filhodir;
    }

    novoNo->pai = pai;
    if (novoNo->chave < pai->chave) {
        pai->filhoesq = novoNo;
    } else {
        pai->filhodir = novoNo;
    }

    balanceamentoInsercaoRubroNegra(arv, novoNo);
}

int removeNoRubroNegra(rb *arv, int valor) {
    noRB *aux = arv->sentinelaRaiz->filhodir;
    noRB *pai = arv->sentinelaRaiz;

    while (aux != arv->sentinelaFolha && aux->chave != valor) {
        pai = aux;
        aux = (aux->chave > valor) ? aux->filhoesq : aux->filhodir;
    }

    if (aux == arv->sentinelaFolha) return 0;

    char corOriginal = aux->cor;
    noRB *noSucessor = arv->sentinelaFolha;
    noRB *paiSucessor = noSucessor->pai;

    if (aux->filhoesq != arv->sentinelaFolha && aux->filhodir != arv->sentinelaFolha) {
        noRB *predecessor = aux->filhoesq;

        while (predecessor->filhodir != arv->sentinelaFolha) {
            predecessor = predecessor->filhodir;
        }

        corOriginal = predecessor->cor;
        aux->chave = predecessor->chave;
        aux = predecessor;
        pai = aux->pai;
    }

    if (aux->filhoesq != arv->sentinelaFolha || aux->filhodir != arv->sentinelaFolha) {
        noRB *filho;

        if (aux->filhodir != arv->sentinelaFolha) {
            filho = aux->filhodir;
        } else {
            filho = aux->filhoesq;
        }

        if (aux == arv->sentinelaRaiz->filhodir) {
            arv->sentinelaRaiz->filhodir = filho;
        } else {
            if (pai->filhoesq == aux) {
                pai->filhoesq = filho;
            } else {
                pai->filhodir = filho;
            }
        }

        filho->pai = pai;

        if (corOriginal == 'P') {
            balanceamentoRemocaoRubroNegra(arv, filho, pai);
        }

        arv->sentinelaFolha->pai = NULL;
        free(aux);
        return 1;
    }

    if (aux == arv->sentinelaRaiz->filhodir) {
        arv->sentinelaRaiz->filhodir = arv->sentinelaFolha;
    } else {
        if (pai->filhoesq == aux) {
            pai->filhoesq = arv->sentinelaFolha;
        } else {
            pai->filhodir = arv->sentinelaFolha;
        }
    }

    arv->sentinelaFolha->pai = pai;
    if (corOriginal == 'P') {
        balanceamentoRemocaoRubroNegra(arv, arv->sentinelaFolha, arv->sentinelaFolha->pai);
    }

    arv->sentinelaFolha->pai = NULL;
    free(aux);
    return 1;
}

void percorreEmPreOrdemRubroNegra(rb *arv, noRB *aux) {
    if (!arv || aux == arv->sentinelaFolha) return;
    
    printf("%d -> %c\n", aux->chave, aux->cor);
    percorreEmPreOrdemRubroNegra(arv, aux->filhoesq);
    percorreEmPreOrdemRubroNegra(arv, aux->filhodir);
}

noRB *retornaRaizRubroNegra(rb *arv) {
    if (arv == NULL) return NULL;
    return arv->sentinelaRaiz->filhodir;
}

void balanceamentoInsercaoRubroNegra(rb *arv, noRB *novoNo) {
    noRB *y;
    while (novoNo->pai->cor == 'V') {
        if (novoNo->pai == novoNo->pai->pai->filhoesq) { // Está a esquerda do avô
            y = novoNo->pai->pai->filhodir;

            if (y->cor == 'V') { // Caso 1
                novoNo->pai->cor = 'P';
                y->cor = 'P';
                novoNo->pai->pai->cor = 'V';
                novoNo = novoNo->pai->pai;
            } else {
                if (novoNo == novoNo->pai->filhodir) { // Caso 2
                    novoNo = novoNo->pai;
                    rotacaoEsquerdaRubroNegra(arv, novoNo);
                }
                novoNo->pai->cor = 'P'; // Caso 3
                novoNo->pai->pai->cor = 'V';
                rotacaoDireitaRubroNegra(arv, novoNo->pai->pai);
            }
        } else { // Está a direita do avô
            y = novoNo->pai->pai->filhoesq;

            if (y->cor == 'V') { // Caso 1
                novoNo->pai->cor = 'P';
                y->cor = 'P';
                novoNo->pai->pai->cor = 'V';
                novoNo = novoNo->pai->pai;
            } else {
                if (novoNo == novoNo->pai->filhoesq) { // Caso 2
                    novoNo = novoNo->pai;
                    rotacaoDireitaRubroNegra(arv, novoNo);
                }
                novoNo->pai->cor = 'P'; // Caso 3
                novoNo->pai->pai->cor = 'V';
                rotacaoEsquerdaRubroNegra(arv, novoNo->pai->pai);
            }
        }
    }
    arv->sentinelaRaiz->filhodir->cor = 'P';
}

void balanceamentoRemocaoRubroNegra(rb *arv, noRB *noSucessor, noRB *noPai) {
    noRB *irmao;

    while (noSucessor != arv->sentinelaRaiz->filhodir && noSucessor->cor == 'P') {
        if (noSucessor == noPai->filhoesq) { // Está a esquerda do pai
            irmao = noPai->filhodir;
            if (irmao->cor == 'V') { // Caso 1
                irmao->cor = 'P';
                noPai->cor = 'V';
                rotacaoEsquerdaRubroNegra(arv, noPai);
                irmao = noPai->filhodir;
            }

            if (irmao->cor == 'P' && irmao->filhodir->cor == 'P' && irmao->filhoesq->cor == 'P') { // Caso 2
                irmao->cor = 'V';
                noSucessor = noSucessor->pai;
            } else {
                if (irmao->cor == 'P' && irmao->filhoesq->cor == 'V') { // Caso 3
                    irmao->filhoesq->cor = 'P';
                    irmao->cor = 'V';
                    rotacaoDireitaRubroNegra(arv, irmao);
                    irmao = noPai->filhodir;
                }

                // Caso 4
                irmao->cor = noPai->cor;
                noPai->cor = 'P';
                irmao->filhodir->cor = 'P';
                rotacaoEsquerdaRubroNegra(arv, noPai);
                noSucessor = arv->sentinelaRaiz->filhodir;
            }
        } else { // Está a direita do pai
            irmao = noPai->filhoesq;
            if (irmao->cor == 'V') { // Caso 1
                irmao->cor = 'P';
                noPai->cor = 'V';
                rotacaoDireitaRubroNegra(arv, noPai);
                irmao = noPai->filhoesq;
            }

            if (irmao->cor == 'P' && irmao->filhoesq->cor == 'P' && irmao->filhodir->cor == 'P') { // Caso 2
                irmao->cor = 'V';
                noSucessor = noSucessor->pai;
            } else {
                if (irmao->cor == 'P' && irmao->filhodir->cor == 'V') { // Caso 3
                    irmao->filhodir->cor = 'P';
                    irmao->cor = 'V';
                    rotacaoEsquerdaRubroNegra(arv, irmao);
                    irmao = noPai->filhoesq;
                }

                // Caso 4
                irmao->cor = noPai->cor;
                noPai->cor = 'P';
                irmao->filhoesq->cor = 'P';
                rotacaoDireitaRubroNegra(arv, noPai);
                noSucessor = arv->sentinelaRaiz->filhodir;
            }
        }
    }

    noSucessor->cor = 'P';
}

void rotacaoDireitaRubroNegra(rb *arv, noRB *noDesbalanceado) {
    noRB *filho = noDesbalanceado->filhoesq;
    noDesbalanceado->filhoesq = filho->filhodir;

    if (filho->filhodir != arv->sentinelaFolha) {
        filho->filhodir->pai = noDesbalanceado;
    }

    filho->pai = noDesbalanceado->pai;

    if (noDesbalanceado->pai == arv->sentinelaRaiz) {
        arv->sentinelaRaiz->filhodir = filho;
    } else {
        if (noDesbalanceado == noDesbalanceado->pai->filhoesq) {
            noDesbalanceado->pai->filhoesq = filho;
        } else {
            noDesbalanceado->pai->filhodir = filho;
        }
    }

    filho->filhodir = noDesbalanceado;
    noDesbalanceado->pai = filho;
}

void rotacaoEsquerdaRubroNegra(rb *arv, noRB *noDesbalanceado) {
    noRB *filho = noDesbalanceado->filhodir;
    noDesbalanceado->filhodir = filho->filhoesq;

    if (filho->filhoesq != arv->sentinelaFolha) {
        filho->filhoesq->pai = noDesbalanceado;
    }

    filho->pai = noDesbalanceado->pai;

    if (noDesbalanceado->pai == arv->sentinelaRaiz) {
        arv->sentinelaRaiz->filhodir = filho;
    } else {
        if (noDesbalanceado == noDesbalanceado->pai->filhoesq) {
            noDesbalanceado->pai->filhoesq = filho;
        } else {
            noDesbalanceado->pai->filhodir = filho;
        }
    }

    filho->filhoesq = noDesbalanceado;
    noDesbalanceado->pai = filho;
}

// *** FUNÇÕES AUXILIARES PARA O CONVERSOR *** //

noRB *getRBSentinelaFolha(rb *arv) {
    return arv->sentinelaFolha;
}

noRB *getRBSentinelaRaiz(rb *arv) {
    return arv->sentinelaRaiz;
}

void setRBCor(noRB *no, char cor) {
    no->cor = cor;
}

void setRBPai(noRB *no, noRB *pai) {
    no->pai = pai;
}

void setRBFilhoEsq(noRB *no, noRB *filho) {
    no->filhoesq = filho;
}

void setRBFilhoDir(noRB *no, noRB *filho) {
    no->filhodir = filho;
}