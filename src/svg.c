#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"
#include "forma.h"
#include "lista.h"

#define SVG_MARGEM 20.0
#define SVG_RAIO_ANEL 6.0
#define SVG_TAMANHO_X 5.0

/* * CONVERSÃO DE COORDENADAS:
 * Se o desenho ficar de ponta cabeça, troca o comentário das linhas abaixo.
 */
static double converte_y(double y, double altura) {
    // OPÇÃO A: Coordenadas de TELA (Y=0 no topo). Se a casa estava invertida, usa esta:
    return y + SVG_MARGEM;

    // OPÇÃO B: Coordenadas CARTESIANAS (Y=0 em baixo). 
    // return altura - y - SVG_MARGEM;
}

static double converte_x(double x) {
    return x + SVG_MARGEM;
}

void svg_calcula_dimensoes(Lista* formas, double* largura, double* altura) {
    double max_x = 0.0, max_y = 0.0;
    int n = lista_tamanho(formas);
    for (int i = 0; i < n; i++) {
        Forma* f = (Forma*) lista_get(formas, i);
        double x = forma_get_x(f);
        double y = forma_get_y(f);
        switch (forma_get_tipo(f)) {
            case FORMA_CIRCULO: {
                double r = forma_get_raio(f);
                if (x + r > max_x) max_x = x + r;
                if (y + r > max_y) max_y = y + r;
                break;
            }
            case FORMA_RETANGULO: {
                double w = forma_get_largura(f);
                double h = forma_get_altura(f);
                if (x + w > max_x) max_x = x + w;
                if (y + h > max_y) max_y = y + h;
                break;
            }
            case FORMA_LINHA: {
                double x2 = forma_get_x2(f);
                double y2 = forma_get_y2(f);
                if (x > max_x) max_x = x; if (x2 > max_x) max_x = x2;
                if (y > max_y) max_y = y; if (y2 > max_y) max_y = y2;
                break;
            }
            case FORMA_TEXTO:
                if (x > max_x) max_x = x;
                if (y > max_y) max_y = y;
                break;
        }
    }
    *largura = max_x + (SVG_MARGEM * 2);
    *altura  = max_y + (SVG_MARGEM * 2);
}

void svg_abre(FILE* arq, double largura, double altura) {
    fprintf(arq, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%.2f\" height=\"%.2f\">\n", largura, altura);
}

void svg_fecha(FILE* arq) {
    fprintf(arq, "</svg>\n");
}

void svg_desenha_forma(FILE* arq, Forma* f, double altura) {
    char* corb = forma_get_cor_borda(f);
    char* corp = forma_get_cor_preench(f);
    double x = forma_get_x(f);
    double y = forma_get_y(f);
    int id = forma_get_id(f);
    double sx = converte_x(x);

    switch (forma_get_tipo(f)) {
        case FORMA_CIRCULO: {
            double cy = converte_y(y, altura);
            fprintf(arq, "  <circle id=\"%d\" cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\"/>\n", id, sx, cy, forma_get_raio(f), corp, corb);
            break;
        }
        case FORMA_RETANGULO: {
            double w = forma_get_largura(f);
            double h = forma_get_altura(f);
            // No modo TELA, o 'y' já é o topo do retângulo
            double ry = converte_y(y, altura); 
            fprintf(arq, "  <rect id=\"%d\" x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\"/>\n", id, sx, ry, w, h, corp, corb);
            break;
        }
        case FORMA_LINHA: {
            fprintf(arq, "  <line id=\"%d\" x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" style=\"stroke:%s;stroke-width:1\"/>\n", 
                    id, sx, converte_y(y, altura), converte_x(forma_get_x2(f)), converte_y(forma_get_y2(f), altura), corb);
            break;
        }
        case FORMA_TEXTO: {
            char* anchor = "start";
            if (forma_get_ancora(f) == 'm') anchor = "middle";
            else if (forma_get_ancora(f) == 'f') anchor = "end";
            fprintf(arq, "  <text id=\"%d\" x=\"%.2f\" y=\"%.2f\" text-anchor=\"%s\" style=\"font-size:12px;fill:%s;stroke:%s\">%s</text>\n", 
                    id, sx, converte_y(y, altura), anchor, corp, corb, forma_get_texto(f));
            break;
        }
    }
}

void svg_desenha_lista(FILE* arq, Lista* formas) {
    double l, a;
    svg_calcula_dimensoes(formas, &l, &a);
    for (int i = 0; i < lista_tamanho(formas); i++)
        svg_desenha_forma(arq, (Forma*)lista_get(formas, i), a);
}

int svg_gera_arquivo(char* caminho, Lista* formas) {
    FILE* arq = fopen(caminho, "w");
    if (!arq) return 0;
    double l, a;
    svg_calcula_dimensoes(formas, &l, &a);
    svg_abre(arq, l, a);
    svg_desenha_lista(arq, formas);
    svg_fecha(arq);
    fclose(arq);
    return 1;
}