#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"
#include "listaDupEncadeada.h"

//Define a estrutura NoLista
typedef struct no{
	struct no *prox;
	Filme *info;
}NoLista;

//Define a estrura da lista com descritor
typedef struct descritor{
	int n;
	NoLista *prim, *ult;
}Descritor;

//Função que cria uma lista vazia do tipo descritor 
Descritor criarLista(){
    Descritor l;
    l.n = 0;
    l.prim = l.ult = NULL;
    return l;
}

//Função que verifica se existe na lista um filme com o ID digitado pelo usuário
int verificaID(Descritor *l, int v){
	NoLista *aux;
	NoListaDup* temp;

	//Pecorre a lista de filmes principais e a lista das sagas e verifica se o ID é existente
	for(aux = l->prim; aux != NULL; aux = aux->prox){
		if(aux->info->id == v){
			return 1;
		}
		else{
			for(temp = aux->info->seq; temp != NULL; temp = temp->prox){
				if (temp->info->id == v){
					return 1;
				}
			}
		}
	}

	//Caso o ID não seja existente, retorna 0
	return 0;
}

//Função que insere novos filmes na lista com descritor (filmes principais)
void insere(Descritor *l, Filme *f) {
	//Aloca espaço para um novo nó
    NoLista* novo = (NoLista*)malloc(sizeof(NoLista));
    NoLista *aux, *ant;

    novo->info = f;
    novo->prox = NULL;

	//Verifica se é o primeiro filme
    if (l->n == 0) {
        l->prim = novo;
        l->ult = novo;
    }
	else {
		//Compara o nome das strings para ordenar em ordem ascendente
        int comparaString = strcmp(f->nome, l->prim->info->nome);

		//Verifica se o novo filme será inserido no inicio da lista
		if (comparaString <= 0) {
            novo->prox = l->prim;
            l->prim = novo;
        }
		else {
            aux = l->prim;
            ant = NULL;

			//Percorre a lista para encontrar a posição que o novo filme será inserido
			while (aux != NULL && comparaString > 0) {
                ant = aux;
                aux = aux->prox;
                if (aux != NULL){
                    comparaString = strcmp(f->nome, aux->info->nome);
                }
            }

			//Insere o filme na posição adequada
            ant->prox = novo;
            novo->prox = aux;

			//Verifica se o novo filme será inserido no final da lista
            if (aux == NULL){
                l->ult = novo;
            }
        }
    }

    l->n++;
}

//Função que remove filmes na lista com descritor (filmes principais)
void removeFilme(Descritor *l, Filme *f, int v){
	NoLista *ant = NULL, *aux;
	NoListaDup *temp;
	int cont = 1;

	//Percorre a lista até achar o ID que o usuário solicitou
	for(aux= l->prim; aux != NULL  && aux->info->id != v; aux=aux->prox){
		ant = aux;
	}

	//Verifica se o ID é válido
	if(aux == NULL){
		printf("\nDigite um ID valido!\n");
	}
	else{
		
		//Verifica se o filme que será removido é o primeiro da lista
		if(ant == NULL){
			l->prim = aux->prox;
			if(l->prim == NULL){
				l->ult == NULL;
			}
		}
		else{
			//Verifica se o filme que será removido é o ultimo da lista
			if(aux->prox == NULL){
				l->ult = ant;
				ant->prox = NULL;
			}
			else{
				ant->prox = aux->prox;
				if(aux->prox == NULL){
                    l->ult=ant;
                }
			}
		}

		//Percorre toda a sequencia do filme e contabiliza quantos filmes serão removidos
		for(temp = aux->info->seq; temp != NULL; temp = temp->prox){
			cont++;
		}

		//Libera espaço da memória ocupado pelo filme que foi removido
		free(aux);

		//Atualiza o número de filmes, retirando o filme removido e sua sequência
		l->n = l->n-cont;
	}
}

//Função que imprime todos os filmes cadastrados
void imprimeFilmes(Descritor *l){
	NoLista *aux;

	//Verifica se não possui filmes
	if(l->n == 0){
		printf("\nA lista de filmes esta vazia!\n");
	}
	else{
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		for(aux = l->prim; aux != NULL; aux = aux->prox){
			imprimeFilme(aux->info);
		
			//Verifica se o filme possui sequência para imprimir na mesma linha
			if(aux->info->seq != NULL){
				NoListaDup *temp;
				for(temp = aux->info->seq; temp != NULL; temp = temp->prox){
					printf(" --> ");
					imprimeFilme(temp->info);
				}
			}
			printf("\n");
		}
		printf("--------------------------------------------------------------------------------------------------------------------\n\n");
	}
}

//Função que altera os dados de um filme já cadastrado
void alteraDados(Descritor *l, Filme *f, int v){
	NoLista *aux;
	NoListaDup *temp;

	for (aux = l->prim; aux != NULL; aux = aux->prox){
		
		//Verifica se o filme que o usuário deseja alterar esta na lista de filmes principais
		if(aux->info->id == v){
			alterarNome(aux->info);
			alterarAno(aux->info);
			insere(l, aux->info);
			removeFilme(l, f, v);
			printf("\nFilme alterado com sucesso!\n\n");
            break;
		}
		//Caso não esteja, percorre a lista de sagas para alterar os dados do filme desejado
		else{
			for(temp = aux->info->seq; temp != NULL; temp = temp->prox){
    			if (temp->info->id == v) {
					alterarNome(temp->info);
            		alterarAno(temp->info);
            		printf("\nFilme alterado com sucesso!\n\n");
            		break;
        		}
			} 
		}
	}
}

//Função que escreve no arquivo todos os filmes armazenados nas listas
void imprimeNoArquivo(Descritor *l, FILE *arquivo){
	NoLista *aux;
	NoListaDup *temp;
	
	//Percorre ambas listas e vai escrevendo no arquivo de acordo com a formatação dada
	for(aux = l->prim; aux != NULL; aux = aux->prox){
		fprintf(arquivo, "%d\t%s\t%d\n", aux->info->id, aux->info->nome, aux->info->ano);
		for(temp = aux->info->seq; temp!= NULL; temp = temp->prox){
			fprintf(arquivo, "|%d|%d|%s\n", temp->info->id, temp->info->ano, temp->info->nome);
		}
	}
}
