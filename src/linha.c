
#include <math.h>
#include "linha.h"
#include "forma.h"

/* delega criacao para forma.c */
Forma* linha_cria(int id, double x1, double y1, double x2, double y2,
                  char* cor) {
    return forma_cria_linha(id, x1, y1, x2, y2, cor);
}

/* retorna segunda extremidade via getters de forma */
double linha_get_x2(Forma* f) { return forma_get_x2(f); }
double linha_get_y2(Forma* f) { return forma_get_y2(f); }

/*
 * comprimento euclidiano: sqrt((x2-x1)^2 + (y2-y1)^2)
 * x1,y1 estao na ancora (forma_get_x, forma_get_y)
 * x2,y2 estao nos dados especificos da linha
 */
double linha_get_comprimento(Forma* f) {
    double dx = forma_get_x2(f) - forma_get_x(f);
    double dy = forma_get_y2(f) - forma_get_y(f);
    return sqrt(dx*dx + dy*dy);
}
