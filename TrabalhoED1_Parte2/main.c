#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"
#include "listaDupEncadeada.h"
#include "listaComDescritor.h"
#define tam 50
 


int main(){
	Filme *filme;
	NoLista* novo = (NoLista*)malloc(sizeof(NoLista));
	Descritor l = criarLista();
	NoLista *temp;
	int opcao=0, idAux=0, idParametro=0, anoParametro=0, idAnterior=0;
	char nomeParametro[tam];
	
	//Abrindo/criando um arquivo para leitura/escrita
	FILE *arquivo = fopen("listadefilmes.txt", "a+");
	
	//Verifica se o arquivo não está vazio
	if(fgetc(arquivo) != EOF){
	    fseek(arquivo, 0, SEEK_SET); //Função chamada para mover o ponteiro para o início do arquivo
            
            //Percorre até chegar ao final do arquivo
            while (!feof(arquivo)){
                //Verifica se o fscanf lê o formato dado, caso não consiga ler, ele lê o formato das sequências e insere o filme na lista de sequências
                if(fscanf(arquivo, "%d\t%[^\t\n]\t%d\n", &idParametro, nomeParametro, &anoParametro) == 0){ //
                    fscanf(arquivo, "|%d|%d|%[^\n]\n", &idParametro, &anoParametro, nomeParametro);
                    filme = leFilme(idParametro, nomeParametro, anoParametro);
                    insereSequencia(filme, &l, idAnterior);
                }
                //Caso consiga ler o formato dado, insere o filme na lista
                else{
                    filme = leFilme(idParametro, nomeParametro, anoParametro);
                    idAnterior = idParametro; //Armazena o ID do filme para o caso da próxima linha lida do arquivo ser uma sequeência
                    insere(&l, filme);
                }
            }
        }
        
        idParametro = 0; //Após todo arquivo lido, a variável recebe zero, para com que os próximos filmes sejam inseridos pelo usuário
        fclose(arquivo); //Fechando o arquivo após toda leitura
        
	do{
		printf("Escolha a opcao desejada:\n1 - Inserir um novo filme\n2 - Alterar os dados de um filme \n3 - Remover um filme \n4 - Imprimir a lista de filmes \n5 - Inserir sequencia de um filme \n6 - Imprimir sequencia de um filme \n7 - Remover sequencia de um filme \n8 - Imprimir filme que antecede um outro \n9 - Imprimir filme que sucede um outro \n10 - Sair\n");
  		scanf("%d", &opcao);
		printf("\n");

  		switch (opcao){
    		case 1:
    			filme = leFilme(idParametro, nomeParametro, anoParametro);
				insere(&l, filme);
    		break;

    		case 2:
				printf("Qual o ID unico do filme que deseja alterar? ");
    			scanf("%d", &idAux);

				if(verificaID(&l, idAux) == 1){
					alteraDados(&l, filme, idAux);
				}
				else{
					printf("\nDigite um ID unico valido!\n\n");
				}
			break;

			case 3:
				printf("Qual o ID unico do filme que deseja remover? ");
				scanf("%d", &idAux);

				removeFilme(&l, filme, idAux);
				printf("\nFilme removido com sucesso!\n\n");
			break;

			case 4:
				imprimeFilmes(&l);
			break;

    		case 5:
				printf("Qual o ID unico do filme que deseja inserir a sequencia? ");
				scanf("%d", &idAux);

				if(verificaID(&l, idAux) == 1){
					filme = leFilme(idParametro, nomeParametro, anoParametro);
					insereSequencia(filme, &l, idAux);
				}
				else{
					printf("\nDigite um ID unico valido!\n\n");
				}
    		break;

			case 6:
				printf("Qual o ID unico do filme que deseja imprimir a sequencia? ");
				scanf("%d", &idAux);

				if(verificaID(&l, idAux) == 1){
    				imprimeSequencia(&l, idAux);
    			} 
				else{
    				printf("\nDigite um ID unico valido!\n\n");
    			}
			break;

    		case 7:
    			printf("Qual o ID unico do filme que deseja remover a sequencia? ");
    			scanf("%d", &idAux);

    			removeSequencia(&l, idAux);
    		break;

			case 8:
    			printf("Qual o ID unico do filme que deseja saber o antecessor? ");
    			scanf("%d", &idAux);
    	
				if(verificaID(&l, idAux) == 1){
					antecede(&l, idAux);
				}
				else{
					printf("\nDigite um ID unico valido!\n\n");
				}
			break;

			case 9:
				printf("Qual o ID unico do filme que deseja saber o sucessor? ");
				scanf("%d", &idAux);

				if(verificaID(&l, idAux) == 1){
					sucede(&l, idAux);
				}
				else{
					printf("\nDigite um ID valido!\n\n");
				}
			break;

			case 10:
			  //Abre o arquivo para escrita e chama uma função que escreve os filmes no arquivo
  	                  arquivo = fopen("listadefilmes.txt", "w");
                	  imprimeNoArquivo(&l, arquivo); 
	                  fclose(arquivo);  
			break;

    		default:
    			printf("\nPor favor, digite uma opcao valida!\n");
		}
  	}while(opcao != 10); 
  	
  	
}
