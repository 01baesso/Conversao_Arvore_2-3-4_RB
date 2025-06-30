# 🌳 Trabalho Prático 2 — Árvores Balanceadas (2-3-4 e Rubro-Negra)

**Universidade Federal de Itajubá — Instituto de Matemática e Computação**  
**Disciplina:** Algoritmos e Estruturas de Dados II (CTCO-02)  
**Professora:** Vanessa Souza  
**Ano:** 2025  

## 🧠 Objetivo
Implementar uma árvore 2-3-4 com suporte às operações básicas (inserção, remoção, busca, impressão) e sua conversão exata para uma árvore Rubro-Negra (RB), que seja estruturalmente válida. O projeto também inclui a execução de testes de desempenho com métricas como número de splits, altura da árvore e quantidade de nós.

---

## 🛠️ Funcionalidades

### 🌲 Árvore 2-3-4
- Inserção de elementos  
- Remoção de elementos  
- Impressão da árvore por camadas  
- Contagem de splits, merges e rotações  
- Conversão direta para Rubro-Negra

### 🌑 Árvore Rubro-Negra
- Geração a partir da 2-3-4  
- Inserção e remoção manual via menu interativo  
- Impressão por camadas e em-ordem  
- Preserva as regras clássicas de RB:
  - Raiz sempre preta
  - Nenhum caminho tem dois nós vermelhos consecutivos
  - Todos os caminhos da raiz às folhas têm mesma quantidade de nós pretos

---

## 🧲 Módulo de Testes Automáticos
**Geração automática de datasets para inserção:**
| Tipo          | Tamanhos                     |
|---------------|------------------------------|
| Ordem crescente | 100, 1000, 10000, 100000     |
| Ordem decrescente | 100, 1000, 10000, 100000  |
| Aleatória     | 100, 1000, 10000, 100000     |

**Geração de métricas:**  
`metrics_insercao.csv`:
- Splits realizados
- Altura final da árvore
- Quantidade total de nós  

`metrics_remocao.csv`:
- Empréstimos e Merges realizados
- Altura após remoção
- Nós restantes
- **Porcentagens testadas:** 10%, 20%, 35%, 50% dos dados removidos aleatoriamente

---

## 📊 Métricas Registradas
| Arquivo              | Métricas                          |
|----------------------|-----------------------------------|
| `metrics_insercao.csv` | Splits, altura, quantidade de nós |
| `metrics_remocao.csv`  | Borrows, merges, altura, nós      |

---

## 👥 Autores
- [Lucas Alexandre dos Santos Baesso](https://github.com/01baesso)  
- [Rafael Fernando Aurélio Ribeiro](https>//github.com/rafaelfernando28)

---

## 📚 Referências
1. [**Mapeamento 2-3-4 → RB** - DigiPen CS280](https://pontus.digipen.edu/~mmead/www/Courses/CS280/Trees-Mapping2-3-4IntoRB.html)  
2. [**Conversão 2-3-4 → RB** - Stack Overflow](https://stackoverflow.com/questions/35955246/converting-a-2-3-4-tree-into-a-red-black-tree)  
3. [**Slides NCKU: 2-3-4 vs RB Trees**](https://smile.ee.ncku.edu.tw/old/Links/MTable/Course/DataStructure/2-3,2-3-4&red-blackTree_952.pdf)  
4. [**Remoção em Árvores-B** - Programiz](https://www.programiz.com/dsa/deletion-from-a-b-tree)
