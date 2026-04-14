PROJ_NAME = ted
CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -ggdb -O0 -Wall
LDFLAGS = -O0

SRC   = src
TST   = tst
UNITY = unity

INC = -I$(SRC) -I$(UNITY)

OBJS = $(SRC)/forma.o $(SRC)/fila.o $(SRC)/lista.o $(SRC)/poligono.o

ted: $(OBJS)
	$(CC) $(LDFLAGS) -o $(SRC)/$(PROJ_NAME) $(OBJS)

$(SRC)/forma.o: $(SRC)/forma.c $(SRC)/forma.h
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
	$(CC) $(CFLAGS) $(INC) $(UNITY)/unity.c $(SRC)/fila.c $(SRC)/poligono.c $(TST)/t_poligono.c -o $(TST)/t_poligono

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
