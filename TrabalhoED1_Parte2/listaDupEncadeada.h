#ifndef LISTADUPENCADEADA_H_INCLUDED
#define LISTADUPENCADEADA_H_INCLUDED

typedef struct filme Filme;
typedef struct descritor Descritor;

typedef struct noDup{
    struct noDup *ant, *prox;
    Filme *info;
}NoListaDup;

void insereSequencia(Filme *f, Descritor *l, int v);

void imprimeSequencia(Descritor *l, int v);
      
void removeSequencia(Descritor *l, int v);
	
void antecede(Descritor *l, int v);
	
void sucede(Descritor *l, int v);
	
#endif // LISTADUPENCADEADA_H_INCLUDED
