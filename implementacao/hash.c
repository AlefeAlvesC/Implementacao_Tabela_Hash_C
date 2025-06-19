#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//#include <stdbool.h>
#include "hash.h"
#define A  0.6180339887

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
    TabelaHash *hash = (TabelaHash*) malloc(sizeof(TabelaHash));
    return hash;
}

bool inserir(TabelaHash* tabela, const char* chave, int valor){
    Viagem *novo = (Viagem*) malloc(sizeof(Viagem));
    strcpy(novo->chave, chave);
    novo->codigo = valor;
    tabela->tabela_hash[hash(chave)] = *novo;
    
    free(novo);
}

int* buscar(TabelaHash* tabela, const char* chave){
    int *valor = &tabela->tabela_hash[hash(chave)].codigo;
    return valor;
}

bool remover(TabelaHash* tabela, const char* chave){

}

void imprimir_tabela(TabelaHash* tabela){

}

void liberar_tabela(TabelaHash* tabela){

}