# Desafios de Programação em C

Sistema de sobrevivência com três níveis de dificuldade progressivos em C.

## Arquivos

- `inventario.c` - Nível Novato: Sistema básico de inventário
- `mochila_avancada.c` - Nível Aventureiro: Vetor vs Lista Encadeada
- `torre_fuga.c` - Nível Mestre: Múltiplos algoritmos com análise de performance

## Compilação

```bash
gcc -o inventario inventario.c
gcc -o mochila_avancada mochila_avancada.c
gcc -o torre_fuga torre_fuga.c
```

## Execução

```bash
./inventario
./mochila_avancada
./torre_fuga
```

## Nível 1 - Novato

Inventário básico com 5 operações (inserir, remover, listar, buscar, calcular total).
Máximo 10 itens.

## Nível 2 - Aventureiro

Comparação de estruturas: vetor vs lista encadeada.
Implementa Bubble Sort e Busca Binária com contadores de comparações.

## Nível 3 - Mestre

Três algoritmos de ordenação (Bubble Sort, Insertion Sort, Selection Sort).
Medição de performance e análise de comparações.
Máximo 20 componentes.
