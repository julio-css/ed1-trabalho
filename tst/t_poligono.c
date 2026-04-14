#include "unity.h"
#include "poligono.h"

Poligono* p;

void setUp() {
    p = pol_cria();
}

void tearDown() {
    pol_destroi(p);
}

void test_cria() {
    TEST_ASSERT_NOT_NULL(p);
    TEST_ASSERT_EQUAL_INT(0, pol_tamanho(p));
    TEST_ASSERT_EQUAL_INT(1, pol_vazio(p));
}

void test_insere() {
    int ret = pol_insere(p, 1.0, 2.0, 10);
    TEST_ASSERT_EQUAL_INT(1, ret);
    TEST_ASSERT_EQUAL_INT(1, pol_tamanho(p));
    TEST_ASSERT_EQUAL_INT(0, pol_vazio(p));
}

void test_remove_fifo() {
    pol_insere(p, 1.0, 2.0, 10);
    pol_insere(p, 3.0, 4.0, 20);

    double x, y;
    int id;
    int ret = pol_remove(p, &x, &y, &id);

    TEST_ASSERT_EQUAL_INT(1, ret);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 1.0, x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 2.0, y);
    TEST_ASSERT_EQUAL_INT(10, id);
    TEST_ASSERT_EQUAL_INT(1, pol_tamanho(p));
}

void test_remove_vazio() {
    double x, y;
    int id;
    TEST_ASSERT_EQUAL_INT(0, pol_remove(p, &x, &y, &id));
}

void test_limpa() {
    pol_insere(p, 1.0, 1.0, 1);
    pol_insere(p, 2.0, 2.0, 2);
    pol_limpa(p);
    TEST_ASSERT_EQUAL_INT(1, pol_vazio(p));
    TEST_ASSERT_EQUAL_INT(0, pol_tamanho(p));
}

void test_cheio() {
    for (int i = 0; i < MAX_PONTOS; i++)
        pol_insere(p, i, i, i);
    TEST_ASSERT_EQUAL_INT(1, pol_cheio(p));
    TEST_ASSERT_EQUAL_INT(0, pol_insere(p, 0, 0, 0));
}

void test_get() {
    pol_insere(p, 5.0, 6.0, 99);
    double x, y;
    int id;
    TEST_ASSERT_EQUAL_INT(1, pol_get(p, 0, &x, &y, &id));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 5.0, x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 6.0, y);
    TEST_ASSERT_EQUAL_INT(99, id);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_cria);
    RUN_TEST(test_insere);
    RUN_TEST(test_remove_fifo);
    RUN_TEST(test_remove_vazio);
    RUN_TEST(test_limpa);
    RUN_TEST(test_cheio);
    RUN_TEST(test_get);
    return UNITY_END();
}