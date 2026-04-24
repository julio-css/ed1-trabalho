#ifndef CIRCULO_H
#define CIRCULO_H

#include "forma.h"

/*
 * Modulo circulo — operacoes especificas para formas do tipo FORMA_CIRCULO.
 * Usa internamente o modulo forma como base.
 * Todas as funcoes assumem que f e do tipo FORMA_CIRCULO.
 */

 

/*
 * circulo_cria
 * cria uma forma do tipo circulo
 * pre-condicao: id >= 1, r > 0, cor_borda e cor_preench != NULL
 * pos-condicao: retorna ponteiro para Forma criada, NULL se falhar
 */
Forma* circulo_cria(int id, double x, double y, double r,
                    char* cor_borda, char* cor_preench);

/*
 * circulo_get_raio
 * pre-condicao: f != NULL e f eh do tipo FORMA_CIRCULO
 * pos-condicao: retorna o raio do circulo
 */ 
double circulo_get_raio(Forma* f);

/*
 * circulo_get_area
 * pre-condicao: f != NULL e f eh do tipo FORMA_CIRCULO
 * pos-condicao: retorna a area do circulo (pi * r^2)
 */
double circulo_get_area(Forma* f);

/*
 * circulo_contem_ponto
 * verifica se o ponto (px,py) esta dentro do circulo
 * pre-condicao: f != NULL e f eh do tipo FORMA_CIRCULO
 * pos-condicao: retorna 1 se contem, 0 caso contrario
 */
int circulo_contem_ponto(Forma* f, double px, double py);

#endif