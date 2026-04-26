PROJ_NAME = ted
CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -ggdb -O0 -Wall
LDFLAGS = -O0 -lm

SRC   = src
TST   = tst
UNITY = unity
INC   = -I$(SRC) -I$(UNITY)

OBJS = $(SRC)/forma.o \
       $(SRC)/circulo.o \
       $(SRC)/retangulo.o \
       $(SRC)/linha.o \
       $(SRC)/texto.o \
       $(SRC)/fila.o \
       $(SRC)/lista.o \
       $(SRC)/poligono.o\
       $(SRC)/svg.o \

ted: $(OBJS) $(SRC)/main.o
	$(CC) -O0 -o $(SRC)/$(PROJ_NAME) $(OBJS) $(SRC)/main.o -lm

$(SRC)/main.o: $(SRC)/main.c
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

$(SRC)/forma.o: $(SRC)/forma.c $(SRC)/forma.h
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

$(SRC)/circulo.o: $(SRC)/circulo.c $(SRC)/circulo.h
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

$(SRC)/retangulo.o: $(SRC)/retangulo.c $(SRC)/retangulo.h
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

$(SRC)/linha.o: $(SRC)/linha.c $(SRC)/linha.h
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

$(SRC)/texto.o: $(SRC)/texto.c $(SRC)/texto.h
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

$(SRC)/fila.o: $(SRC)/fila.c $(SRC)/fila.h
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

$(SRC)/lista.o: $(SRC)/lista.c $(SRC)/lista.h
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

$(SRC)/poligono.o: $(SRC)/poligono.c $(SRC)/poligono.h $(SRC)/fila.h
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

$(TST)/t_fila: $(TST)/t_fila.c $(SRC)/fila.c $(UNITY)/unity.c
	$(CC) $(CFLAGS) $(INC) $(UNITY)/unity.c $(SRC)/fila.c $(TST)/t_fila.c -o $(TST)/t_fila

$(TST)/t_lista: $(TST)/t_lista.c $(SRC)/lista.c $(UNITY)/unity.c
	$(CC) $(CFLAGS) $(INC) $(UNITY)/unity.c $(SRC)/lista.c $(TST)/t_lista.c -o $(TST)/t_lista

$(TST)/t_forma: $(TST)/t_forma.c $(SRC)/forma.c $(UNITY)/unity.c
	$(CC) $(CFLAGS) $(INC) $(UNITY)/unity.c $(SRC)/forma.c $(TST)/t_forma.c -o $(TST)/t_forma

$(TST)/t_poligono: $(TST)/t_poligono.c $(SRC)/poligono.c $(SRC)/fila.c $(UNITY)/unity.c
	$(CC) $(CFLAGS) $(INC) -DUNITY_INCLUDE_DOUBLE $(UNITY)/unity.c $(SRC)/fila.c $(SRC)/poligono.c $(TST)/t_poligono.c -o $(TST)/t_poligono

$(SRC)/svg.o: $(SRC)/svg.c $(SRC)/svg.h
	 $(CC) -c $(CFLAGS) $(INC) $< -o $@

tst_fila: $(TST)/t_fila
	./$(TST)/t_fila

tst_lista: $(TST)/t_lista
	./$(TST)/t_lista

tst_forma: $(TST)/t_forma
	./$(TST)/t_forma

tst_poligono: $(TST)/t_poligono
	./$(TST)/t_poligono

tstall: tst_fila tst_lista tst_forma tst_poligono

clean:
	rm -f $(SRC)/*.o $(SRC)/$(PROJ_NAME)
	rm -f $(TST)/t_fila $(TST)/t_lista $(TST)/t_forma $(TST)/t_poligono

.PHONY: ted tstall tst_fila tst_lista tst_forma tst_poligono clean


# Variavel com as flags completas do Valgrind
VG = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s

# Roda o valgrind em todos os testes
vtest: tstall
	$(VG) ./tst/t_fila
	$(VG) ./tst/t_lista
	$(VG) ./tst/t_forma
	$(VG) ./tst/t_poligono

# Roda o valgrind no programa principal (ajuste os arquivos .geo/.qry conforme precisar testar)
vted: ted
	$(VG) ./src/ted -e testes -f t1.geo -o saida