#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_encad.h"

Lista *lista_cria(){
    Lista *l = (Lista *) malloc(sizeof(Lista));
    l->header = NULL;
    l->tam = 0;
    return l;
}

int lista_insere(Lista *l, Viagem valor){
    if(!l) return 0;

    No *novo =(No *) malloc(sizeof(No));
    if(novo == NULL)
        return 0;

    novo->info = valor;
    novo->prox = l->header;
    l->header = novo;
    l->tam++;
    return 1;
}

int lista_remove(Lista *l, const char* chave){
    if(!l || l->tam == 0)
        return 0;

    No *atual = l->header;
    No *ant = NULL;

    while(atual && strcmp(atual->info.chave, chave) != 0){//Comparação entre strings corrigida
    //while(atual->info.chave != chave)
        ant = atual;
        atual = atual->prox;
    }

    if(atual == NULL)
        return 0;

    if(ant == NULL){
        l->header = atual->prox;
    }else{
        ant->prox = atual->prox;
    }

    free(atual);
    l->tam--;
    return 1;
}

//Função para busca recursiva somente com os nós
int *lista_busca_no(No* header, const char* chave){
    if(header){//Verifica se o nó não esta vazio
        if(strcmp(header->info.chave, chave) == 0){//Verifica se encontrou a chave correspondente
            return &header->info.codigo;//Retorna o ponteiro para o codigo dessa viagem
        }

        return lista_busca_no(header->prox, chave);//Se a chave não for a correspondente verifica o proximo nó
    }
    return NULL;//Retonar null caso o nó seja null, o que significa que não encontramos a chave na lista
}

int *lista_busca(Lista *l, const char* chave){
    if(l == NULL)//Verifica se a lista passada está vazia
        return NULL;

    return lista_busca_no(l->header, chave);//Chama busca recursiva
}

int lista_busca_todas(Lista* l, const char* chave) { 
    if (!l) return 0;

    No* atual = l->header;
    int encontrados = 0;

    while (atual) { //Percorre a lista encadeada buscando todas as ocorrencias de uma chave
        if (strcmp(atual->info.chave, chave) == 0) { // Para cada ocorrencia encontrada, é feito o print da chave e o codigo
            printf("Chave: %s | Código: %d\n", atual->info.chave, atual->info.codigo);
            encontrados++;
        }
        atual = atual->prox;
    }

    return encontrados; // Retorna quantos foram encontrados
}

void lista_imprime(Lista* l){
    if(!l)
        return;
    
    No* atual = l->header;
    while(atual != NULL){
        printf("A chave %s tem o codigo %d\n", atual->info.chave, atual->info.codigo);
        atual = atual->prox;
    }

}

int lista_vazia(Lista *l){
    return l->tam == 0;
}

void no_libera(No* header){
    if(header){
        no_libera(header->prox);
        free(header);
    }
}

void lista_libera(Lista* l){
    if(l == NULL)
        return;

    no_libera(l->header);
    free(l);
}