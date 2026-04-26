#ifndef FORMA_H
#define FORMA_H

#define MAX_COR   32
#define MAX_TEXTO 256

/*
 * Forma e o tipo base de todas as figuras geometricas.
 * A struct interna e definida somente em forma.c.
 * Acesso apenas pelas funcoes abaixo — nunca diretamente.
 */
typedef struct Forma Forma;

/*
 * TipoForma indica qual tipo de figura esta guardada.
 * Determina quais campos internos estao validos.
 */
typedef enum {
    FORMA_CIRCULO,
    FORMA_RETANGULO,
    FORMA_LINHA,
    FORMA_TEXTO
} TipoForma;

/* cria circulo com centro (x,y) e raio r */
Forma* forma_cria_circulo(int id, double x, double y, double r,
                          char* cor_borda, char* cor_preench);

/* cria retangulo com canto inferior esquerdo (x,y), largura w, altura h */
Forma* forma_cria_retangulo(int id, double x, double y, double w, double h,
                            char* cor_borda, char* cor_preench);

/* cria linha com extremidades (x1,y1) e (x2,y2) */
Forma* forma_cria_linha(int id, double x1, double y1, double x2, double y2,
                        char* cor);

/* cria texto em (x,y). ancora_tipo: i=inicio m=meio f=fim */
Forma* forma_cria_texto(int id, double x, double y,
                        char* cor_borda, char* cor_preench,
                        char ancora_tipo, char* texto);

/* libera a memoria da forma */
void forma_destroi(Forma* f);

/* retorna o id da forma */
int forma_get_id(Forma* f);

/* retorna o tipo da forma */
TipoForma forma_get_tipo(Forma* f);

/* retorna coordenada ancora x */
double forma_get_x(Forma* f);

/* retorna coordenada ancora y */
double forma_get_y(Forma* f);

/* retorna segunda extremidade x — apenas para FORMA_LINHA */
double forma_get_x2(Forma* f);

/* retorna segunda extremidade y — apenas para FORMA_LINHA */
double forma_get_y2(Forma* f);

/* retorna raio — apenas para FORMA_CIRCULO */
double forma_get_raio(Forma* f);

/* retorna largura — apenas para FORMA_RETANGULO */
double forma_get_largura(Forma* f);

/* retorna altura — apenas para FORMA_RETANGULO */
double forma_get_altura(Forma* f);

/* retorna string da cor da borda */
char* forma_get_cor_borda(Forma* f);

/* retorna string da cor de preenchimento */
char* forma_get_cor_preench(Forma* f);

/* atualiza coordenada x da ancora */
void forma_set_x(Forma* f, double x);

/* atualiza coordenada y da ancora */
void forma_set_y(Forma* f, double y);

/* atualiza segunda extremidade x - apenas para FORMA_LINHA */
void forma_set_x2(Forma* f, double x2);

/* atualiza segunda extremidade y - apenas para FORMA_LINHA */
void forma_set_y2(Forma* f, double y2);

/* atualiza cor da borda */
void forma_set_cor_borda(Forma* f, char* cor);

/* atualiza cor de preenchimento */
void forma_set_cor_preench(Forma* f, char* cor);

/* retorna o conteudo do texto — apenas para FORMA_TEXTO */
char* forma_get_texto(Forma* f);

/* retorna o tipo da ancora — apenas para FORMA_TEXTO: i m f */
char forma_get_ancora(Forma* f);


#endif
