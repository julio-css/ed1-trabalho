#ifndef FORMA_H
#define FORMA_H

typedef struct Circulo Circulo;
typedef struct Retangulo Retangulo;
typedef struct Linha Linha;
typedef struct Texto Texto;

Circulo* circulo_criar(int id, double x, double y, double r, const char* cor_borda, const char* cor_preench);
void circulo_destruir(Circulo* c);
void circulo_desenhar_svg(Circulo* c, FILE* svg);
int circulo_dentro_retangulo(Circulo* c, double rx, double ry, double rw, double rh);
void circulo_transladar(Circulo* c, double dx, double dy);
void circulo_alterar_cores(Circulo* c, const char* nova_corb, const char* nova_corp);

// similares para Retangulo, Linha, Texto...

#endif