/******************************************************************************
 * Arquivo: testes234.c
 *
 * Descrição: Implementação dos testes realizados sobre a árvore 2-3-4
 *
 * Criadores:
 *            - LUCAS ALEXANDRE DOS SANTOS BAESSO - 2024007172
 *            - RAFAEL FERNANDO AURELIO RIBEIRO - 2024009426
 *
 * Data: 29/06/2025
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../B-234/arvore234.h"

#define MAX_CAMINHO 256
#define NUM_TESTES 10

void ordemCrescente(int *vet, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vet[i] = i + 1;
    }
}

void ordemDecrescente(int *vet, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vet[i] = tamanho - i;
    }
}

void ordemAleatoria(int *vet, int tamanho) {
    for(int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = vet[i];
        vet[i] = vet[j];
        vet[j] = tmp;
    }
}

// Escrita de arquivo .txt
void geraArquivoTxt(const char *caminho, int *vet, int tamanho) {
    FILE *f = fopen(caminho, "w");
    if (f == NULL) {
        printf("Erro ao criar arquivo: %s\n", caminho);
        return;
    }

    for(int i = 0; i < tamanho; i++) {
        fprintf(f, "%d ", vet[i]);
    }
    fclose(f);
}

// Teste de inserção: insere todos os valores de vet na B-tree e grava métricas
void testeInsercao(int *vet, int tamanho, const char *label, FILE *csvInsercao, Metricas234 *m) {
    no234 *raiz = NULL;
    inicializacaoMetricas(m); // Reseta todos os contadores
    
    for (int i = 0; i < tamanho; i++) {
        insere234(&raiz, vet[i], m);
    }

    metricasAlturaBlocos(m, raiz);
    
    int splits = getSplits(m);
    int altura = getAltura(m); 
    int blocos = getBlocos(m); 
    
    // Formato: Tipo,Ordem,Tamanho,Splits,Altura,Blocos
    fprintf(csvInsercao, "Insercao,%s,%d,%d,%d,%d\n", label, tamanho, splits, altura, blocos);
    
    liberaArvore234(raiz);
}

// Teste de remoção: reconstrói a árvore, remove 'porcentagem'% e grava métricas
void testeRemocao(int *vetCompleto, int tamanho, const char *label, double porcentagem, FILE *csvRemocao, Metricas234 *m) {
    no234 *raiz = NULL;
    inicializacaoMetricas(m); // Reseta todos os contadores
    
    int *vet = malloc(tamanho * sizeof(int));
    memcpy(vet, vetCompleto, tamanho * sizeof(int));

    // Reconstruir a árvore completa
    for (int i = 0; i < tamanho; i++) {
        insere234(&raiz, vet[i], m);
    }
    
    // Resetar contadores após construção (só queremos contar as remoções)
    inicializacaoMetricas(m);

    // Embaralhar e remover 'porcentagem'%
    ordemAleatoria(vet, tamanho);
    int tamanhoPercentual = (int)(tamanho * porcentagem + 0.5);

    for (int i = 0; i < tamanhoPercentual; i++) {
        remove234(&raiz, vet[i], m);
    }

    metricasAlturaBlocos(m, raiz);

    int rotacoes = getRotacoes(m);
    int merges = getMerges(m);
    int altura = getAltura(m);
    int blocos = getBlocos(m);
    
    // Formato: Tipo,Ordem,Porcentagem,Tamanho,Rotações,Merges,Altura,Blocos
    fprintf(csvRemocao, "Remocao,%s,%.0f%%,%d,%d,%d,%d,%d\n", label, porcentagem * 100, tamanho, rotacoes, merges, altura, blocos);
    
    free(vet);
    liberaArvore234(raiz);
}

int main () {
    Metricas234 *m = alocaMetricas();
    if (m == NULL) {
        printf("Erro ao alocar memória para métricas!\n");
        return 1;
    }
    srand((unsigned)time(NULL)); // Necessário para testes aleatórios
    
    // Criar diretório de testes
    system("mkdir -p resultadostestes234");

    // Abrir arquivos CSV separados para métricas
    FILE *csvInsercao = fopen("resultadostestes234/metricas_insercao.csv", "w");
    if (csvInsercao == NULL) {
        printf("Erro ao criar arquivo de métricas de inserção!\n");
        return 1;
    }
    
    FILE *csvRemocao = fopen("resultadostestes234/metricas_remocao.csv", "w");
    if (csvRemocao == NULL) {
        printf("Erro ao criar arquivo de métricas de remoção!\n");
        fclose(csvInsercao);
        return 1;
    }
    
    // Cabeçalhos dos CSVs
    fprintf(csvInsercao, "Tipo,Ordem,Tamanho,Splits,Altura,Blocos\n");
    fprintf(csvRemocao, "Tipo,Ordem,Porcentagem,Tamanho,Rotacoes,Merges,Altura,Blocos\n");

    // Alocar buffers
    int *vet100 = malloc(100 * sizeof(int));
    int *vet1000 = malloc(1000 * sizeof(int));
    int *vet10000 = malloc(10000 * sizeof(int));
    int *vet100000 = malloc(100000 * sizeof(int));

    printf("=== GERANDO ARQUIVOS DE TESTE ===\n");
    
    // 1) Gerar e salvar sequências crescentes
    ordemCrescente(vet100, 100);
    ordemCrescente(vet1000, 1000);
    ordemCrescente(vet10000, 10000);
    ordemCrescente(vet100000, 100000);
    
    geraArquivoTxt("resultadostestes234/crescente_100.txt", vet100, 100);
    geraArquivoTxt("resultadostestes234/crescente_1000.txt", vet1000, 1000);
    geraArquivoTxt("resultadostestes234/crescente_10000.txt", vet10000, 10000);
    geraArquivoTxt("resultadostestes234/crescente_100000.txt", vet100000, 100000);

    // 2) Gerar e salvar sequências decrescentes
    ordemDecrescente(vet100, 100);
    ordemDecrescente(vet1000, 1000);
    ordemDecrescente(vet10000, 10000);
    ordemDecrescente(vet100000, 100000);
    
    geraArquivoTxt("resultadostestes234/decrescente_100.txt", vet100, 100);
    geraArquivoTxt("resultadostestes234/decrescente_1000.txt", vet1000, 1000);
    geraArquivoTxt("resultadostestes234/decrescente_10000.txt", vet10000, 10000);
    geraArquivoTxt("resultadostestes234/decrescente_100000.txt", vet100000, 100000);

    // 3) Gerar 40 arquivos aleatórios (10 para cada tamanho)
    char caminho[MAX_CAMINHO];
    for (int t = 1; t <= NUM_TESTES; t++) {
        // Resetar para sequência inicial e embaralhar
        ordemCrescente(vet100, 100);
        ordemAleatoria(vet100, 100);
        sprintf(caminho, "resultadostestes234/rand_100_test%d.txt", t);
        geraArquivoTxt(caminho, vet100, 100);

        ordemCrescente(vet1000, 1000);
        ordemAleatoria(vet1000, 1000);
        sprintf(caminho, "resultadostestes234/rand_1000_test%d.txt", t);
        geraArquivoTxt(caminho, vet1000, 1000);

        ordemCrescente(vet10000, 10000);
        ordemAleatoria(vet10000, 10000);
        sprintf(caminho, "resultadostestes234/rand_10000_test%d.txt", t);
        geraArquivoTxt(caminho, vet10000, 10000);

        ordemCrescente(vet100000, 100000);
        ordemAleatoria(vet100000, 100000);
        sprintf(caminho, "resultadostestes234/rand_100000_test%d.txt", t);
        geraArquivoTxt(caminho, vet100000, 100000);
    }

    printf("=== EXECUTANDO TESTES DE INSERÇÃO ===\n");
    
    // Testes de inserção - Crescente
    printf("Testando inserções crescentes...\n");
    ordemCrescente(vet100, 100);
    testeInsercao(vet100, 100, "crescente_100", csvInsercao, m);
    
    ordemCrescente(vet1000, 1000);
    testeInsercao(vet1000, 1000, "crescente_1000", csvInsercao, m);
    
    ordemCrescente(vet10000, 10000);
    testeInsercao(vet10000, 10000, "crescente_10000", csvInsercao, m);
    
    ordemCrescente(vet100000, 100000);
    testeInsercao(vet100000, 100000, "crescente_100000", csvInsercao, m);

    // Testes de inserção - Decrescente
    printf("Testando inserções decrescentes...\n");
    ordemDecrescente(vet100, 100);
    testeInsercao(vet100, 100, "decrescente_100", csvInsercao, m);
    
    ordemDecrescente(vet1000, 1000);
    testeInsercao(vet1000, 1000, "decrescente_1000", csvInsercao, m);
    
    ordemDecrescente(vet10000, 10000);
    testeInsercao(vet10000, 10000, "decrescente_10000", csvInsercao, m);
    
    ordemDecrescente(vet100000, 100000);
    testeInsercao(vet100000, 100000, "decrescente_100000", csvInsercao, m);

    // Testes de inserção - Aleatório
    printf("Testando inserções aleatórias...\n");
    for(int t = 1; t <= NUM_TESTES; t++) {
        // Recriar as sequências aleatórias para cada teste
        ordemCrescente(vet100, 100);
        ordemAleatoria(vet100, 100);
        sprintf(caminho, "rand_100_test%d", t);
        testeInsercao(vet100, 100, caminho, csvInsercao, m);
        
        ordemCrescente(vet1000, 1000);
        ordemAleatoria(vet1000, 1000);
        sprintf(caminho, "rand_1000_test%d", t);
        testeInsercao(vet1000, 1000, caminho, csvInsercao, m);
        
        ordemCrescente(vet10000, 10000);
        ordemAleatoria(vet10000, 10000);
        sprintf(caminho, "rand_10000_test%d", t);
        testeInsercao(vet10000, 10000, caminho, csvInsercao, m);
        
        ordemCrescente(vet100000, 100000);
        ordemAleatoria(vet100000, 100000);
        sprintf(caminho, "rand_100000_test%d", t);
        testeInsercao(vet100000, 100000, caminho, csvInsercao, m);
    }

    printf("=== EXECUTANDO TESTES DE REMOÇÃO ===\n");
    
    // Porcentagens de remoção
    double porcentagens[] = {0.10, 0.20, 0.35, 0.50};
    const char *names[] = {"crescente_10000", "decrescente_10000"};
    
    int *vetores[] = {vet10000, vet10000};
    int tamanhos[] = {10000, 10000};

    // Testes de remoção - Crescentes e decrescentes
    printf("Testando remoções crescentes e decrescentes...\n");
    for (int i = 0; i < 2; i++) {
        // Recriar a sequência apropriada
        if (i < 1) {
            ordemCrescente(vetores[i], tamanhos[i]);
        } else {
            ordemDecrescente(vetores[i], tamanhos[i]);
        }
        
        for (int j = 0; j < 4; j++) {
            testeRemocao(vetores[i], tamanhos[i], names[i], porcentagens[j], csvRemocao, m);
        }
    }

    // Testes de remoção - Aleatórios
    printf("Testando remoções aleatórias...\n");
    const int tamanho = 10000;
    for (int t = 1; t <= NUM_TESTES; t++) {
        int *a = vet10000;
            
        // Recriar sequência aleatória
        ordemCrescente(a, tamanho);
        ordemAleatoria(a, tamanho);
        
        sprintf(caminho, "rand_%d_test%d", tamanho, t);
        for (int pj = 0; pj < 4; pj++) {
            testeRemocao(a, tamanho, caminho, porcentagens[pj], csvRemocao, m);
        }
    }

    printf("=== TESTES CONCLUÍDOS ===\n");
    printf("Resultados de inserção salvos em: resultadostestes234/metricas_insercao.csv\n");
    printf("Resultados de remoção salvos em: resultadostestes234/metricas_remocao.csv\n");
    printf("Arquivos de teste salvos em: resultadostestes234/\n");

    fclose(csvInsercao);
    fclose(csvRemocao);
    free(vet100); 
    free(vet1000);
    free(vet10000); 
    free(vet100000);
    
    return 0;
}