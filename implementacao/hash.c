#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hash.h"
#include "lista_encad.h"
#define A 0.6180339887

int hash(const char chave[]){
    //Primeiro transforma a chave em número
    int k = 0; 
    for(int i = 0; chave[i] != '\0'; i++){
        //Levando em conta que a chave só contem letras maiusculas, diminui menos 65, pois é a posição de A na tabela ASCII e 26 elevado 5 menos i para a posição da letra na chave
        k += (chave[i]-65) * pow(26, 5 - i);
    }
    
    //Pegando o mod de 1 de k*A. Como % não funciona direito com tipos double, fiz dessa forma para pegar o modulo
    double fracao = (k * A) - (int)(k * A);
    
    int index = (int)(TAMANHO_HASH * fracao);
    return index;
}

TabelaHash* criar_tabela_hash(){
    TabelaHash *tabela = (TabelaHash*) malloc(sizeof(TabelaHash));
    return tabela;
    //Lembrar de implementar uma inicialização da tabela, fazendo com que cada posição seja NULL
}

bool inserir(TabelaHash* tabela, const char* chave, int valor){
    int index = hash(chave);//Salva o index da tabela em que o novo item será inserido
    Lista* l;
    
    if(tabela->tabela_hash[index] == NULL){//Verifica se é o primeiro item a ser inserido, se for cria uma lista
        l = lista_cria();
        tabela->tabela_hash[index] = l;
    }else{//Se não apenas reutiliza o lista já criada
        l = tabela->tabela_hash[index];
    }
    
    
    Viagem *novo = (Viagem*) malloc(sizeof(Viagem));//Cria um novo elemento viagem que deve ser inserido na lista
    strcpy(novo->chave, chave);
    novo->codigo = valor;
    
    lista_insere(l, *novo);
    
    free(novo);
}

int* buscar(TabelaHash* tabela, const char* chave){
    int *valor = lista_busca(tabela->tabela_hash[hash(chave)], chave);

    if(valor == NULL)
        return NULL;
    else
        return valor;
}

bool remover(TabelaHash* tabela, const char* chave){

}

void imprimir_tabela(TabelaHash* tabela){

}

void liberar_tabela(TabelaHash* tabela){

}