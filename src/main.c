#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "fila.h"
#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "poligono.h"

#define MAX_PATH      512
#define MAX_POLIGONOS 10

void processa_geo(FILE* arq_geo, Lista* formas) {
    char cmd[4];
    while (fscanf(arq_geo, "%3s", cmd) == 1) {
        if (strcmp(cmd, "c") == 0) {
            int id; double x, y, r; char corb[32], corp[32];
            fscanf(arq_geo, "%d %lf %lf %lf %31s %31s", &id, &x, &y, &r, corb, corp);
            Forma* f = circulo_cria(id, x, y, r, corb, corp);
            if (f != NULL) lista_insere_fim(formas, f);

        } else if (strcmp(cmd, "r") == 0) {
            int id; double x, y, w, h; char corb[32], corp[32];
            fscanf(arq_geo, "%d %lf %lf %lf %lf %31s %31s", &id, &x, &y, &w, &h, corb, corp);
            Forma* f = retangulo_cria(id, x, y, w, h, corb, corp);
            if (f != NULL) lista_insere_fim(formas, f);

        } else if (strcmp(cmd, "l") == 0) {
            int id; double x1, y1, x2, y2; char cor[32];
            fscanf(arq_geo, "%d %lf %lf %lf %lf %31s", &id, &x1, &y1, &x2, &y2, cor);
            Forma* f = linha_cria(id, x1, y1, x2, y2, cor);
            if (f != NULL) lista_insere_fim(formas, f);

        } else if (strcmp(cmd, "t") == 0) {
            int id; double x, y; char corb[32], corp[32], ancora; char conteudo[256];
            fscanf(arq_geo, "%d %lf %lf %31s %31s %c ", &id, &x, &y, corb, corp, &ancora);
            fgets(conteudo, sizeof(conteudo), arq_geo);
            int len = strlen(conteudo);
            if (len > 0 && conteudo[len-1] == '\n') conteudo[len-1] = '\0';
            Forma* f = forma_cria_texto(id, x, y, corb, corp, ancora, conteudo);
            if (f != NULL) lista_insere_fim(formas, f);

        } else if (strcmp(cmd, "ts") == 0) {
            char familia[32], peso[32], tamanho[32];
            fscanf(arq_geo, "%31s %31s %31s", familia, peso, tamanho);
        }
    }
}

Forma* busca_por_id(Lista* formas, int id) {
    int n = lista_tamanho(formas);
    for (int i = 0; i < n; i++) {
        Forma* f = (Forma*) lista_get(formas, i);
        if (forma_get_id(f) == id) return f;
    }
    return NULL;
}

void processa_qry(FILE* arq_qry, Lista* formas,
                  Poligono** poligonos, FILE* arq_txt) {
    char cmd[8];
    Lista* selecionadas = lista_cria();

    while (fscanf(arq_qry, "%7s", cmd) == 1) {

        if (strcmp(cmd, "inp") == 0) {
            int p, i;
            fscanf(arq_qry, "%d %d", &p, &i);
            if (p < 1 || p > MAX_POLIGONOS) continue;
            Forma* f = busca_por_id(formas, i);
            if (f == NULL) continue;
            double ax = forma_get_x(f), ay = forma_get_y(f);
            if (forma_get_tipo(f) == FORMA_LINHA) {
                double x2 = forma_get_x2(f), y2 = forma_get_y2(f);
                if (x2 < ax || (x2 == ax && y2 < ay)) { ax = x2; ay = y2; }
            }
            pol_insere(poligonos[p-1], ax, ay, i);
            if (arq_txt) fprintf(arq_txt, "[*] inp %d %d\nancora em (%.3f, %.3f)\n", p, i, ax, ay);

        } else if (strcmp(cmd, "rmp") == 0) {
            int p; fscanf(arq_qry, "%d", &p);
            if (p < 1 || p > MAX_POLIGONOS) continue;
            double ox, oy; int oid;
            if (pol_remove(poligonos[p-1], &ox, &oy, &oid))
                if (arq_txt) fprintf(arq_txt, "[*] rmp %d\nremovido: (%.3f, %.3f)\n", p, ox, oy);

        } else if (strcmp(cmd, "clp") == 0) {
            int p; fscanf(arq_qry, "%d", &p);
            if (p < 1 || p > MAX_POLIGONOS) continue;
            pol_limpa(poligonos[p-1]);

        } else if (strcmp(cmd, "sel") == 0) {
            double x, y, w, h;
            fscanf(arq_qry, "%lf %lf %lf %lf", &x, &y, &w, &h);
            lista_destroi(selecionadas);
            selecionadas = lista_cria();
            int n = lista_tamanho(formas);
            if (arq_txt) fprintf(arq_txt, "[*] sel %.1f %.1f %.1f %.1f\n", x, y, w, h);
            for (int i = 0; i < n; i++) {
                Forma* f = (Forma*) lista_get(formas, i);
                double fx = forma_get_x(f), fy = forma_get_y(f);
                if (fx >= x && fx <= x+w && fy >= y && fy <= y+h) {
                    lista_insere_fim(selecionadas, f);
                    if (arq_txt) fprintf(arq_txt, "%d: tipo %d\n", forma_get_id(f), forma_get_tipo(f));
                }
            }

        } else if (strcmp(cmd, "dels") == 0) {
            int n = lista_tamanho(selecionadas);
            for (int i = 0; i < n; i++) {
                Forma* f = (Forma*) lista_get(selecionadas, i);
                if (arq_txt) fprintf(arq_txt, "[*] dels: removido id %d\n", forma_get_id(f));
                lista_remove(formas, f);
                forma_destroi(f);
            }
            lista_destroi(selecionadas);
            selecionadas = lista_cria();

        } else if (strcmp(cmd, "mcs") == 0) {
            double dx, dy; char corb[32], corp[32];
            fscanf(arq_qry, "%lf %lf %31s %31s", &dx, &dy, corb, corp);
            int n = lista_tamanho(selecionadas);
            for (int i = 0; i < n; i++) {
                Forma* f = (Forma*) lista_get(selecionadas, i);
                forma_set_x(f, forma_get_x(f) + dx);
                forma_set_y(f, forma_get_y(f) + dy);
                forma_set_cor_borda(f, corb);
                forma_set_cor_preench(f, corp);
            }
        }
    }
    lista_destroi(selecionadas);
}

int main(int argc, char* argv[]) {
    char dir_entrada[MAX_PATH] = ".";
    char dir_saida[MAX_PATH]   = "";
    char nome_geo[MAX_PATH]    = "";
    char nome_qry[MAX_PATH]    = "";

    for (int i = 1; i < argc; i++) {
        if      (strcmp(argv[i], "-e") == 0 && i+1 < argc) strncpy(dir_entrada, argv[++i], MAX_PATH-1);
        else if (strcmp(argv[i], "-f") == 0 && i+1 < argc) strncpy(nome_geo,    argv[++i], MAX_PATH-1);
        else if (strcmp(argv[i], "-o") == 0 && i+1 < argc) strncpy(dir_saida,   argv[++i], MAX_PATH-1);
        else if (strcmp(argv[i], "-q") == 0 && i+1 < argc) strncpy(nome_qry,    argv[++i], MAX_PATH-1);
    }

    if (strlen(nome_geo) == 0 || strlen(dir_saida) == 0) {
        fprintf(stderr, "uso: ted [-e path] -f arq.geo -o dir [-q arq.qry]\n");
        return 1;
    }

    char caminho_geo[MAX_PATH];
    snprintf(caminho_geo, MAX_PATH-1, "%s/%s", dir_entrada, nome_geo);
    FILE* arq_geo = fopen(caminho_geo, "r");
    if (arq_geo == NULL) { fprintf(stderr, "erro: nao abriu %s\n", caminho_geo); return 1; }

    Lista* formas = lista_cria();
    Poligono* poligonos[MAX_POLIGONOS];
    for (int i = 0; i < MAX_POLIGONOS; i++) poligonos[i] = pol_cria();

    processa_geo(arq_geo, formas);
    fclose(arq_geo);

    if (strlen(nome_qry) > 0) {
        char caminho_qry[MAX_PATH];
        snprintf(caminho_qry, MAX_PATH-1, "%s/%s", dir_entrada, nome_qry);
        FILE* arq_qry = fopen(caminho_qry, "r");
        if (arq_qry != NULL) {
            char base_geo[MAX_PATH], base_qry[MAX_PATH];
            strncpy(base_geo, nome_geo, MAX_PATH-1);
            char* pt = strrchr(base_geo, '.'); if (pt) *pt = '\0';
            strncpy(base_qry, nome_qry, MAX_PATH-1);
            pt = strrchr(base_qry, '.'); if (pt) *pt = '\0';
            char caminho_txt[MAX_PATH];
            snprintf(caminho_txt, MAX_PATH-1, "%s/%s-%s.txt", dir_saida, base_geo, base_qry);
            FILE* arq_txt = fopen(caminho_txt, "w");
            processa_qry(arq_qry, formas, poligonos, arq_txt);
            if (arq_txt) fclose(arq_txt);
            fclose(arq_qry);
        }
    }

    for (int i = 0; i < MAX_POLIGONOS; i++) pol_destroi(poligonos[i]);
    int n = lista_tamanho(formas);
    for (int i = 0; i < n; i++) forma_destroi((Forma*) lista_get(formas, i));
    lista_destroi(formas);
    return 0;
}
