// SISTEMA DE INVENTÁRIO - JOGO DE SOBREVIVÊNCIA
// Sistema de mochila para gerenciar itens coletados

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constantes do sistema
#define MAX_ITENS 10
#define TAMANHO_NOME 30
#define TAMANHO_TIPO 20

// Struct Item: armazena nome, tipo e quantidade
typedef struct {
    char nome[TAMANHO_NOME];
    char tipo[TAMANHO_TIPO];
    int quantidade;
} Item;

// Variáveis globais
Item mochila[MAX_ITENS];
int totalItens = 0;

// Funções do sistema

// Cadastra um novo item na mochila
void inserirItem(void) {
    if (totalItens >= MAX_ITENS) {
        printf("\n❌ ERRO: Mochila cheia! Máximo de %d itens atingido.\n", MAX_ITENS);
        return;
    }

    printf("\n--- 📦 CADASTRAR NOVO ITEM ---\n");
    
    printf("Nome do item: ");
    fgets(mochila[totalItens].nome, TAMANHO_NOME, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0';

    if (strlen(mochila[totalItens].nome) == 0) {
        printf("❌ ERRO: Nome do item não pode estar vazio!\n");
        return;
    }

    printf("Tipo do item (arma/munição/cura/ferramenta): ");
    fgets(mochila[totalItens].tipo, TAMANHO_TIPO, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0';

    if (strlen(mochila[totalItens].tipo) == 0) {
        printf("❌ ERRO: Tipo do item não pode estar vazio!\n");
        return;
    }

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    getchar();

    if (mochila[totalItens].quantidade <= 0) {
        printf("❌ ERRO: Quantidade deve ser maior que zero!\n");
        return;
    }

    totalItens++;
    printf("✅ Item cadastrado com sucesso!\n");
}

// Remove um item da mochila por nome
void removerItem(void) {
    char nomeRemover[TAMANHO_NOME];
    int i, indiceEncontrado = -1;

    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para remover.\n");
        return;
    }

    printf("\n--- 🗑️  REMOVER ITEM ---\n");
    printf("Nome do item a remover: ");
    fgets(nomeRemover, TAMANHO_NOME, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    // Busca sequencial do item pelo nome
    for (i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("❌ ERRO: Item '%s' não encontrado na mochila!\n", nomeRemover);
        return;
    }

    // Remove o item deslocando os itens posteriores
    for (i = indiceEncontrado; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;
    printf("✅ Item '%s' removido com sucesso!\n", nomeRemover);
}

// Lista todos os itens da mochila
void listarItens(void) {
    int i;

    printf("\n--- 📋 INVENTÁRIO DA MOCHILA ---\n");

    if (totalItens == 0) {
        printf("Mochila vazia. Comece a coletar itens!\n");
        return;
    }

    printf("Total de itens: %d/%d\n\n", totalItens, MAX_ITENS);
    printf("├─────┼────────────────────────┼──────────────┼──────────┤\n");
    printf("│ Nº  │ Nome                   │ Tipo         │ Qtd.     │\n");
    printf("├─────┼────────────────────────┼──────────────┼──────────┤\n");

    // Exibe cada item
    for (i = 0; i < totalItens; i++) {
        printf("│ %2d  │ %-22s │ %-12s │ %8d │\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }

    printf("└─────┴────────────────────────┴──────────────┴──────────┘\n");
}

// Busca um item por nome na mochila
void buscarItem(void) {
    char nomeBuscar[TAMANHO_NOME];
    int i, encontrado = 0;

    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }

    printf("\n--- 🔍 BUSCAR ITEM ---\n");
    printf("Nome do item a buscar: ");
    fgets(nomeBuscar, TAMANHO_NOME, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    // Busca sequencial do item pelo nome
    for (i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("┌──────────────────────────┐\n");
            printf("│ DETALHES DO ITEM         │\n");
            printf("├──────────────────────────┤\n");
            printf("│ Nome: %-19s │\n", mochila[i].nome);
            printf("│ Tipo: %-19s │\n", mochila[i].tipo);
            printf("│ Quantidade: %-12d │\n", mochila[i].quantidade);
            printf("└──────────────────────────┘\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("❌ ERRO: Item '%s' não encontrado na mochila!\n", nomeBuscar);
    }
}

// Exibe o menu principal
void exibirMenu(void) {
    printf("\n╔═══════════════════════════════════════════════╗\n");
    printf("║    🎮 SISTEMA DE INVENTÁRIO - SOBREVIVÊNCIA  ║\n");
    printf("╠═══════════════════════════════════════════════╣\n");
    printf("║ 1. 📦 Cadastrar novo item                    ║\n");
    printf("║ 2. 🗑️  Remover item                          ║\n");
    printf("║ 3. 📋 Listar todos os itens                  ║\n");
    printf("║ 4. 🔍 Buscar item                            ║\n");
    printf("║ 5. 🚪 Sair do jogo                           ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
}

// Função principal - loop de interação
int main(void) {
    int opcao;

    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║  BEM-VINDO AO JOGO DE SOBREVIVÊNCIA NA ILHA! ║\n");
    printf("║  Organize sua mochila de loot inicial!        ║\n");
    printf("╚════════════════════════════════════════════════╝\n");

    while (1) {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;

            case 2:
                removerItem();
                listarItens();
                break;

            case 3:
                listarItens();
                break;

            case 4:
                buscarItem();
                break;

            case 5:
                printf("\n👋 Adeus! Boa sorte na sua sobrevivência!\n");
                printf("════════════════════════════════════════════════\n\n");
                return 0;

            default:
                printf("\n❌ ERRO: Opção inválida! Escolha um número de 1 a 5.\n");
        }
    }

    return 0;
}
