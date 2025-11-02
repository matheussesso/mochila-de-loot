// SISTEMA DE MONTAGEM DA TORRE DE FUGA - DESAFIO MESTRE
// Implementação de múltiplos algoritmos de ordenação com análise de desempenho
// Busca binária otimizada após ordenação

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define TAMANHO_NOME 30
#define TAMANHO_TIPO 20

// ============================================================================
// ESTRUTURAS
// ============================================================================

typedef struct {
    char nome[TAMANHO_NOME];
    char tipo[TAMANHO_TIPO];
    int prioridade;
} Componente;

// Estrutura para armazenar estatísticas
typedef struct {
    long comparacoes;
    double tempo;
    char nome_algoritmo[50];
} EstatisticasOrdenacao;

// ============================================================================
// VARIÁVEIS GLOBAIS
// ============================================================================

Componente componentes[MAX_COMPONENTES];
int totalComponentes = 0;
EstatisticasOrdenacao ultimaEstatistica;
long comparacoesGlobal = 0;

// ============================================================================
// FUNÇÕES UTILITÁRIAS
// ============================================================================

void resetarComparacoes(void) {
    comparacoesGlobal = 0;
}

void mostrarComponentes(Componente comp[], int total) {
    int i;
    
    printf("\n--- 📋 COMPONENTES DA TORRE ---\n");
    
    if (total == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    
    printf("Total: %d/%d\n\n", total, MAX_COMPONENTES);
    printf("┌────┬──────────────────────────┬──────────────┬───────────┐\n");
    printf("│ Nº │ Nome                     │ Tipo         │ Prioridad │\n");
    printf("├────┼──────────────────────────┼──────────────┼───────────┤\n");
    
    for (i = 0; i < total; i++) {
        printf("│ %2d │ %-24s │ %-12s │ %3d/10    │\n",
               i + 1,
               comp[i].nome,
               comp[i].tipo,
               comp[i].prioridade);
    }
    
    printf("└────┴──────────────────────────┴──────────────┴───────────┘\n");
}

// ============================================================================
// ALGORITMOS DE ORDENAÇÃO - BUBBLE SORT (por Nome)
// ============================================================================

void bubbleSortNome(Componente comp[], int total) {
    int i, j;
    Componente temp;
    
    resetarComparacoes();
    
    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - i - 1; j++) {
            comparacoesGlobal++;
            if (strcmp(comp[j].nome, comp[j + 1].nome) > 0) {
                temp = comp[j];
                comp[j] = comp[j + 1];
                comp[j + 1] = temp;
            }
        }
    }
}

// ============================================================================
// ALGORITMOS DE ORDENAÇÃO - INSERTION SORT (por Tipo)
// ============================================================================

void insertionSortTipo(Componente comp[], int total) {
    int i, j;
    Componente chave;
    
    resetarComparacoes();
    
    for (i = 1; i < total; i++) {
        chave = comp[i];
        j = i - 1;
        
        while (j >= 0) {
            comparacoesGlobal++;
            if (strcmp(comp[j].tipo, chave.tipo) > 0) {
                comp[j + 1] = comp[j];
                j--;
            } else {
                break;
            }
        }
        comp[j + 1] = chave;
    }
}

// ============================================================================
// ALGORITMOS DE ORDENAÇÃO - SELECTION SORT (por Prioridade)
// ============================================================================

void selectionSortPrioridade(Componente comp[], int total) {
    int i, j, minIdx;
    Componente temp;
    
    resetarComparacoes();
    
    for (i = 0; i < total - 1; i++) {
        minIdx = i;
        
        for (j = i + 1; j < total; j++) {
            comparacoesGlobal++;
            if (comp[j].prioridade > comp[minIdx].prioridade) {
                minIdx = j;
            }
        }
        
        if (minIdx != i) {
            temp = comp[i];
            comp[i] = comp[minIdx];
            comp[minIdx] = temp;
        }
    }
}

// ============================================================================
// BUSCA BINÁRIA (apenas após ordenação por nome)
// ============================================================================

long comparacoesBusca = 0;

int buscaBinariaPorNome(Componente comp[], int total, char nomeBuscar[]) {
    int esq = 0, dir = total - 1, meio;
    comparacoesBusca = 0;
    
    while (esq <= dir) {
        comparacoesBusca++;
        meio = (esq + dir) / 2;
        
        int cmp = strcmp(comp[meio].nome, nomeBuscar);
        
        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    
    return -1;
}

// ============================================================================
// OPERAÇÕES DO SISTEMA
// ============================================================================

void cadastrarComponente(void) {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("\n❌ ERRO: Máximo de %d componentes atingido!\n", MAX_COMPONENTES);
        return;
    }
    
    printf("\n--- 📦 CADASTRAR COMPONENTE ---\n");
    
    printf("Nome do componente: ");
    fgets(componentes[totalComponentes].nome, TAMANHO_NOME, stdin);
    componentes[totalComponentes].nome[strcspn(componentes[totalComponentes].nome, "\n")] = '\0';
    
    if (strlen(componentes[totalComponentes].nome) == 0) {
        printf("❌ ERRO: Nome não pode estar vazio!\n");
        return;
    }
    
    printf("Tipo (controle/suporte/propulsão/outro): ");
    fgets(componentes[totalComponentes].tipo, TAMANHO_TIPO, stdin);
    componentes[totalComponentes].tipo[strcspn(componentes[totalComponentes].tipo, "\n")] = '\0';
    
    if (strlen(componentes[totalComponentes].tipo) == 0) {
        printf("❌ ERRO: Tipo não pode estar vazio!\n");
        return;
    }
    
    printf("Prioridade (1-10): ");
    scanf("%d", &componentes[totalComponentes].prioridade);
    getchar();
    
    if (componentes[totalComponentes].prioridade < 1 || componentes[totalComponentes].prioridade > 10) {
        printf("❌ ERRO: Prioridade deve estar entre 1 e 10!\n");
        return;
    }
    
    totalComponentes++;
    printf("✅ Componente cadastrado com sucesso!\n");
}

void executarBubbleSort(void) {
    clock_t inicio, fim;
    double tempo;
    
    if (totalComponentes == 0) {
        printf("\n❌ Nenhum componente para ordenar!\n");
        return;
    }
    
    printf("\n--- 🔄 BUBBLE SORT (por Nome) ---\n");
    printf("Ordenando...\n");
    
    inicio = clock();
    bubbleSortNome(componentes, totalComponentes);
    fim = clock();
    
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    strcpy(ultimaEstatistica.nome_algoritmo, "Bubble Sort");
    ultimaEstatistica.comparacoes = comparacoesGlobal;
    ultimaEstatistica.tempo = tempo;
    
    printf("\n✅ Ordenação concluída!\n");
    printf("📊 Comparações: %ld\n", comparacoesGlobal);
    printf("⏱️  Tempo: %.4f ms\n", tempo);
    
    mostrarComponentes(componentes, totalComponentes);
}

void executarInsertionSort(void) {
    clock_t inicio, fim;
    double tempo;
    
    if (totalComponentes == 0) {
        printf("\n❌ Nenhum componente para ordenar!\n");
        return;
    }
    
    printf("\n--- 🔄 INSERTION SORT (por Tipo) ---\n");
    printf("Ordenando...\n");
    
    inicio = clock();
    insertionSortTipo(componentes, totalComponentes);
    fim = clock();
    
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    strcpy(ultimaEstatistica.nome_algoritmo, "Insertion Sort");
    ultimaEstatistica.comparacoes = comparacoesGlobal;
    ultimaEstatistica.tempo = tempo;
    
    printf("\n✅ Ordenação concluída!\n");
    printf("📊 Comparações: %ld\n", comparacoesGlobal);
    printf("⏱️  Tempo: %.4f ms\n", tempo);
    
    mostrarComponentes(componentes, totalComponentes);
}

void executarSelectionSort(void) {
    clock_t inicio, fim;
    double tempo;
    
    if (totalComponentes == 0) {
        printf("\n❌ Nenhum componente para ordenar!\n");
        return;
    }
    
    printf("\n--- 🔄 SELECTION SORT (por Prioridade) ---\n");
    printf("Ordenando...\n");
    
    inicio = clock();
    selectionSortPrioridade(componentes, totalComponentes);
    fim = clock();
    
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    strcpy(ultimaEstatistica.nome_algoritmo, "Selection Sort");
    ultimaEstatistica.comparacoes = comparacoesGlobal;
    ultimaEstatistica.tempo = tempo;
    
    printf("\n✅ Ordenação concluída!\n");
    printf("📊 Comparações: %ld\n", comparacoesGlobal);
    printf("⏱️  Tempo: %.4f ms\n", tempo);
    
    mostrarComponentes(componentes, totalComponentes);
}

void buscarComponenteChave(void) {
    char nomeBuscar[TAMANHO_NOME];
    int indice;
    
    if (totalComponentes == 0) {
        printf("\n❌ Nenhum componente para buscar!\n");
        return;
    }
    
    printf("\n--- 🔍 BUSCAR COMPONENTE-CHAVE ---\n");
    printf("(Requer ordenação por nome)\n\n");
    printf("Nome do componente: ");
    fgets(nomeBuscar, TAMANHO_NOME, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';
    
    indice = buscaBinariaPorNome(componentes, totalComponentes, nomeBuscar);
    
    if (indice != -1) {
        printf("\n✅ COMPONENTE-CHAVE ENCONTRADO!\n");
        printf("├─ Nome: %s\n", componentes[indice].nome);
        printf("├─ Tipo: %s\n", componentes[indice].tipo);
        printf("└─ Prioridade: %d/10\n", componentes[indice].prioridade);
        printf("\n🎯 Comparações de busca binária: %ld\n", comparacoesBusca);
    } else {
        printf("\n❌ Componente '%s' não encontrado!\n", nomeBuscar);
        printf("📊 Comparações realizadas: %ld\n", comparacoesBusca);
    }
}

void compararAlgoritmos(void) {
    printf("\n--- ⚡ COMPARAÇÃO DE ALGORITMOS ---\n");
    printf("\nCaracterísticas:\n");
    printf("┌─────────────────────────────────────────────────────────┐\n");
    printf("│ BUBBLE SORT (por Nome)                                 │\n");
    printf("│ ✅ Simples e intuitivo                                 │\n");
    printf("│ ✅ Estável                                             │\n");
    printf("│ ❌ O(n²) - Lento para grandes conjuntos                │\n");
    printf("│ Usa: Poucas comparações, didático                      │\n");
    printf("└─────────────────────────────────────────────────────────┘\n");
    
    printf("\n┌─────────────────────────────────────────────────────────┐\n");
    printf("│ INSERTION SORT (por Tipo)                              │\n");
    printf("│ ✅ Eficiente para pequenos conjuntos                   │\n");
    printf("│ ✅ Estável                                             │\n");
    printf("│ ✅ Adaptável a dados parcialmente ordenados            │\n");
    printf("│ ❌ O(n²) no pior caso                                  │\n");
    printf("│ Usa: Bom desempenho em dados reais                     │\n");
    printf("└─────────────────────────────────────────────────────────┘\n");
    
    printf("\n┌─────────────────────────────────────────────────────────┐\n");
    printf("│ SELECTION SORT (por Prioridade)                        │\n");
    printf("│ ✅ Número previsível de comparações                    │\n");
    printf("│ ✅ Bom para inteiros (prioridade)                      │\n");
    printf("│ ❌ O(n²) sempre                                        │\n");
    printf("│ ❌ Não estável                                         │\n");
    printf("│ Usa: Ordenação por critério numérico                   │\n");
    printf("└─────────────────────────────────────────────────────────┘\n");
    
    printf("\n┌─────────────────────────────────────────────────────────┐\n");
    printf("│ BUSCA BINÁRIA (após ordenação por nome)                │\n");
    printf("│ ✅ O(log n) - Muito rápido!                            │\n");
    printf("│ ✅ Ideal para buscas após ordenação                    │\n");
    printf("│ ❌ Requer dados ordenados                              │\n");
    printf("│ Usa: Localizar componente-chave na missão final        │\n");
    printf("└─────────────────────────────────────────────────────────┘\n");
}

void analisarEstatisticas(void) {
    printf("\n--- 📊 ÚLTIMA ESTATÍSTICA DE ORDENAÇÃO ---\n");
    printf("Algoritmo: %s\n", ultimaEstatistica.nome_algoritmo);
    printf("Comparações: %ld\n", ultimaEstatistica.comparacoes);
    printf("Tempo: %.4f ms\n", ultimaEstatistica.tempo);
}

void montarTorre(void) {
    if (totalComponentes == 0) {
        printf("\n❌ Nenhum componente disponível!\n");
        return;
    }
    
    printf("\n--- 🏗️  MONTAGEM DA TORRE DE FUGA ---\n");
    printf("\nOrdenação atual:\n");
    mostrarComponentes(componentes, totalComponentes);
    
    printf("\n✅ COMPONENTES PRONTOS PARA MONTAGEM!\n");
    printf("Número total de componentes: %d\n", totalComponentes);
    printf("\n⚠️  Para ativar a torre, você precisa encontrar o componente-chave!\n");
}

void menuPrincipal(void) {
    int opcao;
    
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║  🎮 TORRE DE FUGA - DESAFIO MESTRE                  ║\n");
    printf("║  Organize os componentes para escapar da ilha!       ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    while (1) {
        printf("\n╔════════════════════════════════════════════════════════╗\n");
        printf("║         🎮 MENU PRINCIPAL                            ║\n");
        printf("╠════════════════════════════════════════════════════════╣\n");
        printf("║ 1. 📦 Cadastrar componente                           ║\n");
        printf("║ 2. 📋 Listar componentes                             ║\n");
        printf("║ 3. 🔄 Ordenar por Nome (Bubble Sort)                 ║\n");
        printf("║ 4. 🔄 Ordenar por Tipo (Insertion Sort)              ║\n");
        printf("║ 5. 🔄 Ordenar por Prioridade (Selection Sort)        ║\n");
        printf("║ 6. 🔍 Buscar Componente-Chave (Busca Binária)        ║\n");
        printf("║ 7. ⚡ Comparar Algoritmos                            ║\n");
        printf("║ 8. 📊 Análise da Última Ordenação                    ║\n");
        printf("║ 9. 🏗️  Montar Torre                                  ║\n");
        printf("║ 0. 🚪 Sair                                           ║\n");
        printf("╚════════════════════════════════════════════════════════╝\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1:
                cadastrarComponente();
                break;
            case 2:
                mostrarComponentes(componentes, totalComponentes);
                break;
            case 3:
                executarBubbleSort();
                break;
            case 4:
                executarInsertionSort();
                break;
            case 5:
                executarSelectionSort();
                break;
            case 6:
                buscarComponenteChave();
                break;
            case 7:
                compararAlgoritmos();
                break;
            case 8:
                analisarEstatisticas();
                break;
            case 9:
                montarTorre();
                break;
            case 0:
                printf("\n👋 Adeus! Boa sorte na fuga!\n");
                printf("════════════════════════════════════════════════════\n\n");
                return;
            default:
                printf("❌ Opção inválida!\n");
        }
    }
}

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================

int main(void) {
    menuPrincipal();
    return 0;
}
