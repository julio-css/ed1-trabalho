#ifndef LISTA_H
#define LISTA_H

/*
 * Módulo Lista Duplamente Encadeada
 * Implementacao de uma lista dinamica generica que permite armazenamento
   de qualquer tipo de dado atraves de ponteiros void*.
 * Por ser duplamente encadeada, permite percurso em ambas as direcoes
   e insercoes eficientes em ambas as extremidades.
 */

typedef struct Lista Lista;

/* Cria uma nova lista vazia.
 * pos-condição: Retorna um ponteiro para a Lista, ou NULL se falhar.
 */
Lista* lista_criar(void);

/* Libera toda a memoria alocada para os nós da lista e para a estrutura da lista.
 * !!!! Não libera a memria dos dados (void*) apontados pelos nós.
 */
void lista_destruir(Lista* l);

/* Insere um elemento no final da lista.
 * Operacao O(1) devido ao ponteiro 'fim'.
 * Retorna 1 em sucesso, 0 em falha.
 */
int lista_inserir_fim(Lista* l, void* dado);

/* Insere um elemento no inicio da lista.
 * Operacao O(1) devido ao ponteiro 'inicio'.
 * Retorna 1 em sucesso, 0 em falha.
 */
int lista_insere_inicio(Lista* l, void* dado);

/* Remove o nó que contem o ponteiro 'dado'.
 * Realiza uma busca linear (O(n)).
 * Retorna o ponteiro do dado removido ou NULL se n encontrado.
 */
void* lista_remove(Lista* l, void* dado);

/* Retorna o dado na posição 'idx'.
 * Opercao O(n). indice 0 eh o primeiro elemento.
 */
void* lista_get(Lista* l, int idx);

/* Retorna a quantidade de elementos na lista. */
int lista_tamanho(Lista* l);

/* Retorna 1 se a lista estiver vazia, 0 caso contrário. */
int lista_vazia(Lista* l);

#endif