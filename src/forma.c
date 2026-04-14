#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forma.h"

/* ========== Círculo ========== */
struct Circulo {
    int id;
    double x, y, r;
    char cor_borda[20];
    char cor_preench[20];
};

Circulo* circulo_criar(int id, double x, double y, double r, const char* cor_borda, const char* cor_preench) {
    Circulo* c = (Circulo*)malloc(sizeof(Circulo));
    if (!c) return NULL;
    c->id = id;
    c->x = x; c->y = y; c->r = r;
    strncpy(c->cor_borda, cor_borda, 19);
    c->cor_borda[19] = '\0';
    strncpy(c->cor_preench, cor_preench, 19);
    c->cor_preench[19] = '\0';
    return c;
}

void circulo_destruir(Circulo* c) { free(c); }

void circulo_desenhar_svg(Circulo* c, FILE* svg) {
    fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" />\n",
            c->x, c->y, c->r, c->cor_borda, c->cor_preench);
}

int circulo_dentro_retangulo(Circulo* c, double rx, double ry, double rw, double rh) {
    return (c->x - c->r >= rx && c->x + c->r <= rx+rw &&
            c->y - c->r >= ry && c->y + c->r <= ry+rh);
}

void circulo_transladar(Circulo* c, double dx, double dy) {
    c->x += dx; c->y += dy;
}

void circulo_alterar_cores(Circulo* c, const char* cor_borda, const char* cor_preench) {
    if (cor_borda) strncpy(c->cor_borda, cor_borda, 19);
    if (cor_preench) strncpy(c->cor_preench, cor_preench, 19);
}

double circulo_get_x(Circulo* c) { return c->x; }
double circulo_get_y(Circulo* c) { return c->y; }

/* ========== Retângulo ========== */
struct Retangulo {
    int id;
    double x, y, w, h;
    char cor_borda[20];
    char cor_preench[20];
};

Retangulo* retangulo_criar(int id, double x, double y, double w, double h, const char* cor_borda, const char* cor_preench) {
    Retangulo* r = (Retangulo*)malloc(sizeof(Retangulo));
    if (!r) return NULL;
    r->id = id;
    r->x = x; r->y = y; r->w = w; r->h = h;
    strncpy(r->cor_borda, cor_borda, 19);
    r->cor_borda[19] = '\0';
    strncpy(r->cor_preench, cor_preench, 19);
    r->cor_preench[19] = '\0';
    return r;
}

void retangulo_destruir(Retangulo* r) { free(r); }

void retangulo_desenhar_svg(Retangulo* r, FILE* svg) {
    fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" />\n",
            r->x, r->y, r->w, r->h, r->cor_borda, r->cor_preench);
}

int retangulo_dentro_retangulo(Retangulo* r, double rx, double ry, double rw, double rh) {
    return (r->x >= rx && r->y >= ry && r->x+r->w <= rx+rw && r->y+r->h <= ry+rh);
}

void retangulo_transladar(Retangulo* r, double dx, double dy) {
    r->x += dx; r->y += dy;
}

void retangulo_alterar_cores(Retangulo* r, const char* cor_borda, const char* cor_preench) {
    if (cor_borda) strncpy(r->cor_borda, cor_borda, 19);
    if (cor_preench) strncpy(r->cor_preench, cor_preench, 19);
}

double retangulo_get_x(Retangulo* r) { return r->x; }
double retangulo_get_y(Retangulo* r) { return r->y; }

/* ========== Linha (esqueleto) ========== */
struct Linha {
    int id;
    double x1, y1, x2, y2;
    char cor[20];
};
// Implementar depois...

/* ========== Texto (esqueleto) ========== */
struct Texto {
    int id;
    double x, y;
    char* texto;
    char ancora; // 'i','m','f'
    char cor_borda[20];
    char cor_preench[20];
    char font_family[20];
    char font_weight[10];
    int font_size;
};
// Implementar depois...