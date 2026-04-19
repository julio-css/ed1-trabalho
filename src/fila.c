#include <stdlib.h>
#include "fila.h"

struct Fila {
    void* dados[FILA_MAX];
    int ini;
    int fim;
    int qtd;
};

Fila* fila_cria() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if (f == NULL) return NULL;
    f->ini = 0;
    f->fim = 0;
    f->qtd = 0;
    return f;
}

void fila_destroi(Fila* f) {
    if (f == NULL) return;
    free(f);
}

int fila_insere(Fila* f, void* dado) {
    if (fila_cheia(f)) return 0;
    f->dados[f->fim] = dado;
    f->fim = (f->fim + 1) % FILA_MAX;
    f->qtd++;
    return 1;
}

void* fila_remove(Fila* f) {
    if (fila_vazia(f)) return NULL;
    void* dado = f->dados[f->ini];
    f->ini = (f->ini + 1) % FILA_MAX;
    f->qtd--;
    return dado;
}

void* fila_frente(Fila* f) {
    if (fila_vazia(f)) return NULL;
    return f->dados[f->ini];
}

void* fila_get(Fila* f, int idx) {
    if (idx < 0 || idx >= f->qtd) return NULL;
    return f->dados[(f->ini + idx) % FILA_MAX];
}

int fila_tamanho(Fila* f) { return f->qtd; }
int fila_vazia(Fila* f)   { return f->qtd == 0; }
int fila_cheia(Fila* f)   { return f->qtd == FILA_MAX; }

void fila_limpa(Fila* f) {
    f->ini = 0;
    f->fim = 0;
    f->qtd = 0;
}