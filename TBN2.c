#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contato {
    char nome[100];
    char telefone[15];
    struct Contato* anterior;
    struct Contato* proximo;
} Contato;

typedef struct {
    Contato* cabeca;
    Contato* cauda;
} ListaContatos;

ListaContatos* inicializarLista() {
    ListaContatos* lista = (ListaContatos*)malloc(sizeof(ListaContatos));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    return lista;
}

void inserirContato(ListaContatos* lista, const char* nome, const char* telefone) {
    Contato* novoContato = (Contato*)malloc(sizeof(Contato));
    strcpy(novoContato->nome, nome);
    strcpy(novoContato->telefone, telefone);
    novoContato->anterior = lista->cauda;
    novoContato->proximo = NULL;

    if (lista->cauda != NULL) {
        lista->cauda->proximo = novoContato;
    } else {
        lista->cabeca = novoContato;
    }

    lista->cauda = novoContato;
}

void removerContato(ListaContatos* lista, Contato* contato) {
    if (contato->anterior != NULL) {
        contato->anterior->proximo = contato->proximo;
    } else {
        lista->cabeca = contato->proximo;
    }

    if (contato->proximo != NULL) {
        contato->proximo->anterior = contato->anterior;
    } else {
        lista->cauda = contato->anterior;
    }

    free(contato);
}

Contato* buscarContato(ListaContatos* lista, const char* nome) {
    Contato* atual = lista->cabeca;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void imprimirContatos(ListaContatos* lista) {
    Contato* atual = lista->cabeca;
    if (atual == NULL) {
        printf("A lista de contatos está vazia.\n");
        return;
    }

    while (atual != NULL) {
        printf("Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
        atual = atual->proximo;
    }
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void liberarLista(ListaContatos* lista) {
    Contato* atual = lista->cabeca;
    while (atual != NULL) {
        Contato* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(lista);
}

int main() {
    ListaContatos* meusContatos = inicializarLista();

    inserirContato(meusContatos, "Pablo", "(88) 98823-5431");
    inserirContato(meusContatos, "Mateus", "(88) 99973-1242");
    inserirContato(meusContatos, "Alan", "(88) 99616-8922");
    inserirContato(meusContatos, "Fernanda", "(88) 99452-7427");

    int opcao;
    char nome[100], telefone[15];

    do {
        limparTela(); // Limpa a tela antes de mostrar o menu
        printf("Menu:\n");
        printf("1. Adicionar contato\n");
        printf("2. Remover contato\n");
        printf("3. Buscar contato\n");
        printf("4. Listar contatos\n");
        printf("0. Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome: ");
                scanf("%99s", nome);
                printf("Digite o telefone: ");
                scanf("%14s", telefone);
                inserirContato(meusContatos, nome, telefone);
                printf("Contato adicionado com sucesso!\n");
                printf("\nLista de Contatos Atualizada:\n");
                imprimirContatos(meusContatos);
                break;

            case 2:
                printf("Digite o nome do contato a ser removido: ");
                scanf("%99s", nome);
                Contato* contatoRemover = buscarContato(meusContatos, nome);
                if (contatoRemover) {
                    removerContato(meusContatos, contatoRemover);
                    printf("Contato removido com sucesso!\n");
                } else {
                    printf("Contato não encontrado.\n");
                }
                break;

            case 3:
                printf("Digite o nome do contato a ser buscado: ");
                scanf("%99s", nome);
                Contato* encontrado = buscarContato(meusContatos, nome);
                if (encontrado) {
                    printf("\nEncontrado: Nome: %s, Telefone: %s\n", encontrado->nome, encontrado->telefone);
                } else {
                    printf("Contato não encontrado.\n");
                }
                break;

            case 4:
                printf("\nLista de Contatos:\n");
                imprimirContatos(meusContatos);
                break;

            case 0:
                printf("Saindo do programa.\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n'); // Limpa o buffer
            getchar(); // Espera pelo Enter
        }

    } while (opcao != 0);

    liberarLista(meusContatos);
    return 0;
}
