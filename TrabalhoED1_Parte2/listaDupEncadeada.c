#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"
#include "listaComDescritor.h"

//Define a estrutura da lista duplamente encadeada
typedef struct noDup{
    struct noDup *ant, *prox;
    Filme *info;
}NoListaDup;

//Função que insere as sagas dos filmes
void insereSequencia(Filme *f, Descritor *l, int v){
	//Aloca espaço para a nova saga
	NoListaDup *novo = (NoListaDup*)malloc(sizeof(NoListaDup));
	NoLista *aux = NULL;
	NoListaDup *temp, *ant = NULL;

	//Verifica onde está o filme que queremos inserir a saga
    for(aux = l->prim; aux != NULL; aux = aux->prox){
        if(aux->info->id == v){
           break; 
        }
    } 

	//Verifica se o espaço foi alocado com sucesso
    if(novo != NULL){

		//Verifica se é o primeiro filme da saga
        if(aux->info->seq == NULL){
                novo->info = f;
                novo->ant = novo->prox = NULL;
                aux->info->seq = novo;
        }
        else{
            for(temp = aux->info->seq; temp != NULL; temp = temp->prox){
                ant = temp;
            }

            novo->info = f;
            ant->prox = novo;
            novo->prox = NULL;
            novo->ant = ant;
        }
 
        l->n++;
    }  
}

//Função que imprime as sagas dos filmes
void imprimeSequencia(Descritor *l, int v){
	NoLista *aux = NULL;
	NoListaDup *temp = NULL;

	//Percorre a lista de filmes procurando o ID que o usuário informou
	for(aux = l->prim; aux != NULL; aux = aux->prox){
		if(aux->info->id == v){

			//Verifica se o filme possui sequência
			if(aux->info->seq == NULL){
				printf("\nNao possui sequencia!\n");
				break;
			}

			//Imprime todos filmes da saga
			printf("--------------------------------------------------------------------------------------------------------------------");
			for(temp = aux->info->seq; temp != NULL; temp = temp->prox){
				printf("\n| Nome: %s | Ano de Lancamento: %d | ID unico: %d |\n", temp->info->nome, temp->info->ano, temp->info->id);
			}
			printf("--------------------------------------------------------------------------------------------------------------------\n\n");
			break;
		}
	}
}

//Função que remove um filme da saga
void removeSequencia(Descritor *l, int v){
	NoLista *aux;
	NoListaDup *ant, *temp = NULL;
	int idAux;

	//Percorre a lista de filmes procurando o ID do filme principal que o usuário informou
	for(aux = l->prim; aux != NULL; aux = aux->prox){
		if(aux->info->id == v){
			temp = aux->info->seq;
			break;
		}
	}
	
	//Verifica se o ID é válido ou se ele pertence a alguma sequencia
	if(aux == NULL){
		printf("\nO ID unico e invalido ou e pertencente a uma sequencia!\n\n");
		return;
	}

	//Verifica qual o ID da sequência o usuário quer remover
	printf("\nQual o ID unico do filme da sequencia que deseja remover? ");
	scanf("%d", &idAux);

	//Verifica se o ID existe
	if(verificaID(l, idAux) == 1){
    	for(temp = aux->info->seq; temp != NULL && temp->info->id != idAux; temp = temp->prox){
			ant = temp;
		}

		// Verifica se o filme a ser removido é o primeiro da sequência
		if(temp->ant == NULL){
			aux->info->seq = temp->prox;
			if(temp->prox != NULL){
				temp->prox->ant = NULL;
			}
		}

		else{
			// Verifica se o filme a ser removido é o ultimo da sequência
			if(temp->prox == NULL){
				ant->prox = NULL;
			}
			else{
				ant->prox = temp->prox;
				temp->prox->ant = ant;
			}
		}

		//Libera espaço da memória ocupado pelo filme que foi removido
		free(temp);
		temp = NULL;

		//Decrementa 1 a cada filme removido
		l->n--;
		
		printf("\nSequencia removida com sucesso!\n\n");
    } 
	else {
    	printf("\nDigite um ID unico valido!\n\n");
    }
}

//Função que verifica o antecedente de um filme
void antecede(Descritor *l, int v){
	NoLista *aux = NULL;
	NoListaDup *temp = NULL;

	for(aux = l->prim; aux != NULL; aux = aux->prox){
		
		//Verifica se possui antecessor
        if(aux->info->id == v){
			printf("\nNao possui antecessor!\n");
			break;
		}

		for(temp = aux->info->seq; temp != NULL; temp = temp->prox){
			if(temp->info->id == v){
				//Verifica se o antecessor é o filme principal
				if(temp->ant == NULL){
					printf("%s\n", aux->info->nome);
					break;
				}
				else{
					printf("%s\n", temp->ant->info->nome);
					break;
				}
			}
		}
	}
}

//Função que verifica o sucessor de um filme
void sucede(Descritor *l, int v){
	NoLista *aux = NULL;
	NoListaDup *temp;

	//Percorre a lista de filmes procurando o ID que o usuário informou para imprimir o sucessor
	for(aux = l->prim; aux != NULL; aux = aux->prox){
		if(aux->info->id == v){
			if(aux->info->seq == NULL){
				printf("\nNao existe sucessor!\n");
				break;
			}
			else{
				printf("\nO sucessor e: %s\n", aux->info->seq->info->nome);
				break;
			}
		}
		else{
			//Percorre a sequência do filme principal procurando o ID para imprimir o sucessor
			for(temp = aux->info->seq; temp != NULL; temp = temp->prox){
				if(temp->info->id == v){
					if(temp->prox == NULL){
						printf("\nNao existe sucessor!\n");
						break;
					}
					else{
						printf("\nO sucessor e: %s\n", temp->prox->info->nome);
						break;
					}
				}
			}
		}
	}
}
