#ifndef FORMA_H
#define FORMA_H

#define MAX_COR   32
#define MAX_TEXTO 256

/*
 * Modulo Forma (Base Polimorfica)
 * -------------------------------
 * 'Forma' eh o tipo base generico que representa qualquer figura geom.
 * A struct interna eh "opaca" (definida somente em forma.c) para garantir 
   um encapsulamento estrito. O acesso aos dados eh feito EXCLUSIVAMENTE
   pelas funcoes (getters/setters).
 */
typedef struct Forma Forma;

/*
 * TipoForma atua como uma "etiqueta" para o polimorfismo.
 * Ele indica qual figura geometrica a Forma generica esta a guardar no momento,
   determinando quais campos especificos (raio, largura, texto) sao validos.
 */
typedef enum {
    FORMA_CIRCULO,
    FORMA_RETANGULO,
    FORMA_LINHA,
    FORMA_TEXTO
} TipoForma;

/* --- CONSTRUTORES --- */

/* Cria um circulo com centro (x,y) e raio r. Retorna NULL se falhar. */
Forma* forma_cria_circulo(int id, double x, double y, double r,
                          char* cor_borda, char* cor_preench);

/* Cria um retangulo com canto inferior esquerdo (x,y), largura w e altura h. */
Forma* forma_cria_retangulo(int id, double x, double y, double w, double h,
                            char* cor_borda, char* cor_preench);

/* Cria uma linha reta ligando as extremidades (x1,y1) e (x2,y2). */
Forma* forma_cria_linha(int id, double x1, double y1, double x2, double y2,
                        char* cor);

/* Cria um elemento de texto na ancora (x,y). 
 * ancora_tipo: 'i' (início), 'm' (meio) ou 'f' (fim). */
Forma* forma_cria_texto(int id, double x, double y,
                        char* cor_borda, char* cor_preench,
                        char ancora_tipo, char* texto);

/* --- DESTRUIDORRR --- */
/* Liberta em seguranca a memoria alocada para a estrutura Forma. */
void forma_destroi(Forma* f);

/* --- GETTERS (Leitura de Dados) --- */
int forma_get_id(Forma* f);
TipoForma forma_get_tipo(Forma* f);

/* Coordenadas base (ancora principal) */
double forma_get_x(Forma* f);
double forma_get_y(Forma* f);

/* Dados especificos da Linha (Segunda extremidade) */
double forma_get_x2(Forma* f);
double forma_get_y2(Forma* f);

/* Dados especificos do circulo */
double forma_get_raio(Forma* f);

/* Dados especificos do retangulo */
double forma_get_largura(Forma* f);
double forma_get_altura(Forma* f);

/* Cores */
char* forma_get_cor_borda(Forma* f);
char* forma_get_cor_preench(Forma* f);

/* Dados especificos do Texto */
char* forma_get_texto(Forma* f);
char forma_get_ancora(Forma* f); /* Retorna 'i', 'm' ou 'f' */

/*  SETTERS (Alteracao de Dados)  */
void forma_set_x(Forma* f, double x);
void forma_set_y(Forma* f, double y);
void forma_set_x2(Forma* f, double x2); /* Apenas para FORMA_LINHA */
void forma_set_y2(Forma* f, double y2); /* Apenas para FORMA_LINHA */
void forma_set_cor_borda(Forma* f, char* cor);
void forma_set_cor_preench(Forma* f, char* cor);

#endif