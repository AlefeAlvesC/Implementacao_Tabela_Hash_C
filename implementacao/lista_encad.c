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
    if(!l) return 0;//Retorna 0, caso o ponteiro para lista seja invalido ou null

    No *novo =(No *) malloc(sizeof(No));//Cria um novo nó para a lista
    if(novo == NULL)//Verifica se a alocação foi bem suucedida
        return 0;

    //Inicializa os valores do novo nó e o insere na lista
    novo->info = valor;
    novo->prox = l->header;
    l->header = novo;
    l->tam++;
    return 1;//Retorna 1 para a inserção bem sucedida
}

int lista_remove(Lista *l, const char* chave){
    if(!l || l->tam == 0)//Verifica se o ponteiro para lista é valido ou se a lista não está vazia
        return 0;

    No *atual = l->header;
    No *ant = NULL;

    while(atual && strcmp(atual->info.chave, chave) != 0){//Percorre os ponteiros da lista enquanto não for null ou não encontrar o valor correspodente
        ant = atual;
        atual = atual->prox;
    }

    if(atual == NULL)//Se não encontrou retona 0
        return 0;

    if(ant == NULL){
        l->header = atual->prox;//Caso encontrou e é o primeiro elemento da lista
    }else{
        ant->prox = atual->prox;//Caso encontrou e é um elemento no meio da lista 
    }

    free(atual);//Libera o nó encontrada
    l->tam--;//Diminui tamanho da lista
    return 1;//Retorna 1 para remoção bem sucedida
}

int lista_remove_por_chave_valor(Lista* l, const char* chave, int codigo) {
    if (!l || l->tam == 0)
        return 0;

    No *atual = l->header;
    No *ant = NULL;

    //percorre a lista em busca de um nó com chave e código correspondentes
    while (atual) {
        if (strcmp(atual->info.chave, chave) == 0 && atual->info.codigo == codigo)
            break; // achou o nó
        ant = atual;
        atual = atual->prox;
    }

    if (!atual) // nao achou o no 
        return 0;

    //retira o no encontrado da lista
    if (!ant)
        l->header = atual->prox;
    else
        ant->prox = atual->prox;

    free(atual); //libera memória
    l->tam--;
    return 1; //sucesso
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
    if(!l)//Verifica se o ponteiro da lista é valido
        return;
    
    No* atual = l->header;
    while(atual != NULL){//Percorre a lista enquanto o nó não é null e os imprime
        printf("A chave %s tem o codigo %d\n", atual->info.chave, atual->info.codigo);
        atual = atual->prox;
    }

}

int lista_vazia(Lista *l){//Retorna 1 caso lista esteja vazia
    return l->tam == 0;
}

void no_libera(No* header){//Libera recursivamente cada nó da lista encadeada
    if(header){
        no_libera(header->prox);
        free(header);
    }
}

void lista_libera(Lista* l){
    if(l == NULL)//Verifica se o ponteiro para lista é valido
        return;

    no_libera(l->header);//Chama a função para liberar os nós
    free(l);//libera a estrutura lista
}