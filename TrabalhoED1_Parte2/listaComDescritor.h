#ifndef LISTACOMDESCRITOR_H_INCLUDED
#define LISTACOMDESCRITOR_H_INCLUDED

typedef struct filme Filme;

typedef struct no{
	struct no *prox;
	Filme *info;
}NoLista;

typedef struct descritor{
	int n;
	NoLista *prim, *ult;
}Descritor;

Descritor criarLista();

int verificaID(Descritor *l, int v);

void insere(Descritor *l, Filme *f);

void removeFilme(Descritor *l, Filme *f, int v);

void imprimeFilmes(Descritor *l);

void alteraDados(Descritor *l, Filme *f, int v);

void imprimeNoArquivo(Descritor *l, FILE *arquivo);


#endif // LISTACOMDESCRITOR_H_INCLUDED
