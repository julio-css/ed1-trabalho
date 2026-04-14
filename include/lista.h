#ifndef LISTA_H
#define LISTA_H

typedef struct Lista Lista;

/*
 * Cria uma lista vazia.
 * Retorna ponteiro para a lista ou NULL se falhar.
 */
Lista* lista_criar(void);

/*
 * Destroi a lista e todos os seus nós (mas não os dados apontados).
 */
void lista_destruir(Lista* l);

/*
 * Insere um dado no final da lista.
 * Retorna 1 se sucesso, 0 caso contrário.
 */
int lista_inserir_fim(Lista* l, void* dado, int id, int tipo);

/*
 * Remove o nó com o id especificado.
 * Retorna 1 se removeu, 0 se não encontrou.
 */
int lista_remover_por_id(Lista* l, int id);

/*
 * Busca um dado pelo id.
 * Retorna ponteiro para o dado, ou NULL se não existir.
 */
void* lista_buscar_por_id(Lista* l, int id, int* tipo);

/*
 * Retorna o número de elementos na lista.
 */
int lista_tamanho(Lista* l);

/*
 * Percorre a lista executando uma função callback para cada nó.
 * callback recebe: id, tipo, ponteiro para o dado.
 */
void lista_percorrer(Lista* l, void (*callback)(int id, int tipo, void* dado));

#endif