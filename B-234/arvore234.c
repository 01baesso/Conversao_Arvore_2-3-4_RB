/******************************************************************************
 * Arquivo: arvore234.c
 *
 * Descrição: Implementação da árvore 2-3-4 e das suas métricas
 *
 * Criadores:
 *            - LUCAS ALEXANDRE DOS SANTOS BAESSO - 2024007172
 *            - RAFAEL FERNANDO AURELIO RIBEIRO - 2024009426
 *
 * Data: 29/06/2025
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "arvore234.h"

#define MAX_KEYS 3
#define MIN_KEYS (MAX_KEYS/2)


/* Estrutura do nó da árvore 2-3-4 */
struct NO {
    int nroChaves, chaves[MAX_KEYS], folha;
    no234 *filhos[MAX_KEYS + 1];
};

struct Metricas234 {
    int splits; // número de splits realizados
    int rotacoes; // número de rotações realizadas (se usado)
    int merges; // número de merges realizados
    int altura; // altura da árvore após operação
    int blocos; // número de nós (blocos) na árvore
};

no234 *alocaNo234(int folha) {
    no234 *novoNo = (no234*) malloc (sizeof(no234));
    if (!novoNo) return NULL;

    novoNo->nroChaves = 0;
    novoNo->folha = folha;

    for (int i = 0; i < MAX_KEYS + 1; i++) {
        novoNo->filhos[i] = NULL;
    }

    return novoNo;
}

void splitFilho234(no234 *pai, int index, Metricas234 *m) {
    m->splits++;
    no234 *filho = pai->filhos[index];
    no234 *novoFilho = alocaNo234(filho->folha);
    int t = 2;  // Grau mínimo

    // Novo nó recebe t - 1 = 1 chaves (a última chave do filho)
    novoFilho->nroChaves = t - 1;
    novoFilho->chaves[0] = filho->chaves[t];  // Index 2

    // Se não for folha, move os últimos filhos
    if (!filho->folha) {
        novoFilho->filhos[0] = filho->filhos[t];
        novoFilho->filhos[1] = filho->filhos[t+1];
    }

    // Filho original fica com t - 1 chaves
    filho->nroChaves = t - 1;

    // Ajusta ponteiros de filho no pai para inserir o novo filho
    for(int j = pai->nroChaves; j >= index + 1; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }    
    pai->filhos[index + 1] = novoFilho;

    // Move chaves no pai para abrir espaço
    for(int j = pai->nroChaves - 1; j >= index; j--)
        pai->chaves[j + 1] = pai->chaves[j];

    // Sobe a chave mediana do filho para o pai
    pai->chaves[index] = filho->chaves[t-1];  // Index 1
    pai->nroChaves++;
}

void insereNaoCheio234(no234 *no, int chave, Metricas234 *m) {
    int i = no->nroChaves - 1;
    
    if (no->folha) {
        // Insere em folha, mantendo ordenação
        while (i >= 0 && no->chaves[i] > chave) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->nroChaves++;
    } else {
        // Escolhe o filho correto
        while (i >= 0 && no->chaves[i] > chave) {
            i--;
        }
        i++;

        // Se filho cheio, divide-o
        if (no->filhos[i]->nroChaves == MAX_KEYS) {
            splitFilho234(no, i, m);
            if (no->chaves[i] < chave) i++;
        }

        insereNaoCheio234(no->filhos[i], chave, m);
    }
}

void insere234(no234 **raiz, int chave, Metricas234 *m) {
    if (*raiz == NULL) {
        *raiz = alocaNo234(1);
        (*raiz)->chaves[0] = chave;
        (*raiz)->nroChaves = 1;
    } else {
        no234 *r = *raiz;
        if (r->nroChaves == MAX_KEYS) {
            no234 *novo = alocaNo234(0);
            novo->filhos[0] = r;
            splitFilho234(novo, 0, m);
            *raiz = novo;
        }
        insereNaoCheio234(*raiz, chave, m);
    }
}

int buscar234(no234 *raiz, int chave) {
    if (raiz == NULL) return 0; // Árvore vazia

    int i = 0;

    // Procura a primeira chave >= chave procurada
    while (i < raiz->nroChaves && chave > raiz->chaves[i])
        i++;
    
    // Chave foi encontrada
    if (i < raiz->nroChaves && chave == raiz->chaves[i])
        return 1;
    
    // Se é folha e não encontrou
    if (raiz->folha)
        return 0;
    
    // Continua buscando no filho apropriado
    return buscar234(raiz->filhos[i], chave);
}

int buscaChave234 (no234 *no, int chave) {
    if (!no) return 0;  // Proteção contra nó NULL
    
    int idx = 0;
    while (idx < no->nroChaves && no->chaves[idx] < chave)
        ++idx;
    return idx;
}

void removeFolha234(no234 *no, int index) {
    for (int i = index + 1; i < no->nroChaves; i++)
        no->chaves[i - 1] = no->chaves[i];

    no->nroChaves--;
}

int getPredecessor234(no234 *no, int index) {
    no234 *atual = no->filhos[index];

    while (!atual->folha)
        atual = atual->filhos[atual->nroChaves];

    return atual->chaves[atual->nroChaves - 1];
}

int getSucessor234(no234 *no, int index) {
    no234 *atual = no->filhos[index + 1];

    while (!atual->folha)
        atual = atual->filhos[0];

    return atual->chaves[0];
}

void emprestaEsq234(no234 *no, int index, Metricas234 *m) {
    m->rotacoes++;
    no234 *filho = no->filhos[index];
    no234 *irmaoEsq = no->filhos[index - 1];

    // Move chaves de filho para a direita
    for (int i = filho->nroChaves - 1; i >= 0; --i)
        filho->chaves[i + 1] = filho->chaves[i];

    // Move filhos também, se existir
    if (!filho->folha) {
        for (int i = filho->nroChaves; i >= 0; --i)
            filho->filhos[i + 1] = filho->filhos[i];
    }
    
    // Transferência de uma chave do pai para filho
    filho->chaves[0] = no->chaves[index - 1];
    if (!filho->folha)
        filho->filhos[0] = irmaoEsq->filhos[irmaoEsq->nroChaves];

    // Move a última chave do irmao para o pai
    no->chaves[index - 1] = irmaoEsq->chaves[irmaoEsq->nroChaves - 1];

    filho->nroChaves += 1;
    irmaoEsq->nroChaves -= 1;
}

void emprestaDir234(no234 *no, int index, Metricas234 *m) {
    m->rotacoes++;
    no234 *filho = no->filhos[index];
    no234 *irmaoDir = no->filhos[index + 1];

    // Move chave do pai para o final de filho
    filho->chaves[filho->nroChaves] = no->chaves[index];
    if (!filho->folha)
        filho->filhos[filho->nroChaves + 1] = irmaoDir->filhos[0];

    // A primeira chave do irmao sobe para o pai
    no->chaves[index] = irmaoDir->chaves[0];

    // Shift left no irmão
    for (int i = 1; i < irmaoDir->nroChaves; ++i)
        irmaoDir->chaves[i - 1] = irmaoDir->chaves[i];
    
    if (!irmaoDir->folha) {
        for(int i = 1; i <= irmaoDir->nroChaves; ++i)
            irmaoDir->filhos[i-1] = irmaoDir->filhos[i];
    }

    filho->nroChaves += 1;
    irmaoDir->nroChaves -= 1;
}

void merge234(no234 *no, int index, Metricas234 *m) {
    m->merges++;
    no234 *filho = no->filhos[index];
    no234 *irmaoDir = no->filhos[index + 1];

    // Puxa a chave do pai para a posição t - 1 de filho
    filho->chaves[MIN_KEYS] = no->chaves[index];
    
    // Copia chaves do irmão para filho
    for (int i = 0; i < irmaoDir->nroChaves; ++i)
        filho->chaves[i + MIN_KEYS + 1] = irmaoDir->chaves[i];

    // Copia filhos do irmão se não folha
    if (!filho->folha) {
        for (int i = 0; i <= irmaoDir->nroChaves; ++i)
            filho->filhos[i + MIN_KEYS + 1] = irmaoDir->filhos[i];
    }
    filho->nroChaves += 1 + irmaoDir->nroChaves;

    // Ajusta pai após remoção da chave index
    for(int i = index + 1; i < no->nroChaves; ++i)
        no->chaves[i - 1] = no->chaves[i];

    for(int i = index + 2; i <= no->nroChaves; ++i)
        no->filhos[i - 1] = no->filhos[i];

    no->nroChaves--;
    free(irmaoDir);
}

void verificaNroChaves234(no234 *no, int index, Metricas234 *m) {
    if (index != 0 && no->filhos[index - 1]->nroChaves >= MIN_KEYS + 1) {
        emprestaEsq234(no, index, m);
    } else if (index != no->nroChaves && no->filhos[index + 1]->nroChaves >= MIN_KEYS + 1) {
        emprestaDir234(no, index, m);
    } else {
        if (index != no->nroChaves) {
            merge234(no, index, m);
        } else {
            merge234(no, index - 1, m);
        }
    }
}

void removeHandler234(no234 *no, int k, Metricas234 *m) {
    int index = buscaChave234(no, k);

    // Caso: chave está presente neste nó
    if (index < no->nroChaves && no->chaves[index] == k) {
        if (no->folha) {// Caso 1: nó folha  
            removeFolha234(no, index);
        } else {
            // Caso 2: nó intermediário
            if (no->filhos[index]->nroChaves >= MIN_KEYS + 1) {
                // Predecessor existe
                int pred = getPredecessor234(no, index);
                no->chaves[index] = pred;
                removeHandler234(no->filhos[index], pred, m);
            } else if (no->filhos[index + 1]->nroChaves >= MIN_KEYS + 1) {
                // Sucessor existe
                int succ = getSucessor234(no, index);
                no->chaves[index] = succ;
                removeHandler234(no->filhos[index + 1], succ, m);
            } else {
                // Funde os dois filhos e continua a remoção
                merge234(no, index, m);
                removeHandler234(no->filhos[index], k, m);
            }
        }
    } else {
        // Caso 3: chave não está neste nó
        if (no->folha) {
            // Não encontrada
            printf("A chave %d não existe na árvore\n", k);
            return;
        }

        // Define se é o último filho
        int flag = (index == no->nroChaves) ? 1 : 0;

        // Garante que o filho tenha pelo menos t chaves
        if (no->filhos[index]->nroChaves < MIN_KEYS + 1)
            verificaNroChaves234(no, index, m);

        // Se fundiu com o último filho, ajusta índice
        if (flag && index > no->nroChaves) {
            removeHandler234(no->filhos[index - 1], k, m);
        } else {
            removeHandler234(no->filhos[index], k, m);
        }
    }
}

void remove234(no234 **raiz, int k, Metricas234 *m) {
    if (!*raiz) return;
    removeHandler234(*raiz, k, m);

    // Se a raiz ficar vazia (0 chaves), ajusta
    if ((*raiz)->nroChaves == 0) {
        no234 *aux = *raiz;
        if (!(*raiz)->folha) {
            *raiz = (*raiz)->filhos[0];
        } else {
            *raiz = NULL;
        }
        free(aux);
    }
}

void percorreEmPreOrdem234(no234 *raiz) {
    if (raiz == NULL) return;

    for (int i = 0; i < raiz->nroChaves; i++) {
        printf("%d ", raiz->chaves[i]);
    }

    for (int i = 0; i<= raiz->nroChaves; i++) {
        percorreEmPreOrdem234(raiz->filhos[i]);
    }
}

void percorrePorCamadas234(no234 *raiz) {
    if (raiz == NULL) return;

    no234 *nivelAtual[1024];
    no234 *proximoNivel[1024];
    int contagemAtual = 1, proximaContagem = 0;
    int nivel = 0;

    nivelAtual[0] = raiz;

    while (contagemAtual > 0) {
        printf("Nivel %d: ", nivel);
        proximaContagem = 0;

        for (int i = 0; i < contagemAtual; i++) {
            no234 *no = nivelAtual[i];

            printf("[");
            for (int j = 0; j < no->nroChaves; j++) {
                printf("%04d", no->chaves[j]);
                if (j < no->nroChaves - 1) printf(" ");
            }
            printf("] ");

            if (!no->folha) {
                for (int j = 0; j <= no->nroChaves; j++) {
                    if (no->filhos[j] != NULL) {
                        proximoNivel[proximaContagem++] = no->filhos[j];
                    }
                }
            }
        }

        printf("\n");

        // Prepara próximo nível
        for (int i = 0; i < proximaContagem; i++) {
            nivelAtual[i] = proximoNivel[i];
        }
        contagemAtual = proximaContagem;
        nivel++;
    }
}

void liberaArvore234(no234 *raiz) {
    if (!raiz) return;
    for (int i = 0; i <= raiz->nroChaves; i++) 
        liberaArvore234(raiz->filhos[i]);
    free(raiz);
}

// *** FUNÇÕES ACESSORAS UTILIZADAS PELO CONVERSOR *** //

int getBNumChaves(no234 *n) { 
    return n->nroChaves; 
}

int getBChave(no234 *n, int i) { 
    return n->chaves[i]; 
}

no234 *getBFilho(no234 *n, int j) { 
    return n->filhos[j]; 
}

// *** FUNÇÕES ENVOLVENDO AS MÉTRICAS PARA A ANÁLISE DA ÁRVORE 2-3-4 *** //

Metricas234 *alocaMetricas() {
    Metricas234 *m = (Metricas234 *) malloc (sizeof(Metricas234));
    if (!m) {
        return NULL;
    }

    return m;
}

void inicializacaoMetricas(Metricas234 *m) {
    m->splits = 0;
    m->rotacoes = 0;
    m->merges = 0;
    m->altura = 0;
    m->blocos = 0;
}

int altura234(no234 *no) {
    if (!no) return 0;
    int h = 0;
    for (int i = 0; i <= no->nroChaves; i++) {
        int ch = altura234(no->filhos[i]);
        if (ch > h) h = ch;
    }
    return h + 1;
}

int nos234(no234 *no) {
    if (!no) return 0;
    int contagem = 1;
    for (int i = 0; i <= no->nroChaves; i++) {
        contagem += nos234(no->filhos[i]);
    }
    return contagem;
}

void metricasAlturaBlocos(Metricas234 *m, no234 *raiz) {
    m->altura = altura234(raiz);
    m->blocos = nos234(raiz);
}

int getSplits(Metricas234 *m) {
    return m->splits;
}

int getRotacoes(Metricas234 *m) {
    return m->rotacoes;
}

int getMerges(Metricas234 *m) {
    return m->merges;
}

int getAltura(Metricas234 *m) {
    return m->altura;
}

int getBlocos(Metricas234 *m) {
    return m->blocos;
}