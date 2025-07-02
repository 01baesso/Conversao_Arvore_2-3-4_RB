/******************************************************************************
 * Arquivo: main.c
 *
 * Descrição: Função principal do trabalho
 *
 * Criadores:
 *            - LUCAS ALEXANDRE DOS SANTOS BAESSO - 2024007172
 *            - RAFAEL FERNANDO AURELIO RIBEIRO - 2024009426
 *
 * Data: 29/06/2025
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "./B-234/arvore234.h"
#include "./Rubro-negra/arvorerubronegra.h"
#include "./Conversor234-RB/conversor.h"

// *** MENU DE OPÇÕES ÁRVORE 2-3-4 *** //
void menu234() {
    printf("\nÁrvores Balanceadas 2-3-4 : Menu\n");
    printf("\t1. Inserir novo elemento na árvore 2-3-4\n");
    printf("\t2. Remover elemento da árvore 2-3-4\n");
    printf("\t3. Imprimir árvore 2-3-4\n");
    printf("\t4. Converter em uma árvore rubro-negra\n");
    printf("\t5. Métricas da árvore 2-3-4\n");
    printf("\t6. Sair\n");
    printf("Digite sua opção: ");
}

// *** MENU DE OPÇÕES ÁRVORE RUBRO-NEGRA *** //
void menuRB() {
    printf("\nÁrvores Balanceadas Rubro-Negra : Menu\n");
    printf("\t1. Inserir novo elemento na árvore rubro-negra\n");
    printf("\t2. Remover elemento da árvore rubro-negra\n");
    printf("\t3. Imprimir árvore rubro-negra\n");
    printf("\t4. Sair\n");
    printf("Digite sua opção: ");
}

int main () {
    /* Declaração de variáveis */
    FILE *arq;
    int valorInserirArvore, valorRemoverArvore, opcao234, opcaorubronegra, opcaoImpressao;
    char nomeArquivo[30];
    noRB *novoNoRB, *raizRB = NULL;
    no234 *novoNo234, *raiz234 = NULL;
    rb *arvoreRubroNegra;

    /* Alocação das métricas */
    Metricas234 *m = alocaMetricas();
    inicializacaoMetricas(m);

    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArquivo);

    /* Carregar os dados e montagem da árvore 2-3-4 */
    arq = fopen(nomeArquivo, "r");
    if (!arq) return 1;

    while (!feof(arq)) {
        fscanf(arq, "%d", &valorInserirArvore);
        insere234(&raiz234, valorInserirArvore, m);
    }

    /* Percorre a árvore e imprime com base na escolha */
    fclose(arq);
    printf("Como imprimir Árvore 2-3-4?\n");
    printf("\t1. Pré-ordem\n");
    printf("\t2. Em camadas\n");
    printf("Digite sua opção: ");
    scanf("%d", &opcaoImpressao);

    if (opcaoImpressao == 1) {
        printf("\nÁrvore 2-3-4 (pré-ordem):\n");
        percorreEmPreOrdem234(raiz234);
        printf("\n");
    } else {
        printf("\nÁrvore 2-3-4 (por camadas):\n");
        percorrePorCamadas234(raiz234);
    }

    // *** MENU DE OPÇÕES ÁRVORE 2-3-4 *** //
    menu234();
    scanf("%d", &opcao234);
    while (opcao234 != 6) {
        switch (opcao234) {
            case 1: 
                /* Inserir novo elemento na árvore 2-3-4 */
                printf("\n> Digite o elemento a ser inserido: ");
                scanf("%d", &valorInserirArvore);
                insere234(&raiz234, valorInserirArvore, m);
                break;
            case 2:
                /* Remover elemento da árvore 2-3-4 */
                printf("\n> Digite o elemento a ser removido: ");
                scanf("%d", &valorRemoverArvore);
                remove234(&raiz234, valorRemoverArvore, m);
                break;
            case 3:
                /* Imprimir árvore 2-3-4 */
                printf("\n> Como imprimir Árvore 2-3-4?\n");
                printf("\t1. Pré-ordem\n");
                printf("\t2. Em camadas (níveis)\n");
                printf("Digite sua opção: ");
                scanf("%d", &opcaoImpressao);

                if (opcaoImpressao == 1) {
                    printf("\nÁrvore 2-3-4 (pré-ordem): \n");
                    percorreEmPreOrdem234(raiz234);
                    printf("\n");
                } else {
                    printf("\nÁrvore 2-3-4 (por camadas): \n");
                    percorrePorCamadas234(raiz234);
                }
                break;
            case 4:
                /* Conversão da 2-3-4 para Rubro-Negra */
                arvoreRubroNegra = converte234ParaRB(raiz234);
                raizRB = retornaRaizRubroNegra(arvoreRubroNegra);
                
                /* Imprimir Rubro-Negra, informando a chave e sua respectiva cor */
                if (raizRB == getRBSentinelaFolha(arvoreRubroNegra)) {
                    printf("\nÁrvore rubro-negra está vazia.\n");
                } else {
                    printf("\nÁrvore Rubro-Negra (pré-ordem) - Formato: Chave -> Cor: \n");
                    percorreEmPreOrdemRubroNegra(arvoreRubroNegra, raizRB);
                }

                // *** MENU DE OPÇÕES ÁRVORE RUBRO-NEGRA *** //
                menuRB();
                scanf("%d", &opcaorubronegra);

                while (opcaorubronegra != 4) {
                    switch (opcaorubronegra) {
                    case 1:
                        /* Inserir elemento na árvore rubro-negra */
                        printf("\n> Digite o elemento a ser inserido: ");
                        scanf("%d", &valorInserirArvore);
                        novoNoRB = alocaNoRubroNegra(arvoreRubroNegra, valorInserirArvore);
                        if (!novoNoRB) return 1;
                        insereNoRubroNegra(arvoreRubroNegra, novoNoRB);
                        raizRB = retornaRaizRubroNegra(arvoreRubroNegra);
                        break;
                    case 2:
                        /* Remover elemento da árvore rubro-negra */
                        printf("\n> Digite o elemento a ser removido: ");
                        scanf("%d", &valorRemoverArvore);
                        removeNoRubroNegra(arvoreRubroNegra, valorRemoverArvore);
                        raizRB = retornaRaizRubroNegra(arvoreRubroNegra);
                        break;
                    case 3: 
                        /* Imprime a árvore Rubro-Negra em pré ordem */
                        raizRB = retornaRaizRubroNegra(arvoreRubroNegra);
                        printf("\nÁrvore Rubro-Negra (pré-ordem) - Formato: Chave -> Cor: \n");
                        percorreEmPreOrdemRubroNegra(arvoreRubroNegra, raizRB);
                        break;
                    default:
                        printf("\nOpção inválida!\n");
                    }

                    menuRB();
                    scanf("%d", &opcaorubronegra);
                }
                break;
            case 5:
                metricasAlturaBlocos(m, raiz234);
                printf("\nMétricas da árvore 2-3-4:\n");
                printf(" > Altura: %d\n", getAltura(m));
                printf(" > Blocos: %d\n", getBlocos(m));
                printf(" > Splits: %d\n", getSplits(m));
                printf(" > Merges: %d\n", getMerges(m));
                printf(" > Rotações: %d\n", getRotacoes(m));
                break;
            default:
                printf("\nOpção inválida!\n");
        }
        menu234();
        scanf("%d", &opcao234);
    }
    
    liberaArvore234(raiz234);
    fclose(arq);

    return 0;
}