PROJ_NAME = ted
CC        = gcc
CFLAGS    = -std=c99 -fstack-protector-all -ggdb -O0 -Wall
LDFLAGS   = -O0

SRC   = src
TST   = tst
UNITY = unity

INC = -I$(SRC) -I$(UNITY)

#executavel principal: gerado dentro de src/
ted: $(SRC)/poligono.o
	$(CC) $(LDFLAGS) -o $(SRC)/$(PROJ_NAME) $(SRC)/poligono.o

$(SRC)/poligono.o: $(SRC)/poligono.c $(SRC)/poligono.h
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

#testa um de cada vez
$(TST)/t_poligono: $(TST)/t_poligono.c $(SRC)/poligono.c $(UNITY)/unity.c
	$(CC) $(CFLAGS) $(INC) \
		$(UNITY)/unity.c \
		$(SRC)/poligono.c \
		$(TST)/t_poligono.c \
		-o $(TST)/t_poligono

tst_poligono: $(TST)/t_poligono
	./$(TST)/t_poligono

#roda todos os testes
tstall: tst_poligono
	@echo "===== Todos os testes OK ====="

clean:
	rm -f $(SRC)/*.o
	rm -f $(SRC)/$(PROJ_NAME)
	rm -f $(TST)/t_poligono

.PHONY: ted tst_poligono tstall clean