#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaComDescritor.h"
#define tam 50

int static id_unico = 0;


// Define parcialmente a estrutura da lista duplamente encadeada
struct noDup;

// Define a estrutura Filme
typedef struct filme{
	int ano, id;
	char nome[tam];
	struct noDup *seq;
}Filme;

//Função que preenche os dados que a estrutura Filme possui e retorna o filme criado
Filme* leFilme(int idParametro, char nomeParametro[tam], int anoParametro){
      
	//Aloca espaço para um novo filme
	Filme* f = (Filme*) malloc(sizeof(Filme)); 

	//Inicializa a lista de filmes da saga vazia
  	f->seq = NULL; 

        //Verifica se o ID passado por parâmetro é diferente de zero
        if(idParametro != 0){
          f->id = idParametro;
          //Verifica qual é o maior ID, fazendo com que o ID único receba sempre o maior
          if(id_unico <= idParametro){
            id_unico = idParametro;
          }
          f->ano = anoParametro;
          strcpy(f->nome, nomeParametro);
          return f;
        }
        
        //Visto que o ID único recebe o maior ID da lista de filmes, incrementa +1 para o próximo filme
        id_unico++;
        f->id = id_unico;
       
	//Pede ao usuário para preencher o nome e o ano de lançamento do filme e informa o ID único do filme
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	printf("Qual o nome do filme? ");
    scanf(" %49[^\n]", f->nome);
    fflush(stdin);

    printf("Qual o ano de lancamento do filme? ");
    scanf("%d", &f->ano);

    printf("\nFilme adicionado com sucesso!\nO ID unico do filme e: %d\n", f->id);
    printf("---------------------------------------------------------------------------------------------------------------------\n\n");

    return f;
}

//Função que altera o nome do filme
void alterarNome(Filme* f){
		printf("\nQual o novo nome do filme? ");
		scanf(" %49[^\n]", f->nome);
		fflush(stdin);
}

//Função que altera o ano de lançamento do filme
void alterarAno(Filme* f){
		printf("Qual o novo ano de lancamento do filme? ");
		scanf("%d", &f->ano);
}

//Função que retorna o ano de lançamento do filme
int retornaAno(Filme* f){
	    return f->ano;
}

//Função que formata a impressão dos filmes
void imprimeFilme(Filme* f){
	printf("| ID unico: %d | Nome: %s | Ano de Lancamento: %d |", f->id, f->nome, f->ano);
}
