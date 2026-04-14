#ifndef POLIGONO_H
#define POLIGONO_H

#define MAX_PONTOS 100

typedef struct Poligono Poligono;

/*
 -cria um poligono vazio
 -retorna ponteiro para o poligono criado, ou NULL se falhar
 */
Poligono* pol_cria();

/*
 -libera a memoria do poligono
 */
void pol_destroi(Poligono* p);

/*
 -insere uma coordenada no poligono
 -x, y: coordenadas da ancora
 -id: identificador da figura de origem
 -retorna 1 se inseriu, 0 se a fila esta cheia
 */
int pol_insere(Poligono* p, double x, double y, int id);

/*
 -remove a coordenada mais antiga do poligono (FIFO)
 -ox, oy: coordenadas removidas (saida)
 -oid: id da figura removida (saida)
 -retorna 1 se removeu, 0 se estava vazio
 */
int pol_remove(Poligono* p, double* ox, double* oy, int* oid);

/*
 -remove todas as coordenadas do poligono
*/
void pol_limpa(Poligono* p);

/*
-retorna quantos pontos tem no poligono
*/
int pol_tamanho(Poligono* p);

/*
-retorna 1 se o poligono esta vazio, 0 caso contrario
*/
int pol_vazio(Poligono* p);

/*
retorna 1 se o poligono esta cheio, 0 caso contrario
*/
int pol_cheio(Poligono* p);

/*
-acessa um ponto pelo indice sem remover (0 = mais antigo)
-ox, oy: coordenadas do ponto (saida)
-oid: id da figura (saida)
-retorna 1 se o indice e valido, 0 caso contrario
*/
int pol_get(Poligono* p, int idx, double* ox, double* oy, int* oid);

#endif