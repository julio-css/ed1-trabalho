#include <stdlib.h>
#include "lista.h"

/* O Nó só precisa guardar o ponteiro genérico e os links */
typedef struct No {
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

int lista_inserir_fim(Lista* l, void* dado) {
    if (!l) return 0;
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) return 0;
    novo->dado = dado;
    novo->prox = NULL;
    novo->ant = l->fim;
    
    if (l->fim) l->fim->prox = novo;
    else l->inicio = novo;
    
    l->fim = novo;
    l->tamanho++;
    return 1;
}

int lista_insere_inicio(Lista* l, void* dado) {
    if (!l) return 0;
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) return 0;
    novo->dado = dado;
    novo->ant = NULL;
    novo->prox = l->inicio;
    
    if (l->inicio) l->inicio->ant = novo;
    else l->fim = novo;
    
    l->inicio = novo;
    l->tamanho++;
    return 1;
}

void* lista_remove(Lista* l, void* dado) {
    if (!l) return NULL;
    No* atual = l->inicio;
    while (atual) {
        if (atual->dado == dado) {
            if (atual->ant) atual->ant->prox = atual->prox;
            else l->inicio = atual->prox;
            
            if (atual->prox) atual->prox->ant = atual->ant;
            else l->fim = atual->ant;
            
            void* ret = atual->dado;
            free(atual);
            l->tamanho--;
            return ret;
        }
        atual = atual->prox;
    }
    return NULL;
}

void* lista_get(Lista* l, int idx) {
    if (!l || idx < 0 || idx >= l->tamanho) return NULL;
    No* atual = l->inicio;
    for (int i = 0; i < idx; i++) {
        atual = atual->prox;
    }
    return atual->dado;
}

int lista_tamanho(Lista* l) {
    return l ? l->tamanho : 0;
}

int lista_vazia(Lista* l) {
    return l ? (l->tamanho == 0) : 1;
}