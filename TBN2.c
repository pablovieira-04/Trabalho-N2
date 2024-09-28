
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
    while (atual != NULL) {
        printf("Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
        atual = atual->proximo;
    }
}

int main() {
    ListaContatos* meusContatos = inicializarLista();

    inserirContato(meusContatos, "Pablo", "(88) 98823-5431");
    inserirContato(meusContatos, "Mateus", "(88) 99973-1242");
    inserirContato(meusContatos, "Alan", "(88) 99616-8922");
    inserirContato(meusContatos, "Fernanda", "(88) 99452-7427");

    char nome[100], telefone[15];
    for (int i = 0; i < 5; i++) {
        printf("Digite o nome da pessoa %d: ", i + 1);
        scanf("%99s", nome); 
        printf("Digite o telefone da pessoa %d: ", i + 1);
        scanf("%14s", telefone); 
        inserirContato(meusContatos, nome, telefone);
    }

    printf("\nLista de Contatos:\n");
    imprimirContatos(meusContatos);

    printf("\nBuscando contato 'Mateus':\n");
    Contato* encontrado = buscarContato(meusContatos, "Mateus");
    if (encontrado) {
        printf("Encontrado: Nome: %s, Telefone: %s\n", encontrado->nome, encontrado->telefone);
    }

    printf("\nRemovendo contato 'Pablo'.\n");
    removerContato(meusContatos, buscarContato(meusContatos, "Pablo"));

    printf("\nLista de Contatos após remoção:\n");
    imprimirContatos(meusContatos);

    while (meusContatos->cabeca != NULL) {
        removerContato(meusContatos, meusContatos->cabeca);
    }
    free(meusContatos);

    return 0;
}
