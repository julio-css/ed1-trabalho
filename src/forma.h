#include <stdio.h>
#ifndef FORMA_H
#define FORMA_H


/* tamanho maximo para strings de cor e texto */
#define MAX_COR   32
#define MAX_TEXTO 256

/*
 * tipo abstrato Forma
 *
 * uma forma e um elemento geometrico que pode ser
 * circulo, retangulo, linha ou texto.
 * cada forma tem um id unico, uma posicao ancora (x,y)
 * e dados especificos do seu tipo.
 *
 * a struct e definida somente em forma.c
 */
typedef struct Forma Forma;

/* tipos possiveis de forma */
typedef enum {
    FORMA_CIRCULO,
    FORMA_RETANGULO,
    FORMA_LINHA,
    FORMA_TEXTO
} TipoForma;

/*
 * forma_cria_circulo
 * cria uma forma do tipo circulo
 * pre-condicao: id >= 1, r > 0
 * pos-condicao: retorna ponteiro para a forma criada, ou NULL se falhar
 */
Forma* forma_cria_circulo(int id, double x, double y, double r,
                           char* cor_borda, char* cor_preench);

/*
 * forma_cria_retangulo
 * cria uma forma do tipo retangulo
 * pre-condicao: id >= 1, w > 0, h > 0
 * pos-condicao: retorna ponteiro para a forma criada, ou NULL se falhar
 */
Forma* forma_cria_retangulo(int id, double x, double y, double w, double h,
                             char* cor_borda, char* cor_preench);

/*
 * forma_cria_linha
 * cria uma forma do tipo linha com extremidades (x1,y1) e (x2,y2)
 * pre-condicao: id >= 1
 * pos-condicao: retorna ponteiro para a forma criada, ou NULL se falhar
 */
Forma* forma_cria_linha(int id, double x1, double y1, double x2, double y2,
                         char* cor);

/*
 * forma_cria_texto
 * cria uma forma do tipo texto
 * ancora_tipo: 'i' inicio, 'm' meio, 'f' fim
 * pre-condicao: id >= 1, texto != NULL
 * pos-condicao: retorna ponteiro para a forma criada, ou NULL se falhar
 */
Forma* forma_cria_texto(int id, double x, double y,
                         char* cor_borda, char* cor_preench,
                         char ancora_tipo, char* texto);

/*
 * forma_destroi
 * libera a memoria da forma
 * pre-condicao: nenhuma
 * pos-condicao: memoria liberada, ponteiro invalido apos chamada
 */
void forma_destroi(Forma* f);

/*
 * forma_get_id
 * pos-condicao: retorna o id da forma
 */
int forma_get_id(Forma* f);

/*
 * forma_get_tipo
 * pos-condicao: retorna o tipo da forma (TipoForma)
 */
TipoForma forma_get_tipo(Forma* f);

/*  
 * forma_get_x / forma_get_y
 * pos-condicao: retorna a coordenada ancora da forma
 */
double forma_get_x(Forma* f);
double forma_get_y(Forma* f);

/*
 * forma_get_x2 / forma_get_y2
 * pre-condicao: forma e do tipo FORMA_LINHA
 * pos-condicao: retorna a segunda extremidade da linha
 */
double forma_get_x2(Forma* f);
double forma_get_y2(Forma* f);

/*
 * forma_get_raio
 * pre-condicao: forma e do tipo FORMA_CIRCULO
 * pos-condicao: retorna o raio do circulo
 */
double forma_get_raio(Forma* f);

/*
 * forma_get_largura / forma_get_altura
 * pre-condicao: forma e do tipo FORMA_RETANGULO
 * pos-condicao: retorna largura ou altura do retangulo
 */
double forma_get_largura(Forma* f);
double forma_get_altura(Forma* f);

/*
 * forma_get_cor_borda / forma_get_cor_preench
 * pos-condicao: retorna string da cor (nao modifique o ponteiro retornado)
 */
char* forma_get_cor_borda(Forma* f);
char* forma_get_cor_preench(Forma* f);

/*
 * forma_set_x / forma_set_y
 * pos-condicao: atualiza a posicao ancora da forma
 */
void forma_set_x(Forma* f, double x);
void forma_set_y(Forma* f, double y);

/*
 * forma_set_cor_borda / forma_set_cor_preench
 * pos-condicao: atualiza as cores da forma
 */
void forma_set_cor_borda(Forma* f, char* cor);
void forma_set_cor_preench(Forma* f, char* cor);

// Linha
typedef struct Linha Linha;
Linha* linha_criar(int id, double x1, double y1, double x2, double y2, const char* cor);
void linha_destruir(Linha* l);
void linha_desenhar_svg(Linha* l, FILE* svg);
int linha_dentro_retangulo(Linha* l, double rx, double ry, double rw, double rh);
void linha_transladar(Linha* l, double dx, double dy);
void linha_alterar_cor(Linha* l, const char* nova_cor);

// Texto
typedef struct Texto Texto;
Texto* texto_criar(int id, double x, double y, const char* texto, char ancora,
                   const char* cor_borda, const char* cor_preench,
                   const char* font_family, const char* font_weight, int font_size);
void texto_destruir(Texto* t);
void texto_desenhar_svg(Texto* t, FILE* svg);
int texto_dentro_retangulo(Texto* t, double rx, double ry, double rw, double rh);
void texto_transladar(Texto* t, double dx, double dy);
void texto_alterar_cores(Texto* t, const char* cor_borda, const char* cor_preench);

#endif