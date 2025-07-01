/******************************************************************************
 * Arquivo: testes234.h
 *
 * Descrição: Interface dos testes realizados sobre a árvore 2-3-4
 *
 * Criadores:
 *            - LUCAS ALEXANDRE DOS SANTOS BAESSO - 2024007172
 *            - RAFAEL FERNANDO AURELIO RIBEIRO - 2024009426
 *
 * Data: 29/06/2025
 ******************************************************************************/

#ifndef TESTES_234_H
#define TESTES_234_H

#include <stdio.h>
#include "../B-234/arvore234.h"

// Função que gera um vetor de tamanho 'tamanho' em ordem crescente
void ordemCrescente(int *vet, int tamanho);

// Função que gera um vetor de tamanho 'tamanho' em ordem decrescente
void ordemDecrescente(int *vet, int tamanho);

// Função que gera um vetor de tamanho 'tamanho' em ordem aleatória
void ordemAleatoria(int *vet, int tamanho);

// Função que gera um arquivo .txt com os vetores criados
void geraArquivoTxt(const char *caminho, int *vet, int tamanho);

// Função que realiza o teste de inserção dos elementos (splits, altura e blocos)
void testeInsercao(int *vet, int tamanho, const char *label, FILE *csv, Metricas234 *m);

// Função que realiza o teste de remoção dos elementos (rotações, merges, altura e blocos)
void testeRemocao(int *vetCompleto, int tamanho, const char *label, double porcentagem, FILE *csv, Metricas234 *m);

#endif // BT234_RB_H