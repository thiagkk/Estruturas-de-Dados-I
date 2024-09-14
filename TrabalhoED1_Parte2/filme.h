#ifndef FILME_H_INCLUDED
#define FILME_H_INCLUDED
#define tam 50

typedef struct filme{
	int ano, id;
	char nome[tam];
	struct noDup *seq;
}Filme;

Filme* leFilme(int idParametro, char nomeParametro[tam], int anoParametro);

void alterarNome(Filme* f);

void alterarAno(Filme* f);

int retornaAno(Filme* f);

void imprimeFilme(Filme* f);

#endif // FILME_H_INCLUDED



