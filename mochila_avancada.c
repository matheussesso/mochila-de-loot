// SISTEMA DE INVENTÁRIO AVANÇADO - JOGO DE SOBREVIVÊNCIA
// Comparação entre Vetor (Lista Sequencial) e Lista Encadeada
// Análise de desempenho com busca sequencial e binária

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constantes
#define MAX_ITENS 10
#define TAMANHO_NOME 30
#define TAMANHO_TIPO 20

// ============================================================================
// ESTRUTURAS DE DADOS
// ============================================================================

typedef struct {
    char nome[TAMANHO_NOME];
    char tipo[TAMANHO_TIPO];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ============================================================================
// VARIÁVEIS GLOBAIS - VETOR
// ============================================================================

Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;
long comparacoesSequencial = 0;
long comparacoesBinaria = 0;

// ============================================================================
// VARIÁVEIS GLOBAIS - LISTA ENCADEADA
// ============================================================================

No* mochilaLista = NULL;
int totalLista = 0;
long comparacoesListaSequencial = 0;

// ============================================================================
// FUNÇÕES - VETOR
// ============================================================================

void inserirItemVetor(void) {
    if (totalVetor >= MAX_ITENS) {
        printf("\n❌ ERRO: Mochila (vetor) cheia! Máximo de %d itens.\n", MAX_ITENS);
        return;
    }

    printf("\n--- 📦 CADASTRAR ITEM (VETOR) ---\n");
    printf("Nome: ");
    fgets(mochilaVetor[totalVetor].nome, TAMANHO_NOME, stdin);
    mochilaVetor[totalVetor].nome[strcspn(mochilaVetor[totalVetor].nome, "\n")] = '\0';

    if (strlen(mochilaVetor[totalVetor].nome) == 0) {
        printf("❌ ERRO: Nome não pode estar vazio!\n");
        return;
    }

    printf("Tipo: ");
    fgets(mochilaVetor[totalVetor].tipo, TAMANHO_TIPO, stdin);
    mochilaVetor[totalVetor].tipo[strcspn(mochilaVetor[totalVetor].tipo, "\n")] = '\0';

    if (strlen(mochilaVetor[totalVetor].tipo) == 0) {
        printf("❌ ERRO: Tipo não pode estar vazio!\n");
        return;
    }

    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[totalVetor].quantidade);
    getchar();

    if (mochilaVetor[totalVetor].quantidade <= 0) {
        printf("❌ ERRO: Quantidade deve ser maior que zero!\n");
        return;
    }

    totalVetor++;
    printf("✅ Item cadastrado com sucesso!\n");
}

void removerItemVetor(void) {
    char nomeRemover[TAMANHO_NOME];
    int i, indice = -1;

    if (totalVetor == 0) {
        printf("\n❌ Mochila (vetor) vazia!\n");
        return;
    }

    printf("\n--- 🗑️  REMOVER ITEM (VETOR) ---\n");
    printf("Nome do item: ");
    fgets(nomeRemover, TAMANHO_NOME, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    for (i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeRemover) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("❌ ERRO: Item '%s' não encontrado!\n", nomeRemover);
        return;
    }

    for (i = indice; i < totalVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }

    totalVetor--;
    printf("✅ Item removido com sucesso!\n");
}

void listarItensVetor(void) {
    int i;

    printf("\n--- 📋 INVENTÁRIO (VETOR) ---\n");

    if (totalVetor == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("Total: %d/%d\n\n", totalVetor, MAX_ITENS);
    printf("┌─────┬────────────────────────┬──────────────┬──────────┐\n");
    printf("│ Nº  │ Nome                   │ Tipo         │ Qtd.     │\n");
    printf("├─────┼────────────────────────┼──────────────┼──────────┤\n");

    for (i = 0; i < totalVetor; i++) {
        printf("│ %2d  │ %-22s │ %-12s │ %8d │\n",
               i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }

    printf("└─────┴────────────────────────┴──────────────┴──────────┘\n");
}

// Comparador para qsort
int compararItens(const void* a, const void* b) {
    return strcmp(((Item*)a)->nome, ((Item*)b)->nome);
}

void ordenarVetor(void) {
    if (totalVetor == 0) {
        printf("\n❌ Mochila vazia!\n");
        return;
    }

    printf("\n--- 📊 ORDENANDO VETOR ---\n");
    qsort(mochilaVetor, totalVetor, sizeof(Item), compararItens);
    printf("✅ Vetor ordenado alfabeticamente por nome!\n");
    listarItensVetor();
}

void buscarSequencialVetor(void) {
    char nomeBuscar[TAMANHO_NOME];
    int i;

    if (totalVetor == 0) {
        printf("\n❌ Mochila vazia!\n");
        return;
    }

    printf("\n--- 🔍 BUSCA SEQUENCIAL (VETOR) ---\n");
    printf("Nome do item: ");
    fgets(nomeBuscar, TAMANHO_NOME, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    comparacoesSequencial = 0;

    for (i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nomeBuscar) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("├─ Nome: %s\n", mochilaVetor[i].nome);
            printf("├─ Tipo: %s\n", mochilaVetor[i].tipo);
            printf("└─ Quantidade: %d\n", mochilaVetor[i].quantidade);
            printf("\n📊 Comparações realizadas: %ld\n", comparacoesSequencial);
            return;
        }
    }

    printf("❌ Item '%s' não encontrado.\n", nomeBuscar);
    printf("📊 Comparações realizadas: %ld\n", comparacoesSequencial);
}

void buscarBinariaVetor(void) {
    char nomeBuscar[TAMANHO_NOME];
    int esq = 0, dir = totalVetor - 1, meio;
    int encontrado = 0;

    if (totalVetor == 0) {
        printf("\n❌ Mochila vazia!\n");
        return;
    }

    printf("\n--- 🔎 BUSCA BINÁRIA (VETOR) ---\n");
    printf("Nome do item: ");
    fgets(nomeBuscar, TAMANHO_NOME, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    comparacoesBinaria = 0;

    while (esq <= dir) {
        comparacoesBinaria++;
        meio = (esq + dir) / 2;

        if (strcmp(mochilaVetor[meio].nome, nomeBuscar) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("├─ Nome: %s\n", mochilaVetor[meio].nome);
            printf("├─ Tipo: %s\n", mochilaVetor[meio].tipo);
            printf("└─ Quantidade: %d\n", mochilaVetor[meio].quantidade);
            printf("\n📊 Comparações realizadas: %ld\n", comparacoesBinaria);
            encontrado = 1;
            break;
        } else if (strcmp(mochilaVetor[meio].nome, nomeBuscar) < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    if (!encontrado) {
        printf("❌ Item '%s' não encontrado.\n", nomeBuscar);
        printf("📊 Comparações realizadas: %ld\n", comparacoesBinaria);
    }
}

void compararBuscasVetor(void) {
    if (totalVetor == 0) {
        printf("\n❌ Mochila vazia!\n");
        return;
    }

    printf("\n--- ⚡ COMPARAÇÃO DE DESEMPENHO (VETOR) ---\n");
    printf("┌────────────────────────────────────────────┐\n");
    printf("│ Última Busca Sequencial: %ld comparações  │\n", comparacoesSequencial);
    printf("│ Última Busca Binária: %ld comparações     │\n", comparacoesBinaria);
    
    if (comparacoesBinaria > 0) {
        double reducao = ((double)(comparacoesSequencial - comparacoesBinaria) / comparacoesSequencial) * 100;
        printf("│ Redução: %.1f%% ⚡                        │\n", reducao);
    }
    printf("└────────────────────────────────────────────┘\n");
}

// ============================================================================
// FUNÇÕES - LISTA ENCADEADA
// ============================================================================

void inserirItemLista(void) {
    No* novo;
    int contador = 0;
    No* temp = mochilaLista;

    while (temp != NULL) {
        contador++;
        temp = temp->proximo;
    }

    if (contador >= MAX_ITENS) {
        printf("\n❌ ERRO: Mochila (lista) cheia! Máximo de %d itens.\n", MAX_ITENS);
        return;
    }

    novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("❌ ERRO: Falha na alocação de memória!\n");
        return;
    }

    printf("\n--- 📦 CADASTRAR ITEM (LISTA) ---\n");
    printf("Nome: ");
    fgets(novo->dados.nome, TAMANHO_NOME, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    if (strlen(novo->dados.nome) == 0) {
        printf("❌ ERRO: Nome não pode estar vazio!\n");
        free(novo);
        return;
    }

    printf("Tipo: ");
    fgets(novo->dados.tipo, TAMANHO_TIPO, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    if (strlen(novo->dados.tipo) == 0) {
        printf("❌ ERRO: Tipo não pode estar vazio!\n");
        free(novo);
        return;
    }

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    if (novo->dados.quantidade <= 0) {
        printf("❌ ERRO: Quantidade deve ser maior que zero!\n");
        free(novo);
        return;
    }

    novo->proximo = mochilaLista;
    mochilaLista = novo;
    totalLista++;
    printf("✅ Item cadastrado com sucesso!\n");
}

void removerItemLista(void) {
    char nomeRemover[TAMANHO_NOME];
    No* atual = mochilaLista;
    No* anterior = NULL;

    if (mochilaLista == NULL) {
        printf("\n❌ Mochila (lista) vazia!\n");
        return;
    }

    printf("\n--- 🗑️  REMOVER ITEM (LISTA) ---\n");
    printf("Nome do item: ");
    fgets(nomeRemover, TAMANHO_NOME, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeRemover) == 0) {
            if (anterior == NULL) {
                mochilaLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            totalLista--;
            printf("✅ Item removido com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("❌ ERRO: Item '%s' não encontrado!\n", nomeRemover);
}

void listarItensLista(void) {
    No* atual = mochilaLista;
    int i = 1;

    printf("\n--- 📋 INVENTÁRIO (LISTA ENCADEADA) ---\n");

    if (mochilaLista == NULL) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("Total: %d/%d\n\n", totalLista, MAX_ITENS);
    printf("┌─────┬────────────────────────┬──────────────┬──────────┐\n");
    printf("│ Nº  │ Nome                   │ Tipo         │ Qtd.     │\n");
    printf("├─────┼────────────────────────┼──────────────┼──────────┤\n");

    while (atual != NULL) {
        printf("│ %2d  │ %-22s │ %-12s │ %8d │\n",
               i, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        i++;
        atual = atual->proximo;
    }

    printf("└─────┴────────────────────────┴──────────────┴──────────┘\n");
}

void buscarSequencialLista(void) {
    char nomeBuscar[TAMANHO_NOME];
    No* atual = mochilaLista;

    if (mochilaLista == NULL) {
        printf("\n❌ Mochila vazia!\n");
        return;
    }

    printf("\n--- 🔍 BUSCA SEQUENCIAL (LISTA) ---\n");
    printf("Nome do item: ");
    fgets(nomeBuscar, TAMANHO_NOME, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    comparacoesListaSequencial = 0;

    while (atual != NULL) {
        comparacoesListaSequencial++;
        if (strcmp(atual->dados.nome, nomeBuscar) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("├─ Nome: %s\n", atual->dados.nome);
            printf("├─ Tipo: %s\n", atual->dados.tipo);
            printf("└─ Quantidade: %d\n", atual->dados.quantidade);
            printf("\n📊 Comparações realizadas: %ld\n", comparacoesListaSequencial);
            return;
        }
        atual = atual->proximo;
    }

    printf("❌ Item '%s' não encontrado.\n", nomeBuscar);
    printf("📊 Comparações realizadas: %ld\n", comparacoesListaSequencial);
}

void liberarLista(void) {
    No* atual = mochilaLista;
    No* temp;

    while (atual != NULL) {
        temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    mochilaLista = NULL;
    totalLista = 0;
}

// ============================================================================
// MENU
// ============================================================================

void menuVetor(void) {
    int opcao;

    while (1) {
        printf("\n╔═══════════════════════════════════════════════╗\n");
        printf("║       🎮 MOCHILA COM VETOR                  ║\n");
        printf("╠═══════════════════════════════════════════════╣\n");
        printf("║ 1. 📦 Cadastrar item                         ║\n");
        printf("║ 2. 🗑️  Remover item                          ║\n");
        printf("║ 3. 📋 Listar itens                           ║\n");
        printf("║ 4. 📊 Ordenar vetor                          ║\n");
        printf("║ 5. 🔍 Busca sequencial                       ║\n");
        printf("║ 6. 🔎 Busca binária (requer ordenação)       ║\n");
        printf("║ 7. ⚡ Comparar buscas                        ║\n");
        printf("║ 8. 🔙 Voltar ao menu principal              ║\n");
        printf("╚═══════════════════════════════════════════════╝\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: ordenarVetor(); break;
            case 5: buscarSequencialVetor(); break;
            case 6: buscarBinariaVetor(); break;
            case 7: compararBuscasVetor(); break;
            case 8: return;
            default: printf("❌ Opção inválida!\n");
        }
    }
}

void menuLista(void) {
    int opcao;

    while (1) {
        printf("\n╔═══════════════════════════════════════════════╗\n");
        printf("║    🎮 MOCHILA COM LISTA ENCADEADA           ║\n");
        printf("╠═══════════════════════════════════════════════╣\n");
        printf("║ 1. 📦 Cadastrar item                         ║\n");
        printf("║ 2. 🗑️  Remover item                          ║\n");
        printf("║ 3. 📋 Listar itens                           ║\n");
        printf("║ 4. 🔍 Busca sequencial                       ║\n");
        printf("║ 5. 🔙 Voltar ao menu principal              ║\n");
        printf("╚═══════════════════════════════════════════════╝\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: buscarSequencialLista(); break;
            case 5: return;
            default: printf("❌ Opção inválida!\n");
        }
    }
}

void menuPrincipal(void) {
    int opcao;

    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║  BEM-VINDO AO JOGO DE SOBREVIVÊNCIA NA ILHA! ║\n");
    printf("║  VERSÃO AVANÇADA - ANÁLISE DE ESTRUTURAS     ║\n");
    printf("╚════════════════════════════════════════════════╝\n");

    while (1) {
        printf("\n╔═══════════════════════════════════════════════╗\n");
        printf("║   🎮 SISTEMA DE INVENTÁRIO AVANÇADO          ║\n");
        printf("╠═══════════════════════════════════════════════╣\n");
        printf("║ 1. 📦 Mochila com Vetor                      ║\n");
        printf("║ 2. 📦 Mochila com Lista Encadeada            ║\n");
        printf("║ 3. 📊 Comparar Estruturas                    ║\n");
        printf("║ 4. 🚪 Sair                                   ║\n");
        printf("╚═══════════════════════════════════════════════╝\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 3:
                printf("\n--- 📊 COMPARAÇÃO DE ESTRUTURAS ---\n");
                printf("VETOR:\n");
                printf("  ✅ Acesso direto O(1)\n");
                printf("  ✅ Busca binária possível após ordenação\n");
                printf("  ❌ Inserção/Remoção O(n)\n");
                printf("  ❌ Espaço pré-alocado fixo\n\n");
                printf("LISTA ENCADEADA:\n");
                printf("  ✅ Inserção/Remoção O(1) no início\n");
                printf("  ✅ Memória alocada dinamicamente\n");
                printf("  ❌ Busca sequencial O(n)\n");
                printf("  ❌ Sem acesso direto\n");
                break;
            case 4:
                printf("\n👋 Adeus! Boa sorte na sua sobrevivência!\n\n");
                liberarLista();
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
