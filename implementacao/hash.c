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
    
    for(int i = 0; i < TAMANHO_HASH; i++){//Inicializa cada ponteiro com NULL, para evitar acesso a lixo de memória 
        tabela->tabela_hash[i] = NULL;
    }
    
    return tabela;
}

//Lembrar de arrumar a função inserir para retornar FALSE caso ocorra err na inserção
bool inserir(TabelaHash* tabela, const char* chave, int valor){
    int index = hash(chave);//Salva o index da tabela em que o novo item será inserido
    Lista* l;
    
    if(tabela->tabela_hash[index] == NULL){//Verifica se é o primeiro item a ser inserido, se for cria uma lista
        l = lista_cria();
        tabela->tabela_hash[index] = l;
    }else{//Se não apenas reutiliza o lista já criada
        l = tabela->tabela_hash[index];
    }
    
    Viagem *novo = (Viagem*) malloc(sizeof(Viagem));//Cria um novo elemento viagem auxiliar que deve ser inserido na lista
    strcpy(novo->chave, chave);
    novo->codigo = valor;
    
    lista_insere(l, *novo);//Insere na lista uma cópia do que o ponteiro novo aponta, não o ponteiro em si
    
    free(novo);//Damos free no ponteiro auxiliar de viagem
}

int* buscar(TabelaHash* tabela, const char* chave){
    int index = hash(chave);//Salvamos o index da posição da hash que buscuremos o informação
    int *valor = lista_busca(tabela->tabela_hash[index], chave);//Realizamos a busca na lista 

    //Verificamos se o valor retornado da busca é valido
    if(valor == NULL)
        return NULL;
    else
        return valor;
}

//Assim como a função inserir, depois devemos ajeitar esta para retornar TRUE OU FALSE
bool remover(TabelaHash* tabela, const char* chave){
    if(!tabela)
        return false;

    int index = hash(chave);
    lista_remove(tabela->tabela_hash[index], chave);
}

void imprimir_tabela(TabelaHash* tabela){
    if(!tabela)
        return;
    printf("--- Imprimindo TABELA HASH ---\n");
    for(int i = 0; i < TAMANHO_HASH; i++){
        if(tabela->tabela_hash[i] != NULL){
            printf("\nImprimindo itens na posicao %d da tabela:\n", i);
            lista_imprime(tabela->tabela_hash[i]);
        }
        
    }
}

void liberar_tabela(TabelaHash* tabela){
    if(tabela == NULL)
        return;

    for(int i = 0; i < TAMANHO_HASH; i++){
        lista_libera(tabela->tabela_hash[i]);
    }

    free(tabela);
}