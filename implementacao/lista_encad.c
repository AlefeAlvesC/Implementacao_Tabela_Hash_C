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

void lista_insere(Lista *l, Viagem valor){
    No *novo =(No *) malloc(sizeof(No));
    novo->info = valor;
    novo->prox = l->header;
    l->header = novo;
    l->tam++;
}

void lista_remove(Lista *l, const char* chave){
    if(l->tam == 0)
        return;

    No *atual = l->header;
    No *ant = NULL;

    //while(strcmp(atual->info.chave, chave))
    while(atual->info.chave != chave){//Depois verificar se essa comparação está correta, acho que o ideal seria usar strcmp mesmo, mas depois vejo
        ant = atual;
        atual = atual->prox;
    }

    if(atual == NULL)
        return;

    if(ant == NULL){
        l->header = atual->prox;
    }else{
        ant->prox = atual->prox;
    }

    free(atual);
    l->tam--;
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

int lista_vazia(Lista *l){
    return l->tam == 0;
}

void no_libera(No* header){
    if(header->prox){
        no_libera(header->prox);
        free(header);
    }
}

void lista_libera(Lista* l){
    no_libera(l->header);
    free(l);
}
