#include <stdlib.h>
#include <string.h>
#include "forma.h"

/* --- ESTRUTURAS DE DADOS ESPECIFICAS --- */
typedef struct { double raio; } DadosCirculo;
typedef struct { double w, h; } DadosRetangulo;
typedef struct { double x2, y2; } DadosLinha;
typedef struct { char ancora_tipo; char texto[MAX_TEXTO]; } DadosTexto;

/*
 * ESTRUTURA PRINCIPAL
 * Utilizamos uma 'union' para os dados especificos.
 * Ao contrário de uma struct normal (onde todos os campos somam memória),
   a 'union' faz com que circ, ret, lin e txt partilhem EXATAMENTE o mesmo
   espaço na mem. ram. O tamanho da union sera apenas o tamanho da maior 
   struct interna (DadosTexto). Isso poupa muita memoriae permite que a 
   nossa lista encadeada guarde "Formas" genericas sem saber os seus tipos.
 */
struct Forma {
    int id;
    double x, y;
    char cor_borda[MAX_COR];
    char cor_preench[MAX_COR];
    TipoForma tipo;
    union {
        DadosCirculo   circ;
        DadosRetangulo ret;
        DadosLinha     lin;
        DadosTexto     txt;
    } dados;
};

/*
 * FUNcaO DE APOIO INTERNA (Static)
 * Usamos a aplicacao do principio DRY (Don't Repeat Yourself).
   Como todas as formas partilham o id, coordenadas base e cores, centralizamos
   o malloc e o preenchimento inicial aqui. As funcoees criadoras especificas 
   apenas chamam esta base e preenchem as suas partes da union.
 */
static Forma* aloca_forma(int id, double x, double y,
                           char* cor_borda, char* cor_preench,
                           TipoForma tipo) {
    Forma* f = (Forma*) malloc(sizeof(Forma));
    if (f == NULL) return NULL;
    
    f->id   = id;
    f->x    = x;
    f->y    = y;
    f->tipo = tipo;
    
    /* Prevencao contra Buffer Overflow ao copiar strings */
    strncpy(f->cor_borda, cor_borda, MAX_COR - 1);
    strncpy(f->cor_preench, cor_preench, MAX_COR - 1);
    f->cor_borda[MAX_COR - 1]   = '\0';
    f->cor_preench[MAX_COR - 1] = '\0';
    
    return f;
}

/* --- CONSTRUTORES PÚBLICOS --- */

Forma* forma_cria_circulo(int id, double x, double y, double r,
                           char* cor_borda, char* cor_preench) {
    Forma* f = aloca_forma(id, x, y, cor_borda, cor_preench, FORMA_CIRCULO);
    if (f != NULL) f->dados.circ.raio = r;
    return f;
}

Forma* forma_cria_retangulo(int id, double x, double y, double w, double h,
                             char* cor_borda, char* cor_preench) {
    Forma* f = aloca_forma(id, x, y, cor_borda, cor_preench, FORMA_RETANGULO);
    if (f != NULL) {
        f->dados.ret.w = w;
        f->dados.ret.h = h;
    }
    return f;
}

Forma* forma_cria_linha(int id, double x1, double y1, double x2, double y2,
                         char* cor) {
    Forma* f = aloca_forma(id, x1, y1, cor, cor, FORMA_LINHA);
    if (f != NULL) {
        f->dados.lin.x2 = x2;
        f->dados.lin.y2 = y2;
    }
    return f;
}

Forma* forma_cria_texto(int id, double x, double y,
                         char* cor_borda, char* cor_preench,
                         char ancora_tipo, char* texto) {
    Forma* f = aloca_forma(id, x, y, cor_borda, cor_preench, FORMA_TEXTO);
    if (f != NULL) {
        f->dados.txt.ancora_tipo = ancora_tipo;
        strncpy(f->dados.txt.texto, texto, MAX_TEXTO - 1);
        f->dados.txt.texto[MAX_TEXTO - 1] = '\0';
    }
    return f;
}

void forma_destroi(Forma* f) {
    if (f == NULL) return;
    free(f);
}

/* GETTERS BÁSICOS  */
int       forma_get_id(Forma* f)          { return f->id; }
TipoForma forma_get_tipo(Forma* f)        { return f->tipo; }
double    forma_get_x(Forma* f)           { return f->x; }
double    forma_get_y(Forma* f)           { return f->y; }
char* forma_get_cor_borda(Forma* f)   { return f->cor_borda; }
char* forma_get_cor_preench(Forma* f) { return f->cor_preench; }

/* GETTERS ESPECÍFICOS (Acessam a Union) */
double    forma_get_x2(Forma* f)          { return f->dados.lin.x2; }
double    forma_get_y2(Forma* f)          { return f->dados.lin.y2; }
double    forma_get_raio(Forma* f)        { return f->dados.circ.raio; }
double    forma_get_largura(Forma* f)     { return f->dados.ret.w; }
double    forma_get_altura(Forma* f)      { return f->dados.ret.h; }
char* forma_get_texto(Forma* f)       { return f->dados.txt.texto; }
char      forma_get_ancora(Forma* f)      { return f->dados.txt.ancora_tipo; }

/* --- SETTERS --- */
void forma_set_x(Forma* f, double x)   { f->x = x; }
void forma_set_y(Forma* f, double y)   { f->y = y; }
void forma_set_x2(Forma* f, double x2) { f->dados.lin.x2 = x2; }
void forma_set_y2(Forma* f, double y2) { f->dados.lin.y2 = y2; }

/* Setters com protecao de tamanho de string */
void forma_set_cor_borda(Forma* f, char* cor) {
    strncpy(f->cor_borda, cor, MAX_COR - 1);
    f->cor_borda[MAX_COR - 1] = '\0';
}

void forma_set_cor_preench(Forma* f, char* cor) {
    strncpy(f->cor_preench, cor, MAX_COR - 1);
    f->cor_preench[MAX_COR - 1] = '\0';
}