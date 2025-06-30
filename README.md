# 🌳 Trabalho Prático 2 — Árvores Balanceadas (2-3-4 e Rubro-Negra)

**Universidade Federal de Itajubá — Instituto de Matemática e Computação**  
**Disciplina:** Algoritmos e Estruturas de Dados II (CTCO-02)  
**Professora:** Vanessa Souza  
**Ano:** 2025  

## 🧠 Objetivo
Implementar uma árvore 2-3-4 com suporte às operações básicas (inserção, remoção, busca, impressão) e sua conversão exata para uma árvore Rubro-Negra (RB), que seja estruturalmente equivalente. O projeto também inclui a execução de testes de desempenho com métricas como número de splits, altura da árvore e quantidade de nós.

---

## 🛠️ Funcionalidades

### 🌲 Árvore 2-3-4
- Inserção de elementos  
- Remoção de elementos  
- Impressão da árvore por camadas  
- Contagem de splits, merges e rotações  
- Conversão direta para Rubro-Negra (sem balanceamentos extras)  

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
- Borrows e Merges realizados
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
- [Lucas Baesso](https://github.com/lucasbaesso)  
- [Nomes dos colegas do grupo se houver]

---

## 📚 Referências
1. DigiPen CS280 – Mapping 2-3-4 to RB Trees  
2. Stack Overflow: Converting 2-3-4 to Red-Black  
3. NCKU Slides: 2-3-4 vs RB Tree  
