/******************************************************************************
 * Arquivo: conversor.h
 *
 * Descrição: Interface do conversor de árvore 2-3-4 em árvore rubro-negra
 *
 * Criadores:
 *            - LUCAS ALEXANDRE DOS SANTOS BAESSO - 2024007172
 *            - RAFAEL FERNANDO AURELIO RIBEIRO - 2024009426
 *
 * Data: 29/06/2025
 ******************************************************************************/

#ifndef BT234_RB_H
#define BT234_RB_H

/*
 * Conversão de Árvore 2-3-4 (B-tree de ordem 4) -> Árvore Red-Black
 *
 * Critérios de mapeamento por tipo de nó na B-tree:
 *
 * 1) Nó-2 (1 chave):
 *    [ k ]
 *     |
 *    RB: nó preto único
 *    (P)
 *
 *
 * 2) Nó-3 (2 chaves):
 *    [ k0 | k1 ]
 *     /   |   \
 *   c0   c1  c2
 *
 *    RB: pai preto com k1 e filho vermelho com k0 à esquerda
 *
 *    Mapeia:
 *      [ k0 | k1 ]                     P(k1)
 *       /  |  \        ->             /
 *     c0  c1  c2                 V(k0)
 *
 * 3) Nó-4 (3 chaves):
 *    [ k0 | k1 | k2 ]
 *     /   |   |   \
 *   c0   c1  c2  c3
 *
 *    RB: nó preto com k1 e dois filhos vermelhos k0 e k2
 *
 *    Mapeia:
 *      [ k0 | k1 | k2 ]             P(k1)
 *       / |  |  \         ->       /    \
 *      c0 c1 c2 c3              V(k0)  V(k2)
 *
 * A travessia in-order da RB-tree preserva a ordenação original da B-tree.
 */

// Função que converte a árvore 2-3-4 em árvore rubro-negra
rb* converte234ParaRB(no234 *raizB);

#endif // BT234_RB_H