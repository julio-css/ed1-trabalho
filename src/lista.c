#include <stdlib.h>
#include "lista.h"

typedef struct No {
    int id;
    int tipo;
    void* dado;
    struct No* ant;
    struct No* prox;
} No;

struct Lista {
    No* inicio;
    No* fim;
    int tamanho;
};

Lista* lista_criar(void) {
    Lista* l = (Lista*)malloc(sizeof(Lista));
    if (!l) return NULL;
    l->inicio = l->fim = NULL;
    l->tamanho = 0;
    return l;
}

void lista_destruir(Lista* l) {
    if (!l) return;
    No* atual = l->inicio;
    while (atual) {
        No* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(l);
}

int lista_inserir_fim(Lista* l, void* dado, int id, int tipo) {
    if (!l) return 0;
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) return 0;
    novo->id = id;
    novo->tipo = tipo;
    novo->dado = dado;
    novo->prox = NULL;
    novo->ant = l->fim;
    if (l->fim) l->fim->prox = novo;
    else l->inicio = novo;
    l->fim = novo;
    l->tamanho++;
    return 1;
}

int lista_remover_por_id(Lista* l, int id) {
    if (!l) return 0;
    No* atual = l->inicio;
    while (atual) {
        if (atual->id == id) {
            if (atual->ant) atual->ant->prox = atual->prox;
            else l->inicio = atual->prox;
            if (atual->prox) atual->prox->ant = atual->ant;
            else l->fim = atual->ant;
            free(atual);
            l->tamanho--;
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

void* lista_buscar_por_id(Lista* l, int id, int* tipo) {
    if (!l) return NULL;
    No* atual = l->inicio;
    while (atual) {
        if (atual->id == id) {
            if (tipo) *tipo = atual->tipo;
            return atual->dado;
        }
        atual = atual->prox;
    }
    return NULL;
}

int lista_tamanho(Lista* l) {
    return l ? l->tamanho : 0;
}

void lista_percorrer(Lista* l, void (*callback)(int id, int tipo, void* dado)) {
    if (!l || !callback) return;
    No* atual = l->inicio;
    while (atual) {
        callback(atual->id, atual->tipo, atual->dado);
        atual = atual->prox;
    }
}