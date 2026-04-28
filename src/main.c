#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* modulos do projeto */
#include "lista.h"
#include "fila.h"
#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "poligono.h"
#include "svg.h"

/* Tamanho maximo seguro para a construcao de caminhos de ficheiros */
#define MAX_PATH      512

/* Numero maximo de poligonos estipulado pelas regras do trabalho (1 a 10) */
#define MAX_POLIGONOS 10

/*
 * modulo parser: processa_geo
 * ---------------------------
 * Funciona como um padrao "Factory". Lê o ficheiro de entrada linha por linha 
   e, dependendo da assinatura do comando (c, r, l, t),
   invoca o construtor apropriado do modulo 'forma'. O ponteiro generico resultante
   eh entao armazenado de forma agnostica na Lista Principal.
 */
void processa_geo(FILE* arq_geo, Lista* formas) {
    char cmd[4]; 

    while (fscanf(arq_geo, "%3s", cmd) == 1) {
        if (strcmp(cmd, "c") == 0) {
            int id; double x, y, r; char corb[32], corp[32];
            fscanf(arq_geo, "%d %lf %lf %lf %31s %31s", &id, &x, &y, &r, corb, corp);
            Forma* f = circulo_cria(id, x, y, r, corb, corp);
            if (f != NULL) lista_inserir_fim(formas, f);

        } else if (strcmp(cmd, "r") == 0) {
            int id; double x, y, w, h; char corb[32], corp[32];
            fscanf(arq_geo, "%d %lf %lf %lf %lf %31s %31s", &id, &x, &y, &w, &h, corb, corp);
            Forma* f = retangulo_cria(id, x, y, w, h, corb, corp);
            if (f != NULL) lista_inserir_fim(formas, f);

        } else if (strcmp(cmd, "l") == 0) {
            int id; double x1, y1, x2, y2; char cor[32];
            fscanf(arq_geo, "%d %lf %lf %lf %lf %31s", &id, &x1, &y1, &x2, &y2, cor);
            Forma* f = linha_cria(id, x1, y1, x2, y2, cor);
            if (f != NULL) lista_inserir_fim(formas, f);

        } else if (strcmp(cmd, "t") == 0) {
            int id; double x, y; char corb[32], corp[32], ancora; char conteudo[256];
            fscanf(arq_geo, "%d %lf %lf %31s %31s %c ", &id, &x, &y, corb, corp, &ancora);
            /* O fgets é necessario porque o texto pode conter espacos (ex: "Ola Mundo") */
            fgets(conteudo, sizeof(conteudo), arq_geo);
            int len = strlen(conteudo);
            if (len > 0 && conteudo[len-1] == '\n') conteudo[len-1] = '\0'; // Limpa a quebra de linha
            
            Forma* f = forma_cria_texto(id, x, y, corb, corp, ancora, conteudo);
            if (f != NULL) lista_inserir_fim(formas, f);

        } else if (strcmp(cmd, "ts") == 0) {
            /* Lê e ignora propriedades de fonte por enquanto, conforme especificacao atual */
            char familia[32], peso[32], tamanho[32];
            fscanf(arq_geo, "%31s %31s %31s", familia, peso, tamanho);
        }
    }
}

/*
 * entra como funcao auxiliar: busca_por_id
 * Como as formas estao numa Lista Encadeada nao ordenada,
   a busca eh feita de forma linear (O(n)). Percorre-se a lista testando 
   o ID de cada elemento ate encontrar o alvo.
 */
Forma* busca_por_id(Lista* formas, int id) {
    int n = lista_tamanho(formas);
    for (int i = 0; i < n; i++) {
        Forma* f = (Forma*) lista_get(formas, i);
        if (forma_get_id(f) == id) return f;
    }
    return NULL; 
}

/*
 * modulo motor main: processa_qry
 * Atua como uma maquina de estados. Comandos de selecao ('sel')
   criam um subconjunto de formas (a lista 'selecionadas'). Comandos mutadores 
   ('dels', 'mcs') atuam EXCLUSIVAMENTE sobre este subconjunto em memoria.
 */
void processa_qry(FILE* arq_qry, Lista* formas, Poligono** poligonos, FILE* arq_txt) {
    char cmd[8];
    Lista* selecionadas = lista_criar();

    while (fscanf(arq_qry, "%7s", cmd) == 1) {

        if (strcmp(cmd, "inp") == 0) {
            int p, i;
            fscanf(arq_qry, "%d %d", &p, &i);
            if (p < 1 || p > MAX_POLIGONOS) continue;
            
            Forma* f = busca_por_id(formas, i);
            if (f == NULL) continue;
            
            double ax = forma_get_x(f), ay = forma_get_y(f);
            
            /* Regra especifica do trabalho: se for linha, usar a menor extremidade */
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
            
            /* Esvazia selecoes anteriores */
            lista_destruir(selecionadas);
            selecionadas = lista_criar();
            
            int n = lista_tamanho(formas);
            if (arq_txt) fprintf(arq_txt, "[*] sel %.1f %.1f %.1f %.1f\n", x, y, w, h);
            
            /* Filtro Espacial: Verifica se a ancora da forma esta dentro do retanglo demilitador */
            for (int i = 0; i < n; i++) {
                Forma* f = (Forma*) lista_get(formas, i);
                double fx = forma_get_x(f), fy = forma_get_y(f);
                if (fx >= x && fx <= x+w && fy >= y && fy <= y+h) {
                    lista_inserir_fim(selecionadas, f);
                    if (arq_txt) fprintf(arq_txt, "%d: tipo %d\n", forma_get_id(f), forma_get_tipo(f));
                }
            }

        } else if (strcmp(cmd, "dels") == 0) {
            int n = lista_tamanho(selecionadas);
            for (int i = 0; i < n; i++) {
                Forma* f = (Forma*) lista_get(selecionadas, i);
                if (arq_txt) fprintf(arq_txt, "[*] dels: removido id %d\n", forma_get_id(f));
                /* Remove fisicamente da memoria e da lista principal */
                lista_remove(formas, f);
                forma_destroi(f);
            }
            lista_destruir(selecionadas);
            selecionadas = lista_criar();

        } else if (strcmp(cmd, "mcs") == 0) {
            /* Translacao (dx, dy) e recoloracao das formas selecionadas */
            double dx, dy; char corb[32], corp[32];
            fscanf(arq_qry, "%lf %lf %31s %31s", &dx, &dy, corb, corp);
            
            int n = lista_tamanho(selecionadas);
            for (int i = 0; i < n; i++) {
                Forma* f = (Forma*) lista_get(selecionadas, i);
                
                /* Move a ancora principal */
                forma_set_x(f, forma_get_x(f) + dx);
                forma_set_y(f, forma_get_y(f) + dy);
                
                /* excecao estrutural -> linhas possuem dois pontos no plano.
                 * Ambos os pontos devem ser transladados para que a linha 
                   mova de forma rigida e nao distorca. */
                if (forma_get_tipo(f) == FORMA_LINHA) {
                    forma_set_x2(f, forma_get_x2(f) + dx);
                    forma_set_y2(f, forma_get_y2(f) + dy);
                }
                
                forma_set_cor_borda(f, corb);
                forma_set_cor_preench(f, corp);
            }
        }
    }
    lista_destruir(selecionadas);
}

/*
 * PONTO DE ENTRADA DO PROGRAMA 
 * Parsing de parametros -> Leitura de dados -> Processamento -> Exportacao
 */
int main(int argc, char* argv[]) {
    char dir_entrada[MAX_PATH] = "."; 
    char dir_saida[MAX_PATH]   = "";
    char nome_geo[MAX_PATH]    = "";
    char nome_qry[MAX_PATH]    = "";

    /* Processamento Seguro de Argumentos CLI */
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

    /* Construcao de caminhos evitando Buffer Overflow (snprintf) */
    char caminho_geo[MAX_PATH * 2];
    snprintf(caminho_geo, sizeof(caminho_geo), "%s/%s", dir_entrada, nome_geo);
    
    FILE* arq_geo = fopen(caminho_geo, "r");
    if (arq_geo == NULL) { fprintf(stderr, "erro: nao abriu %s\n", caminho_geo); return 1; }

    /* Inicializacao das Estruturas de Dados */
    Lista* formas = lista_criar();
    Poligono* poligonos[MAX_POLIGONOS];
    for (int i = 0; i < MAX_POLIGONOS; i++) poligonos[i] = pol_cria();

    /* PASSO 1: Lê e cria o cenario base */
    processa_geo(arq_geo, formas);
    fclose(arq_geo);

    /* PASSO 2: Gera o primeiro SVG (Snapshot do "Antes") */
    char caminho_svg_inicial[MAX_PATH];
    strncpy(caminho_svg_inicial, nome_geo, MAX_PATH-1);
    char* pt_svg = strrchr(caminho_svg_inicial, '.'); 
    if (pt_svg) *pt_svg = '\0'; /* Remove a extensao .geo */
    
    char svg_path[MAX_PATH * 2]; 
    snprintf(svg_path, sizeof(svg_path), "%s/%s.svg", dir_saida, caminho_svg_inicial);
    svg_gera_arquivo(svg_path, formas);

    /* PASSO 3: Aplicacao de cnsultas (seexistir arquivo .qry) */
    if (strlen(nome_qry) > 0) {
        char caminho_qry[MAX_PATH * 2];
        snprintf(caminho_qry, sizeof(caminho_qry), "%s/%s", dir_entrada, nome_qry);
        FILE* arq_qry = fopen(caminho_qry, "r");
        
        if (arq_qry != NULL) {
            /* extrai os nomes base (sem extensoes) para compor o nome de saida final */
            char base_geo[MAX_PATH], base_qry[MAX_PATH];
            
            strncpy(base_geo, nome_geo, MAX_PATH-1);
            char* pt = strrchr(base_geo, '.'); if (pt) *pt = '\0';
            
            strncpy(base_qry, nome_qry, MAX_PATH-1);
            pt = strrchr(base_qry, '.'); if (pt) *pt = '\0';
            
            /* gera o arquivo de log .txt contendo os echos dos comandos */
            char caminho_txt[MAX_PATH * 4]; 
            snprintf(caminho_txt, sizeof(caminho_txt), "%s/%s-%s.txt", dir_saida, base_geo, base_qry);
            FILE* arq_txt = fopen(caminho_txt, "w");
            
            processa_qry(arq_qry, formas, poligonos, arq_txt);
            
            if (arq_txt) fclose(arq_txt);
            fclose(arq_qry);

            /* PASSO 4: Gera o SEGUNDO SVG (Snapshot do "Depois") */
            char caminho_svg_final[MAX_PATH * 4];
            snprintf(caminho_svg_final, sizeof(caminho_svg_final), "%s/%s-%s.svg", dir_saida, base_geo, base_qry);
            svg_gera_arquivo(caminho_svg_final, formas);
        }
    }

    /* PASSO 5: Limpeza de Memoria Rigorosa (Evita Memory Leaks) */
    for (int i = 0; i < MAX_POLIGONOS; i++) pol_destroi(poligonos[i]);

    /* Destroi primeiro os elementos armazenados e depois o "recipiente" (a Lista) */
    int n = lista_tamanho(formas);
    for (int i = 0; i < n; i++) forma_destroi((Forma*) lista_get(formas, i));
    lista_destruir(formas);

    return 0;
}