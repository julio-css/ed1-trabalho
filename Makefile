PROJ_NAME = ted
CC        = gcc
CFLAGS    = -std=c99 -fstack-protector-all -ggdb -O0 -Wall
LDFLAGS   = -O0

SRC   = src
TST   = tst
UNITY = unity

INC = -I$(SRC) -I$(UNITY)

OBJS = $(SRC)/forma.o $(SRC)/lista.o $(SRC)/poligono.o

ted: $(OBJS)
	$(CC) $(LDFLAGS) -o $(SRC)/$(PROJ_NAME) $(OBJS)

$(SRC)/forma.o: $(SRC)/forma.c $(SRC)/forma.h
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

$(SRC)/lista.o: $(SRC)/lista.c $(SRC)/lista.h
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

$(SRC)/poligono.o: $(SRC)/poligono.c $(SRC)/poligono.h
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

# Testes
$(TST)/t_lista: $(TST)/t_lista.c $(SRC)/lista.c $(UNITY)/unity.c
	$(CC) $(CFLAGS) $(INC) $(UNITY)/unity.c $(SRC)/lista.c $(TST)/t_lista.c -o $@
	
$(TST)/t_poligono: $(TST)/t_poligono.c $(SRC)/poligono.c $(SRC)/fila.c $(UNITY)/unity.c
	$(CC) $(CFLAGS) $(INC) -DUNITY_INCLUDE_DOUBLE $(UNITY)/unity.c $(SRC)/fila.c $(SRC)/poligono.c $(TST)/t_poligono.c -o $@

$(TST)/t_forma: $(TST)/t_forma.c $(SRC)/forma.c $(UNITY)/unity.c
	$(CC) $(CFLAGS) $(INC) $(UNITY)/unity.c $(SRC)/forma.c $(TST)/t_forma.c -o $@

tst_lista: $(TST)/t_lista
	./$(TST)/t_lista

tst_poligono: $(TST)/t_poligono
	./$(TST)/t_poligono

tst_forma: $(TST)/t_forma
	./$(TST)/t_forma

tstall: tst_lista tst_poligono tst_forma

clean:
	rm -f $(SRC)/*.o $(SRC)/$(PROJ_NAME)
	rm -f $(TST)/t_lista $(TST)/t_poligono $(TST)/t_forma

.PHONY: ted tstall tst_lista tst_poligono tst_forma clean