#ifndef LISTA_H
#define LISTA_H

typedef struct Lista Lista;

Lista* lista_criar(void);
void lista_destruir(Lista* l);
int lista_inserir_fim(Lista* l, void* dado, int id, int tipo);
int lista_remover_por_id(Lista* l, int id);
void* lista_buscar_por_id(Lista* l, int id, int* tipo);
int lista_tamanho(Lista* l);
void lista_percorrer(Lista* l, void (*callback)(int id, int tipo, void* dado));

#endif