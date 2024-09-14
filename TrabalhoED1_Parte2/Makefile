all: compila executa clean
compila: main.o filme.o listaComDescritor.o listaDupEncadeada.o
	gcc main.o filme.o listaComDescritor.o listaDupEncadeada.o -o trabalho
main.o: main.c
	gcc -c main.c
filme.o: filme.c
	gcc -c filme.c
listaComDescritor.o: listaComDescritor.c
	gcc -c listaComDescritor.c
listaDupEncadeada.o: listaDupEncadeada.c
	gcc -c listaDupEncadeada.c
executa:
	./trabalho
clean:
	rm main.o filme.o listaComDescritor.o listaDupEncadeada.o 


