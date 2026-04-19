#include "unity.h"
#include "lista.h"

Lista* l;

void setUp(void) {
    l = lista_criar();
}

void tearDown(void) {
    lista_destruir(l);
}

void test_cria_vazia(void) {
    TEST_ASSERT_NOT_NULL(l);
    TEST_ASSERT_EQUAL_INT(0, lista_tamanho(l));
}

void test_inserir_e_buscar(void) {
    int a = 10, b = 20;
    
    // Inserir com id=1, tipo=0
    TEST_ASSERT_TRUE(lista_inserir_fim(l, &a, 1, 0));
    TEST_ASSERT_EQUAL_INT(1, lista_tamanho(l));
    
    // Inserir com id=2, tipo=0
    TEST_ASSERT_TRUE(lista_inserir_fim(l, &b, 2, 0));
    TEST_ASSERT_EQUAL_INT(2, lista_tamanho(l));
    
    // Buscar por id
    int tipo;
    void* dado = lista_buscar_por_id(l, 1, &tipo);
    TEST_ASSERT_EQUAL_PTR(&a, dado);
    TEST_ASSERT_EQUAL_INT(0, tipo);
    
    dado = lista_buscar_por_id(l, 2, &tipo);
    TEST_ASSERT_EQUAL_PTR(&b, dado);
    
    // Buscar id inexistente
    dado = lista_buscar_por_id(l, 99, NULL);
    TEST_ASSERT_NULL(dado);
}

void test_remover_por_id(void) {
    int a = 5, b = 15, c = 25;
    lista_inserir_fim(l, &a, 1, 0);
    lista_inserir_fim(l, &b, 2, 0);
    lista_inserir_fim(l, &c, 3, 0);
    
    TEST_ASSERT_EQUAL_INT(3, lista_tamanho(l));
    
    // Remover do meio (id=2)
    TEST_ASSERT_TRUE(lista_remover_por_id(l, 2));
    TEST_ASSERT_EQUAL_INT(2, lista_tamanho(l));
    
    // Verificar que os outros ainda estão lá
    int tipo;
    void* dado = lista_buscar_por_id(l, 1, &tipo);
    TEST_ASSERT_EQUAL_PTR(&a, dado);
    dado = lista_buscar_por_id(l, 3, &tipo);
    TEST_ASSERT_EQUAL_PTR(&c, dado);
    
    // Remover id inexistente
    TEST_ASSERT_FALSE(lista_remover_por_id(l, 99));
    
    // Remover primeiro (id=1)
    TEST_ASSERT_TRUE(lista_remover_por_id(l, 1));
    TEST_ASSERT_EQUAL_INT(1, lista_tamanho(l));
    
    // Remover último (id=3)
    TEST_ASSERT_TRUE(lista_remover_por_id(l, 3));
    TEST_ASSERT_EQUAL_INT(0, lista_tamanho(l));
}

void test_percorrer(void) {
    int valores[] = {100, 200, 300};
    lista_inserir_fim(l, &valores[0], 1, 0);
    lista_inserir_fim(l, &valores[1], 2, 0);
    lista_inserir_fim(l, &valores[2], 3, 0);
    
    int soma = 0;
    void callback(int id, int tipo, void* dado) {
        soma += *(int*)dado;
    }
    lista_percorrer(l, callback);
    TEST_ASSERT_EQUAL_INT(600, soma);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_cria_vazia);
    RUN_TEST(test_inserir_e_buscar);
    RUN_TEST(test_remover_por_id);
    RUN_TEST(test_percorrer);
    return UNITY_END();
}                      