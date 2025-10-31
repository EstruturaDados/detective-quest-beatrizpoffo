#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Comodo {
    char nome[50];
    struct Comodo *esquerda;
    struct Comodo *direita;
} Comodo;

Comodo* criarComodo(const char *nome) {
    Comodo *novo = (Comodo*)malloc(sizeof(Comodo));
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(novo->nome, nome);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

Comodo* montarMansao() {
    Comodo *entrada = criarComodo("Entrada da Mansão");
    Comodo *sala = criarComodo("Sala Principal");
    Comodo *biblioteca = criarComodo("Biblioteca");
    Comodo *cozinha = criarComodo("Cozinha");
    Comodo *jardim = criarComodo("Jardim");
    Comodo *porao = criarComodo("Porão Misterioso");
    Comodo *escritorio = criarComodo("Escritório Secreto");

    entrada->esquerda = sala;
    entrada->direita = biblioteca;

    sala->esquerda = cozinha;
    sala->direita = jardim;

    biblioteca->esquerda = porao;
    biblioteca->direita = escritorio;


    return entrada; 
}

void explorar(Comodo *atual) {
    if (atual == NULL) return;

    printf("\nVocê está no(a): %s\n", atual->nome);

    if (atual->esquerda == NULL && atual->direita == NULL) {
        printf("Você chegou a um beco sem saída...\n");
        printf("Após investigar, você descobre que o culpado está neste cômodo!\n");
        printf("🎯 Parabéns, detetive! Caso resolvido!\n");
        return;
    }

    printf("Para onde deseja ir agora?\n");

    if (atual->esquerda) printf("1 - Ir para %s\n", atual->esquerda->nome);
    if (atual->direita) printf("2 - Ir para %s\n", atual->direita->nome);
    printf("0 - Sair do jogo\n");

    int escolha;
    printf("Escolha: ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            if (atual->esquerda) explorar(atual->esquerda);
            else printf("Não há caminho à esquerda!\n");
            break;
        case 2:
            if (atual->direita) explorar(atual->direita);
            else printf("Não há caminho à direita!\n");
            break;
        case 0:
            printf("Você decidiu encerrar a investigação.\n");
            return;
        default:
            printf("Opção inválida!\n");
            explorar(atual);
    }
}

void liberarMansao(Comodo *raiz) {
    if (raiz == NULL) return;
    liberarMansao(raiz->esquerda);
    liberarMansao(raiz->direita);
    free(raiz);
}

int main() {
    printf("=== DETECTIVE QUEST ===\n");
    printf("Você é um detetive em busca do culpado dentro de uma mansão misteriosa.\n");

    Comodo *mansao = montarMansao();
    explorar(mansao);

    liberarMansao(mansao);
    printf("\nObrigado por jogar Detective Quest!\n");

    return 0;
}
