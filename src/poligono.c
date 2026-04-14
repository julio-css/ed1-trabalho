#include <stdlib.h>
#include "poligono.h"

typedef struct {
    double x;
    double y;
    int id;
} Ponto;

struct Poligono {
    Ponto pontos[MAX_PONTOS];
    int ini;
    int fim;
    int qtd;
};

Poligono* pol_cria() {
    Poligono* p = (Poligono*) malloc(sizeof(Poligono));
    if (p == NULL) return NULL;
    p->ini = 0;
    p->fim = 0;
    p->qtd = 0;
    return p;
}

void pol_destroi(Poligono* p) {
    if (p == NULL) return;
    free(p);
}

int pol_insere(Poligono* p, double x, double y, int id) {
    if (pol_cheio(p)) return 0;
    p->pontos[p->fim].x  = x;
    p->pontos[p->fim].y  = y;
    p->pontos[p->fim].id = id;
    p->fim = (p->fim + 1) % MAX_PONTOS;
    p->qtd++;
    return 1;
}

int pol_remove(Poligono* p, double* ox, double* oy, int* oid) {
    if (pol_vazio(p)) return 0;
    *ox  = p->pontos[p->ini].x;
    *oy  = p->pontos[p->ini].y;
    *oid = p->pontos[p->ini].id;
    p->ini = (p->ini + 1) % MAX_PONTOS;
    p->qtd--;
    return 1;
}

void pol_limpa(Poligono* p) {
    p->ini = 0;
    p->fim = 0;
    p->qtd = 0;
}

int pol_tamanho(Poligono* p) {
    return p->qtd;
}

int pol_vazio(Poligono* p) {
    return (p->qtd == 0);
}

int pol_cheio(Poligono* p) {
    return (p->qtd == MAX_PONTOS);
}

int pol_get(Poligono* p, int idx, double* ox, double* oy, int* oid) {
    if (idx < 0 || idx >= p->qtd) return 0;
    int pos = (p->ini + idx) % MAX_PONTOS;
    *ox  = p->pontos[pos].x;
    *oy  = p->pontos[pos].y;
    *oid = p->pontos[pos].id;
    return 1;
}