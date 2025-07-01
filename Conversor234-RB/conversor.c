/******************************************************************************
 * Arquivo: conversor.c
 *
 * Descrição: Implementação do conversor de árvore 2-3-4 em árvore rubro-negra
 *
 * Criadores:
 *            - LUCAS ALEXANDRE DOS SANTOS BAESSO - 2024007172
 *            - RAFAEL FERNANDO AURELIO RIBEIRO - 2024009426
 *
 * Data: 29/06/2025
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../B-234/arvore234.h"
#include "../Rubro-negra/arvorerubronegra.h"
#include "conversor.h"

// Função auxiliar recursiva usando apenas funções acessoras das árvores
static noRB *converte234ParaRB_Handler(no234 *b, rb *nova) {
    if (b == NULL) // Nó nulo da 2-3-4 vira folha sentinela preta
        return getRBSentinelaFolha(nova);

    noRB *raizRB, *noVermelho, *noDireito;
    int numChaves = getBNumChaves(b);

    if (numChaves == 1) {
        // Caso nó-2: 1 chave (chaves[0])
        raizRB = alocaNoRubroNegra(nova, getBChave(b, 0));
        setRBCor(raizRB, 'P');  // Tornar o nó preto

        // Converter filhos esquerdo e direito
        noRB *filhoEsq = converte234ParaRB_Handler(getBFilho(b, 0), nova);
        setRBFilhoEsq(raizRB, filhoEsq);
        if (filhoEsq != getRBSentinelaFolha(nova))
            setRBPai(filhoEsq, raizRB);
            
        noRB *filhoDir = converte234ParaRB_Handler(getBFilho(b, 1), nova);
        setRBFilhoDir(raizRB, filhoDir);
        if (filhoDir != getRBSentinelaFolha(nova))
            setRBPai(filhoDir, raizRB);
            
        return raizRB;
    } else if (numChaves == 2) {
        // Caso nó-3: 2 chaves (chaves[0] = k0, chaves[1] = k1)
        int k0 = getBChave(b, 0);
        int k1 = getBChave(b, 1);

        // Criar nó preto com k1
        raizRB = alocaNoRubroNegra(nova, k1);
        setRBCor(raizRB, 'P');

        // Criar nó vermelho com k0
        noVermelho = alocaNoRubroNegra(nova, k0);
        setRBCor(noVermelho, 'V');
        setRBPai(noVermelho, raizRB);
        setRBFilhoEsq(raizRB, noVermelho);

        // Filho direito do nó preto é recursão em b->filho[2]
        noRB *filhoDir = converte234ParaRB_Handler(getBFilho(b, 2), nova);
        setRBFilhoDir(raizRB, filhoDir);
        if (filhoDir != getRBSentinelaFolha(nova))
            setRBPai(filhoDir, raizRB);

        // Filhos do nó vermelho: b->filho[0] e b->filho[1]
        noRB *filhoVermEsq = converte234ParaRB_Handler(getBFilho(b, 0), nova);
        setRBFilhoEsq(noVermelho, filhoVermEsq);
        if (filhoVermEsq != getRBSentinelaFolha(nova))
            setRBPai(filhoVermEsq, noVermelho);
            
        noRB *filhoVermDir = converte234ParaRB_Handler(getBFilho(b, 1), nova);
        setRBFilhoDir(noVermelho, filhoVermDir);
        if (filhoVermDir != getRBSentinelaFolha(nova))
            setRBPai(filhoVermDir, noVermelho);
            
        return raizRB;
    } else { // numChaves == 3
        // Caso nó-4: 3 chaves (chaves[0]=k0, chaves[1]=k1, chaves[2]=k2)
        int k0 = getBChave(b, 0);
        int k1 = getBChave(b, 1);
        int k2 = getBChave(b, 2);

        // Criar nó preto com k1
        raizRB = alocaNoRubroNegra(nova, k1);
        setRBCor(raizRB, 'P');

        // Criar nós vermelhos com k0 (esquerda) e k2 (direita)
        noVermelho = alocaNoRubroNegra(nova, k0);
        noDireito = alocaNoRubroNegra(nova, k2);
        
        // Definir cores como vermelhas
        setRBCor(noVermelho, 'V');
        setRBCor(noDireito, 'V');

        // Configurar pais e ligações
        setRBPai(noVermelho, raizRB);
        setRBPai(noDireito, raizRB);
        setRBFilhoEsq(raizRB, noVermelho);
        setRBFilhoDir(raizRB, noDireito);

        // Filhos do nó vermelho da esquerda: b->filhos[0] e [1]
        noRB *filhoVermEsq = converte234ParaRB_Handler(getBFilho(b, 0), nova);
        setRBFilhoEsq(noVermelho, filhoVermEsq);
        if (filhoVermEsq != getRBSentinelaFolha(nova))
            setRBPai(filhoVermEsq, noVermelho);
            
        noRB *filhoVermDir = converte234ParaRB_Handler(getBFilho(b, 1), nova);
        setRBFilhoDir(noVermelho, filhoVermDir);
        if (filhoVermDir != getRBSentinelaFolha(nova))
            setRBPai(filhoVermDir, noVermelho);

        // Filhos do nó vermelho da direita: b->filhos[2] e [3]
        noRB *filhoDirEsq = converte234ParaRB_Handler(getBFilho(b, 2), nova);
        setRBFilhoEsq(noDireito, filhoDirEsq);
        if (filhoDirEsq != getRBSentinelaFolha(nova))
            setRBPai(filhoDirEsq, noDireito);
            
        noRB *filhoDirDir = converte234ParaRB_Handler(getBFilho(b, 3), nova);
        setRBFilhoDir(noDireito, filhoDirDir);
        if (filhoDirDir != getRBSentinelaFolha(nova))
            setRBPai(filhoDirDir, noDireito);
            
        return raizRB;
    }
}

// Função principal da conversão
rb *converte234ParaRB(no234 *raizB) {
    // Alocar e inicializar árvore RB vazia
    rb *nova = alocaArvoreRubroNegra();
    if (raizB == NULL) // Árvore vazia -> retorna somente a estrutura sentinela
        return nova;
    
    // Converter recursivamente a raiz da 2-3-4
    noRB *raiz = converte234ParaRB_Handler(raizB, nova);
    
    // Conectar ao sentinelaRaiz da RB
    noRB *sentinelaRaiz = getRBSentinelaRaiz(nova);
    setRBFilhoDir(sentinelaRaiz, raiz);
    setRBPai(raiz, sentinelaRaiz);
    
    // Garantir raiz preta
    setRBCor(raiz, 'P');
    
    return nova;
}