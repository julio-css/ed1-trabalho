#include <math.h>
#include "circulo.h"
#include "forma.h"

/* delega para forma_cria_circulo — mantem a criacao centralizada em forma.c */
Forma* circulo_cria(int id, double x, double y, double r,
                    char* cor_borda, char* cor_preench) {
    return forma_cria_circulo(id, x, y, r, cor_borda, cor_preench);
}

/* acessa o raio via getter generico de forma */
double circulo_get_raio(Forma* f) {
    return forma_get_raio(f);
}

/* area = pi * r^2 */
double circulo_get_area(Forma* f) {
    double r = forma_get_raio(f);
    return 3.14159265358979 * r * r;
}

/*
 * verifica se (px,py) esta dentro do circulo
 * calcula distancia ao quadrado do ponto ao centro
 * se distancia <= raio^2, o ponto esta dentro
 * usa quadrado para evitar sqrt desnecessario
 */
int circulo_contem_ponto(Forma* f, double px, double py) {
    double cx = forma_get_x(f);
    double cy = forma_get_y(f);
    double r  = forma_get_raio(f);
    double dx = px - cx;
    double dy = py - cy;
    return (dx*dx + dy*dy) <= (r*r);
}
