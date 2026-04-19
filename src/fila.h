#ifndef FILA_H
#define FILA_H

#define FILA_MAX 100

typedef struct Fila Fila;

/* cria fila vazia. retorna NULL se falhar */
Fila* fila_cria();

/* libera memoria da fila. nao libera os elementos internos */
void fila_destroi(Fila* f);

/* insere elemento no fim. retorna 1 se ok, 0 se cheia */
int fila_insere(Fila* f, void* dado);

/* remove e retorna o mais antigo. retorna NULL se vazia */
void* fila_remove(Fila* f);

/* retorna o mais antigo sem remover. NULL se vazia */
void* fila_frente(Fila* f);

/* acessa elemento pelo indice sem remover. NULL se invalido */
void* fila_get(Fila* f, int idx);

/* retorna quantos elementos tem */
int fila_tamanho(Fila* f);

/* retorna 1 se vazia, 0 caso contrario */
int fila_vazia(Fila* f);

/* retorna 1 se cheia, 0 caso contrario */
int fila_cheia(Fila* f);

/* remove todos os elementos sem liberar os dados */
void fila_limpa(Fila* f);

#endif